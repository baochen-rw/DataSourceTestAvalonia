# Function Documentation & Code Review

## Code Simplification Recommendations

### 1. **InitializeApplication() Method Refactoring**

**Current Issue**: 80+ line method handling multiple responsibilities

**Suggested Simplification**:

```csharp
private void InitializeApplication()
{
    try
    {
        SetupUIBindings();
        SetupEventHandlers();
        InitializeServices();
        InitializeTheme();
        StartServerAndUpdateUI();
    }
    catch (Exception ex)
    {
        HandleInitializationError(ex);
        throw;
    }
}

private void SetupUIBindings()
{
    WarningListBox.ItemsSource = _warnings;
    XmlDataGrid.ItemsSource = _filteredIF;
    SessionChangesItemsControl.ItemsSource = _sessionChanges;
}

private void SetupEventHandlers()
{
    // Button event handlers
    BrowseClientButton.Click += BrowseClientButton_Click;
    ClientButton.Click += ClientButton_Click;
    // ... etc

    // Control event handlers
    InterfaceNameTextBox.TextChanged += InterfaceNameTextBox_TextChanged;
    ModuleComboBox.SelectionChanged += ModuleComboBox_SelectionChanged;
    XmlDataGrid.CellEditEnding += XmlDataGrid_CellEditEnding;

    // Server event handlers
    _server.StatusChanged += (msg) => Dispatcher.UIThread.Post(() => UpdateServerStatus(msg));
}

private void InitializeServices()
{
    CurrentState = AppState.Initializing;
    SetupPaths();
    SetupXmlRecording();
    LoadAppSettings();
    LoadSavedClientPath();
    CreateKanziClientDllSaveFolder();
    LoadPreconditions();
}
```

### 2. **Message History Tracking Simplification**

**Current Issue**: Dictionary increment/add logic repeated

**Suggested Simplification**:

```csharp
private void TrackMessageInHistory(string fileName, string name, string type, string value)
{
    try
    {
        string messageKey = CreateMessageKey(fileName, name, value);
        IncrementMessageCount(messageKey);

        // Always update UI and save
        Dispatcher.UIThread.Post(() => UpdateCommonMessagesUI());
        SaveAppSettings();
    }
    catch (Exception ex)
    {
        AddWarning($"❌ Error tracking message history: {ex.Message}");
    }
}

private string CreateMessageKey(string fileName, string name, string value)
    => $"{name}={value} ({fileName})";

private void IncrementMessageCount(string messageKey)
{
    _messageHistory[messageKey] = _messageHistory.GetValueOrDefault(messageKey, 0) + 1;
}
```

### 3. **Boolean Value Conversion Simplification**

**Current Issue**: Complex boolean conversion logic scattered

**Suggested Simplification**:

```csharp
private static string ConvertBooleanValue(string value, string type)
{
    if (type != "bool") return value;

    return value switch
    {
        "0" or "false" or "False" => "false",
        _ => "true"
    };
}
```

---

## Complete Function Documentation

### **MainWindow.axaml.cs Functions**

#### **Constructor & Initialization**

##### `MainWindow()`

```csharp
/// <summary>
/// Initializes the main application window.
/// Sets up UI components and starts application initialization sequence.
/// </summary>
/// <exception cref="Exception">Thrown when UI initialization fails</exception>
```

##### `InitializeApplication()`

```csharp
/// <summary>
/// Initializes the complete application including UI bindings, event handlers, and services.
/// This method orchestrates the entire application startup sequence.
/// </summary>
/// <exception cref="Exception">Thrown when any initialization step fails</exception>
/// <remarks>
/// Initialization order:
/// 1. Setup UI data bindings
/// 2. Register all event handlers
/// 3. Initialize application services
/// 4. Load persistent settings
/// 5. Start TCP server
/// 6. Update UI state
/// </remarks>
```

#### **State Management**

##### `HandleStateChange(AppState newState)`

```csharp
/// <summary>
/// Manages UI state transitions based on application status.
/// Controls button states, status text, and feature availability.
/// </summary>
/// <param name="newState">The new application state to transition to</param>
/// <remarks>
/// State transitions:
/// - Initializing: All controls disabled, server starting
/// - ServerStarted: Waiting for client connection
/// - ClientConnected: Full functionality enabled, load XML interfaces
/// - ClientDisconnected: Client-dependent features disabled
/// - Error: All features disabled, error state displayed
/// </remarks>
```

