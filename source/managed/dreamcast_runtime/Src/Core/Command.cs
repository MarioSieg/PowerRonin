namespace Dreamcast.Core
{
    /// <summary>
    ///     Executor hook for a command.
    /// </summary>
    /// <param name="args"></param>
    public delegate void CommandExecutor(string args);

    /// <summary>
    ///     Represents an executable terminal command.
    /// </summary>
    public struct Command
    {
        /// <summary>
        ///     The name used in the terminal.
        /// </summary>
        public string name;

        /// <summary>
        ///     Short description.
        /// </summary>
        public string brief;

        /// <summary>
        ///     Number of parameters. 0 if none.
        /// </summary>
        public byte parameterCount;

        /// <summary>
        ///     True if it requires native engine root privileges, else false.
        /// </summary>
        public bool requiresRootPrivileges;

        /// <summary>
        ///     Executor hook.
        /// </summary>
        public CommandExecutor executor;

        /// <summary>
        /// </summary>
        /// <returns>The string.</returns>
        public override string ToString()
        {
            return
                $"{nameof(name)}: {name}, {nameof(brief)}: {brief}, {nameof(parameterCount)}: {parameterCount}, {nameof(requiresRootPrivileges)}: {requiresRootPrivileges}";
        }
    }
}