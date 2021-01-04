using System;

namespace PowerRonin.Json.Serialization
{
    /// <summary>
    ///     Provides data for the Error event.
    /// </summary>
    public class ErrorEventArgs : EventArgs
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="ErrorEventArgs" /> class.
        /// </summary>
        /// <param name="currentObject">The current object.</param>
        /// <param name="errorContext">The error context.</param>
        public ErrorEventArgs(object? currentObject, ErrorContext errorContext)
        {
            CurrentObject = currentObject;
            ErrorContext = errorContext;
        }

        /// <summary>
        ///     Gets the current object the error event is being raised against.
        /// </summary>
        /// <value>The current object the error event is being raised against.</value>
        public object? CurrentObject { get; }

        /// <summary>
        ///     Gets the error context.
        /// </summary>
        /// <value>The error context.</value>
        public ErrorContext ErrorContext { get; }
    }
}