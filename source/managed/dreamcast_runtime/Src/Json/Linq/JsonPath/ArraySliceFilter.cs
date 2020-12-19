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

using System;
using System.Collections.Generic;
using System.Globalization;
using Dreamcast.Json.Utilities;

namespace Dreamcast.Json.Linq.JsonPath
{
    internal class ArraySliceFilter : PathFilter
    {
        public int? Start { get; set; }
        public int? End { get; set; }
        public int? Step { get; set; }

        public override IEnumerable<JToken> ExecuteFilter(JToken root, IEnumerable<JToken> current, bool errorWhenNoMatch)
        {
            if (Step == 0) throw new JsonException("Step cannot be zero.");

            foreach (var t in current)
                if (t is JArray a)
                {
                    // set defaults for null arguments
                    var stepCount = Step ?? 1;
                    var startIndex = Start ?? (stepCount > 0 ? 0 : a.Count - 1);
                    var stopIndex = End ?? (stepCount > 0 ? a.Count : -1);

                    // start from the end of the list if start is negative
                    if (Start < 0) startIndex = a.Count + startIndex;

                    // end from the start of the list if stop is negative
                    if (End < 0) stopIndex = a.Count + stopIndex;

                    // ensure indexes keep within collection bounds
                    startIndex = Math.Max(startIndex, stepCount > 0 ? 0 : int.MinValue);
                    startIndex = Math.Min(startIndex, stepCount > 0 ? a.Count : a.Count - 1);
                    stopIndex = Math.Max(stopIndex, -1);
                    stopIndex = Math.Min(stopIndex, a.Count);

                    var positiveStep = stepCount > 0;

                    if (IsValid(startIndex, stopIndex, positiveStep))
                    {
                        for (var i = startIndex; IsValid(i, stopIndex, positiveStep); i += stepCount) yield return a[i];
                    }
                    else
                    {
                        if (errorWhenNoMatch)
                            throw new JsonException("Array slice of {0} to {1} returned no results.".FormatWith(CultureInfo.InvariantCulture,
                                Start != null ? Start.GetValueOrDefault().ToString(CultureInfo.InvariantCulture) : "*",
                                End != null ? End.GetValueOrDefault().ToString(CultureInfo.InvariantCulture) : "*"));
                    }
                }
                else
                {
                    if (errorWhenNoMatch) throw new JsonException("Array slice is not valid on {0}.".FormatWith(CultureInfo.InvariantCulture, t.GetType().Name));
                }
        }

        private bool IsValid(int index, int stopIndex, bool positiveStep)
        {
            if (positiveStep) return index < stopIndex;

            return index > stopIndex;
        }
    }
}