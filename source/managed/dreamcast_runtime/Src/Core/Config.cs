using System;
using System.IO;

namespace Dreamcast.Core
{
    /// <summary>
    ///     Contains all configuration variables.
    /// </summary>
    public sealed partial class Config
    {
        /// <summary>
        ///     The name of the directory where configs are saved in.
        /// </summary>
        public const string ConfigDirectory = "config";

        /// <summary>
        ///     Display config.
        /// </summary>
        public DisplayConfig Display { get; set; }

        /// <summary>
        ///     System overlay config.
        /// </summary>
        public EditorConfig Editor { get; set; }

        /// <summary>
        ///     Graphics config.
        /// </summary>
        public GraphicsConfig Graphics { get; set; }

        /// <summary>
        ///     Serializes all configs into their files.
        /// </summary>
        public void Serialize()
        {
            try
            {
                if (!Directory.Exists(ConfigDirectory))
                    Directory.CreateDirectory(ConfigDirectory);
                Serializer.SerializeToJsonFile(Display, DisplayConfig.FilePath);
                Serializer.SerializeToJsonFile(Editor, EditorConfig.FilePath);
                Serializer.SerializeToJsonFile(Graphics, GraphicsConfig.FilePath);
            }
            catch (Exception ex)
            {
                Protocol.Error("Failed to serialize config: " + ex);
            }
        }

        /// <summary>
        ///     Deserializes all configs from their files.
        /// </summary>
        public void Deserialize()
        {
            if (!Directory.Exists(ConfigDirectory))
            {
                Serialize();
                return;
            }

            try
            {
                Display = Serializer.DeserializeFromJsonFile(DisplayConfig.FilePath, DefaultEditorSettings.Display);
                Editor = Serializer.DeserializeFromJsonFile(EditorConfig.FilePath, DefaultEditorSettings.Editor);
                Graphics = Serializer.DeserializeFromJsonFile(GraphicsConfig.FilePath, DefaultEditorSettings.Graphics);
            }
            catch (Exception ex)
            {
                Protocol.Error("Failed to deserialize config: " + ex);
                Serialize();
                Protocol.Info("Serialized default config.");
            }
        }

        /// <summary>
        ///     Apply all settings to take effect.
        /// </summary>
        public void ApplyAll()
        {
            Display.Apply();
            Editor.Apply();
            Graphics.Apply();
        }
    }
}