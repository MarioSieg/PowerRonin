using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Net.Sockets;
using Dreamcast.Mathematics;
using Dreamcast.Tools;

namespace Dreamcast.Core
{
    /// <summary>
    ///     Contains command functionality.
    /// </summary>
    public static class CommandDB
    {
        /// <summary>
        ///     All currently registered commands.
        /// </summary>
        public static List<Command> RegisteredCommands { get; set; } = new();

        /// <summary>
        ///     The history of commands entered.
        /// </summary>
        public static List<Tuple<string, double>> CommandHistory { get; } = new();

        /// <summary>
        ///     Registers most basic common commands.
        /// </summary>
        public static void RegisterCommonCommands()
        {
            RegisteredCommands.AddRange(new[]
            {
                new Command
                {
                    name = "help",
                    brief = "Displays some help.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate
                    {
                        for (var i = 0; i < RegisteredCommands.Count; ++i)
                            Protocol.Info($"Command {i}: {RegisteredCommands[i]}");
                    }
                },
                new Command
                {
                    name = "flush",
                    brief = "Clears the terminal and writes it into a log file.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate { Protocol.Flush(); }
                },
                new Command
                {
                    name = "echo",
                    brief = "Writes the command into the terminal.",
                    parameterCount = 1,
                    requiresRootPrivileges = false,
                    executor = Protocol.Info
                },
                new Command
                {
                    name = "history",
                    brief = "Displays all commands history with execution time.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate
                    {
                        foreach (var (item1, item2) in CommandHistory) Protocol.Info($"{item1} -> {item2}ms");
                    }
                },
                new Command
                {
                    name = "clear_history",
                    brief = "Clears the command history.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate
                    {
                        var size = CommandHistory.Count;
                        CommandHistory.Clear();
                        Protocol.Info($"Removed {size} items from history!");
                    }
                },
                new Command
                {
                    name = "info",
                    brief = "Prints some basic system info.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate
                    {
                        Protocol.Info("C# CLR v." + Environment.Version);
                        Protocol.Info("Current directory: " + Environment.CurrentDirectory);
                        Protocol.Info("Machine: " + Environment.MachineName);
                        Protocol.Info("Operating system version: " + Environment.OSVersion);
                        Protocol.Info("Logical cores: " + Environment.ProcessorCount);
                        Protocol.Info("User: " + Environment.UserName);
                    }
                },
                new Command
                {
                    name = "env",
                    brief = "Displays all environment variables.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate
                    {
                        foreach (DictionaryEntry entry in Environment.GetEnvironmentVariables())
                        {
                            var name = (string) entry.Key;
                            var value = (string) entry.Value;
                            Protocol.Info(name + " = " + value);
                        }
                    }
                },
                new Command
                {
                    name = "list_dir",
                    brief = "Recursively lists all files and folders in the current working directory",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate
                    {
                        var files = Directory.GetFiles(Directory.GetCurrentDirectory(), "*",
                            SearchOption.AllDirectories);
                        foreach (var file in files) Protocol.Info(file);
                    }
                },
                new Command
                {
                    name = "test_math_format",
                    brief = "Prints all math structures to test correct formatting.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate
                    {
                        var angle = new AngleSingle(30.0f, AngleType.Degree);
                        Protocol.Info($"{nameof(angle)}: {angle}");

                        var boundingBox = new BoundingBox(Vector3.Zero, Vector3.One);
                        Protocol.Info($"{nameof(boundingBox)}: {boundingBox}");

                        var boundingFrustum = new BoundingFrustum(Matrix4x4.Identity);
                        Protocol.Info($"{nameof(boundingFrustum)}: {boundingFrustum}");

                        var boundingSphere = new BoundingSphere(Vector3.Zero, 1.0f);
                        Protocol.Info($"{nameof(boundingSphere)}: {boundingSphere}");

                        var color = Color.BlueViolet;
                        Protocol.Info($"{color.GetType()}: {color}");

                        var color3 = Color.BlueViolet;
                        Protocol.Info($"{color3.GetType()}: {color3}");

                        var color4 = Color.BlueViolet;
                        Protocol.Info($"{color4.GetType()}: {color4}");

                        var colorRgba = Color.BlueViolet;
                        Protocol.Info($"{colorRgba.GetType()}: {colorRgba}");

                        var half = new Half((float) Math.PI);
                        Protocol.Info($"{half.GetType()}: {half}");

                        var half2 = new Half2((float) Math.PI, (float) Math.PI);
                        Protocol.Info($"{half2.GetType()}: {half2}");

                        var half3 = new Half3((float) Math.PI, (float) Math.PI, (float) Math.PI);
                        Protocol.Info($"{half3.GetType()}: {half3}");

                        var half4 = new Half4((float) Math.PI, (float) Math.PI, (float) Math.PI, (float) Math.PI);
                        Protocol.Info($"{half4.GetType()}: {half4}");

                        var mat3x2 = Matrix3x2.Identity;
                        Protocol.Info($"{mat3x2.GetType()}: {mat3x2}");

                        var mat3x3 = Matrix3x3.Identity;
                        Protocol.Info($"{mat3x3.GetType()}: {mat3x3}");

                        var mat4x4 = Matrix4x4.Identity;
                        Protocol.Info($"{mat4x4.GetType()}: {mat4x4}");

                        var mat5x4 = Matrix5x4.Identity;
                        Protocol.Info($"{mat5x4.GetType()}: {mat5x4}");

                        var oob = new OrientedBoundingBox(Vector3.Zero, Vector3.One);
                        Protocol.Info($"{oob.GetType()}: {oob}");

                        var plane = new Plane(Vector3.Zero, Vector3.One);
                        Protocol.Info($"{plane.GetType()}: {plane}");

                        var point = new Point(0, 1);
                        Protocol.Info($"{point.GetType()}: {point}");

                        var quaternion = Quaternion.Identity;
                        Protocol.Info($"{quaternion.GetType()}: {quaternion}");

                        var ray = new Ray(Vector3.Zero, Vector3.ForwardLH);
                        Protocol.Info($"{ray.GetType()}: {ray}");

                        var rect = Rectangle.Empty;
                        Protocol.Info($"{rect.GetType()}: {rect}");

                        var rectf = RectangleF.Empty;
                        Protocol.Info($"{rectf.GetType()}: {rectf}");

                        var size2 = Size2.Zero;
                        Protocol.Info($"{size2.GetType()}: {size2}");

                        var size2f = Size2.Zero;
                        Protocol.Info($"{size2f.GetType()}: {size2f}");

                        var vec2 = Vector2.Zero;
                        Protocol.Info($"{vec2.GetType()}: {vec2}");

                        var vec3 = Vector3.Zero;
                        Protocol.Info($"{vec3.GetType()}: {vec3}");

                        var vec3i = Vector3I.Zero;
                        Protocol.Info($"{vec3i.GetType()}: {vec3i}");

                        var vec4 = Vector4.Zero;
                        Protocol.Info($"{vec4.GetType()}: {vec4}");

                        var vec4i = Vector4I.Zero;
                        Protocol.Info($"{vec4i.GetType()}: {vec4i}");

                        var viewport = new Viewport(1, 2, 3, 4);
                        Protocol.Info($"{viewport.GetType()}: {viewport}");

                        var viewportf = new ViewportF(1, 2, 3, 4);
                        Protocol.Info($"{viewportf.GetType()}: {viewportf}");
                    }
                },
                new Command
                {
                    name = "args",
                    brief = "Prints the command line arguments.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate
                    {
                        var args = Environment.GetCommandLineArgs();
                        if (args.Length == 0)
                        {
                            Protocol.Info("No cli args!");
                            return;
                        }

                        for (var i = 0; i < args.Length; ++i) Protocol.Info($"Arg {i}: {args[i]}");
                    }
                },
                new Command
                {
                    name = "drives",
                    brief = "Prints all logical drives.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate
                    {
                        foreach (var drive in Environment.GetLogicalDrives()) Protocol.Info("Drive " + drive);
                    }
                },
                new Command
                {
                    name = "gc",
                    brief = "Print some garbage collector info.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate
                    {
                        Protocol.Info("Max generation: " + GC.MaxGeneration);
                        Protocol.Info("Total memory: " + GC.GetTotalMemory(false) + "B");
                    }
                },
                new Command
                {
                    name = "ip",
                    brief = "Print the local ip.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate
                    {
                        string? localIp;
                        using (var socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, 0))
                        {
                            socket.Connect("8.8.8.8", 65530);
                            var endPoint = socket.LocalEndPoint as IPEndPoint;
                            localIp = endPoint?.Address.ToString();
                        }

                        Protocol.Info("Local IP: " + localIp);
                    }
                },
                new Command
                {
                    name = "config",
                    brief = "Prints the system config.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate
                    {
                        Protocol.Info(Configuration.DisplayConfiguration.FilePath + ":\n" +
                                      Serializer<Configuration.DisplayConfiguration>.SerializeToJsonString(Configuration
                                          .Current.Display));
                        Protocol.Info(Configuration.OverlayConfiguration.FilePath + ":\n" +
                                      Serializer<Configuration.OverlayConfiguration>.SerializeToJsonString(Configuration
                                          .Current.Overlay));
                        Protocol.Info(Configuration.GraphicsConfiguration.FilePath + ":\n" +
                                      Serializer<Configuration.GraphicsConfiguration>.SerializeToJsonString(
                                          Configuration.Current.Graphics));
                    }
                },
                new Command
                {
                    name = "config_apply",
                    brief = "Applies the whole config to all systems.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate { Configuration.Current.Apply(); }
                },
                new Command
                {
                    name = "config_load",
                    brief = "Loads the current config from the config file.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate { Configuration.Deserialize(); }
                },
                new Command
                {
                    name = "config_save",
                    brief = "Saves the current config to the config file.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate { Configuration.Serialize(); }
                },
                new Command
                {
                    name = "config_rem",
                    brief = "Deletes the config files.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate { Directory.Delete(Configuration.ConfigDirectory, true); }
                },
                new Command
                {
                    name = "deploy_editor",
                    brief = "Builds the editor into the \"bin\" folder.",
                    parameterCount = 0,
                    requiresRootPrivileges = false,
                    executor = delegate { Builder.BuildEditorStandalone(); }
                }
            });
        }

