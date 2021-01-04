using System;
using System.Runtime.InteropServices;

namespace PowerRonin.Core
{
    /// <summary>
    ///     Utils and helper class.
    /// </summary>
    public static class Helper
    {
        /// <summary>
        ///     The current platform.
        /// </summary>
        public static readonly Platform CurrentPlatform = DetermineCurrentPlatform();

        /// <summary>
        /// </summary>
        public static GraphicsApi SmartDetermineGraphicsApi(bool preferModern = false)
        {
            switch (CurrentPlatform)
            {
                case Platform.Windows:
                    return preferModern ? GraphicsApi.Direct3D12 : GraphicsApi.Direct3D11;
                case Platform.Linux:
                    return preferModern ? GraphicsApi.Vulkan : GraphicsApi.OpenGl;
                case Platform.Mac:
                    return preferModern ? GraphicsApi.Metal : GraphicsApi.OpenGl;
                default:
                    return GraphicsApi.OpenGl;
            }
        }

        private static Platform DetermineCurrentPlatform()
        {
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows)) return Platform.Windows;
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux)) return Platform.Linux;
            if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX)) return Platform.Mac;

            throw new Exception("Unknown runtime platform!");
        }
    }
}