##### `CurrentState { get; set; }`

```csharp
/// <summary>
/// Gets or sets the current application state.
/// Automatically triggers UI updates when changed.
/// </summary>
/// <value>The current AppState value</value>
/// <remarks>
/// Setting this property automatically calls HandleStateChange() to update the UI
/// </remarks>
```

##### `UpdateClientButtonState()`

```csharp
/// <summary>
/// Updates client-related button states based on client executable availability and connection status.
/// </summary>
/// <remarks>
/// Button state logic:
/// - ClientButton: Always enabled (handles missing exe internally)
/// - ResendMessageButton: Only enabled when client connected
/// - NewKzbButton: Only enabled when valid client executable exists
/// </remarks>
```

#### **Server Communication**

##### `StartServer()`

```csharp
/// <summary>
/// Initializes and starts the TCP server on port 22207.
/// Sets up asynchronous client connection handling.
/// </summary>
/// <remarks>
/// The server automatically transitions to ClientConnected state when a client connects.
/// Uses background task to avoid blocking the UI thread.
/// </remarks>
```

##### `UpdateServerStatus(string message)`

```csharp
/// <summary>
/// Updates server status display in the UI.
/// Called by server event handlers to provide real-time status updates.
/// </summary>
/// <param name="message">Status message to display</param>
/// <remarks>
/// This method is thread-safe and can be called from background threads.
/// </remarks>
```

##### `SendToClient(string fileName, string name, string type, string value, bool trackInHistory = true)`

```csharp
/// <summary>
/// Sends a command to the connected client and updates session state.
/// </summary>
/// <param name="fileName">XML file name containing the interface</param>
/// <param name="name">Interface element name</param>
/// <param name="type">Data type (string, int, float, bool)</param>
/// <param name="value">New value to send</param>
/// <param name="trackInHistory">Whether to record this message in usage history (default: true)</param>
/// <remarks>
/// Functionality:
/// 1. Updates session changes collection for UI display
/// 2. Converts boolean values for client compatibility
/// 3. Sends command via TCP server
/// 4. Optionally tracks message frequency for "Most Used" feature
///
/// Boolean conversion: "0"/"false" becomes "false", everything else becomes "true"
/// History tracking disabled for precondition loads to avoid cluttering frequently used messages.
/// </remarks>
```

#### **Data Management**

##### `LoadInterfacesFromClientFolder()`

```csharp
/// <summary>
/// Loads XML interface files from the selected client directory.
/// Populates the main data grid with available interfaces.
/// </summary>
/// <remarks>
/// Process:
/// 1. Validates client directory exists
/// 2. Uses ReadXML service to parse XML files
/// 3. Converts DataTable to ObservableCollection for UI binding
/// 4. Applies any active filters (module, interface name)
///
/// Called automatically when client connects or when explicitly refreshed.
/// </remarks>
```

##### `ApplyFilters()`

```csharp
/// <summary>
/// Applies module and interface name filters to the displayed data.
/// Updates the data grid to show only matching interfaces.
/// </summary>
/// <remarks>
/// Filtering criteria:
/// - Module filter: Exact match on module name
/// - Interface name filter: Case-insensitive substring match
/// - Both filters can be active simultaneously (AND logic)
/// </remarks>
```

##### `XmlDataGrid_CellEditEnding(object? sender, DataGridCellEditEndingEventArgs e)`

```csharp
/// <summary>
/// Handles user edits in the main data grid.
/// Processes value changes and sends them to the connected client.
/// </summary>
/// <param name="sender">The DataGrid that triggered the event</param>
/// <param name="e">Event arguments containing edit details</param>
/// <remarks>
/// Process:
/// 1. Validates edit is on Value column (other columns read-only)
/// 2. Extracts new value from editing control
/// 3. Updates the data item
/// 4. Sends change to client via SendToClient()
/// 5. Automatically tracks in message history
///
/// Only processes "Value" column edits; other columns are informational.
/// </remarks>
```

#### **Session Management**

##### `ClearSessionButton_Click(object? sender, RoutedEventArgs e)`

```csharp
/// <summary>
/// Clears all session changes and reloads original XML data.
/// Resets the testing session to initial state.
/// </summary>
/// <param name="sender">Button that triggered the event</param>
/// <param name="e">Event arguments</param>
/// <remarks>
/// Actions performed:
/// 1. Clears session changes collection (removes all modifications)
/// 2. Reloads original XML interfaces from files
/// 3. Resets data grid to original values
/// 4. Maintains message history (separate from session data)
/// </remarks>
```

