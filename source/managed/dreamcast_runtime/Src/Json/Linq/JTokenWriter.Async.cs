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
using System.Threading;
using System.Threading.Tasks;
using Dreamcast.Json.Utilities;

namespace Dreamcast.Json.Linq
{
    public partial class JTokenWriter
    {
        // This is the only method that can benefit from Task-based asynchronicity, and that only when
        // the reader provides it.
        internal override Task WriteTokenAsync(JsonReader reader, bool writeChildren, bool writeDateConstructorAsDate, bool writeComments, CancellationToken cancellationToken)
        {
            // Since JTokenReader is a common target (and with an optimised path) and since it can't
            // read truly async, catch that case.
            if (reader is JTokenReader)
            {
                WriteToken(reader, writeChildren, writeDateConstructorAsDate, writeComments);
                return AsyncUtils.CompletedTask;
            }

            return WriteTokenSyncReadingAsync(reader, cancellationToken);
        }
    }
}

#endif