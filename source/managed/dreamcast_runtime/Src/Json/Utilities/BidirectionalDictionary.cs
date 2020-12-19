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

namespace Dreamcast.Json.Utilities
{
    internal class BidirectionalDictionary<TFirst, TSecond>
    {
        private readonly string _duplicateFirstErrorMessage;
        private readonly string _duplicateSecondErrorMessage;
        private readonly IDictionary<TFirst, TSecond> _firstToSecond;
        private readonly IDictionary<TSecond, TFirst> _secondToFirst;

        public BidirectionalDictionary()
            : this(EqualityComparer<TFirst>.Default, EqualityComparer<TSecond>.Default)
        {
        }

        public BidirectionalDictionary(IEqualityComparer<TFirst> firstEqualityComparer, IEqualityComparer<TSecond> secondEqualityComparer)
            : this(
                firstEqualityComparer,
                secondEqualityComparer,
                "Duplicate item already exists for '{0}'.",
                "Duplicate item already exists for '{0}'.")
        {
        }

        public BidirectionalDictionary(IEqualityComparer<TFirst> firstEqualityComparer,
            IEqualityComparer<TSecond> secondEqualityComparer,
            string duplicateFirstErrorMessage,
            string duplicateSecondErrorMessage)
        {
            _firstToSecond = new Dictionary<TFirst, TSecond>(firstEqualityComparer);
            _secondToFirst = new Dictionary<TSecond, TFirst>(secondEqualityComparer);
            _duplicateFirstErrorMessage = duplicateFirstErrorMessage;
            _duplicateSecondErrorMessage = duplicateSecondErrorMessage;
        }

        public void Set(TFirst first, TSecond second)
        {
            if (_firstToSecond.TryGetValue(first, out var existingSecond))
                if (!existingSecond!.Equals(second))
                    throw new ArgumentException(_duplicateFirstErrorMessage.FormatWith(CultureInfo.InvariantCulture, first));

            if (_secondToFirst.TryGetValue(second, out var existingFirst))
                if (!existingFirst!.Equals(first))
                    throw new ArgumentException(_duplicateSecondErrorMessage.FormatWith(CultureInfo.InvariantCulture, second));

            _firstToSecond.Add(first, second);
            _secondToFirst.Add(second, first);
        }

        public bool TryGetByFirst(TFirst first, out TSecond second)
        {
            return _firstToSecond.TryGetValue(first, out second);
        }

        public bool TryGetBySecond(TSecond second, out TFirst first)
        {
            return _secondToFirst.TryGetValue(second, out first);
        }
    }
}