##### `ResendMessageButton_Click(object? sender, RoutedEventArgs e)`

```csharp
/// <summary>
/// Resends all current session changes to the connected client.
/// Useful for synchronizing client state after reconnection.
/// </summary>
/// <param name="sender">Button that triggered the event</param>
/// <param name="e">Event arguments</param>
/// <remarks>
/// Iterates through all session changes and resends them via SendToClient().
/// Does not track these as new message history entries (trackInHistory: false).
/// Only enabled when client is connected.
/// </remarks>
```

#### **Precondition System**

##### `LoadPreconditions()`

```csharp
/// <summary>
/// Scans for precondition XML files and populates the precondition dropdown.
/// </summary>
/// <remarks>
/// Searches in "PreCondition" subfolder of application directory.
/// Precondition files contain predefined sequences of interface changes.
/// Updates PreconditionComboBox with available files.
/// </remarks>
```

##### `LoadPreconditionFile(string filePath)`

```csharp
/// <summary>
/// Loads and executes a precondition file with sequential command execution.
/// </summary>
/// <param name="filePath">Path to the precondition XML file</param>
/// <remarks>
/// Execution process:
/// 1. Parses XML file to extract commands
/// 2. Executes each command with 500ms delay between commands
/// 3. Sends commands to client (trackInHistory: false to avoid cluttering message history)
/// 4. Updates session changes display
/// 5. Provides progress feedback via warning messages
///
/// Precondition commands are not tracked in message history to keep "Most Used"
/// panel focused on manual testing patterns.
/// </remarks>
```

##### `LoadPreconditionButton_Click(object? sender, RoutedEventArgs e)`

```csharp
/// <summary>
/// Executes the currently selected precondition file.
/// </summary>
/// <param name="sender">Button that triggered the event</param>
/// <param name="e">Event arguments</param>
/// <remarks>
/// Validates precondition is selected before execution.
/// Calls LoadPreconditionFile() with the selected file path.
/// </remarks>
```

#### **File Operations**

##### `BrowseClientButton_Click(object? sender, RoutedEventArgs e)`

```csharp
/// <summary>
/// Opens folder browser dialog to select client executable directory.
/// </summary>
/// <param name="sender">Button that triggered the event</param>
/// <param name="e">Event arguments</param>
/// <remarks>
/// Process:
/// 1. Shows folder picker dialog
/// 2. Validates selected directory contains expected files
/// 3. Updates client directory path and saves to settings
/// 4. Updates UI labels and button states
/// 5. Automatically loads XML interfaces if available
/// </remarks>
```

##### `CopyDllButton_Click(object? sender, RoutedEventArgs e)`

```csharp
/// <summary>
/// Copies both standard DLL files and saved DLL files to client directory.
/// Combines functionality of standard DLL copy and DLL Save copy operations.
/// </summary>
/// <param name="sender">Button that triggered the event</param>
/// <param name="e">Event arguments</param>
/// <remarks>
/// Operations performed:
/// 1. Calls CopyDatasourceToolsDll() for standard DLL files
/// 2. Calls CopyKanziClientDllSaveFiles() for saved DLL files
/// 3. Provides progress feedback for each operation
/// 4. Handles errors gracefully with user-friendly messages
/// </remarks>
```

##### `CopyClientButton_Click(object? sender, RoutedEventArgs e)`

```csharp
/// <summary>
/// Copies client executable files to the selected directory.
/// </summary>
/// <param name="sender">Button that triggered the event</param>
/// <param name="e">Event arguments</param>
/// <remarks>
/// Copies client application files from KanziClientSave folder to selected directory.
/// Creates destination directory if it doesn't exist.
/// Provides detailed progress feedback via warning messages.
/// </remarks>
```

#### **Message History System**

##### `TrackMessageInHistory(string fileName, string name, string type, string value)`

