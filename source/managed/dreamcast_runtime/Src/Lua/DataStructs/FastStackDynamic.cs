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

namespace Dreamcast.Lua.Interpreter.DataStructs
{
#if USE_DYNAMIC_STACKS
	internal class FastStack<T> : FastStackDynamic<T>
	{
		public FastStack(int startingCapacity)
			: base(startingCapacity)
		{
		}
	}
#endif

    /// <summary>
    ///     A non preallocated, non_fixed size stack
    /// </summary>
    /// <typeparam name="T"></typeparam>
    internal class FastStackDynamic<T> : List<T>
    {
        public FastStackDynamic(int startingCapacity)
            : base(startingCapacity)
        {
        }


        public void Set(int idxofs, T item)
        {
            this[Count - 1 - idxofs] = item;
        }


        public T Push(T item)
        {
            Add(item);
            return item;
        }

        public void Expand(int size)
        {
            for (var i = 0; i < size; i++)
                Add(default);
        }

        public void Zero(int index)
        {
            this[index] = default;
        }

        public T Peek(int idxofs = 0)
        {
            var item = this[Count - 1 - idxofs];
            return item;
        }

        public void CropAtCount(int p)
        {
            RemoveLast(Count - p);
        }

        public void RemoveLast(int cnt = 1)
        {
            if (cnt == 1)
                RemoveAt(Count - 1);
            else
                RemoveRange(Count - cnt, cnt);
        }

        public T Pop()
        {
            var retval = this[Count - 1];
            RemoveAt(Count - 1);
            return retval;
        }
    }
}