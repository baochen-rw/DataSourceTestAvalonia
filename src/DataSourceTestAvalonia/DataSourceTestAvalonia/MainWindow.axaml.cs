using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Threading;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Data;
using System;
using System.IO;
using System.Xml;
using System.Linq;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Threading.Tasks;
using System.Text.Json;

namespace DataSourceTestAvalonia;

// Simple data model for the grid
public class XmlDataItem : INotifyPropertyChanged
{
    private string _fileName = "";
    private string _name = "";
    private string _type = "";
    private string _value = "";

    public string FileName
    {
        get => _fileName;
        set
        {
            if (_fileName != value)
            {
                _fileName = value;
                OnPropertyChanged();
            }
        }
    }

    public string Name
    {
        get => _name;
        set
        {
            if (_name != value)
            {
                _name = value;
                OnPropertyChanged();
            }
        }
    }

    public string Type
    {
        get => _type;
        set
        {
            if (_type != value)
            {
                _type = value;
                OnPropertyChanged();
            }
        }
    }

    public string Value
    {
        get => _value;
        set
        {
            if (_value != value)
            {
                _value = value;
                OnPropertyChanged();
            }
        }
    }

    public event PropertyChangedEventHandler? PropertyChanged;

    protected virtual void OnPropertyChanged([CallerMemberName] string? propertyName = null)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}

// Settings data model
public class AppSettings
{
    public string ClientDirectory { get; set; } = "";
    public string LastKzbDirectory { get; set; } = "";
    public Dictionary<string, int> MessageHistory { get; set; } = new();
    public string Theme { get; set; } = "Light"; // "Light" or "Dark"
    public string KzbWatchFolder { get; set; } = "";
    public bool KzbWatchEnabled { get; set; } = false;
}

internal partial class MainWindow : Window
{
    private readonly TestToolServer _server = new();
    private readonly ReadXML _xmlReader = new();
    private readonly ObservableCollection<string> _warnings = new();

    // Session-based data storage - keeps current values without modifying XML files
    private ObservableCollection<XmlDataItem> _filteredIF = new();
    // Session changes for UI display - shows only modified values
    private readonly ObservableCollection<XmlDataItem> _sessionChanges = new();

    // Client process management
    private Process? _clientProcess;
    private DateTime _clientStartTime;
    private System.Timers.Timer? _clientCheckTimer;
    private string _clientDirectory = "";
    private string _lastKzbDirectory = "";

    // KZB file watching
    private readonly KzbFileWatcher _kzbWatcher = new();

    // Message history for frequently used messages
    private readonly Dictionary<string, int> _messageHistory = new();
    private readonly int _maxHistoryMessages = 10;

    // Debounced settings save to improve performance
    private System.Timers.Timer? _settingsSaveTimer;
    private bool _settingsNeedSave = false;

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
    #region Initialization
    /// <summary>
    /// Initializes the complete application including UI bindings, event handlers, and services.
    /// This method orchestrates the entire application startup sequence.
    /// </summary>
    /// <exception cref="Exception">Thrown when any initialization step fails</exception>
    private void InitializeApplication()
    {
        try
        {
            SetupUIBindings();
            SetupEventHandlers();
            InitializeServices();
            InitializeThemeAndUI();
        }
        catch (Exception ex)
        {
            HandleInitializationError(ex);
            throw;
        }
    }

    /// <summary>
    /// Sets up data bindings between UI controls and data collections.
    /// </summary>
    private void SetupUIBindings()
    {
        WarningListBox.ItemsSource = _warnings;
        XmlDataGrid.ItemsSource = _filteredIF;
        SessionChangesItemsControl.ItemsSource = _sessionChanges;
    }

    /// <summary>
    /// Registers all event handlers for UI controls and services.
    /// </summary>
    private void SetupEventHandlers()
    {
        // Button event handlers
        BrowseClientButton.Click += BrowseClientButton_Click;
        ClientButton.Click += ClientButton_Click;
        ResendMessageButton.Click += ResendMessageButton_Click;
        ClearSessionButton.Click += ClearSessionButton_Click;
        NewKzbButton.Click += NewKzbButton_Click;
        ScreenshotButton.Click += ScreenshotButton_Click;
        PreconditionComboBox.SelectionChanged += PreconditionComboBox_SelectionChanged;
        LoadPreconditionButton.Click += LoadPreconditionButton_Click;
        CopyDllButton.Click += CopyDllButton_Click;
        CopyClientButton.Click += CopyClientButton_Click;
        OpenFolderMenuItem.Click += OpenFolderMenuItem_Click;
        RefreshMessagesButton.Click += RefreshMessagesButton_Click;
        ThemeToggleButton.Click += ThemeToggleButton_Click;
        ClearHistoryButton.Click += ClearHistoryButton_Click;

        // KZB watcher event handlers
        KzbWatchCheckBox.IsCheckedChanged += KzbWatchCheckBox_IsCheckedChanged;
        BrowseKzbWatchButton.Click += BrowseKzbWatchButton_Click;

        // Control event handlers
        InterfaceNameTextBox.TextChanged += InterfaceNameTextBox_TextChanged;
        ModuleComboBox.SelectionChanged += ModuleComboBox_SelectionChanged;
        XmlDataGrid.CellEditEnding += XmlDataGrid_CellEditEnding;

        // Server event handlers
        _server.StatusChanged += (msg) => Dispatcher.UIThread.Post(() => UpdateServerStatus(msg));
    }

