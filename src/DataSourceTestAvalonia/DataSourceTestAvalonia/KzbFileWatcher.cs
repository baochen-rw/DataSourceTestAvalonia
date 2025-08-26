using System;
using System.IO;
using System.Threading.Tasks;
using Avalonia.Controls;
using Avalonia.Threading;

namespace DataSourceTestAvalonia;

/// <summary>
/// Handles KZB file monitoring and automatic processing when files change
/// </summary>
public class KzbFileWatcher : IDisposable
{
    private FileSystemWatcher? _fileWatcher;
    private string _watchFolder = "";
    private bool _isEnabled = false;
    private bool _disposed = false;
    private string _lastProcessedFile = "";
    private DateTime _lastProcessedTime = DateTime.MinValue;

    // Event to notify when KZB file changes are detected
    public event Func<string, Task>? KzbFileChanged;
    public event Action<string>? StatusMessage;

    /// <summary>
    /// Gets whether the watcher is currently enabled
    /// </summary>
    public bool IsEnabled => _isEnabled;

    /// <summary>
    /// Gets the currently watched folder
    /// </summary>
    public string WatchFolder => _watchFolder;

    /// <summary>
    /// Gets whether the watcher is actively monitoring (enabled and folder is valid)
    /// </summary>
    public bool IsActivelyWatching => _isEnabled && !string.IsNullOrEmpty(_watchFolder) && 
                                      Directory.Exists(_watchFolder) && _fileWatcher != null;

    /// <summary>
    /// Sets the folder to watch for KZB files
    /// </summary>
    public void SetWatchFolder(string folderPath)
    {
        if (_disposed) return;

        _watchFolder = folderPath ?? "";
        OnStatusMessage($"📂 KZB watch folder set to: {_watchFolder}");
        
        // Restart watcher if it was enabled
        if (_isEnabled)
        {
            StartWatching();
        }
    }

    /// <summary>
    /// Enables or disables the file watcher
    /// </summary>
    public void SetEnabled(bool enabled)
    {
        if (_disposed) return;

        _isEnabled = enabled;
        
        if (_isEnabled)
        {
            StartWatching();
        }
        else
        {
            StopWatching();
        }
    }

    /// <summary>
    /// Configures the watcher with folder and enabled state
    /// </summary>
    public void Configure(string watchFolder, bool enabled)
    {
        if (_disposed) return;

        _watchFolder = watchFolder ?? "";
        _isEnabled = enabled;
        
        OnStatusMessage($"📂 KZB watcher configured: Folder='{_watchFolder}', Enabled={_isEnabled}");
        
        if (_isEnabled && !string.IsNullOrEmpty(_watchFolder) && Directory.Exists(_watchFolder))
        {
            StartWatching();
        }
        else
        {
            StopWatching();
        }
    }

    /// <summary>
    /// Gets the current status for display
    /// </summary>
    public (string text, string color) GetStatus()
    {
        if (_disposed)
            return ("🔴 Disposed", "DarkRed");

        if (IsActivelyWatching)
            return ("🟢 Active", "Green");
        
        if (_isEnabled && !string.IsNullOrEmpty(_watchFolder))
            return ("🟡 Ready", "Orange");
        
        return ("🔴 Inactive", "DarkRed");
    }

    /// <summary>
    /// Starts the file system watcher
    /// </summary>
    private void StartWatching()
    {
        try
        {
            StopWatching(); // Stop any existing watcher

            if (string.IsNullOrEmpty(_watchFolder) || !Directory.Exists(_watchFolder))
            {
                OnStatusMessage($"❌ Cannot start KZB watcher: Invalid folder path");
                return;
            }

            _fileWatcher = new FileSystemWatcher
            {
                Path = _watchFolder,
                Filter = "*.kzb",
                NotifyFilter = NotifyFilters.LastWrite | NotifyFilters.FileName | NotifyFilters.CreationTime,
                IncludeSubdirectories = true, // Watch subdirectories for KZB file changes
                EnableRaisingEvents = true
            };

            _fileWatcher.Changed += OnFileSystemEvent;
            _fileWatcher.Created += OnFileSystemEvent;
            _fileWatcher.Renamed += OnFileRenamed;

            OnStatusMessage($"🔍 KZB file watcher started for: {_watchFolder} (including subdirectories)");
        }
        catch (Exception ex)
        {
            OnStatusMessage($"❌ Error starting KZB watcher: {ex.Message}");
        }
    }

