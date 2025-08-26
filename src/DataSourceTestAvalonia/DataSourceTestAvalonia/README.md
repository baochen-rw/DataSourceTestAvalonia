# Data Source Test Tool

## Overview

The **Data Source Test Tool** is a desktop application built with Avalonia UI for testing and debugging XML-based data source configurations. It acts as a server that communicates with external clients over TCP, allowing real-time modification of XML interface values and monitoring of session changes.

### Key Features

- **TCP Server Communication**: Establishes a connection with external client applications on port 22207
- **Real-time XML Data Editing**: Interactive data grid for modifying XML interface values
- **Session Management**: Tracks changes made during testing sessions without modifying source files
- **Message History**: Automatically tracks frequently used messages for quick access
- **Precondition Loading**: Supports loading predefined test scenarios from XML files
- **Theme Support**: Light/Dark theme toggle with persistent settings
- **File Management**: Automated DLL and client file copying capabilities

---

## User Interface Components

### Status Section (Top Row)

- **Server Status**: Shows current server state (Initializing/Ready/Running/Error)
- **Client Status**: Displays client connection status
- **Browse Client**: Select client executable directory
- **Start Client**: Launch the selected client application
- **Resend Messages**: Resend all session changes to connected client
- **Clear Session**: Reset all session changes
- **New KZB**: Update client with new KZB files
- **Theme Toggle**: Switch between Light/Dark themes
- **Directory Label**: Shows current client directory with context menu to open in Explorer

### Control Panel (Second Row)

- **Module Filter**: ComboBox to filter interfaces by module
- **Interface Name Filter**: TextBox to filter interfaces by name
- **Precondition**: ComboBox to select precondition files
- **Load Button**: Execute selected precondition
- **Screenshot**: Capture client screenshot
- **Copy DLL Files**: Copy both standard and saved DLL files to client directory
- **Client.exe**: Copy client executable to selected directory

### Most Used Messages Panel (Third Row)

- **Real-time Display**: Shows top 10 most frequently used manual messages
- **Click to Apply**: Click any message button to instantly apply that value
- **Auto-refresh**: Updates automatically as new messages are sent
- **Clear History**: Reset message frequency tracking

### Main Data Grid (Center)

- **Interactive Editing**: Double-click cells to modify values
- **Column Sorting**: Click headers to sort data
- **Real-time Updates**: Changes immediately sent to connected client
- **Type-aware**: Handles different data types (string, int, float, bool)

### Session Changes Panel (Bottom Center)

- **4-Column Layout**: Displays modified values in organized grid
- **Visual Feedback**: Highlights changed values with distinct formatting
- **Scrollable**: Handles large numbers of changes efficiently

### Warnings/Log Panel (Bottom)

- **Real-time Logging**: Shows all application events and errors
- **Auto-scroll**: Automatically scrolls to newest messages
- **Emoji Indicators**: Uses emojis for visual categorization of message types

---

## Button Functionality Reference

| Button                  | Function                | Enabled When          | Description                                                   |
| ----------------------- | ----------------------- | --------------------- | ------------------------------------------------------------- |
| **Browse Client**       | Select client directory | Always                | Opens folder browser to select client executable location     |
| **Start Client**        | Launch client process   | Always                | Starts the client application if executable exists            |
| **Resend Messages**     | Resend session changes  | Client connected      | Sends all modified values to client again                     |
| **Clear Session**       | Reset session data      | Always                | Clears all session changes and reloads original data          |
| **New KZB**             | Update client files     | Valid client selected | Copies new KZB files and restarts client                      |
| **🌙/☀️ Theme**         | Toggle theme            | Always                | Switches between Light and Dark themes                        |
| **Load (Precondition)** | Execute precondition    | Precondition selected | Loads and executes selected precondition file                 |
| **Screenshot**          | Capture screen          | Client connected      | Takes screenshot of client application                        |
| **Copy DLL Files**      | Copy DLL files          | Always                | Copies both standard and saved DLL files to client            |
| **Client.exe**          | Copy executable         | Always                | Copies client executable files to selected directory          |
| **↻ Refresh**           | Update message list     | Always                | Manually refreshes most used messages (normally auto-updates) |
| **🗑️ Clear**            | Clear message history   | Always                | Resets message frequency tracking                             |

