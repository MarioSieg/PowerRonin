namespace Dreamcast.Core
{
    /// <summary>
    ///     Contains all supported graphics APIs.
    /// </summary>
    public enum GraphicsAPI
    {
        /// <summary>
        ///     Windows only.
        /// </summary>
        Direct3D11,

        /// <summary>
        ///     Windows only.
        /// </summary>
        Direct3D12,

        /// <summary>
        ///     Mac only.
        /// </summary>
        Metal,

        /// <summary>
        ///     Cross platform.
        /// </summary>
        Vulkan,

        /// <summary>
        ///     Cross platform.
        /// </summary>
        OpenGL
    }
}