    /// <summary>
    /// Stops the file system watcher
    /// </summary>
    private void StopWatching()
    {
        try
        {
            if (_fileWatcher != null)
            {
                _fileWatcher.EnableRaisingEvents = false;
                _fileWatcher.Changed -= OnFileSystemEvent;
                _fileWatcher.Created -= OnFileSystemEvent;
                _fileWatcher.Renamed -= OnFileRenamed;
                _fileWatcher.Dispose();
                _fileWatcher = null;
                OnStatusMessage("⏹️ KZB file watcher stopped");
            }
        }
        catch (Exception ex)
        {
            OnStatusMessage($"❌ Error stopping KZB watcher: {ex.Message}");
        }
    }

    /// <summary>
    /// Handles file system events (Created/Changed)
    /// </summary>
    private async void OnFileSystemEvent(object sender, FileSystemEventArgs e)
    {
        try
        {
            // Prevent duplicate processing of the same file within 5 seconds
            string filePath = e.FullPath;
            DateTime now = DateTime.Now;
            
            if (_lastProcessedFile == filePath && (now - _lastProcessedTime).TotalSeconds < 5)
            {
                OnStatusMessage($"🔄 Skipping duplicate event for: {Path.GetFileName(filePath)}");
                return;
            }
            
            _lastProcessedFile = filePath;
            _lastProcessedTime = now;
            
            // Debounce file events - wait for file operations to complete
            await Task.Delay(500);
            
            await Dispatcher.UIThread.InvokeAsync(async () =>
            {
                OnStatusMessage($"📁 KZB file detected: {Path.GetFileName(e.FullPath)}");
                OnStatusMessage($"🔄 Auto-triggering KZB processing...");
                
                // Notify subscribers about the file change
                if (KzbFileChanged != null)
                {
                    await KzbFileChanged.Invoke(e.FullPath);
                }
            });
        }
        catch (Exception ex)
        {
            await Dispatcher.UIThread.InvokeAsync(() =>
            {
                OnStatusMessage($"❌ Error processing KZB file change: {ex.Message}");
            });
        }
    }

    /// <summary>
    /// Handles file rename events
    /// </summary>
    private async void OnFileRenamed(object sender, RenamedEventArgs e)
    {
        try
        {
            // Prevent duplicate processing of the same file within 5 seconds
            string filePath = e.FullPath;
            DateTime now = DateTime.Now;
            
            if (_lastProcessedFile == filePath && (now - _lastProcessedTime).TotalSeconds < 5)
            {
                OnStatusMessage($"🔄 Skipping duplicate rename event for: {Path.GetFileName(filePath)}");
                return;
            }
            
            _lastProcessedFile = filePath;
            _lastProcessedTime = now;
            
            await Task.Delay(500);
            
            await Dispatcher.UIThread.InvokeAsync(async () =>
            {
                OnStatusMessage($"📁 KZB file renamed: {Path.GetFileName(e.OldName)} → {Path.GetFileName(e.FullPath)}");
                OnStatusMessage($"🔄 Auto-triggering KZB processing...");
                
                // Notify subscribers about the file change
                if (KzbFileChanged != null)
                {
                    await KzbFileChanged.Invoke(e.FullPath);
                }
            });
        }
        catch (Exception ex)
        {
            await Dispatcher.UIThread.InvokeAsync(() =>
            {
                OnStatusMessage($"❌ Error processing KZB file rename: {ex.Message}");
            });
        }
    }

    /// <summary>
    /// Raises the StatusMessage event
    /// </summary>
    private void OnStatusMessage(string message)
    {
        StatusMessage?.Invoke(message);
    }

    /// <summary>
    /// Disposes of the file watcher resources
    /// </summary>
    public void Dispose()
    {
        if (!_disposed)
        {
            StopWatching();
            _disposed = true;
        }
    }
}