        /// <summary>
        ///     Executes the command.
        /// </summary>
        /// <param name="commandText">The command text to execute.</param>
        public static void Execute(string commandText)
        {
            try
            {
                // Setup stopwatch to measure time:
                var stopwatch = Stopwatch.StartNew();

                // Search command:
                foreach (var command in RegisteredCommands)
                {
                    // Not this command:
                    if (!commandText.StartsWith(command.name)) continue;

                    // Remove the command itself from the string;
                    var cleanedCommand = commandText.Replace(command.name, string.Empty);

                    if (command.parameterCount > 0 && string.IsNullOrWhiteSpace(cleanedCommand))
                    {
                        Protocol.Warn("Missing parameter for command: " + command);
                        return;
                    }

                    // Print command for logging:
                    Protocol.Trace(commandText);

                    // Call executor delegate:
                    command.executor(cleanedCommand);

                    // Converts ticks to milliseconds.
                    double frequency = Stopwatch.Frequency;
                    double ticks = stopwatch.ElapsedTicks;
                    var milliseconds = ticks / frequency * 1000.0;

                    // Add it to history with the time elapsed.
                    CommandHistory.Add(new Tuple<string, double>(commandText, milliseconds));
                    return;
                }

                Protocol.Warn("Command not found: " + commandText);
            }
            catch (Exception ex)
            {
                Protocol.Error("Failed to execute command!");
                Protocol.Error(ex.Message);
            }
        }

        [CalledFromNativeRuntime]
        private static void OnCommandEnter(string commandText)
        {
            Execute(commandText);
        }
    }
}