```csharp
/// <summary>
/// Records message usage frequency for "Most Used Messages" feature.
/// Only tracks manual user interactions, excludes precondition loads.
/// </summary>
/// <param name="fileName">XML file containing the interface</param>
/// <param name="name">Interface element name</param>
/// <param name="type">Data type</param>
/// <param name="value">Value that was set</param>
/// <remarks>
/// Functionality:
/// 1. Creates unique message key: "name=value (fileName)"
/// 2. Increments usage counter in _messageHistory dictionary
/// 3. Immediately updates "Most Used Messages" UI panel
/// 4. Saves settings to persist history across app sessions
///
/// Performance: Saves after every message to prevent data loss on unexpected shutdown.
/// UI: Updates immediately for real-time feedback.
/// </remarks>
```

##### `GetTopMessages()`

```csharp
/// <summary>
/// Retrieves the top 10 most frequently used messages for UI display.
/// </summary>
/// <returns>List of formatted message strings with usage counts</returns>
/// <remarks>
/// Format: "InterfaceName=Value (FileName) (5x)"
/// Sorted by usage frequency (descending).
/// Used to populate "Most Used Messages" panel buttons.
/// </remarks>
```

##### `UpdateCommonMessagesUI()`

```csharp
/// <summary>
/// Updates the "Most Used Messages" panel with current message frequency data.
/// Creates clickable buttons for top messages.
/// </summary>
/// <remarks>
/// Process:
/// 1. Clears existing message buttons
/// 2. Gets top messages from GetTopMessages()
/// 3. Creates new buttons for each frequently used message
/// 4. Sets up click handlers to apply message values instantly
/// 5. Arranges buttons in horizontal wrap panel
///
/// Called automatically when messages are tracked and on app startup.
/// </remarks>
```

#### **Theme Management**

##### `ThemeToggleButton_Click(object? sender, RoutedEventArgs e)`

```csharp
/// <summary>
/// Toggles between Light and Dark themes and saves preference.
/// </summary>
/// <param name="sender">Button that triggered the event</param>
/// <param name="e">Event arguments</param>
/// <remarks>
/// Process:
/// 1. Calls ThemeManager.ToggleTheme() to switch themes
/// 2. Updates button text to show next available theme
/// 3. Immediately saves settings to persist preference
/// 4. Provides user feedback via warning message
/// </remarks>
```

##### `UpdateThemeButton()`

```csharp
/// <summary>
/// Updates theme toggle button text to show the next available theme.
/// </summary>
/// <remarks>
/// Button shows the theme that will be applied on next click:
/// - Shows "🌙 Dark" when current theme is Light
/// - Shows "☀️ Light" when current theme is Dark
/// </remarks>
```

#### **Settings Management**

##### `LoadAppSettings()`

```csharp
/// <summary>
/// Loads application settings from app_settings.json file.
/// Applies saved configuration including theme, directories, and message history.
/// </summary>
/// <remarks>
/// Loading process:
/// 1. Reads app_settings.json from application directory
/// 2. Deserializes JSON to AppSettings object
/// 3. Applies theme setting via ThemeManager
/// 4. Restores client and KZB directory paths
/// 5. Loads message history dictionary
/// 6. Falls back to defaults if file doesn't exist
/// 7. Attempts migration from old settings files if needed
///
/// Error handling: Gracefully handles missing or corrupted settings files.
/// </remarks>
```

##### `SaveAppSettings()`

```csharp
/// <summary>
/// Saves current application settings to app_settings.json file.
/// Persists theme, directories, and message history.
/// </summary>
/// <remarks>
/// Saves:
/// - ClientDirectory: Selected client executable path
/// - LastKzbDirectory: Last used KZB file directory
/// - MessageHistory: Message frequency tracking data
/// - Theme: Current theme preference ("Light" or "Dark")
///
/// Format: Pretty-printed JSON for readability.
/// Called frequently to prevent data loss.
/// </remarks>
```

#### **Utility Functions**

##### `AddWarning(string message)`

```csharp
/// <summary>
/// Adds a message to the warnings panel and auto-scrolls to show it.
/// Thread-safe method for providing user feedback.
/// </summary>
/// <param name="message">Message to display (supports emoji formatting)</param>
/// <remarks>
/// Features:
/// - Thread-safe: Can be called from background threads
/// - Auto-scroll: Automatically scrolls to newest message
/// - Emoji support: Supports emoji categorization for message types
/// - Real-time display: Messages appear immediately in UI
/// </remarks>
```

##### `GetClientExePath()`

```csharp
/// <summary>
/// Constructs the full path to the client executable based on selected directory.
/// </summary>
/// <returns>Full path to client executable, or empty string if no directory selected</returns>
/// <remarks>
/// Combines client directory with standard executable name: "DataSourceTestToolClient.exe"
/// Used to validate client availability and enable/disable related buttons.
/// </remarks>
```

