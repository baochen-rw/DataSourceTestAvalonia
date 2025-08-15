using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Threading;
using System.Collections.ObjectModel;
using System.Data;
using System;
using System.IO;
using System.Xml;
using System.Linq;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading.Tasks;

namespace DataSourceTestAvalonia;

// Simple data model for the grid
public class XmlDataItem
{
    public string FileName { get; set; } = "";
    public string Name { get; set; } = "";
    public string Type { get; set; } = "";
    public string Value { get; set; } = "";
}

internal partial class MainWindow : Window
{
    private readonly TestToolServer _server = new();
    private readonly ReadXML _xmlReader = new();
    private readonly ObservableCollection<string> _warnings = new();

    // Session-based data storage - keeps current values without modifying XML files
    private ObservableCollection<XmlDataItem> _sessionData = new();
    private readonly Dictionary<string, string> _sessionValues = new(); // Key: "fileName|name", Value: current value

    // Client process management
    private Process? _clientProcess;
    private string _clientDirectory = "";

    /// <summary>
    /// Gets the client executable path by combining the client directory with the exe filename
    /// </summary>
    private string GetClientExePath()
    {
        if (string.IsNullOrEmpty(_clientDirectory))
            return "";

        return Path.Combine(_clientDirectory, "DataSourceTestToolClient.exe");
    }

    private string _outputPath = "";
    private XmlDocument _recordXml = new XmlDocument();
    private XmlElement? _scriptRoot;
    private int _screenshotIndex = 0;
    private string _baseDir = AppDomain.CurrentDomain.BaseDirectory;
    private AppState _currentState = AppState.Initializing;

    // Debug property for easier watch expressions
    public string DebugState => $"State: {_currentState} | Server: {(_server != null ? "Ready" : "Not Ready")}";

    /// <summary>
    /// Adds a warning message and automatically scrolls to the bottom of the warnings list
    /// </summary>
    private void AddWarning(string message)
    {
        _warnings.Add(message);

        // Auto-scroll to bottom on UI thread
        Dispatcher.UIThread.Post(() =>
        {
            try
            {
                if (WarningsScrollViewer != null)
                {
                    WarningsScrollViewer.ScrollToEnd();
                }
            }
            catch { /* Ignore scroll errors */ }
        });
    }

    public AppState CurrentState
    {
        get => _currentState;
        set
        {
            if (_currentState != value)
            /// <summary>
            /// Main application window. Handles UI logic, server communication, and XML data management.
            /// </summary>
            {
                _currentState = value;
                HandleStateChange(value);
            }
        }
    }

    public MainWindow()
    {
        try
        {
            InitializeComponent();
            InitializeApplication();
        }
        catch (Exception ex)
        {
            // If we can't show UI, at least try to write to console
            Console.WriteLine($"Error during MainWindow initialization: {ex.Message}");
            Console.WriteLine($"Stack trace: {ex.StackTrace}");
            throw; // Re-throw so the application fails clearly
        }
    }

    private void InitializeApplication()
    {
        try
        {
            // Setup UI bindings
            WarningListBox.ItemsSource = _warnings;

            // Setup event handlers
            // Removed LoadXmlButton
            BrowseClientButton.Click += BrowseClientButton_Click;
            ClientButton.Click += ClientButton_Click;
            ResendMessageButton.Click += ResendMessageButton_Click;
            ClearSessionButton.Click += ClearSessionButton_Click;
            NewKzbButton.Click += NewKzbButton_Click;
            ScreenshotButton.Click += ScreenshotButton_Click;
            PreconditionComboBox.SelectionChanged += PreconditionComboBox_SelectionChanged;
            CopyDllButton.Click += CopyDllButton_Click;
            CopyClientButton.Click += CopyClientButton_Click;

            InterfaceNameTextBox.TextChanged += InterfaceNameTextBox_TextChanged;
            ModuleComboBox.SelectionChanged += ModuleComboBox_SelectionChanged;

            // Setup DataGrid event handlers
            XmlDataGrid.CellEditEnding += XmlDataGrid_CellEditEnding;

            // Setup server event handlers
            _server.StatusChanged += (msg) =>
            {
                Dispatcher.UIThread.Post(() => UpdateServerStatus(msg));
            };

            // Initialize application
            CurrentState = AppState.Initializing;
            SetupPaths();
            SetupXmlRecording();
            LoadSavedClientPath();
            // Don't automatically copy files - user will trigger with buttons
            // CopyDatasourceToolsDll();
            // CopyKanziClientSaveFiles();
            // Don't load interfaces at startup - wait for client connection
            //LoadInterfacesFromClientFolder();
            LoadPreconditions();
            StartServer();
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error during application initialization: {ex.Message}");
            Console.WriteLine($"Stack trace: {ex.StackTrace}");

            // Try to show error in warnings if possible
            try
            {
                _warnings?.Add($"Initialization Error: {ex.Message}");
            }
            catch { }

            throw;
        }
    }

