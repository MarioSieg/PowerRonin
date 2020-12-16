using System.Collections.Generic;

namespace Dreamcast.Core
{
    public static class CommandDB
    {
        public static List<string> CommandHistory { get; private set; } = new List<string>();
        
        [CalledFromNativeRuntime]
        private static void OnCommandEnter(string command)
        {
            CommandHistory.Add(command);
        }
    }
}
