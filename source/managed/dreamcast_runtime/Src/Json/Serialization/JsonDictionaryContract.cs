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
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using Dreamcast.Json.Utilities;
#if !HAVE_LINQ

#endif

namespace Dreamcast.Json.Serialization
{
    /// <summary>
    ///     Contract details for a <see cref="System.Type" /> used by the <see cref="JsonSerializer" />.
    /// </summary>
    public class JsonDictionaryContract : JsonContainerContract
    {
        private readonly Type? _genericCollectionDefinitionType;

        private readonly ConstructorInfo? _parameterizedConstructor;

        private Func<object>? _genericTemporaryDictionaryCreator;
        private ObjectConstructor<object>? _genericWrapperCreator;

        private Type? _genericWrapperType;

        private ObjectConstructor<object>? _parameterizedCreator;

        /// <summary>
        ///     Initializes a new instance of the <see cref="JsonDictionaryContract" /> class.
        /// </summary>
        /// <param name="underlyingType">The underlying type for the contract.</param>
        public JsonDictionaryContract(Type underlyingType)
            : base(underlyingType)
        {
            ContractType = JsonContractType.Dictionary;

            Type? keyType;
            Type? valueType;

            if (ReflectionUtils.ImplementsGenericDefinition(underlyingType, typeof(IDictionary<,>), out _genericCollectionDefinitionType))
            {
                keyType = _genericCollectionDefinitionType.GetGenericArguments()[0];
                valueType = _genericCollectionDefinitionType.GetGenericArguments()[1];

                if (ReflectionUtils.IsGenericDefinition(UnderlyingType, typeof(IDictionary<,>)))
                {
                    CreatedType = typeof(Dictionary<,>).MakeGenericType(keyType, valueType);
                }
                else if (underlyingType.IsGenericType())
                {
                    // ConcurrentDictionary<,> + IDictionary setter + null value = error
                    // wrap to use generic setter
                    // https://github.com/JamesNK/Dreamcast.Json/issues/1582
                    var typeDefinition = underlyingType.GetGenericTypeDefinition();
                    if (typeDefinition.FullName == JsonTypeReflector.ConcurrentDictionaryTypeName) ShouldCreateWrapper = true;
                }

#if HAVE_READ_ONLY_COLLECTIONS
                IsReadOnlyOrFixedSize = ReflectionUtils.InheritsGenericDefinition(underlyingType, typeof(ReadOnlyDictionary<,>));
#endif
            }
#if HAVE_READ_ONLY_COLLECTIONS
            else if (ReflectionUtils.ImplementsGenericDefinition(underlyingType, typeof(IReadOnlyDictionary<,>), out _genericCollectionDefinitionType))
            {
                keyType = _genericCollectionDefinitionType.GetGenericArguments()[0];
                valueType = _genericCollectionDefinitionType.GetGenericArguments()[1];

                if (ReflectionUtils.IsGenericDefinition(UnderlyingType, typeof(IReadOnlyDictionary<,>)))
                {
                    CreatedType = typeof(ReadOnlyDictionary<,>).MakeGenericType(keyType, valueType);
                }

                IsReadOnlyOrFixedSize = true;
            }
#endif
            else
            {
                ReflectionUtils.GetDictionaryKeyValueTypes(UnderlyingType, out keyType, out valueType);

                if (UnderlyingType == typeof(IDictionary)) CreatedType = typeof(Dictionary<object, object>);
            }

            if (keyType != null && valueType != null)
            {
                _parameterizedConstructor = CollectionUtils.ResolveEnumerableCollectionConstructor(
                    CreatedType,
                    typeof(KeyValuePair<,>).MakeGenericType(keyType, valueType),
                    typeof(IDictionary<,>).MakeGenericType(keyType, valueType));

#if HAVE_FSHARP_TYPES
                if (!HasParameterizedCreatorInternal && underlyingType.Name == FSharpUtils.FSharpMapTypeName)
                {
                    FSharpUtils.EnsureInitialized(underlyingType.Assembly());
                    _parameterizedCreator = FSharpUtils.Instance.CreateMap(keyType, valueType);
                }
#endif
            }

            if (!typeof(IDictionary).IsAssignableFrom(CreatedType)) ShouldCreateWrapper = true;

            DictionaryKeyType = keyType;
            DictionaryValueType = valueType;

#if (NET20 || NET35)
            if (DictionaryValueType != null && ReflectionUtils.IsNullableType(DictionaryValueType))
            {
                // bug in .NET 2.0 & 3.5 that Dictionary<TKey, Nullable<TValue>> throws an error when adding null via IDictionary[key] = object
                // wrapper will handle calling Add(T) instead
                if (ReflectionUtils.InheritsGenericDefinition(CreatedType, typeof(Dictionary<,>), out _))
                {
                    ShouldCreateWrapper = true;
                }
            }
#endif

            if (DictionaryKeyType != null &&
                DictionaryValueType != null &&
                ImmutableCollectionsUtils.TryBuildImmutableForDictionaryContract(
                    underlyingType,
                    DictionaryKeyType,
                    DictionaryValueType,
                    out var immutableCreatedType,
                    out var immutableParameterizedCreator))
            {
                CreatedType = immutableCreatedType;
                _parameterizedCreator = immutableParameterizedCreator;
                IsReadOnlyOrFixedSize = true;
            }
        }

