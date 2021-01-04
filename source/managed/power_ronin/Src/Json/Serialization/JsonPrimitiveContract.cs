using System;
using System.Collections.Generic;
using PowerRonin.Json.Utilities;

namespace PowerRonin.Json.Serialization
{
    /// <summary>
    ///     Contract details for a <see cref="Type" /> used by the <see cref="JsonSerializer" />.
    /// </summary>
    public class JsonPrimitiveContract : JsonContract
    {
        private static readonly Dictionary<Type, ReadType> ReadTypeMap = new()
        {
            [typeof(byte[])] = ReadType.ReadAsBytes,
            [typeof(byte)] = ReadType.ReadAsInt32,
            [typeof(short)] = ReadType.ReadAsInt32,
            [typeof(int)] = ReadType.ReadAsInt32,
            [typeof(decimal)] = ReadType.ReadAsDecimal,
            [typeof(bool)] = ReadType.ReadAsBoolean,
            [typeof(string)] = ReadType.ReadAsString,
            [typeof(DateTime)] = ReadType.ReadAsDateTime,
#if HAVE_DATE_TIME_OFFSET
            [typeof(DateTimeOffset)] = ReadType.ReadAsDateTimeOffset,
#endif
            [typeof(float)] = ReadType.ReadAsDouble,
            [typeof(double)] = ReadType.ReadAsDouble,
            [typeof(long)] = ReadType.ReadAsInt64
        };

        /// <summary>
        ///     Initializes a new instance of the <see cref="JsonPrimitiveContract" /> class.
        /// </summary>
        /// <param name="underlyingType">The underlying type for the contract.</param>
        public JsonPrimitiveContract(Type underlyingType)
            : base(underlyingType)
        {
            ContractType = JsonContractType.Primitive;

            TypeCode = ConvertUtils.GetTypeCode(underlyingType);
            IsReadOnlyOrFixedSize = true;

            if (ReadTypeMap.TryGetValue(NonNullableUnderlyingType, out var readType)) InternalReadType = readType;
        }

        internal PrimitiveTypeCode TypeCode { get; set; }
    }
}