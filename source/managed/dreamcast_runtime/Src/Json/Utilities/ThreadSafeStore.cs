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
using Dreamcast.Json.Serialization;
#if !HAVE_LINQ
#endif
#if HAVE_CONCURRENT_DICTIONARY
using System.Collections.Concurrent;
#endif

namespace Dreamcast.Json.Utilities
{
    internal class ThreadSafeStore<TKey, TValue>
    {
#if HAVE_CONCURRENT_DICTIONARY
        private readonly ConcurrentDictionary<TKey, TValue> _concurrentStore;
#else
        private readonly object _lock = new();
        private Dictionary<TKey, TValue> _store;
#endif
        private readonly Func<TKey, TValue> _creator;

        public ThreadSafeStore(Func<TKey, TValue> creator)
        {
            ValidationUtils.ArgumentNotNull(creator, nameof(creator));

            _creator = creator;
#if HAVE_CONCURRENT_DICTIONARY
            _concurrentStore = new ConcurrentDictionary<TKey, TValue>();
#else
            _store = new Dictionary<TKey, TValue>();
#endif
        }

        public TValue Get(TKey key)
        {
#if HAVE_CONCURRENT_DICTIONARY
            return _concurrentStore.GetOrAdd(key, _creator);
#else
            if (!_store.TryGetValue(key, out var value)) return AddValue(key);

            return value;
#endif
        }

#if !HAVE_CONCURRENT_DICTIONARY
        private TValue AddValue(TKey key)
        {
            var value = _creator(key);

            lock (_lock)
            {
                if (_store == null)
                {
                    _store = new Dictionary<TKey, TValue>();
                    _store[key] = value;
                }
                else
                {
                    // double check locking
                    if (_store.TryGetValue(key, out var checkValue)) return checkValue;

                    var newStore = new Dictionary<TKey, TValue>(_store);
                    newStore[key] = value;

#if HAVE_MEMORY_BARRIER
                    Thread.MemoryBarrier();
#endif
                    _store = newStore;
                }

                return value;
            }
        }
#endif
    }
}