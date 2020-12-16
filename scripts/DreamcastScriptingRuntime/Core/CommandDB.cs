// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

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
        public static List<Command> RegisteredCommands { get; set; } = new List<Command>();

        /// <summary>
        ///     The history of commands entered.
        /// </summary>
        public static List<Tuple<string, double>> CommandHistory { get; } = new List<Tuple<string, double>>();

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
                }
            });
        }

        /// <summary>
        ///     Executes the command.
        /// </summary>
        /// <param name="commandText">The command text to execute.</param>
        public static void Execute(string commandText)
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

                // Call executor delegate:
                command.executor(cleanedCommand);

                // Converts ticks to nanoseconds:
                double frequency = Stopwatch.Frequency;
                double ticks = stopwatch.ElapsedTicks;
                var milliseconds = ticks / frequency * 1000.0;

                // Add it to history with the time elapsed.
                CommandHistory.Add(new Tuple<string, double>(commandText, milliseconds));
                return;
            }

            Protocol.Warn("Command not found: " + commandText);
        }

        [CalledFromNativeRuntime]
        private static void OnCommandEnter(string commandText)
        {
            Execute(commandText);
        }
    }
}