##### `DebugState`

```csharp
/// <summary>
/// Debug property providing quick access to application state information.
/// Useful for debugging and watch expressions.
/// </summary>
/// <value>Formatted string showing current state and server status</value>
/// <remarks>
/// Format: "State: {CurrentState} | Server: {ServerStatus}"
/// Read-only property for debugging purposes.
/// </remarks>
```

---

## **TestToolServer.cs Functions**

##### `Start()`

```csharp
/// <summary>
/// Initializes TCP server on port 22207 and begins listening for client connections.
/// Sets up asynchronous connection handling to avoid blocking UI.
/// </summary>
/// <exception cref="Exception">Thrown when server cannot start (port in use, permissions, etc.)</exception>
```

##### `SendSyncCommand(string fileName, string type, string name, string value)`

```csharp
/// <summary>
/// Sends a synchronous command to the connected client.
/// </summary>
/// <param name="fileName">Target XML file name</param>
/// <param name="type">Data type (string, int, float, bool)</param>
/// <param name="name">Interface element name</param>
/// <param name="value">New value to set</param>
/// <remarks>
/// Command format: Custom protocol for client communication
/// Thread-safe: Can be called from UI thread
/// Error handling: Gracefully handles client disconnection
/// </remarks>
```

##### `WaitForClientConnection()`

```csharp
/// <summary>
/// Asynchronous method that waits for and handles client connections.
/// Runs in background thread to avoid blocking UI.
/// </summary>
/// <remarks>
/// Process:
/// 1. Accepts incoming client connections
/// 2. Stores client information (IP, executable path, connection time)
/// 3. Raises StatusChanged events for UI updates
/// 4. Maintains single client connection (new clients replace existing)
/// </remarks>
```

---

## **ReadXML.cs Functions**

##### `LoadFromDirectory(string directoryPath, List<string> warningList)`

```csharp
/// <summary>
/// Scans directory for XML files and loads interface definitions.
/// </summary>
/// <param name="directoryPath">Directory containing XML files</param>
/// <param name="warningList">List to collect parsing warnings</param>
/// <returns>Success status</returns>
/// <remarks>
/// Supported XML formats: Multiple interface definition schemas
/// Error handling: Continues processing despite individual file errors
/// Performance: Processes files in parallel where possible
/// </remarks>
```

##### `FilterData(string moduleFilter, string nameFilter)`

```csharp
/// <summary>
/// Applies filters to loaded XML data for display.
/// </summary>
/// <param name="moduleFilter">Module name filter (exact match)</param>
/// <param name="nameFilter">Interface name filter (substring match)</param>
/// <returns>Filtered DataTable for UI binding</returns>
/// <remarks>
/// Filter logic: AND combination of both filters
/// Case sensitivity: Name filter is case-insensitive
/// Performance: Uses DataTable.Select() for efficient filtering
/// </remarks>
```

---

## **ThemeManager.cs Functions**

##### `SetTheme(AppTheme theme)`

```csharp
/// <summary>
/// Applies the specified theme to the application.
/// </summary>
/// <param name="theme">Theme to apply (Light or Dark)</param>
/// <remarks>
/// Integration: Uses Avalonia's built-in theme system
/// Events: Raises ThemeChanged event for subscribers
/// Persistence: Theme choice should be saved separately
/// </remarks>
```

##### `ToggleTheme()`

```csharp
/// <summary>
/// Switches between Light and Dark themes.
/// </summary>
/// <remarks>
/// Toggle logic: Light → Dark, Dark → Light
/// Immediate effect: Theme applies instantly
/// Events: Triggers ThemeChanged event
/// </remarks>
```

---

## **Performance Optimization Recommendations**

### 1. **Reduce Settings Save Frequency**

Current: Saves after every message
Suggested: Implement debounced save (e.g., 2-second delay)

### 2. **Optimize UI Updates**

Current: UI updates on every message
Suggested: Batch UI updates using timer

### 3. **Lazy Load XML Data**

Current: Loads all XML files on connection
Suggested: Load on demand with background refresh

### 4. **Cache Filtered Results**

Current: Reapplies filters on every change
Suggested: Cache filtered results until data changes

---

This documentation provides comprehensive coverage of all major functions with their purposes, parameters, behavior, and implementation details.
