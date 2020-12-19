// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

using System.Collections.Generic;
using System.Globalization;
using System.Text;

namespace YAXLib
{
    /// <summary>
    ///     Holds list of exception occured during serialization/deserialization.
    /// </summary>
    public class YAXParsingErrors
    {
        #region Fields

        /// <summary>
        ///     The list of exception occured during serialization/deserialization.
        /// </summary>
        private readonly List<KeyValuePair<YAXException, YAXExceptionTypes>> listExceptions = new List<KeyValuePair<YAXException, YAXExceptionTypes>>();

        #endregion

        #region Indexers

        /// <summary>
        ///     Gets the the pair of Exception and its corresponding exception-type with the specified n.
        /// </summary>
        /// <param name="n">The index of the exception/exception type pair in the error list to return.</param>
        /// <value></value>
        public KeyValuePair<YAXException, YAXExceptionTypes> this[int n] => listExceptions[n];

        #endregion

        #region Properties

        /// <summary>
        ///     Gets a value indicating whether the list of errors is empty or not.
        /// </summary>
        /// <value><c>true</c> if the list is not empty; otherwise, <c>false</c>.</value>
        public bool ContainsAnyError => listExceptions.Count > 0;

        /// <summary>
        ///     Gets the number of errors within the list of errors.
        /// </summary>
        /// <value>the number of errors within the list of errors.</value>
        public int Count => listExceptions.Count;

        #endregion

        #region Methods

        /// <summary>
        ///     Adds an exception with the corresponding type.
        /// </summary>
        /// <param name="exception">The exception to add.</param>
        /// <param name="exceptionType">Type of the exception added.</param>
        public void AddException(YAXException exception, YAXExceptionTypes exceptionType)
        {
            listExceptions.Add(new KeyValuePair<YAXException, YAXExceptionTypes>(exception, exceptionType));
        }

        /// <summary>
        ///     Clears the list of errors.
        /// </summary>
        public void ClearErrors()
        {
            listExceptions.Clear();
        }

        /// <summary>
        ///     Adds the list of errors within another instance of <c>YAXParsingErrors</c>.
        /// </summary>
        /// <param name="parsingErrors">The parsing errors to add its content.</param>
        public void AddRange(YAXParsingErrors parsingErrors)
        {
            parsingErrors.listExceptions.ForEach(listExceptions.Add);
        }

        /// <summary>
        ///     Returns a <see cref="T:System.String" /> that represents the current <see cref="T:System.Object" />.
        /// </summary>
        /// <returns>
        ///     A <see cref="T:System.String" /> that represents the current <see cref="T:System.Object" />.
        /// </returns>
        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();

            listExceptions.ForEach(pair =>
            {
                sb.AppendLine(string.Format(CultureInfo.CurrentCulture, "{0,-8} : {1}", pair.Value, pair.Key.Message));
                sb.AppendLine();
            });

            return sb.ToString();
        }

        #endregion
    }
}