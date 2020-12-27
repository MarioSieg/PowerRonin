using System.Collections.Generic;

namespace Dreamcast.Json.Linq.JsonPath
{
    internal class RootFilter : PathFilter
    {
        public static readonly RootFilter Instance = new();

        private RootFilter()
        {
        }

        public override IEnumerable<JToken> ExecuteFilter(JToken root, IEnumerable<JToken> current,
            bool errorWhenNoMatch)
        {
            return new[] {root};
        }
    }
}