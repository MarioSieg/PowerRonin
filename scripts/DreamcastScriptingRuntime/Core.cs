using System;
using System.Diagnostics;

namespace Dreamcast
{
    /// <summary>
    /// Engine core class.
    /// </summary>
    public sealed class Core
    {
        private void OnStart()
        {
            var stopwatch = Stopwatch.StartNew();
            PrintInformation();
            Protocol.Info($"Scripting backend online! Boot took: {stopwatch.Elapsed.TotalSeconds}s!");
        }

        /// <summary>
        /// Prints some general system information from System.Environment.
        /// </summary>
        public static void PrintInformation()
        {
            Protocol.Info("C# CLR v." + Environment.Version.ToString());
            Protocol.Info("Current directory: " + Environment.CurrentDirectory);
            Protocol.Info("Is 64-bit operating system? " +  Environment.Is64BitOperatingSystem);
            Protocol.Info("Is 64-bit process? " + Environment.Is64BitProcess);
            Protocol.Info("Machine: " + Environment.MachineName);
            Protocol.Info("Operating system version: " + Environment.OSVersion.ToString());
            Protocol.Info("Processor count: " + Environment.ProcessorCount);
            Protocol.Info("System page size: " + Environment.SystemPageSize);
            Protocol.Info("Tick count: " + Environment.TickCount.ToString());
            Protocol.Info("Working set: " + Environment.WorkingSet);
            Protocol.Info("User: " + Environment.UserName);
            Protocol.Info("User domain: " + Environment.UserDomainName);
        }
    }
}