    /// <summary>
    /// Initializes application services and loads persistent data.
    /// </summary>
    private void InitializeServices()
    {
        CurrentState = AppState.Initializing;
        SetupPaths();
        SetupXmlRecording();
        LoadAppSettings();
        LoadSavedClientPath();
        CreateKanziClientDllSaveFolder();
        LoadPreconditions();
        InitializeDebouncedSave();
        InitializeClientHealthCheck();
        InitializeKzbWatcher();
    }

    /// <summary>
    /// Initializes the debounced settings save timer.
    /// </summary>
    private void InitializeDebouncedSave()
    {
        _settingsSaveTimer = new System.Timers.Timer(2000); // 2 second delay
        _settingsSaveTimer.Elapsed += (sender, e) =>
        {
            if (_settingsNeedSave)
            {
                SaveAppSettings();
                _settingsNeedSave = false;
            }
        };
        _settingsSaveTimer.AutoReset = false; // Only fire once per trigger
    }

    /// <summary>
    /// Initializes a timer to periodically check client status and show helpful reminders.
    /// </summary>
    private void InitializeClientHealthCheck()
    {
        _clientCheckTimer = new System.Timers.Timer(30000); // Check every 30 seconds
        _clientCheckTimer.Elapsed += (sender, e) =>
        {
            try
            {
                Dispatcher.UIThread.Post(() =>
                {
                    // Only show reminders if not connected and no client is running
                    if (CurrentState != AppState.ClientConnected && CurrentState != AppState.Initializing)
                    {
                        string clientExePath = GetClientExePath();
                        if (string.IsNullOrEmpty(clientExePath) || !File.Exists(clientExePath))
                        {
                            AddWarning("⏰ REMINDER: No client executable found! Use 'Browse Client Directory' or 'Client.exe' button.");
                        }
                    }
                });
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error in client health check: {ex.Message}");
            }
        };
        _clientCheckTimer.AutoReset = true;
        _clientCheckTimer.Start();
    }

    /// <summary>
    /// Schedules a debounced settings save to improve performance.
    /// Settings will be saved after a 2-second delay from the last call.
    /// </summary>
    private void ScheduleSettingsSave()
    {
        _settingsNeedSave = true;
        _settingsSaveTimer?.Stop();
        _settingsSaveTimer?.Start();
    }

    /// <summary>
    /// Initializes theme, starts server, and updates UI.
    /// </summary>
    private void InitializeThemeAndUI()
    {
        UpdateThemeButton();
        StartServer();
        UpdateCommonMessagesUI();
    }

    /// <summary>
    /// Handles initialization errors with proper logging and cleanup.
    /// </summary>
    /// <param name="ex">The exception that occurred during initialization</param>
    private void HandleInitializationError(Exception ex)
    {
        Console.WriteLine($"Error during application initialization: {ex.Message}");
        Console.WriteLine($"Stack trace: {ex.StackTrace}");

        // Try to show error in warnings if possible
        try
        {
            _warnings?.Add($"❌ Initialization Error: {ex.Message}");
        }
        catch { }
    }
    #endregion
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
                        // Load interfaces when client connects and preserve current filters
                        LoadInterfacesFromClientFolderWithFilters();
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
            string destinationFolder = DetermineDestinationFolder();

            if (!ValidateSourceFolder(sourceFolder)) return;

            EnsureDestinationFolderExists(destinationFolder);

