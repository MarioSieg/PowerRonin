using System.IO;

namespace PowerRonin.Core
{
    /// <summary>
    ///     Helper to copy whole directories.
    /// </summary>
    public static class CopyDir
    {
        public static void Copy(string sourceDirectory, string targetDirectory, bool verbose = false)
        {
            var diSource = new DirectoryInfo(sourceDirectory);
            var diTarget = new DirectoryInfo(targetDirectory);

            CopyAll(diSource, diTarget, verbose);
        }

        public static void CopyAll(DirectoryInfo source, DirectoryInfo target, bool verbose = false)
        {
            Directory.CreateDirectory(target.FullName);

            // Copy each file into the new directory.
            foreach (var fi in source.GetFiles())
            {
                if (verbose)
                    Protocol.Info($"Copying {fi.FullName}...");
                fi.CopyTo(Path.Combine(target.FullName, fi.Name), true);
            }

            // Copy each sub directory using recursion.
            foreach (var diSourceSubDir in source.GetDirectories())
            {
                var nextTargetSubDir = target.CreateSubdirectory(diSourceSubDir.Name);
                CopyAll(diSourceSubDir, nextTargetSubDir);
            }
        }
    }
}