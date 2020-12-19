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
using System.Collections.ObjectModel;
using System.Diagnostics.CodeAnalysis;
using Dreamcast.Json.Utilities;

namespace Dreamcast.Json.Linq
{
    internal class JPropertyKeyedCollection : Collection<JToken>
    {
        private static readonly IEqualityComparer<string> Comparer = StringComparer.Ordinal;

        private Dictionary<string, JToken>? _dictionary;

        public JPropertyKeyedCollection() : base(new List<JToken>())
        {
        }

        public JToken this[string key]
        {
            get
            {
                if (key == null) throw new ArgumentNullException(nameof(key));

                if (_dictionary != null) return _dictionary[key];

                throw new KeyNotFoundException();
            }
        }

        public ICollection<string> Keys
        {
            get
            {
                EnsureDictionary();
                return _dictionary!.Keys;
            }
        }

        public ICollection<JToken> Values
        {
            get
            {
                EnsureDictionary();
                return _dictionary!.Values;
            }
        }

        private void AddKey(string key, JToken item)
        {
            EnsureDictionary();
            _dictionary![key] = item;
        }

        protected void ChangeItemKey(JToken item, string newKey)
        {
            if (!ContainsItem(item)) throw new ArgumentException("The specified item does not exist in this KeyedCollection.");

            var keyForItem = GetKeyForItem(item);
            if (!Comparer.Equals(keyForItem, newKey))
            {
                if (newKey != null) AddKey(newKey, item);

                if (keyForItem != null) RemoveKey(keyForItem);
            }
        }

        protected override void ClearItems()
        {
            base.ClearItems();

            _dictionary?.Clear();
        }

        public bool Contains(string key)
        {
            if (key == null) throw new ArgumentNullException(nameof(key));

            if (_dictionary != null) return _dictionary.ContainsKey(key);

            return false;
        }

        private bool ContainsItem(JToken item)
        {
            if (_dictionary == null) return false;

            var key = GetKeyForItem(item);
            return _dictionary.TryGetValue(key, out _);
        }

        private void EnsureDictionary()
        {
            if (_dictionary == null) _dictionary = new Dictionary<string, JToken>(Comparer);
        }

        private string GetKeyForItem(JToken item)
        {
            return ((JProperty) item).Name;
        }

        protected override void InsertItem(int index, JToken item)
        {
            AddKey(GetKeyForItem(item), item);
            base.InsertItem(index, item);
        }

        public bool Remove(string key)
        {
            if (key == null) throw new ArgumentNullException(nameof(key));

            if (_dictionary != null) return _dictionary.TryGetValue(key, out var value) && Remove(value);

            return false;
        }

        protected override void RemoveItem(int index)
        {
            var keyForItem = GetKeyForItem(Items[index]);
            RemoveKey(keyForItem);
            base.RemoveItem(index);
        }

        private void RemoveKey(string key)
        {
            _dictionary?.Remove(key);
        }

        protected override void SetItem(int index, JToken item)
        {
            var keyForItem = GetKeyForItem(item);
            var keyAtIndex = GetKeyForItem(Items[index]);

            if (Comparer.Equals(keyAtIndex, keyForItem))
            {
                if (_dictionary != null) _dictionary[keyForItem] = item;
            }
            else
            {
                AddKey(keyForItem, item);

                if (keyAtIndex != null) RemoveKey(keyAtIndex);
            }

            base.SetItem(index, item);
        }

        public bool TryGetValue(string key,
            [NotNullWhen(true)]
            out JToken? value)
        {
            if (_dictionary == null)
            {
                value = null;
                return false;
            }

            return _dictionary.TryGetValue(key, out value);
        }

        public int IndexOfReference(JToken t)
        {
            return ((List<JToken>) Items).IndexOfReference(t);
        }

        public bool Compare(JPropertyKeyedCollection other)
        {
            if (this == other) return true;

            // dictionaries in JavaScript aren't ordered
            // ignore order when comparing properties
            var d1 = _dictionary;
            var d2 = other._dictionary;

            if (d1 == null && d2 == null) return true;

            if (d1 == null) return d2!.Count == 0;

            if (d2 == null) return d1.Count == 0;

            if (d1.Count != d2.Count) return false;

            foreach (var keyAndProperty in d1)
            {
                if (!d2.TryGetValue(keyAndProperty.Key, out var secondValue)) return false;

                var p1 = (JProperty) keyAndProperty.Value;
                var p2 = (JProperty) secondValue;

                if (p1.Value == null) return p2.Value == null;

                if (!p1.Value.DeepEquals(p2.Value)) return false;
            }

            return true;
        }
    }
}