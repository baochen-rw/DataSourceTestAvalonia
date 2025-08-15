using System;
using System.Net.Sockets;
using System.Threading.Tasks;
using System.Text;
using System.Net;

namespace DataSourceTestAvalonia
{
    /// <summary>
    /// Basic TCP server that sends commands to connected clients
    /// </summary>
    public class TestToolServer
    {
        private TcpListener? server;
        private TcpClient? client;
        private NetworkStream? stream;

        // Store client information
        public string? ClientIPAddress { get; private set; }
        public string? ClientExecutablePath { get; private set; }
        public DateTime? ClientConnectedTime { get; private set; }

        public event Action<string>? StatusChanged;

        public void Start()
        {
            try
            {
                server = new TcpListener(System.Net.IPAddress.Any, 22207);
                server.Start();
                Task.Run(WaitForClients);
                UpdateStatus("Server started - waiting for connection");
                async void WaitForClients()
                {
                    while (server != null)
                    {
                        try
                        {
                            UpdateStatus("Server started - waiting for connection");
                            client = await server.AcceptTcpClientAsync();
                            stream = client.GetStream();

                            // Store client connection information
                            ClientConnectedTime = DateTime.Now;

                            // Get client IP address
                            if (client.Client.RemoteEndPoint is IPEndPoint remoteEndPoint)
                            {
                                ClientIPAddress = remoteEndPoint.Address.ToString();
                            }

                            UpdateStatus($"Client connected from {ClientIPAddress}");
                            if (!string.IsNullOrEmpty(ClientExecutablePath))
                            {
                                UpdateStatus($"Client executable detected: {ClientExecutablePath}");
                            }

                            // Wait for client to disconnect, then loop back to wait for new connections
                            await WaitForDisconnection();
                        }
                        catch (Exception ex)
                        {
                            if (server != null) // Only log if server is still running
                            {
                                UpdateStatus($"Connection error: {ex.Message}");
                                await Task.Delay(1000); // Wait a bit before trying again
                            }
                        }
                    }
                }

                async Task WaitForDisconnection()
                {
                    try
                    {
                        if (client != null && stream != null)
                        {
                            // Monitor the connection more reliably
                            var buffer = new byte[1024];
                            while (client.Connected)
                            {
                                try
                                {
                                    // Use a timeout to detect disconnection more quickly
                                    var readTask = stream.ReadAsync(buffer, 0, buffer.Length);
                                    var timeoutTask = Task.Delay(1000); // 1 second timeout

                                    var completedTask = await Task.WhenAny(readTask, timeoutTask);

                                    if (completedTask == readTask)
                                    {
                                        var result = await readTask;
                                        if (result == 0)
                                        {
                                            break; // Client disconnected
                                        }
                                        // If we received data, process it if needed
                                    }
                                    else
                                    {
                                        // Timeout occurred, check if client is still connected
                                        if (!IsClientConnected())
                                        {
                                            break;
                                        }
                                    }
                                }
                                catch
                                {
                                    break; // Connection lost
                                }
                            }
                        }
                    }
                    catch { }
                    finally
                    {
                        UpdateStatus("Client disconnected - waiting for new connection");
                        ClientIPAddress = null;
                        ClientExecutablePath = null;
                        ClientConnectedTime = null;

                        // Clean up client connection
                        try
                        {
                            stream?.Close();
                            client?.Close();
                        }
                        catch { }
                        stream = null;
                        client = null;
                    }
                }

                bool IsClientConnected()
                {
                    try
                    {
                        if (client?.Client == null) return false;

                        // Check if socket is still connected
                        return !(client.Client.Poll(1, SelectMode.SelectRead) && client.Client.Available == 0);
                    }
                    catch
                    {
                        return false;
                    }
                }
            }
            catch (Exception ex)
            {
                UpdateStatus($"Server failed: {ex.Message}");
            }
        }

        private void UpdateStatus(string message)
        {
            StatusChanged?.Invoke(message);
        }

        public bool SendCommand(string message)
        {
            try
            {
                if (stream != null && client?.Connected == true)
                {
                    byte[] data = Encoding.UTF8.GetBytes(message);
                    stream.Write(data, 0, data.Length);
                    return true;
                }
            }
            catch
            {
                UpdateStatus("Send failed - client disconnected");
            }
            return false;
        }

        /// <summary>
        /// Send sync command: "SYNC::file::type::name::value"
        /// </summary>
        public bool SendSyncCommand(string file, string type, string name, string value)
        {
            return SendCommand($"SYNC::{file}::{type}::{name}::{value}");
        }

        /// <summary>
        /// Send async command: "ASYNC::file::type::name::value"
        /// </summary>
        public bool SendAsyncCommand(string file, string type, string name, string value)
        {
            return SendCommand($"ASYNC::{file}::{type}::{name}::{value}");
        }

        /// <summary>
        /// Send screenshot command: "SCREENSHOT::filename"
        /// </summary>
        public bool SendScreenshotCommand(string filePath)
        {
            return SendCommand($"SCREENSHOT::{filePath}");
        }

        /// <summary>
        /// Close everything
        /// </summary>
        public void Close()
        {
            try
            {
                stream?.Close();
                client?.Close();
                server?.Stop();
                UpdateStatus("Server stopped");
            }
            catch { }
        }

    }
}
