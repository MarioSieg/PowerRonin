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

#if HAVE_ASYNC
using System.Globalization;
using System.IO;
using System.Threading;
using System.Threading.Tasks;

namespace Dreamcast.Json.Linq
{
    public partial class JRaw
    {
        /// <summary>
        /// Asynchronously creates an instance of <see cref="JRaw"/> with the content of the reader's current token.
        /// </summary>
        /// <param name="reader">The reader.</param>
        /// <param name="cancellationToken">The token to monitor for cancellation requests. The default value is <see cref="CancellationToken.None"/>.</param>
        /// <returns>A <see cref="Task{TResult}"/> representing the asynchronous creation. The <see cref="Task{TResult}.Result"/>
        /// property returns an instance of <see cref="JRaw"/> with the content of the reader's current token.</returns>
        public static async Task<JRaw> CreateAsync(JsonReader reader, CancellationToken cancellationToken = default)
        {
            using (StringWriter sw = new StringWriter(CultureInfo.InvariantCulture))
            using (JsonTextWriter jsonWriter = new JsonTextWriter(sw))
            {
                await jsonWriter.WriteTokenSyncReadingAsync(reader, cancellationToken).ConfigureAwait(false);

                return new JRaw(sw.ToString());
            }
        }
    }
}

#endif