---

## File Structure and Functionality

### Core Application Files

#### **MainWindow.axaml.cs** (1,688 lines)

**Primary application logic and UI management**

**Key Classes:**

- `XmlDataItem`: Data model for grid items (FileName, Name, Type, Value)
- `AppSettings`: Configuration model (ClientDirectory, LastKzbDirectory, MessageHistory, Theme)
- `MainWindow`: Main application window and logic controller

**Core Functionality:**

- UI event handling and state management
- TCP server communication coordination
- XML data loading and filtering
- Session change tracking
- Settings persistence (JSON format)
- Message history management

**Key Methods:**

- `InitializeApplication()`: Sets up UI bindings and event handlers
- `HandleStateChange()`: Manages UI state based on application status
- `SendToClient()`: Sends commands to connected client
- `LoadInterfacesFromClientFolder()`: Loads XML interface files
- `TrackMessageInHistory()`: Records frequently used messages
- `SaveAppSettings()/LoadAppSettings()`: Persistent configuration management

#### **TestToolServer.cs** (220 lines)

**TCP server implementation for client communication**

**Key Features:**

- Listens on port 22207 for incoming connections
- Maintains single client connection
- Handles command sending and client status tracking
- Provides connection events for UI updates

**Key Methods:**

- `Start()`: Initializes and starts TCP server
- `SendSyncCommand()`: Sends commands to connected client
- `WaitForClientConnection()`: Asynchronous client connection handling
- `Close()`: Cleanup and connection termination

#### **ReadXML.cs** (255 lines)

**XML file parsing and data extraction**

**Key Features:**

- Parses XML interface definition files
- Extracts module and interface information
- Builds DataTable for UI binding
- Handles multiple XML file formats

**Key Methods:**

- `LoadFromDirectory()`: Scans directory for XML files
- `ProcessXmlFile()`: Parses individual XML files
- `ExtractModuleList()`: Builds module filter list
- `FilterData()`: Applies module and name filters

#### **ThemeManager.cs** (82 lines)

**Theme management system**

**Key Features:**

- Singleton pattern for global theme management
- Light/Dark theme support
- Avalonia theme integration
- Theme change notifications

**Key Methods:**

- `SetTheme()`: Apply specific theme
- `ToggleTheme()`: Switch between themes
- `GetThemeDisplayName()`: UI-friendly theme names

#### **AppState.cs** (16 lines)

**Application state enumeration**

```csharp
public enum AppState
{
    Initializing,    // Application starting up
    ServerStarted,   // TCP server ready for connections
    ClientConnected, // Client successfully connected
    ClientDisconnected, // Client disconnected
    Error           // Error state
}
```

### Configuration Files

#### **app_settings.json**

**Persistent application settings**

```json
{
  "ClientDirectory": "path/to/client",
  "LastKzbDirectory": "path/to/kzb",
  "MessageHistory": {
    "InterfaceName=Value (FileName)": frequency_count
  },
  "Theme": "Light" // or "Dark"
}
```

### External Dependencies

#### **FileTransferHelper.dll**

**Utility library for file operations**

- Handles complex file copying scenarios
- Provides enhanced file transfer capabilities

---

## Application Workflow

### 1. **Startup Sequence**

```
Initialize UI Components
↓
Load Settings (app_settings.json)
↓
Apply Theme
↓
Create Required Directories
↓
Start TCP Server (Port 22207)
↓
Wait for Client Connection
```

### 2. **Client Connection Flow**

```
Client Connects
↓
Load XML Interface Files
↓
Populate Data Grid
↓
Enable UI Controls
↓
Ready for Testing
```

### 3. **Testing Session Flow**

```
User Modifies Values in Grid
↓
Track in Message History (if manual)
↓
Send to Connected Client
↓
Record in Session Changes
↓
Auto-save Settings
```

