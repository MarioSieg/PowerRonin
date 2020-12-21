using System.Collections.Generic;

namespace Dreamcast.Lua.Interpreter.DataStructs
{
    /// <summary>
    ///     Implementation of IEqualityComparer enforcing reference equality
    /// </summary>
    internal class ReferenceEqualityComparer : IEqualityComparer<object>
    {
        bool IEqualityComparer<object>.Equals(object x, object y)
        {
            return ReferenceEquals(x, y);
        }

        int IEqualityComparer<object>.GetHashCode(object obj)
        {
            return obj.GetHashCode();
        }
    }
}