    /// <summary>
    /// Test method to verify DataGrid functionality with hardcoded data
    /// </summary>
    private void HandleStateChange(AppState newState)
    {
        try
        {
            Dispatcher.UIThread.Post(() =>
            {
                switch (newState)
                {
                    case AppState.Initializing:
                        StatusText.Text = "Server: Initializing...";
                        ClientStatusText.Text = "Client: Not Connected";
                        EnableControls(false);
                        break;

                    case AppState.ServerStarted:
                        StatusText.Text = "Server: Ready";
                        ClientStatusText.Text = "Client: Waiting for connection";
                        EnableControls(false);
                        break;

                    case AppState.ClientConnected:
                        StatusText.Text = "Server: Running";
                        ClientStatusText.Text = "Client: Connected";
                        EnableControls(true);
                        _screenshotIndex = 0;
                        // Load interfaces when client connects and DataGrid is enabled
                        LoadInterfacesFromClientFolder();
                        break;

                    case AppState.ClientDisconnected:
                        StatusText.Text = "Server: Ready";
                        ClientStatusText.Text = "Client: Disconnected";
                        EnableControls(false);
                        break;

                    case AppState.Error:
                        StatusText.Text = "Server: Error";
                        ClientStatusText.Text = "Client: Error";
                        EnableControls(false);
                        break;
                }
            });
        }
        catch { }
        void EnableControls(bool enabled)
        {
            InterfaceNameTextBox.IsEnabled = enabled;
            // DataGrid enabled state follows the general control state
            XmlDataGrid.IsEnabled = enabled;
            ScreenshotButton.IsEnabled = enabled;
            ModuleComboBox.IsEnabled = enabled;
            PreconditionComboBox.IsEnabled = enabled;
            // BrowseClientButton is always enabled
            // ClientButton and RefreshClientButton enabled based on whether we have a valid exe path (independent of connection status)
            UpdateClientButtonState();
            // Removed LoadPreconditionButton
        }
    }

    private void UpdateClientButtonState()
    {
        string clientExePath = GetClientExePath();
        bool hasValidClient = !string.IsNullOrEmpty(clientExePath) && File.Exists(clientExePath);
        // Keep ClientButton always enabled - it will handle missing exe internally
        ClientButton.IsEnabled = true;
        // RefreshClientButton (now "Resend Messages") only enabled when client is connected
        ResendMessageButton.IsEnabled = (CurrentState == AppState.ClientConnected);
        NewKzbButton.IsEnabled = hasValidClient;
    }

    void UpdateServerStatus(string message)
    {
        if (message.Contains("started") || message.Contains("waiting"))
            CurrentState = AppState.ServerStarted;
        else if (message.Contains("connected") && !message.Contains("disconnected"))
            CurrentState = AppState.ClientConnected;
        else if (message.Contains("disconnected") || message.Contains("failed"))
            CurrentState = AppState.ClientDisconnected;
        else if (message.Contains("error") || message.Contains("failed"))
            CurrentState = AppState.Error;
    }

    private void SetupPaths()
    {
        _outputPath = Path.Combine(_baseDir, "out", DateTime.Now.ToString("yyyy_MM_dd_hh-mm-ss"));
        Directory.CreateDirectory(_outputPath);
        AddWarning($"Created output directory: {_outputPath}");
    }

