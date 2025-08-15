using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Xml;

namespace DataSourceTestAvalonia
{
    /// <summary>
    /// Handles reading and parsing XML interface definition files
    /// </summary>
    public class ReadXML
    {
        #region Fields
        private List<string>? warningList;

        public List<string> ModuleList = new List<string>();
        public DataTable mDataTable = new DataTable();
        #endregion

        #region Constructor
        public ReadXML()
        {
            InitializeDataTable();
        }

        private void InitializeDataTable()
        {
            mDataTable.Columns.Add("fileName", typeof(string));
            mDataTable.Columns.Add("name", typeof(string));
            mDataTable.Columns.Add("type", typeof(string));
            mDataTable.Columns.Add("value", typeof(string));
        }
        #endregion

        #region Public Methods
        /// <summary>
        /// Sets the warning list for collecting parsing warnings
        /// </summary>
        public void SetWarningList(List<string> warnings)
        {
            warningList = warnings;
        }

        /// <summary>
        /// Reads all XML files from the specified directory
        /// </summary>
        public void XmlDocumentRead(string directoryPath, List<string> warnings)
        {
            SetWarningList(warnings);

            try
            {
                if (!Directory.Exists(directoryPath))
                {
                    warningList?.Add($"Directory not found: {directoryPath}");
                    return;
                }

                var xmlFiles = Directory.GetFiles(directoryPath, "*.xml");

                // Clear existing data
                mDataTable.Rows.Clear();
                ModuleList.Clear();

                // Process each XML file
                foreach (var file in xmlFiles)
                {
                    ReadSingleXmlFile(file);
                }
            }
            catch (Exception ex)
            {
                warningList?.Add($"Error reading XML files: {ex.Message}");
            }
        }
        #endregion

        #region Private Methods
        /// <summary>
        /// Reads a single XML file and extracts interface data
        /// </summary>
        private void ReadSingleXmlFile(string filePath)
        {
            try
            {
                var doc = new XmlDocument();
                var settings = new XmlReaderSettings { IgnoreComments = true };

                using (var reader = XmlReader.Create(filePath, settings))
                {
                    doc.Load(reader);
                    var rootNodes = doc.SelectNodes("*");
                    ProcessXmlNodes(rootNodes);
                }
            }
            catch (XmlException ex)
            {
                warningList?.Add($"XML parsing error in {filePath}: {ex.Message}");
            }
            catch (Exception ex)
            {
                warningList?.Add($"Error reading {filePath}: {ex.Message}");
            }
        }

        /// <summary>
        /// Processes XML nodes and extracts interface definitions
        /// </summary>
        private void ProcessXmlNodes(XmlNodeList? nodeList)
        {
            if (nodeList == null) return;

            try
            {
                foreach (XmlNode node in nodeList)
                {
                    // Handle warning items
                    if (node.Name == "wtitem")
                    {
                        ProcessWarningItem(node);
                        continue;
                    }

                    // Handle interface elements with type attribute
                    if (node.Attributes?["type"] != null)
                    {
                        ProcessInterfaceElement(node);
                    }
                    else if (node.HasChildNodes)
                    {
                        // Recursively process child nodes
                        ProcessXmlNodes(node.ChildNodes);
                    }
                }
            }
            catch (Exception ex)
            {
                warningList?.Add($"Error processing XML nodes: {ex.Message}");
            }
        }

        /// <summary>
        /// Processes warning items from XML
        /// </summary>
        private void ProcessWarningItem(XmlNode warningNode)
        {
            try
            {
                foreach (XmlNode childNode in warningNode.ChildNodes)
                {
                    if (childNode.Name == "id" && childNode.FirstChild?.NodeType == XmlNodeType.Text)
                    {
                        warningList?.Add(childNode.FirstChild.Value ?? "");
                    }
                }
            }
            catch (Exception ex)
            {
                warningList?.Add($"Error processing warning item: {ex.Message}");
            }
        }

        /// <summary>
        /// Processes interface elements and adds them to the data table
        /// </summary>
        private void ProcessInterfaceElement(XmlNode node)
        {
            try
            {
                // Build the full path name by traversing up the XML tree
                string name = BuildElementPath(node);
                string type = node.Attributes?["type"]?.Value ?? "";
                string value = GetElementValue(node, type);
                string fileName = GetFileName(node);

                // Add to module list if not already present
                if (!string.IsNullOrEmpty(fileName) && !ModuleList.Contains(fileName))
                {
                    ModuleList.Add(fileName);
                }

                // Create data array and add to DataTable
                mDataTable.Rows.Add(fileName, name, type, value);
            }
            catch (Exception ex)
            {
                warningList?.Add($"Error processing interface element {node.Name}: {ex.Message}");
            }
        }

        /// <summary>
        /// Builds the full element path by traversing up the XML hierarchy
        /// </summary>
        private string BuildElementPath(XmlNode node)
        {
            string name = "";
            XmlNode? currentNode = node;

            while (currentNode != null && currentNode.Name != "#document")
            {
                if (currentNode.Name != "#text")
                {
                    name = string.IsNullOrEmpty(name) ? currentNode.Name : $"{currentNode.Name}.{name}";
                }

                if (currentNode.ParentNode?.Name == "#document")
                    break;

                currentNode = currentNode.ParentNode;
            }

            return name;
        }

        /// <summary>
        /// Gets the element value, handling type-specific conversions
        /// </summary>
        private string GetElementValue(XmlNode node, string type)
        {
            string value = node.FirstChild?.Value ?? "";

            // Handle boolean conversions
            if (type == "bool" || type == "boolean")
            {
                return value.ToLower() == "true" ? "1" : "0";
            }

            // Handle empty string types
            if (type == "string" && string.IsNullOrEmpty(value))
            {
                return "";
            }

            return value;
        }

        /// <summary>
        /// Gets the filename from the root element's name attribute
        /// </summary>
        private string GetFileName(XmlNode node)
        {
            XmlNode? currentNode = node;

            while (currentNode?.ParentNode != null && currentNode.ParentNode.Name != "#document")
            {
                currentNode = currentNode.ParentNode;
            }

            return currentNode?.Attributes?["name"]?.Value ?? "";
        }
        #endregion
    }
}
