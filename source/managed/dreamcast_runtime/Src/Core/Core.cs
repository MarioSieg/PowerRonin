namespace Dreamcast.Core
{
    /// <summary>
    ///     Engine core class.
    /// </summary>
    public static class Core
    {
        private static void OnPreStartup()
        {
            CommandDB.RegisterCommonCommands();
            CommandDB.Execute("info");
            Configuration.Deserialize();
            Configuration.Current.Apply();
        }

        private static void OnPostStartup()
        {
        }

        private static void OnPreTick()
        {
            Input.Update();
            Chrono.Update();
        }

        private static void OnPostTick()
        {
        }

        private static void OnPreShutdown()
        {
        }

        private static void OnPostShutdown()
        {
        }
    }
}