    private void CopyKanziClientSaveFiles()
    {
        try
        {
            string sourceFolder = Path.Combine(_baseDir, "KanziClientSave");

            // Use selected client directory if available, otherwise use default KanziClient folder
            string destinationFolder;
            if (!string.IsNullOrEmpty(_clientDirectory))
            {
                destinationFolder = _clientDirectory;
            }
            else
            {
                destinationFolder = Path.Combine(_baseDir, "KanziClient");
            }

            if (!Directory.Exists(sourceFolder))
            {
                _warnings.Add($"KanziClientSave folder not found: {sourceFolder}. Skipping file copy.");
                return;
            }

            // Create destination folder if it doesn't exist
            if (!Directory.Exists(destinationFolder))
            {
                Directory.CreateDirectory(destinationFolder);
                _warnings.Add($"Created destination folder: {destinationFolder}");
            }

            // Copy all files from source to destination
            string[] files = Directory.GetFiles(sourceFolder, "*", SearchOption.AllDirectories);
            int copiedCount = 0;

            foreach (string sourceFile in files)
            {
                // Get relative path to maintain folder structure
                string relativePath = Path.GetRelativePath(sourceFolder, sourceFile);
                string destinationFile = Path.Combine(destinationFolder, relativePath);

                // Create subdirectories if needed
                string? destinationDir = Path.GetDirectoryName(destinationFile);
                if (!string.IsNullOrEmpty(destinationDir) && !Directory.Exists(destinationDir))
                {
                    Directory.CreateDirectory(destinationDir);
                }

                // Copy file with overwrite
                File.Copy(sourceFile, destinationFile, true);
                copiedCount++;
            }

            _warnings.Add($"Copied {copiedCount} files from KanziClientSave to {destinationFolder}");
        }


        catch (Exception ex)
        {
            _warnings.Add($"Error copying KanziClientSave files: {ex.Message}");
        }
    }

    private void CopyDatasourceToolsDll()
    {
        try
        {
            // Use selected client directory if available, otherwise use default KanziClient folder
            string targetClientFolder;
            if (!string.IsNullOrEmpty(_clientDirectory))
            {
                targetClientFolder = _clientDirectory;
            }
            else
            {
                targetClientFolder = Path.Combine(_baseDir, "KanziClient");
            }

            string datasourceToolsFolder = Path.Combine(targetClientFolder, "DatasourceToolsDll");

            if (!Directory.Exists(datasourceToolsFolder))
            {
                _warnings.Add($"DatasourceToolsDll folder not found: {datasourceToolsFolder}. Skipping DLL content copy.");
                return;
            }

            // Copy all files from DatasourceToolsDll folder to the target client folder
            string[] files = Directory.GetFiles(datasourceToolsFolder, "*", SearchOption.AllDirectories);
            int copiedCount = 0;

            foreach (string sourceFile in files)
            {
                // Get relative path to maintain folder structure
                string relativePath = Path.GetRelativePath(datasourceToolsFolder, sourceFile);
                string destinationFile = Path.Combine(targetClientFolder, relativePath);

                // Create subdirectories if needed
                string? destinationDir = Path.GetDirectoryName(destinationFile);
                if (!string.IsNullOrEmpty(destinationDir) && !Directory.Exists(destinationDir))
                {
                    Directory.CreateDirectory(destinationDir);
                }

                // Copy file with overwrite
                File.Copy(sourceFile, destinationFile, true);
                copiedCount++;
            }

            _warnings.Add($"Copied {copiedCount} files from DatasourceToolsDll to {targetClientFolder}");
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error copying DatasourceToolsDll files: {ex.Message}");
        }
    }

    private void SetupXmlRecording()
    {
        _scriptRoot = _recordXml.CreateElement("script");
        _recordXml.AppendChild(_scriptRoot);
    }

    private void LoadInterfacesFromClientFolder()
    {
        string interfacePath;
        if (!string.IsNullOrEmpty(_clientDirectory))
        {
            interfacePath = Path.Combine(_clientDirectory, "Interface");
        }
        else
        {
            interfacePath = Path.Combine(_baseDir, "KanziClient/Interface");
        }

        if (!Directory.Exists(interfacePath))
        {
            _warnings.Add($"Interface folder not found: {interfacePath}. It will be created automatically.");
            Directory.CreateDirectory(interfacePath);
        }

        XmlDirectoryLabel.Text = _clientDirectory;
        LoadXmlFromDirectory(interfacePath);
    }

