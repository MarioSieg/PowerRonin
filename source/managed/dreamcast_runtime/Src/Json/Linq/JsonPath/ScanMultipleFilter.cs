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

namespace Dreamcast.Json.Linq.JsonPath
{
    internal class ScanMultipleFilter : PathFilter
    {
        private readonly List<string> _names;

        public ScanMultipleFilter(List<string> names)
        {
            _names = names;
        }

        public override IEnumerable<JToken> ExecuteFilter(JToken root, IEnumerable<JToken> current, bool errorWhenNoMatch)
        {
            foreach (var c in current)
            {
                var value = c;

                while (true)
                {
                    var container = value as JContainer;

                    value = GetNextScanValue(c, container, value);
                    if (value == null) break;

                    if (value is JProperty property)
                        foreach (var name in _names)
                            if (property.Name == name)
                                yield return property.Value;
                }
            }
        }
    }
}