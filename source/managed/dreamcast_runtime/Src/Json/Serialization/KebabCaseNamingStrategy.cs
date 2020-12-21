using Dreamcast.Json.Utilities;

namespace Dreamcast.Json.Serialization
{
    /// <summary>
    ///     A kebab case naming strategy.
    /// </summary>
    public class KebabCaseNamingStrategy : NamingStrategy
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="KebabCaseNamingStrategy" /> class.
        /// </summary>
        /// <param name="processDictionaryKeys">
        ///     A flag indicating whether dictionary keys should be processed.
        /// </param>
        /// <param name="overrideSpecifiedNames">
        ///     A flag indicating whether explicitly specified property names should be processed,
        ///     e.g. a property name customized with a <see cref="JsonPropertyAttribute" />.
        /// </param>
        public KebabCaseNamingStrategy(bool processDictionaryKeys, bool overrideSpecifiedNames)
        {
            ProcessDictionaryKeys = processDictionaryKeys;
            OverrideSpecifiedNames = overrideSpecifiedNames;
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="KebabCaseNamingStrategy" /> class.
        /// </summary>
        /// <param name="processDictionaryKeys">
        ///     A flag indicating whether dictionary keys should be processed.
        /// </param>
        /// <param name="overrideSpecifiedNames">
        ///     A flag indicating whether explicitly specified property names should be processed,
        ///     e.g. a property name customized with a <see cref="JsonPropertyAttribute" />.
        /// </param>
        /// <param name="processExtensionDataNames">
        ///     A flag indicating whether extension data names should be processed.
        /// </param>
        public KebabCaseNamingStrategy(bool processDictionaryKeys, bool overrideSpecifiedNames,
            bool processExtensionDataNames)
            : this(processDictionaryKeys, overrideSpecifiedNames)
        {
            ProcessExtensionDataNames = processExtensionDataNames;
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="KebabCaseNamingStrategy" /> class.
        /// </summary>
        public KebabCaseNamingStrategy()
        {
        }

        /// <summary>
        ///     Resolves the specified property name.
        /// </summary>
        /// <param name="name">The property name to resolve.</param>
        /// <returns>The resolved property name.</returns>
        protected override string ResolvePropertyName(string name)
        {
            return StringUtils.ToKebabCase(name);
        }
    }
}