    private void LoadXmlFromDirectory(string directoryPath)
    {
        _warnings.Clear();
        var warnList = new List<string>();
        _xmlReader.XmlDocumentRead(directoryPath, warnList);

        foreach (var w in warnList)
            _warnings.Add(w);

        // Add debug info
        _warnings.Add($"Loaded {_xmlReader.mDataTable.Rows.Count} rows from XML files");
        _warnings.Add($"Found {_xmlReader.ModuleList.Count} modules");

        // Load module names
        ModuleComboBox.Items.Clear();
        ModuleComboBox.Items.Add("ALL");
        foreach (string module in _xmlReader.ModuleList)
            ModuleComboBox.Items.Add(module);

        if (ModuleComboBox.Items.Count > 0)
            ModuleComboBox.SelectedIndex = 0;

        UpdateDataGrid();
    }

    private void LoadPreconditions()
    {
        string preconditionPath = Path.Combine(_baseDir, "PreCondition");
        if (!Directory.Exists(preconditionPath))
        {
            _warnings.Add($"PreCondition folder not found: {preconditionPath}. It will be created automatically.");
            Directory.CreateDirectory(preconditionPath);
        }

        if (Directory.Exists(preconditionPath))
        {
            string[] files = Directory.GetFiles(preconditionPath, "*.xml");
            PreconditionComboBox.Items.Clear();
            foreach (string file in files)
                PreconditionComboBox.Items.Add(Path.GetFileName(file));
        }
    }

    private void StartServer()
    {
        _server.Start();
        CurrentState = AppState.ServerStarted;
    }

    private void UpdateDataGrid(string module = "", string filter = "")
    {
        string moduleFilter = (module == "ALL" || string.IsNullOrEmpty(module)) ? "" : module;

        var filteredRows = _xmlReader.mDataTable.AsEnumerable()
            .Where(row =>
                row["fileName"].ToString()?.Contains(moduleFilter, StringComparison.OrdinalIgnoreCase) == true &&
                row["name"].ToString()?.Contains(filter, StringComparison.OrdinalIgnoreCase) == true);

        _warnings.Add($"Filtering: module='{moduleFilter}', filter='{filter}', found {filteredRows.Count()} rows");

        // Convert DataTable rows to objects, applying session values if they exist
        var itemsList = filteredRows.Select(row =>
        {
            string fileName = row["fileName"].ToString() ?? "";
            string name = row["name"].ToString() ?? "";
            string originalValue = row["value"].ToString() ?? "";

            // Check if we have a session value override
            string sessionKey = $"{fileName}|{name}";
            string currentValue = _sessionValues.ContainsKey(sessionKey) ? _sessionValues[sessionKey] : originalValue;

            return new XmlDataItem
            {
                FileName = fileName,
                Name = name,
                Type = row["type"].ToString() ?? "",
                Value = currentValue
            };
        }).ToList();

        // Update the session data collection
        _sessionData.Clear();
        foreach (var item in itemsList)
        {
            _sessionData.Add(item);
        }

        // Bind to the session data (which supports property change notifications)
        XmlDataGrid.ItemsSource = _sessionData;

        _warnings.Add($"Set DataGrid ItemsSource to {itemsList.Count} items (with session overrides)");
    }

    private void SendToClient(string fileName, string name, string type, string value)
    {
        if (name == "screenshot") return;

        // Store the value in session data (don't modify the original DataTable)
        string sessionKey = $"{fileName}|{name}";
        _sessionValues[sessionKey] = value;

        // Convert bool values for client communication
        string sendValue = value;
        if (type == "bool")
            sendValue = (value == "0" || value.ToLower() == "false") ? "false" : "true";

        _server.SendSyncCommand(fileName, type, name, sendValue);
    }

    private void RecordAction(string fileName, string type, string name, string value)
    {
        if (_scriptRoot == null) return;

        XmlElement element = _recordXml.CreateElement(name);
        element.SetAttribute("filename", fileName);
        element.SetAttribute("type", type);
        element.SetAttribute("value", value == "True" || value == "true" ? "1" :
                                     value == "False" || value == "false" ? "0" : value);
        _scriptRoot.AppendChild(element);
        _recordXml.Save(Path.Combine(_outputPath, "Unit_Test_Record.xml"));
    }