            int copiedCount = CopyAllFiles(sourceFolder, destinationFolder);
            _warnings.Add($"Copied {copiedCount} files from KanziClientSave to {destinationFolder}");
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error copying KanziClientSave files: {ex.Message}");
        }
    }

    /// <summary>
    /// Determines the destination folder for file copying based on client directory setting
    /// </summary>
    private string DetermineDestinationFolder()
    {
        return !string.IsNullOrEmpty(_clientDirectory)
            ? _clientDirectory
            : Path.Combine(_baseDir, "KanziClient");
    }

    /// <summary>
    /// Validates that the source folder exists
    /// </summary>
    private bool ValidateSourceFolder(string sourceFolder)
    {
        if (Directory.Exists(sourceFolder)) return true;

        _warnings.Add($"KanziClientSave folder not found: {sourceFolder}. Skipping file copy.");
        return false;
    }

    /// <summary>
    /// Ensures the destination folder exists, creating it if necessary
    /// </summary>
    private void EnsureDestinationFolderExists(string destinationFolder)
    {
        if (Directory.Exists(destinationFolder)) return;

        Directory.CreateDirectory(destinationFolder);
        _warnings.Add($"Created destination folder: {destinationFolder}");
    }

    /// <summary>
    /// Copies all files from source to destination, maintaining folder structure
    /// </summary>
    private int CopyAllFiles(string sourceFolder, string destinationFolder)
    {
        string[] files = Directory.GetFiles(sourceFolder, "*", SearchOption.AllDirectories);
        int copiedCount = 0;

        foreach (string sourceFile in files)
        {
            CopyFileWithStructure(sourceFile, sourceFolder, destinationFolder);
            copiedCount++;
        }

        return copiedCount;
    }

    /// <summary>
    /// Copies a single file while maintaining directory structure
    /// </summary>
    private void CopyFileWithStructure(string sourceFile, string sourceFolder, string destinationFolder)
    {
        string relativePath = Path.GetRelativePath(sourceFolder, sourceFile);
        string destinationFile = Path.Combine(destinationFolder, relativePath);

        // Create subdirectories if needed
        string? destinationDir = Path.GetDirectoryName(destinationFile);
        if (!string.IsNullOrEmpty(destinationDir) && !Directory.Exists(destinationDir))
        {
            Directory.CreateDirectory(destinationDir);
        }

        File.Copy(sourceFile, destinationFile, true);
    }

    private void CreateKanziClientDllSaveFolder()
    {
        try
        {
            string dllSaveFolder = Path.Combine(_baseDir, "KanziClientDLLSave");

            if (!Directory.Exists(dllSaveFolder))
            {
                Directory.CreateDirectory(dllSaveFolder);
                AddWarning($"📁 Created KanziClientDLLSave folder: {dllSaveFolder}");
            }
            else
            {
                AddWarning($"✅ KanziClientDLLSave folder already exists: {dllSaveFolder}");
            }
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error creating KanziClientDLLSave folder: {ex.Message}");
        }
    }

    private void CopyKanziClientDllSaveFiles()
    {
        try
        {
            string sourceFolder = Path.Combine(_baseDir, "KanziClientDLLSave");

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
                AddWarning($"📁 KanziClientDLLSave folder not found: {sourceFolder}. Creating it now...");
                Directory.CreateDirectory(sourceFolder);
                AddWarning($"💡 Please place your DLL files in {sourceFolder} and try again.");
                return;
            }

            // Create destination folder if it doesn't exist
            if (!Directory.Exists(destinationFolder))
            {
                Directory.CreateDirectory(destinationFolder);
                AddWarning($"📁 Created destination folder: {destinationFolder}");
            }

            // Copy all files from source to destination
            string[] files = Directory.GetFiles(sourceFolder, "*", SearchOption.AllDirectories);

            if (files.Length == 0)
            {
                AddWarning($"⚠️ No files found in KanziClientDLLSave folder. Please add DLL files to {sourceFolder}");
                return;
            }

            int copiedCount = 0;
            int replacedCount = 0;

            AddWarning($"🔄 Starting to copy {files.Length} files from KanziClientDLLSave...");

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

                // Check if file already exists
                bool fileExists = File.Exists(destinationFile);
                if (fileExists)
                {
                    replacedCount++;
                    AddWarning($"🔄 Replacing existing file: {relativePath}");
                }

                // Copy file with overwrite
                File.Copy(sourceFile, destinationFile, true);
                copiedCount++;
            }

            AddWarning($"✅ Successfully copied {copiedCount} files from KanziClientDLLSave to {destinationFolder}");
            if (replacedCount > 0)
            {
                AddWarning($"🔄 Replaced {replacedCount} existing files");
            }
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error copying KanziClientDLLSave files: {ex.Message}");
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

    /// <summary>
    /// Loads interfaces from client folder while preserving current filter settings
    /// </summary>
    private void LoadInterfacesFromClientFolderWithFilters()
    {
        // Store current filter values
        string currentModule = ModuleComboBox.SelectedItem?.ToString() ?? "ALL";
        string currentFilter = InterfaceNameTextBox.Text ?? "";

        // Load interfaces normally
        LoadInterfacesFromClientFolder();

        // Restore filter values and apply them
        if (ModuleComboBox.Items.Contains(currentModule))
        {
            ModuleComboBox.SelectedItem = currentModule;
        }
        InterfaceNameTextBox.Text = currentFilter;

        // Apply the preserved filters
        UpdateDataGrid(currentModule, currentFilter);
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
            var sessionItem = _sessionChanges.FirstOrDefault(x => x.FileName == fileName && x.Name == name);
            string currentValue = sessionItem?.Value ?? originalValue;

            return new XmlDataItem
            {
                FileName = fileName,
                Name = name,
                Type = row["type"].ToString() ?? "",
                Value = currentValue
            };
        }).ToList();

        // Update the session data collection
        _filteredIF.Clear();
        foreach (var item in itemsList)
        {
            _filteredIF.Add(item);
        }

        _warnings.Add($"Set DataGrid ItemsSource to {itemsList.Count} items (with session overrides)");
    }

    /// <summary>
    /// Sends a command to the connected client and updates session state.
    /// </summary>
    /// <param name="fileName">XML file name containing the interface</param>
    /// <param name="name">Interface element name</param>
    /// <param name="type">Data type (string, int, float, bool)</param>
    /// <param name="value">New value to send</param>
    /// <param name="trackInHistory">Whether to record this message in usage history (default: true)</param>
    private void SendToClient(string fileName, string name, string type, string value, bool trackInHistory = true)
    {
        if (name == "screenshot") return;

        UpdateSessionChanges(fileName, name, type, value);

        string sendValue = ConvertBooleanValue(value, type);
        _server.SendSyncCommand(fileName, type, name, sendValue);

        // Track this message in history only if requested (exclude preconditions)
        if (trackInHistory)
        {
            TrackMessageInHistory(fileName, name, type, value);
        }
    }

    /// <summary>
    /// Updates the session changes collection with the new value.
    /// </summary>
    /// <param name="fileName">XML file name</param>
    /// <param name="name">Interface element name</param>
    /// <param name="type">Data type</param>
    /// <param name="value">New value</param>
    private void UpdateSessionChanges(string fileName, string name, string type, string value)
    {
        var existingItem = _sessionChanges.FirstOrDefault(x => x.FileName == fileName && x.Name == name);
        if (existingItem != null)
        {
            existingItem.Value = value;
            // Force UI refresh by removing and re-adding the item
            var index = _sessionChanges.IndexOf(existingItem);
            _sessionChanges.RemoveAt(index);
            _sessionChanges.Insert(index, existingItem);
        }
        else
        {
            _sessionChanges.Add(new XmlDataItem
            {
                FileName = fileName,
                Name = name,
                Type = type,
                Value = value
            });
        }
    }

    /// <summary>
    /// Converts boolean values to client-compatible format.
    /// </summary>
    /// <param name="value">Original value</param>
    /// <param name="type">Data type</param>
    /// <returns>Converted value for client communication</returns>
    private static string ConvertBooleanValue(string value, string type)
    {
        if (type != "bool") return value;

        return value switch
        {
            "0" or "false" or "False" => "false",
            _ => "true"
        };
    }

    /// <summary>
    /// Records message usage frequency for "Most Used Messages" feature.
    /// Only tracks manual user interactions, excludes precondition loads.
    /// </summary>
    /// <param name="fileName">XML file containing the interface</param>
    /// <param name="name">Interface element name</param>
    /// <param name="type">Data type</param>
    /// <param name="value">Value that was set</param>
    private void TrackMessageInHistory(string fileName, string name, string type, string value)
    {
        try
        {
            string messageKey = CreateMessageKey(fileName, name, value);
            IncrementMessageCount(messageKey);

            // Always update UI immediately
            Dispatcher.UIThread.Post(() => UpdateCommonMessagesUI());

            // Use debounced save for better performance
            ScheduleSettingsSave();
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error tracking message history: {ex.Message}");
        }
    }

    /// <summary>
    /// Creates a unique message key for history tracking.
    /// </summary>
    /// <param name="fileName">XML file name</param>
    /// <param name="name">Interface name</param>
    /// <param name="value">Interface value</param>
    /// <returns>Formatted message key</returns>
    private string CreateMessageKey(string fileName, string name, string value)
        => $"{name}={value} ({fileName})";

    /// <summary>
    /// Increments the usage count for a message key.
    /// </summary>
    /// <param name="messageKey">Message key to increment</param>
    private void IncrementMessageCount(string messageKey)
    {
        _messageHistory[messageKey] = _messageHistory.GetValueOrDefault(messageKey, 0) + 1;
    }

    private List<string> GetTopMessages()
    {
        return _messageHistory
            .OrderByDescending(kvp => kvp.Value)
            .Take(_maxHistoryMessages)
            .Select(kvp => $"{kvp.Key} ({kvp.Value}x)")
            .ToList();
    }

    private void RecordAction(string fileName, string type, string name, string value)
    {
        if (_scriptRoot == null) return;

        XmlElement element = _recordXml.CreateElement(name);
        element.SetAttribute("filename", fileName);
        element.SetAttribute("type", type);
        element.SetAttribute("value", ConvertValueForRecording(value));
        _scriptRoot.AppendChild(element);
        _recordXml.Save(Path.Combine(_outputPath, "Unit_Test_Record.xml"));
    }

    /// <summary>
    /// Converts boolean values to XML format for recording (True/False -> 1/0)
    /// </summary>
    private static string ConvertValueForRecording(string value)
    {
        return value switch
        {
            "True" or "true" => "1",
            "False" or "false" => "0",
            _ => value
        };
    }



    private async void LoadPreconditionFile(string filePath)
    {
        try
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(filePath);

            if (doc.DocumentElement != null)
            {
                await ProcessPreconditionCommands(doc.DocumentElement);
            }
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error loading precondition file: {ex.Message}");
        }
    }

    /// <summary>
    /// Processes precondition commands from XML with delays between commands
    /// </summary>
    private async Task ProcessPreconditionCommands(XmlElement documentElement)
    {
        var commands = documentElement.ChildNodes.OfType<XmlElement>().ToList();
        _warnings.Add($"Loading {commands.Count} precondition commands with 500ms delays...");

        foreach (XmlElement item in commands)
        {
            ExecutePreconditionCommand(item);
            await Task.Delay(500);
        }

        _warnings.Add("Finished loading precondition commands.");
    }

    /// <summary>
    /// Executes a single precondition command
    /// </summary>
    private void ExecutePreconditionCommand(XmlElement item)
    {
        string fileName = item.GetAttribute("filename");
        string name = item.Name;
        string type = item.GetAttribute("type");
        string value = item.GetAttribute("value");

        SendToClient(fileName, name, type, value, trackInHistory: false);
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
            AddWarning("🔄 Starting DLL file operations...");

            // Copy standard DLL files
            CopyDatasourceToolsDll();
            AddWarning("✅ Standard DLL files copied successfully!");

            // Copy DLL Save files
            CopyKanziClientDllSaveFiles();
            AddWarning("✅ DLL Save files copied successfully!");

            AddWarning("🎯 All DLL file operations completed!");
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error during DLL file operations: {ex.Message}");
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
            int sessionCount = _sessionChanges.Count;

            // Clear the session changes collection
            _sessionChanges.Clear();

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
                AddWarning("🚨 ❌ CRITICAL: NO CLIENT EXECUTABLE FOUND! 🚨");
                AddWarning("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
                AddWarning("📋 TO FIX THIS ISSUE:");
                AddWarning("   1️⃣ Click 'Browse Client Directory' to select client folder");
                AddWarning("   2️⃣ OR click the green 'Client.exe' button to copy client files");
                AddWarning("   3️⃣ Make sure 'DataSourceTestToolClient.exe' exists in the client folder you just selected");
                AddWarning("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
                AddWarning($"🔍 Looking for: {(!string.IsNullOrEmpty(clientExePath) ? clientExePath : "No path set")}");
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

            _clientStartTime = DateTime.Now;
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
                // Calculate how long the client was running
                TimeSpan runTime = DateTime.Now - _clientStartTime;

                // Check if client exited without ever establishing connection
                // This is a much better indicator of DLL issues than just time
                bool neverConnected = (CurrentState != AppState.ClientConnected &&
                                     (CurrentState == AppState.ServerStarted ||
                                      CurrentState == AppState.ClientDisconnected));

                if (neverConnected && runTime.TotalSeconds > 3)
                {
                    // Client was visible but never connected - classic DLL missing scenario
                    AddWarning("💥 🔌 CLIENT STARTED BUT NEVER CONNECTED!");
                    AddWarning("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
                    AddWarning("🔍 DIAGNOSIS: Client window appeared but couldn't establish connection");
                    AddWarning("🎯 MOST LIKELY CAUSE: Missing or incompatible DLL files");
                    AddWarning("🛠️ SOLUTION:");
                    AddWarning("   1️⃣ Click 'Copy DLL' button to copy required DLLs");
                    AddWarning("   2️⃣ Ensure all dependencies are in the client directory");
                    AddWarning("   3️⃣ Try starting the client again");
                    AddWarning("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
                    AddWarning($"⏱️ Client ran for {runTime.TotalSeconds:F1} seconds without connecting");
                }
                else if (runTime.TotalSeconds < 3)
                {
                    // Client crashed immediately - different issue
                    AddWarning("💥 ⚡ CLIENT CRASHED IMMEDIATELY! (< 3 seconds)");
                    AddWarning("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
                    AddWarning("🔍 CAUSE: Severe compatibility or missing system files");
                    AddWarning("🛠️ SOLUTION:");
                    AddWarning("   1️⃣ Check Windows Event Viewer for crash details");
                    AddWarning("   2️⃣ Click 'Copy DLL' button to copy required DLLs");
                    AddWarning("   3️⃣ Ensure .NET runtime is installed");
                    AddWarning("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
                    AddWarning($"⏱️ Client crashed after only {runTime.TotalSeconds:F1} seconds");
                }
                else
                {
                    AddWarning($"Client process has exited after {runTime.TotalSeconds:F1} seconds");
                }                // Update UI state if client disconnected
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
            if (_sessionChanges.Count > 0)
            {
                _warnings.Add($"Resending {_sessionChanges.Count} session values to client with 200ms delays...");

                foreach (var sessionItem in _sessionChanges)
                {
                    SendToClient(sessionItem.FileName, sessionItem.Name, sessionItem.Type, sessionItem.Value);

                    // Add 200ms delay between commands
                    await Task.Delay(200);
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

            // Set starting directory to last KZB directory if available, otherwise use client directory
            if (!string.IsNullOrEmpty(_lastKzbDirectory) && Directory.Exists(_lastKzbDirectory))
            {
                options.SuggestedStartLocation = await topLevel.StorageProvider.TryGetFolderFromPathAsync(new Uri(_lastKzbDirectory));
            }
            else if (!string.IsNullOrEmpty(_clientDirectory) && Directory.Exists(_clientDirectory))
            {
                options.SuggestedStartLocation = await topLevel.StorageProvider.TryGetFolderFromPathAsync(new Uri(_clientDirectory));
            }

            var result = await topLevel.StorageProvider.OpenFilePickerAsync(options);
            if (result.Count > 0)
            {
                string selectedKzbFile = result[0].Path.LocalPath;
                string kzbFileName = Path.GetFileName(selectedKzbFile);
                string destinationPath = Path.Combine(_clientDirectory, kzbFileName);

                // Save the directory of the selected KZB file for next time
                _lastKzbDirectory = Path.GetDirectoryName(selectedKzbFile) ?? "";
                SaveLastKzbDirectory();

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

                _clientStartTime = DateTime.Now;
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

    private void LoadPreconditionButton_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            var preconditionFile = PreconditionComboBox.SelectedItem?.ToString();
            if (string.IsNullOrEmpty(preconditionFile))
            {
                AddWarning("⚠️ Please select a precondition file first.");
                return;
            }

            string preconditionPath = Path.Combine(_baseDir, "PreCondition", preconditionFile);
            if (File.Exists(preconditionPath))
            {
                AddWarning($"🔄 Loading precondition: {preconditionFile}");
                LoadPreconditionFile(preconditionPath);
            }
            else
            {
                AddWarning($"❌ Precondition file not found: {preconditionFile}");
            }
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error loading precondition: {ex.Message}");
        }
    }

    private void OpenFolderMenuItem_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            if (string.IsNullOrEmpty(_clientDirectory) || !Directory.Exists(_clientDirectory))
            {
                AddWarning("❌ No client directory set or directory doesn't exist.");
                return;
            }

            // Open the folder in Windows Explorer
            Process.Start(new ProcessStartInfo
            {
                FileName = "explorer.exe",
                Arguments = $"\"{_clientDirectory}\"",
                UseShellExecute = true
            });

            AddWarning($"📂 Opened client folder: {_clientDirectory}");
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error opening folder: {ex.Message}");
        }
    }

    private void RefreshMessagesButton_Click(object? sender, RoutedEventArgs e)
    {
        UpdateCommonMessagesUI();
    }

    private void ClearHistoryButton_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            _messageHistory.Clear();
            SaveAppSettings();
            UpdateCommonMessagesUI();
            AddWarning("🗑️ Message history cleared!");
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error clearing message history: {ex.Message}");
        }
    }

    private void ThemeToggleButton_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            ThemeManager.Instance.ToggleTheme();
            UpdateThemeButton();
            SaveAppSettings(); // Save theme preference immediately
            AddWarning($"🎨 Theme switched to {ThemeManager.Instance.GetThemeDisplayName()}");
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error toggling theme: {ex.Message}");
        }
    }

    private void UpdateThemeButton()
    {
        ThemeToggleButton.Content = ThemeManager.Instance.GetNextThemeDisplayName();
    }

    #region KZB File Watcher Event Handlers

    /// <summary>
    /// Initializes the KZB file watcher and sets up event handlers
    /// </summary>
    private void InitializeKzbWatcher()
    {
        // Set up event handlers for the KZB watcher
        _kzbWatcher.KzbFileChanged += OnKzbFileChanged;
        _kzbWatcher.StatusMessage += AddWarning;
    }

    private void KzbWatchCheckBox_IsCheckedChanged(object? sender, RoutedEventArgs e)
    {
        try
        {
            bool enabled = KzbWatchCheckBox.IsChecked == true;
            _kzbWatcher.SetEnabled(enabled);
            UpdateKzbWatchStatus();
            ScheduleSettingsSave(); // Save the setting
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error toggling KZB watcher: {ex.Message}");
        }
    }

    private async void BrowseKzbWatchButton_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            var topLevel = GetTopLevel(this);
            if (topLevel != null)
            {
                var folders = await topLevel.StorageProvider.OpenFolderPickerAsync(new Avalonia.Platform.Storage.FolderPickerOpenOptions
                {
                    Title = "Select KZB Watch Folder",
                    AllowMultiple = false
                });

                if (folders.Count > 0)
                {
                    string selectedFolder = folders[0].Path.LocalPath;

                    // Auto-locate child folder with master.kzb (similar to client folder selection)
                    string actualWatchFolder = FindKzbFolder(selectedFolder);

                    _kzbWatcher.SetWatchFolder(actualWatchFolder);
                    KzbWatchFolderLabel.Text = actualWatchFolder;
                    UpdateKzbWatchStatus();
                    ScheduleSettingsSave(); // Save the folder path
                }
            }
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error selecting KZB watch folder: {ex.Message}");
        }
    }

    /// <summary>
    /// Finds the folder containing master.kzb in the selected directory or subdirectories
    /// </summary>
    private string FindKzbFolder(string selectedFolder)
    {
        try
        {
            // Search for master.kzb in the selected folder and subdirectories
            var foundFiles = Directory.GetFiles(selectedFolder, "master.kzb", SearchOption.AllDirectories);

            if (foundFiles.Length > 0)
            {
                // Get the directory containing master.kzb
                string foundDirectory = Path.GetDirectoryName(foundFiles[0]) ?? selectedFolder;
                AddWarning($"📂 Auto-located KZB folder: {foundDirectory}");
                return foundDirectory;
            }
            else
            {
                AddWarning($"⚠️ master.kzb not found in {selectedFolder} or its subdirectories. Using selected folder.");
                return selectedFolder;
            }
        }
        catch (Exception ex)
        {
            AddWarning($"⚠️ Error searching for master.kzb: {ex.Message}. Using selected folder.");
            return selectedFolder;
        }
    }

    /// <summary>
    /// Handles KZB file change events from the watcher
    /// </summary>
    private async Task OnKzbFileChanged(string kzbFilePath)
    {
        try
        {
            if (!File.Exists(kzbFilePath))
            {
                AddWarning($"❌ KZB file no longer exists: {kzbFilePath}");
                return;
            }

            if (CurrentState != AppState.ClientConnected)
            {
                AddWarning("⚠️ Client not connected. Starting client with new KZB file...");
            }

            string kzbFileName = Path.GetFileName(kzbFilePath);
            string destinationPath = Path.Combine(_clientDirectory, kzbFileName);
            // Kill existing client if running
            if (_clientProcess != null && !_clientProcess.HasExited)
            {
                _clientProcess.Kill();
                _clientProcess.WaitForExit(3000);
                AddWarning("🔄 Stopped existing client");
            }

            // Wait a moment then start client with new KZB
            await Task.Delay(1000);
            // Copy the KZB file
            File.Copy(kzbFilePath, destinationPath, true);
            AddWarning($"✅ Copied KZB file: {kzbFileName}");



            // Start new client process
            _clientProcess = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = GetClientExePath(),
                    Arguments = kzbFileName,
                    WorkingDirectory = _clientDirectory,
                    UseShellExecute = true
                }
            };

            // Set up process exit monitoring
            _clientProcess.EnableRaisingEvents = true;
            _clientProcess.Exited += ClientProcess_Exited;

            _clientStartTime = DateTime.Now;
            _clientProcess.Start();
            AddWarning($"� Auto-restarted client with new KZB: {kzbFileName}");

            // Wait a moment for client to connect, then resend session values
            await Task.Delay(2000);
            await ResendSessionValues();
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error processing KZB file: {ex.Message}");
        }
    }

    /// <summary>
    /// Updates the KZB watcher status display
    /// </summary>
    private void UpdateKzbWatchStatus()
    {
        var (statusText, statusColor) = _kzbWatcher.GetStatus();
        KzbWatchStatusLabel.Text = statusText;
        KzbWatchStatusLabel.Foreground = new Avalonia.Media.SolidColorBrush(Avalonia.Media.Color.Parse(statusColor));
    }

    #endregion

    private void UpdateCommonMessagesUI()
    {
        try
        {
            CommonMessagesPanel.Children.Clear();

            var topMessages = GetTopMessages();
            if (topMessages.Count == 0)
            {
                var noMessagesText = new TextBlock
                {
                    Text = "No common messages yet. Edit some interface values to build history.",
                    FontStyle = Avalonia.Media.FontStyle.Italic,
                    Foreground = Avalonia.Media.Brushes.Gray,
                    Margin = new Avalonia.Thickness(5)
                };
                CommonMessagesPanel.Children.Add(noMessagesText);
                return;
            }

            foreach (var message in topMessages)
            {
                // Parse the message format: "name=value (filename) (count)"
                if (TryParseMessageHistory(message, out string name, out string value, out string fileName, out int count))
                {
                    var button = new Button
                    {
                        Content = $"{name}={value} ({count}x)",
                        Margin = new Avalonia.Thickness(2),
                        Padding = new Avalonia.Thickness(8, 4),
                        FontSize = 11,
                        Background = Avalonia.Media.Brushes.LightBlue
                    };

                    // Add click handler to reapply this message
                    button.Click += (s, e) => ApplyCommonMessage(fileName, name, value);

                    CommonMessagesPanel.Children.Add(button);
                }
            }
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error updating common messages UI: {ex.Message}");
        }
    }

    private bool TryParseMessageHistory(string message, out string name, out string value, out string fileName, out int count)
    {
        name = "";
        value = "";
        fileName = "";
        count = 0;

        try
        {
            // Format: "name=value (filename) (countx)"
            var parts = message.Split(" (");
            if (parts.Length >= 3)
            {
                var nameValue = parts[0].Split("=", 2);
                if (nameValue.Length == 2)
                {
                    name = nameValue[0];
                    value = nameValue[1];
                    fileName = parts[1].TrimEnd(')');
                    var countStr = parts[2].Replace("x)", "");
                    return int.TryParse(countStr, out count);
                }
            }
        }
        catch { }

        return false;
    }

    private void ApplyCommonMessage(string fileName, string name, string value)
    {
        try
        {
            // Find the item type from current session data
            var item = _filteredIF.FirstOrDefault(x => x.FileName == fileName && x.Name == name);
            if (item != null)
            {
                // Update the item in the main grid
                item.Value = value;

                // Send to client
                SendToClient(fileName, name, item.Type, value);

                AddWarning($"📤 Applied common message: {name}={value} from {fileName}");
            }
            else
            {
                AddWarning($"⚠️ Could not find interface {name} in {fileName}. Try refreshing the interface list.");
            }
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error applying common message: {ex.Message}");
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
            // This will be handled by LoadAppSettings now - just update UI
            if (!string.IsNullOrEmpty(_clientDirectory))
            {
                // Always show the directory in the label
                XmlDirectoryLabel.Text = _clientDirectory;

                string clientExePath = GetClientExePath();
                if (File.Exists(clientExePath))
                {
                    UpdateClientButtonState();
                    AddWarning($"✅ Loaded saved client: {clientExePath}");
                    LoadInterfacesFromClientFolder();
                }
                else
                {
                    UpdateClientButtonState();
                    AddWarning($"⚠️ Client directory loaded but executable not found: {clientExePath}");
                    AddWarning($"💡 Tip: Use the 'Client.exe' button to copy client files or browse for a different location.");
                }
            }
            else
            {
                XmlDirectoryLabel.Text = "No client selected";
                UpdateClientButtonState();
                AddWarning($"🔍 No saved client directory found. Please browse for client location.");
            }
        }
        catch (Exception ex)
        {
            AddWarning($"❌ Error loading saved client path: {ex.Message}");
            XmlDirectoryLabel.Text = "Error loading client";
            UpdateClientButtonState();
        }
    }

    private void SaveClientPath()
    {
        SaveAppSettings();
    }

    private void SaveLastKzbDirectory()
    {
        SaveAppSettings();
    }

    private void SaveAppSettings()
    {
        try
        {
            var settings = new AppSettings
            {
                ClientDirectory = _clientDirectory,
                LastKzbDirectory = _lastKzbDirectory,
                MessageHistory = new Dictionary<string, int>(_messageHistory),
                Theme = ThemeManager.Instance.CurrentTheme.ToString(),
                KzbWatchFolder = _kzbWatcher.WatchFolder,
                KzbWatchEnabled = _kzbWatcher.IsEnabled
            };

            string settingsPath = Path.Combine(_baseDir, "app_settings.json");
            string json = JsonSerializer.Serialize(settings, new JsonSerializerOptions { WriteIndented = true });
            File.WriteAllText(settingsPath, json);
        }
        catch (Exception ex)
        {
            _warnings.Add($"❌ Error saving app settings: {ex.Message}");
        }
    }

    private void LoadLastKzbDirectory()
    {
        LoadAppSettings();
    }

    private void LoadAppSettings()
    {
        try
        {
            string settingsPath = Path.Combine(_baseDir, "app_settings.json");
            if (File.Exists(settingsPath))
            {
                string json = File.ReadAllText(settingsPath);
                var settings = JsonSerializer.Deserialize<AppSettings>(json);

                if (settings != null)
                {
                    _clientDirectory = settings.ClientDirectory ?? "";
                    _lastKzbDirectory = settings.LastKzbDirectory ?? "";

                    // Configure KZB watcher with saved settings
                    _kzbWatcher.Configure(settings.KzbWatchFolder ?? "", settings.KzbWatchEnabled);

                    // Update KZB watcher UI
                    KzbWatchCheckBox.IsChecked = _kzbWatcher.IsEnabled;
                    KzbWatchFolderLabel.Text = string.IsNullOrEmpty(_kzbWatcher.WatchFolder) ? "No folder selected" : _kzbWatcher.WatchFolder;
                    UpdateKzbWatchStatus();

                    // Load and apply theme
                    string themeName = settings.Theme ?? "Light";
                    if (Enum.TryParse<AppTheme>(themeName, out AppTheme theme))
                    {
                        ThemeManager.Instance.SetTheme(theme);
                        AddWarning($"🎨 Applied saved theme: {ThemeManager.Instance.GetThemeDisplayName()}");
                    }
                    else
                    {
                        // Default to Light theme if invalid value
                        ThemeManager.Instance.SetTheme(AppTheme.Light);
                        AddWarning($"⚠️ Invalid theme '{themeName}' in settings, defaulting to Light theme");
                    }

                    // Load message history
                    _messageHistory.Clear();
                    if (settings.MessageHistory != null)
                    {
                        foreach (var kvp in settings.MessageHistory)
                        {
                            _messageHistory[kvp.Key] = kvp.Value;
                        }
                    }

                    _warnings.Add($"💾 Loaded app settings - Client: {_clientDirectory}, Last KZB: {_lastKzbDirectory}, Messages: {_messageHistory.Count}, Theme: {themeName}");
                }
            }
            else
            {
                // No settings file exists - use defaults
                ThemeManager.Instance.SetTheme(AppTheme.Light);
                AddWarning($"🎨 No settings file found, using default Light theme");

                // Try to migrate from old settings files
                MigrateOldSettings();
            }
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error loading app settings: {ex.Message}");
            // Try to migrate from old settings files
            MigrateOldSettings();
        }
    }

    private void MigrateOldSettings()
    {
        try
        {
            // Migrate client settings
            string clientSettingsPath = Path.Combine(_baseDir, "client_settings.txt");
            if (File.Exists(clientSettingsPath))
            {
                _clientDirectory = File.ReadAllText(clientSettingsPath).Trim();
            }

            // Migrate KZB settings
            string kzbSettingsPath = Path.Combine(_baseDir, "last_kzb_settings.txt");
            if (File.Exists(kzbSettingsPath))
            {
                _lastKzbDirectory = File.ReadAllText(kzbSettingsPath).Trim();
            }

            // Save to new format and delete old files
            if (!string.IsNullOrEmpty(_clientDirectory) || !string.IsNullOrEmpty(_lastKzbDirectory))
            {
                SaveAppSettings();

                // Delete old files
                try { File.Delete(clientSettingsPath); } catch { }
                try { File.Delete(kzbSettingsPath); } catch { }

                _warnings.Add("Migrated settings from old format to new JSON format.");
            }
        }
        catch (Exception ex)
        {
            _warnings.Add($"Error migrating old settings: {ex.Message}");
        }
    }
    #endregion

    protected override void OnClosed(EventArgs e)
    {
        // Save settings one final time to ensure message history is preserved
        try
        {
            // Stop debounced timer and force immediate save
            _settingsSaveTimer?.Stop();
            SaveAppSettings();
            AddWarning("💾 Final settings save completed on app close");
        }
        catch (Exception ex)
        {
            // Even if saving fails, continue with cleanup
            AddWarning($"❌ Error saving settings on close: {ex.Message}");
        }

        // Cleanup timer
        try
        {
            _settingsSaveTimer?.Dispose();
            _clientCheckTimer?.Stop();
            _clientCheckTimer?.Dispose();
            _kzbWatcher?.Dispose(); // Stop and dispose KZB file watcher
        }
        catch { }

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