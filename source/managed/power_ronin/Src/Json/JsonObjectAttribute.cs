using System;

namespace PowerRonin.Json
{
    /// <summary>
    ///     Instructs the <see cref="JsonSerializer" /> how to serialize the object.
    /// </summary>
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct | AttributeTargets.Interface)]
    public sealed class JsonObjectAttribute : JsonContainerAttribute
    {
        internal NullValueHandling? _itemNullValueHandling;

        // yuck. can't set nullable properties on an attribute in C#
        // have to use this approach to get an unset default state
        internal Required? _itemRequired;
        internal MissingMemberHandling? _missingMemberHandling;

        /// <summary>
        ///     Initializes a new instance of the <see cref="JsonObjectAttribute" /> class.
        /// </summary>
        public JsonObjectAttribute()
        {
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="JsonObjectAttribute" /> class with the specified member serialization.
        /// </summary>
        /// <param name="memberSerialization">The member serialization.</param>
        public JsonObjectAttribute(MemberSerialization memberSerialization)
        {
            MemberSerialization = memberSerialization;
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="JsonObjectAttribute" /> class with the specified container Id.
        /// </summary>
        /// <param name="id">The container Id.</param>
        public JsonObjectAttribute(string id)
            : base(id)
        {
        }

        /// <summary>
        ///     Gets or sets the member serialization.
        /// </summary>
        /// <value>The member serialization.</value>
        public MemberSerialization MemberSerialization { get; set; } = MemberSerialization.OptOut;

        /// <summary>
        ///     Gets or sets the missing member handling used when deserializing this object.
        /// </summary>
        /// <value>The missing member handling.</value>
        public MissingMemberHandling MissingMemberHandling
        {
            get => _missingMemberHandling ?? default;
            set => _missingMemberHandling = value;
        }

        /// <summary>
        ///     Gets or sets how the object's properties with null values are handled during serialization and deserialization.
        /// </summary>
        /// <value>How the object's properties with null values are handled during serialization and deserialization.</value>
        public NullValueHandling ItemNullValueHandling
        {
            get => _itemNullValueHandling ?? default;
            set => _itemNullValueHandling = value;
        }

        /// <summary>
        ///     Gets or sets a value that indicates whether the object's properties are required.
        /// </summary>
        /// <value>
        ///     A value indicating whether the object's properties are required.
        /// </value>
        public Required ItemRequired
        {
            get => _itemRequired ?? default;
            set => _itemRequired = value;
        }
    }
}