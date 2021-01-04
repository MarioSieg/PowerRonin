using System;
using System.Collections.Generic;
using System.IO;

namespace PowerRonin.Core
{
    /// <summary>
    ///     Represents the type a required item.
    ///     Can be a file or a dir.
    /// </summary>
    public enum RequiredItemType
    {
        /// <summary>
        ///     A directory is required.
        /// </summary>
        Directory,

        /// <summary>
        ///     A file is required.
        /// </summary>
        File
    }

    /// <summary>
    ///     Action to do if an important item is missing.
    /// </summary>
    public enum MissingAction
    {
        /// <summary>
        ///     Create the file or directory.
        /// </summary>
        Create,

        /// <summary>
        ///     Abort the program with a fatal error.
        /// </summary>
        Error,

        /// <summary>
        ///     Ignore it, it's not important or the file/directory is not needed strictly.
        /// </summary>
        Ignore
    }

    /// <summary>
    ///     Contains tools to validate an editor and retail installation directory.
    /// </summary>
    public static class InstallationValidation
    {
        /// <summary>
        ///     All commonly required directories in an editor installation.
        ///     You can add your own.
        /// </summary>
        public static List<Tuple<string, RequiredItemType, MissingAction>> RequiredEntries =
            new()
            {
                new Tuple<string, RequiredItemType, MissingAction>("audio", RequiredItemType.Directory,
                    MissingAction.Error),
                new Tuple<string, RequiredItemType, MissingAction>("config", RequiredItemType.Directory,
                    MissingAction.Create),
                new Tuple<string, RequiredItemType, MissingAction>("engine", RequiredItemType.Directory,
                    MissingAction.Error),
                new Tuple<string, RequiredItemType, MissingAction>("examples", RequiredItemType.Directory,
                    MissingAction.Ignore),
                new Tuple<string, RequiredItemType, MissingAction>("fonts", RequiredItemType.Directory,
                    MissingAction.Error),
                new Tuple<string, RequiredItemType, MissingAction>("meshes", RequiredItemType.Directory,
                    MissingAction.Error),
                new Tuple<string, RequiredItemType, MissingAction>("shaders", RequiredItemType.Directory,
                    MissingAction.Error),
                new Tuple<string, RequiredItemType, MissingAction>("textures", RequiredItemType.Directory,
                    MissingAction.Error),
                new Tuple<string, RequiredItemType, MissingAction>("runtime", RequiredItemType.Directory,
                    MissingAction.Error)
            };

        /// <summary>
        ///     Run it in the specified directory.
        /// </summary>
        /// <param name="directory">Validate the directory.</param>
        public static void Run(string directory)
        {
            try
            {
                foreach (var entry in RequiredEntries)
                {
                    if (entry.Item3 == MissingAction.Ignore) continue;

                    if (entry.Item2 == RequiredItemType.Directory)
                    {
                        string path = Path.Combine(directory, entry.Item1);
                        if (!Directory.Exists(path))
                        {
                            if (entry.Item3 == MissingAction.Error)
                                throw new IOException("Missing required directory: " + path);

                            if (entry.Item3 == MissingAction.Create) Directory.CreateDirectory(path);
                        }
                    }
                    else
                    {
                        string path = Path.Combine(directory, entry.Item1);
                        if (!File.Exists(path))
                        {
                            if (entry.Item3 == MissingAction.Error)
                                throw new IOException("Missing required file: " + path);

                            if (entry.Item3 == MissingAction.Create) File.Create(path);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Protocol.Error("Installation validation failed: " + ex);
            }
        }
    }
}