### 4. **Precondition Execution**

```
Select Precondition File
↓
Parse XML Commands
↓
Execute Commands with Delays
↓
Update Session Display
↓
(Skip Message History Tracking)
```

---

## Technical Implementation Details

### **State Management**

The application uses a centralized state system (`AppState` enum) that controls UI behavior:

- **UI Control Enabling/Disabling**: Based on current state
- **Button Availability**: Context-sensitive button states
- **Status Display**: Real-time status updates

### **Data Flow Architecture**

```
XML Files → ReadXML Parser → ObservableCollection → DataGrid → UI
                                    ↓
Session Changes ← SendToClient ← User Edits ← Cell Editing
                                    ↓
TCP Client ← TestToolServer ← Command Queue
```

### **Message History System**

- **Tracking**: Only manual edits (excludes preconditions)
- **Storage**: Persistent JSON with frequency counts
- **Display**: Top 10 most used, auto-refreshing UI
- **Performance**: Immediate save on each message

### **Error Handling Strategy**

- **Comprehensive Try-Catch**: All major operations wrapped
- **User-Friendly Messages**: Emoji-categorized warnings
- **Graceful Degradation**: Application continues despite errors
- **Debug Information**: Detailed console output for troubleshooting

---

## Usage Scenarios

### **Scenario 1: Basic Testing**

1. Start application
2. Browse and select client directory
3. Start client application
4. Modify values in data grid
5. Observe changes in client
6. Use session changes panel to review modifications

### **Scenario 2: Precondition Testing**

1. Ensure client is connected
2. Select precondition from dropdown
3. Click "Load" button
4. Watch automated command execution
5. Verify client receives all commands
6. Review session changes (preconditions don't affect message history)

### **Scenario 3: Frequent Value Testing**

1. Perform manual testing over time
2. Observe most used messages panel populate
3. Click frequently used message buttons for quick access
4. Use message history for regression testing

### **Scenario 4: Theme Customization**

1. Click theme toggle button to switch themes
2. Settings automatically saved
3. Theme persists across application restarts

---

## Troubleshooting

### **Common Issues**

**Client Won't Connect**

- Verify client is configured for port 22207
- Check firewall settings
- Ensure no other application is using the port

**XML Files Not Loading**

- Verify XML files are in client directory
- Check XML file format and structure
- Review warning panel for parsing errors

**Theme Not Persisting**

- Check write permissions for application directory
- Verify app_settings.json is being created/updated
- Review warnings panel for save errors

**Performance Issues**

- Large XML files may cause slow loading
- Consider filtering interfaces by module
- Message history auto-save may impact performance with high-frequency changes

### **Log Analysis**

The warnings panel provides real-time feedback with emoji categorization:

- ✅ Success operations
- ❌ Error conditions
- ⚠️ Warnings requiring attention
- 🔄 Processing operations
- 💾 File operations
- 🎨 Theme changes
- 📂 Directory operations

---

## Development Notes

### **Code Organization**

- **Single Responsibility**: Each class has a focused purpose
- **Event-Driven Architecture**: UI updates through event handlers
- **Observable Collections**: Automatic UI binding updates
- **Dependency Injection**: Services injected where needed

### **Performance Considerations**

- **Lazy Loading**: XML files loaded only when needed
- **Efficient Filtering**: DataTable-based filtering for large datasets
- **Memory Management**: Proper disposal of resources
- **Background Operations**: Async methods for long-running tasks

### **Extensibility Points**

- **New File Formats**: Extend ReadXML for additional formats
- **Additional Themes**: Extend ThemeManager for custom themes
- **Protocol Extensions**: Expand TestToolServer for new commands
- **UI Enhancements**: Add new panels through MainWindow

---

This documentation provides a comprehensive overview of the Data Source Test Tool's functionality, architecture, and usage patterns. The application serves as a robust testing platform for XML-based data source configurations with an intuitive user interface and powerful automation capabilities.
