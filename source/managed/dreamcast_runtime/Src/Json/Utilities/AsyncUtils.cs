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
using System.Diagnostics;
using System.IO;
using System.Threading;
using System.Threading.Tasks;

namespace Dreamcast.Json.Utilities
{
    internal static class AsyncUtils
    {
        // Pre-allocate to avoid wasted allocations.
        public static readonly Task<bool> False = Task.FromResult(false);
        public static readonly Task<bool> True = Task.FromResult(true);

        internal static Task<bool> ToAsync(this bool value) => value ? True : False;

        public static Task? CancelIfRequestedAsync(this CancellationToken cancellationToken)
        {
            return cancellationToken.IsCancellationRequested ? FromCanceled(cancellationToken) : null;
        }

        public static Task<T>? CancelIfRequestedAsync<T>(this CancellationToken cancellationToken)
        {
            return cancellationToken.IsCancellationRequested ? FromCanceled<T>(cancellationToken) : null;
        }

        // From 4.6 on we could use Task.FromCanceled(), but we need an equivalent for
        // previous frameworks.
        public static Task FromCanceled(this CancellationToken cancellationToken)
        {
            MiscellaneousUtils.Assert(cancellationToken.IsCancellationRequested);
            return new Task(() => {}, cancellationToken);
        }

        public static Task<T> FromCanceled<T>(this CancellationToken cancellationToken)
        {
            MiscellaneousUtils.Assert(cancellationToken.IsCancellationRequested);
#pragma warning disable CS8603 // Possible null reference return.
            return new Task<T>(() => default, cancellationToken);
#pragma warning restore CS8603 // Possible null reference return.
        }

        // Task.Delay(0) is optimised as a cached task within the framework, and indeed
        // the same cached task that Task.CompletedTask returns as of 4.6, but we'll add
        // our own cached field for previous frameworks.
        internal static readonly Task CompletedTask = Task.Delay(0);

        public static Task WriteAsync(this TextWriter writer, char value, CancellationToken cancellationToken)
        {
            MiscellaneousUtils.Assert(writer != null);
            return cancellationToken.IsCancellationRequested ? FromCanceled(cancellationToken) : writer.WriteAsync(value);
        }

        public static Task WriteAsync(this TextWriter writer, string? value, CancellationToken cancellationToken)
        {
            MiscellaneousUtils.Assert(writer != null);
            return cancellationToken.IsCancellationRequested ? FromCanceled(cancellationToken) : writer.WriteAsync(value);
        }

        public static Task WriteAsync(this TextWriter writer, char[] value, int start, int count, CancellationToken cancellationToken)
        {
            MiscellaneousUtils.Assert(writer != null);
            return cancellationToken.IsCancellationRequested ? FromCanceled(cancellationToken) : writer.WriteAsync(value, start, count);
        }

        public static Task<int> ReadAsync(this TextReader reader, char[] buffer, int index, int count, CancellationToken cancellationToken)
        {
            MiscellaneousUtils.Assert(reader != null);
            return cancellationToken.IsCancellationRequested ? FromCanceled<int>(cancellationToken) : reader.ReadAsync(buffer, index, count);
        }

        public static bool IsCompletedSucessfully(this Task task)
        {
            // IsCompletedSucessfully is the faster method, but only currently exposed on .NET Core 2.0
#if NETCOREAPP2_0
            return task.IsCompletedSucessfully;
#else
            return task.Status == TaskStatus.RanToCompletion;
#endif
        }
    }
}

#endif