        /// <summary>
        ///     Gets or sets the dictionary key resolver.
        /// </summary>
        /// <value>The dictionary key resolver.</value>
        public Func<string, string>? DictionaryKeyResolver { get; set; }

        /// <summary>
        ///     Gets the <see cref="System.Type" /> of the dictionary keys.
        /// </summary>
        /// <value>The <see cref="System.Type" /> of the dictionary keys.</value>
        public Type? DictionaryKeyType { get; }

        /// <summary>
        ///     Gets the <see cref="System.Type" /> of the dictionary values.
        /// </summary>
        /// <value>The <see cref="System.Type" /> of the dictionary values.</value>
        public Type? DictionaryValueType { get; }

        internal JsonContract? KeyContract { get; set; }

        internal bool ShouldCreateWrapper { get; }

        internal ObjectConstructor<object>? ParameterizedCreator
        {
            get
            {
                if (_parameterizedCreator == null && _parameterizedConstructor != null) _parameterizedCreator = JsonTypeReflector.ReflectionDelegateFactory.CreateParameterizedConstructor(_parameterizedConstructor);

                return _parameterizedCreator;
            }
        }

        /// <summary>
        ///     Gets or sets the function used to create the object. When set this function will override
        ///     <see cref="JsonContract.DefaultCreator" />.
        /// </summary>
        /// <value>The function used to create the object.</value>
        public ObjectConstructor<object>? OverrideCreator { get; set; }

        /// <summary>
        ///     Gets a value indicating whether the creator has a parameter with the dictionary values.
        /// </summary>
        /// <value><c>true</c> if the creator has a parameter with the dictionary values; otherwise, <c>false</c>.</value>
        public bool HasParameterizedCreator { get; set; }

        internal bool HasParameterizedCreatorInternal => HasParameterizedCreator || _parameterizedCreator != null || _parameterizedConstructor != null;

        internal IWrappedDictionary CreateWrapper(object dictionary)
        {
            if (_genericWrapperCreator == null)
            {
                _genericWrapperType = typeof(DictionaryWrapper<,>).MakeGenericType(DictionaryKeyType, DictionaryValueType);

                var genericWrapperConstructor = _genericWrapperType.GetConstructor(new[] {_genericCollectionDefinitionType!});
                _genericWrapperCreator = JsonTypeReflector.ReflectionDelegateFactory.CreateParameterizedConstructor(genericWrapperConstructor);
            }

            return (IWrappedDictionary) _genericWrapperCreator(dictionary);
        }

        internal IDictionary CreateTemporaryDictionary()
        {
            if (_genericTemporaryDictionaryCreator == null)
            {
                var temporaryDictionaryType = typeof(Dictionary<,>).MakeGenericType(DictionaryKeyType ?? typeof(object), DictionaryValueType ?? typeof(object));

                _genericTemporaryDictionaryCreator = JsonTypeReflector.ReflectionDelegateFactory.CreateDefaultConstructor<object>(temporaryDictionaryType);
            }

            return (IDictionary) _genericTemporaryDictionaryCreator();
        }
    }
}