    private async void LoadPreconditionFile(string filePath)
    {
        try
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(filePath);

            if (doc.DocumentElement != null)
            {
                var commands = doc.DocumentElement.ChildNodes.OfType<XmlElement>().ToList();
                _warnings.Add($"Loading {commands.Count} precondition commands with 200ms delays...");

                foreach (XmlElement item in commands)
                {
                    string fileName = item.GetAttribute("filename");
                    string name = item.Name;
                    string type = item.GetAttribute("type");
                    string value = item.GetAttribute("value");
                    SendToClient(fileName, name, type, value);

                    // Add 200ms delay between commands
                    await Task.Delay(500);
                }

                _warnings.Add("Finished loading precondition commands.");
            }
            // Removed LoadPreconditionButton.Content update
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error loading precondition file: {ex.Message}");
        }
    }

    #region Event Handlers

    /// <summary>
    /// Handles DataGrid cell edit completion to save changes in session data (not XML files)
    /// </summary>
    private void XmlDataGrid_CellEditEnding(object? sender, DataGridCellEditEndingEventArgs e)
    {
        try
        {
            // Get the edited item
            if (e.Row.DataContext is XmlDataItem editedItem)
            {
                // Get the new value from the editing element
                string newValue = "";
                if (e.EditingElement is TextBox textBox)
                {
                    newValue = textBox.Text ?? "";
                }

                // Determine which column was edited
                string columnName = e.Column.Header?.ToString() ?? "";

                _warnings.Add($"Cell edit: Item '{editedItem.Name}', Column '{columnName}', New Value '{newValue}'");

                // Only process Value column edits (other columns should be read-only)
                if (columnName == "Value")
                {
                    // Store the change in session data (not in XML files)
                    string sessionKey = $"{editedItem.FileName}|{editedItem.Name}";
                    _sessionValues[sessionKey] = newValue;

                    // Update the current item's value
                    editedItem.Value = newValue;

                    // Send the change to the client
                    SendToClient(editedItem.FileName, editedItem.Name, editedItem.Type, newValue);

                    // Record the action for test playback
                    RecordAction(editedItem.FileName, editedItem.Type, editedItem.Name, newValue);

                    _warnings.Add($"Session Update: {editedItem.Name} = {newValue} (sent to client, not saved to XML)");
                }
            }
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error saving cell edit: {ex.Message}");
        }
    }

    private void LoadXmlButton_Click(object? sender, RoutedEventArgs e)
    {
        var dir = XmlDirectoryLabel.Text ?? string.Empty;
        if (!string.IsNullOrEmpty(dir) && dir != "No directory selected")
        {
            LoadXmlFromDirectory(dir);
        }
        else
        {
            _warnings.Add("Please select a directory first using the Browse button.");
        }
    }

    private async void BrowseDirectoryButton_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            var topLevel = TopLevel.GetTopLevel(this);
            if (topLevel != null)
            {
                var folders = await topLevel.StorageProvider.OpenFolderPickerAsync(new Avalonia.Platform.Storage.FolderPickerOpenOptions
                {
                    Title = "Select XML Interface Directory",
                    AllowMultiple = false
                });

                if (folders.Count > 0)
                {
                    string selectedPath = folders[0].Path.LocalPath;
                    XmlDirectoryLabel.Text = selectedPath;
                    _warnings.Add($"Selected directory: {selectedPath}");
                    // Automatically load XML from the selected directory
                    LoadXmlFromDirectory(selectedPath);
                }

            }
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error selecting directory: {ex.Message}");
        }
    }

    private void InterfaceNameTextBox_TextChanged(object? sender, TextChangedEventArgs e)
    {
        var module = ModuleComboBox.SelectedItem?.ToString() ?? "";
        var filter = InterfaceNameTextBox.Text ?? "";
        UpdateDataGrid(module, filter);
    }

    private void ModuleComboBox_SelectionChanged(object? sender, SelectionChangedEventArgs e)
    {
        var module = ModuleComboBox.SelectedItem?.ToString() ?? "";
        var filter = InterfaceNameTextBox.Text ?? "";
        UpdateDataGrid(module, filter);
    }

    private void ScreenshotButton_Click(object? sender, RoutedEventArgs e)
    {
        string screenshotPath = Path.Combine(_outputPath, $"{_screenshotIndex}.png");
        _warnings.Add($"Taking screenshot: {screenshotPath}");
        _server.SendScreenshotCommand(screenshotPath);
        _screenshotIndex++;
    }

    private void CopyDllButton_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            AddWarning("Manual DLL copy triggered...");
            CopyDatasourceToolsDll();
            AddWarning("DLL copy completed.");
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error during manual DLL copy: {ex.Message}");
        }
    }

    private void CopyClientButton_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            AddWarning("Manual client files copy triggered...");
            CopyKanziClientSaveFiles();
            AddWarning("Client files copy completed.");
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error during manual client files copy: {ex.Message}");
        }
    }

    private void ClearSessionButton_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            int sessionCount = _sessionValues.Count;

            // Clear the session values dictionary
            _sessionValues.Clear();

            // Refresh the DataGrid to show original values (without session overrides)
            var module = ModuleComboBox.SelectedItem?.ToString() ?? "";
            var filter = InterfaceNameTextBox.Text ?? "";
            UpdateDataGrid(module, filter);

            AddWarning($"🗑️ Session history cleared! Removed {sessionCount} session values.");
            AddWarning("💡 DataGrid now shows original XML values. 'Resend Messages' will send nothing until new changes are made.");
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error clearing session: {ex.Message}");
        }
    }

    private void ClientButton_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            string clientExePath = GetClientExePath();
            if (string.IsNullOrEmpty(clientExePath) || !File.Exists(clientExePath))
            {
                AddWarning("❌ No client executable found! Please browse for the client first, or click 'Client.exe' button to copy client files.");
                AddWarning("💡 Tip: Use the green 'Client.exe' button to copy client files to the selected directory.");
                return;
            }

            // Close existing client if running
            if (_clientProcess != null && !_clientProcess.HasExited)
            {
                _clientProcess.Kill();
                _clientProcess.WaitForExit(3000);
            }

            // Start new client process
            _clientProcess = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = clientExePath,
                    WorkingDirectory = _clientDirectory,
                    UseShellExecute = true
                }
            };

            // Set up process exit monitoring
            _clientProcess.EnableRaisingEvents = true;
            _clientProcess.Exited += ClientProcess_Exited;

            _clientProcess.Start();
            AddWarning($"Started client: {clientExePath}");
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error starting client: {ex.Message}");
        }
    }

    private void ClientProcess_Exited(object? sender, EventArgs e)
    {
        try
        {
            Dispatcher.UIThread.Post(() =>
            {
                _warnings.Add("Client process has exited");

                // Update UI state if client disconnected
                if (CurrentState == AppState.ClientConnected)
                {
                    CurrentState = AppState.ClientDisconnected;
                }
            });
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error handling client process exit: {ex.Message}");
        }
    }

    private async void ResendMessageButton_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            // Check if client is connected
            if (CurrentState != AppState.ClientConnected)
            {
                AddWarning("❌ Client not connected! Please start the client first.");
                return;
            }

            AddWarning("🔄 Resending session messages to client...");
            await ResendSessionValues();
            AddWarning("✅ Session messages resent successfully.");
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error resending messages: {ex.Message}");
        }
    }

    /// <summary>
    /// Resends all current session values to the client
    /// </summary>
    private async Task ResendSessionValues()
    {
        try
        {
            if (_sessionValues.Count > 0)
            {
                _warnings.Add($"Resending {_sessionValues.Count} session values to client with 200ms delays...");

                foreach (var kvp in _sessionValues)
                {
                    // Parse the session key: "fileName|name"
                    string[] parts = kvp.Key.Split('|');
                    if (parts.Length == 2)
                    {
                        string fileName = parts[0];
                        string name = parts[1];
                        string value = kvp.Value;

                        // Find the type from the current session data
                        var item = _sessionData.FirstOrDefault(x => x.FileName == fileName && x.Name == name);
                        if (item != null)
                        {
                            SendToClient(fileName, name, item.Type, value);

                            // Add 200ms delay between commands
                            await Task.Delay(200);
                        }
                    }
                }

                _warnings.Add("Finished resending session values");
            }
            else
            {
                _warnings.Add("No session values to resend");
            }
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error resending session values: {ex.Message}");
        }
    }

    private async void NewKzbButton_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            string clientExePath = GetClientExePath();
            if (string.IsNullOrEmpty(clientExePath) || !File.Exists(clientExePath))
            {
                _warnings.Add("No client executable found. Please browse for the client first.");
                return;
            }

            // Get TopLevel for file dialog
            var topLevel = TopLevel.GetTopLevel(this);
            if (topLevel == null)
            {
                _warnings.Add("Error: Cannot access file dialog.");
                return;
            }

            // Open file picker to select KZB file
            var options = new Avalonia.Platform.Storage.FilePickerOpenOptions
            {
                Title = "Select KZB File",
                AllowMultiple = false,
                FileTypeFilter = new[] {
                    new Avalonia.Platform.Storage.FilePickerFileType("KZB Files") { Patterns = new[] { "*.kzb" } },
                    new Avalonia.Platform.Storage.FilePickerFileType("All Files") { Patterns = new[] { "*.*" } }
                }
            };
            // Close existing client if running
            if (_clientProcess != null && !_clientProcess.HasExited)
            {
                _clientProcess.Kill();
                _clientProcess.WaitForExit(3000);
                _warnings.Add("Closed existing client for KZB update");
            }

            // Set starting directory to client directory if available
            if (!string.IsNullOrEmpty(_clientDirectory) && Directory.Exists(_clientDirectory))
            {
                options.SuggestedStartLocation = await topLevel.StorageProvider.TryGetFolderFromPathAsync(new Uri(_clientDirectory));
            }

            var result = await topLevel.StorageProvider.OpenFilePickerAsync(options);
            if (result.Count > 0)
            {
                string selectedKzbFile = result[0].Path.LocalPath;
                string kzbFileName = Path.GetFileName(selectedKzbFile);
                string destinationPath = Path.Combine(_clientDirectory, kzbFileName);

                _warnings.Add($"Copying KZB file: {kzbFileName}");

                // Copy the KZB file to client directory
                File.Copy(selectedKzbFile, destinationPath, true);
                _warnings.Add($"Copied {kzbFileName} to client directory");


                // Start new client process
                _clientProcess = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = clientExePath,
                        WorkingDirectory = _clientDirectory,
                        UseShellExecute = true
                    }
                };

                // Set up process exit monitoring
                _clientProcess.EnableRaisingEvents = true;
                _clientProcess.Exited += ClientProcess_Exited;

                _clientProcess.Start();
                _warnings.Add($"Restarted client with new KZB: {kzbFileName}");

                // Wait a moment for client to connect, then resend session values
                await Task.Delay(2000); // Give client time to connect
                await ResendSessionValues();
            }
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error updating KZB file: {ex.Message}");
        }
    }

    private void PreconditionComboBox_SelectionChanged(object? sender, SelectionChangedEventArgs e)
    {
        var preconditionFile = PreconditionComboBox.SelectedItem?.ToString();
        if (!string.IsNullOrEmpty(preconditionFile))
        {
            string preconditionPath = Path.Combine(_baseDir, "PreCondition", preconditionFile);
            if (File.Exists(preconditionPath))
            {
                LoadPreconditionFile(preconditionPath);
            }
        }
    }


    private async void BrowseClientButton_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            var topLevel = TopLevel.GetTopLevel(this);
            if (topLevel != null)
            {
                // Default folder selection mode
                await BrowseForClientFolder(topLevel);
            }
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error selecting client: {ex.Message}");
        }
    }

    private async void BrowseFileMenuItem_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            var topLevel = TopLevel.GetTopLevel(this);
            if (topLevel != null)
            {
                // Direct file selection mode
                await BrowseForExecutableFile(topLevel);
            }
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error selecting client file: {ex.Message}");
        }
    }

    private async Task BrowseForClientFolder(TopLevel topLevel)
    {
        // Folder picker for automatic detection
        var folders = await topLevel.StorageProvider.OpenFolderPickerAsync(new Avalonia.Platform.Storage.FolderPickerOpenOptions
        {
            Title = "Select Folder Containing Client (Right-click Browse button for file picker)",
            AllowMultiple = false
        });
        string foundExePath = "";
        string foundDirectory = "";

        if (folders.Count > 0)
        {
            // User selected a folder - search for DataSourceTestToolClient.exe
            string selectedFolder = folders[0].Path.LocalPath;

            // Search for DataSourceTestToolClient.exe in the selected folder and subdirectories
            var foundFiles = Directory.GetFiles(selectedFolder, "master.kzb", SearchOption.AllDirectories);

            if (foundFiles.Length > 0)
            {
                // Get the directory containing master.kzb
                foundDirectory = Path.GetDirectoryName(foundFiles[0]) ?? "";

                // Construct the path to DataSourceTestToolClient.exe in the same directory
                foundExePath = Path.Combine(foundDirectory, "DataSourceTestToolClient.exe");


            }
            else
            {
                _warnings.Add($"master.kzb not found in {selectedFolder} or its subdirectories, there is probably no kanzi binary inside this folder.");

                // Ask user if they want to browse for file directly
                _warnings.Add("Tip: Right-click the 'Browse Client' button to browse for the executable file directly.");
                return;
            }
        }
        else
        {
            // User cancelled folder picker - don't show another dialog automatically
            _warnings.Add("Folder selection cancelled. Tip: Right-click the 'Browse Client' button for file picker.");
            return;
        }

        if (!string.IsNullOrEmpty(foundExePath))
        {
            SetClientPath(foundExePath, foundDirectory);
        }
    }

    private async Task BrowseForExecutableFile(TopLevel topLevel)
    {
        // Direct file picker
        var files = await topLevel.StorageProvider.OpenFilePickerAsync(new Avalonia.Platform.Storage.FilePickerOpenOptions
        {
            Title = "Select Client Executable",
            AllowMultiple = false,
            FileTypeFilter = new[] { new Avalonia.Platform.Storage.FilePickerFileType("Executable Files") { Patterns = new[] { "*.exe" } } }
        });

        if (files.Count > 0)
        {
            string foundExePath = files[0].Path.LocalPath;
            string foundDirectory = Path.GetDirectoryName(foundExePath) ?? "";
            SetClientPath(foundExePath, foundDirectory);
        }
        else
        {
            _warnings.Add("No executable file selected.");
        }
    }

    private void SetClientPath(string exePath, string directory)
    {
        // Only store the directory, not the exe path
        _clientDirectory = directory;

        // Save the client path for future use
        SaveClientPath();

        // Don't automatically copy files - user will trigger with buttons
        // CopyKanziClientSaveFiles();

        // Update UI
        XmlDirectoryLabel.Text = _clientDirectory;
        _warnings.Add($"Selected client: {exePath}");
        _warnings.Add("Tip: Use 'Copy DLL Files' and 'Copy Client Files' buttons to copy required files.");

        // Enable the client button
        UpdateClientButtonState();

        // Load interfaces from the new client directory
        LoadInterfacesFromClientFolder();
    }

    private void LoadSavedClientPath()
    {
        try
        {
            string settingsPath = Path.Combine(_baseDir, "client_settings.txt");
            if (File.Exists(settingsPath))
            {
                _clientDirectory = File.ReadAllText(settingsPath).Trim();
                string clientExePath = GetClientExePath();
                if (!string.IsNullOrEmpty(_clientDirectory) && File.Exists(clientExePath))
                {
                    XmlDirectoryLabel.Text = _clientDirectory;
                    UpdateClientButtonState();
                    _warnings.Add($"Loaded saved client: {clientExePath}");

                    // Don't automatically copy files - user will trigger with buttons
                    // CopyKanziClientSaveFiles();

                    // Load interfaces from the saved client directory
                    LoadInterfacesFromClientFolder();
                }
                else
                {
                    _clientDirectory = "";
                    XmlDirectoryLabel.Text = "No client selected";
                    UpdateClientButtonState();
                }
            }
            else
            {
                XmlDirectoryLabel.Text = "No client selected";
                UpdateClientButtonState();
            }
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error loading saved client path: {ex.Message}");
            XmlDirectoryLabel.Text = "No client selected";
            UpdateClientButtonState();
        }
    }

    private void SaveClientPath()
    {
        try
        {
            string settingsPath = Path.Combine(_baseDir, "client_settings.txt");
            File.WriteAllText(settingsPath, _clientDirectory);
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error saving client path: {ex.Message}");
        }
    }
    #endregion

    protected override void OnClosed(EventArgs e)
    {
        // Close client process if running
        if (_clientProcess != null && !_clientProcess.HasExited)
        {
            try
            {
                _clientProcess.Kill();
                _clientProcess.WaitForExit(3000);
            }
            catch { }
        }

        // Dispose of client process
        try
        {
            _clientProcess?.Dispose();
        }
        catch { }

        _server.Close();
        base.OnClosed(e);
    }
}