namespace PowerRonin.Core
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
        public string Name;

        /// <summary>
        ///     Short description.
        /// </summary>
        public string Brief;

        /// <summary>
        ///     Number of parameters. 0 if none.
        /// </summary>
        public byte ParameterCount;

        /// <summary>
        ///     True if it requires native engine root privileges, else false.
        /// </summary>
        public bool RequiresRootPrivileges;

        /// <summary>
        ///     Executor hook.
        /// </summary>
        public CommandExecutor Executor;

        /// <summary>
        /// </summary>
        /// <returns>The string.</returns>
        public override string ToString()
        {
            return
                $"{nameof(Name)}: {Name}, {nameof(Brief)}: {Brief}, {nameof(ParameterCount)}: {ParameterCount}, {nameof(RequiresRootPrivileges)}: {RequiresRootPrivileges}";
        }
    }
}