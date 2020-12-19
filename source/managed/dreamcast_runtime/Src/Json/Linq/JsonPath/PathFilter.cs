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
using Dreamcast.Json.Utilities;

namespace Dreamcast.Json.Linq.JsonPath
{
    internal abstract class PathFilter
    {
        public abstract IEnumerable<JToken> ExecuteFilter(JToken root, IEnumerable<JToken> current, bool errorWhenNoMatch);

        protected static JToken? GetTokenIndex(JToken t, bool errorWhenNoMatch, int index)
        {
            if (t is JArray a)
            {
                if (a.Count <= index)
                {
                    if (errorWhenNoMatch) throw new JsonException("Index {0} outside the bounds of JArray.".FormatWith(CultureInfo.InvariantCulture, index));

                    return null;
                }

                return a[index];
            }

            if (t is JConstructor c)
            {
                if (c.Count <= index)
                {
                    if (errorWhenNoMatch) throw new JsonException("Index {0} outside the bounds of JConstructor.".FormatWith(CultureInfo.InvariantCulture, index));

                    return null;
                }

                return c[index];
            }

            if (errorWhenNoMatch) throw new JsonException("Index {0} not valid on {1}.".FormatWith(CultureInfo.InvariantCulture, index, t.GetType().Name));

            return null;
        }

        protected static JToken? GetNextScanValue(JToken originalParent, JToken? container, JToken? value)
        {
            // step into container's values
            if (container != null && container.HasValues)
            {
                value = container.First;
            }
            else
            {
                // finished container, move to parent
                while (value != null && value != originalParent && value == value.Parent!.Last) value = value.Parent;

                // finished
                if (value == null || value == originalParent) return null;

                // move to next value in container
                value = value.Next;
            }

            return value;
        }
    }
}