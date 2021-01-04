using System.Globalization;
using PowerRonin.Json.Utilities;

namespace PowerRonin.Json.Serialization
{
    internal class DefaultReferenceResolver : IReferenceResolver
    {
        private int _referenceCount;

        public object ResolveReference(object context, string reference)
        {
            GetMappings(context).TryGetByFirst(reference, out var value);
            return value;
        }

        public string GetReference(object context, object value)
        {
            var mappings = GetMappings(context);

            if (!mappings.TryGetBySecond(value, out var reference))
            {
                _referenceCount++;
                reference = _referenceCount.ToString(CultureInfo.InvariantCulture);
                mappings.Set(reference, value);
            }

            return reference;
        }

        public void AddReference(object context, string reference, object value)
        {
            GetMappings(context).Set(reference, value);
        }

        public bool IsReferenced(object context, object value)
        {
            return GetMappings(context).TryGetBySecond(value, out _);
        }

        private BidirectionalDictionary<string, object> GetMappings(object context)
        {
            if (!(context is JsonSerializerInternalBase internalSerializer))
            {
                if (context is JsonSerializerProxy proxy)
                    internalSerializer = proxy.GetInternalSerializer();
                else
                    throw new JsonException("The DefaultReferenceResolver can only be used internally.");
            }

            return internalSerializer.DefaultReferenceMappings;
        }
    }
}