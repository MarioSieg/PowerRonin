using System;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using Dreamcast.Json;
using Dreamcast.Json.Converters;

namespace Dreamcast.Core
{
    /// <summary>
    ///     Contains helpers for de/serialization.
    /// </summary>
    public static class Serializer
    {
        public static void SetupFormatter()
        {
            JsonConvert.DefaultSettings = () =>
            {
                var settings = new JsonSerializerSettings();
                settings.Converters.Add(new StringEnumConverter());
                settings.Formatting = Formatting.Indented;
                return settings;
            };
        }

        /// <summary>
        ///     Serializes T into a XML string.
        /// </summary>
        /// <param name="instance">The instance to serialize.</param>
        /// <returns></returns>
        public static string SerializeToJsonString<T>(in T instance) where T : new()
        {
            return JsonConvert.SerializeObject(instance);
        }

        /// <summary>
        ///     Deserializes the object from a XML string.
        /// </summary>
        /// <param name="data">The XML string.</param>
        /// <returns>The deserialized object.</returns>
        public static T DeserializeFromJsonString<T>(string data) where T : new()
        {
            return JsonConvert.DeserializeObject<T>(data) ?? new T();
        }

        /// <summary>
        ///     Serializes T into a XML file.
        /// </summary>
        /// <param name="instance">The instance to serialize.</param>
        /// <param name="path">The file to serialize into.</param>
        public static void SerializeToJsonFile<T>(in T instance, string path) where T : new()
        {
            File.WriteAllText(path, JsonConvert.SerializeObject(instance));
        }

        /// <summary>
        ///     Deserializes the object from a XML file.
        /// </summary>
        /// <param name="path">The file to serialize from.</param>
        /// <returns>The deserialized object.</returns>
        public static T DeserializeFromJsonFile<T>(string path) where T : new()
        {
            return JsonConvert.DeserializeObject<T>(File.ReadAllText(path)) ?? new T();
        }

        /// <summary>
        ///     Serializes T into a binary file.
        /// </summary>
        /// <param name="instance">The instance to serialize.</param>
        /// <param name="path">The file to serialize into.</param>
        public static void SerializeToBinaryFile<T>(in T instance, string path) where T : new()
        {
            if (instance == null) throw new ArgumentNullException(nameof(instance));
            var formatter = new BinaryFormatter();
            using var stream = new FileStream(path, FileMode.OpenOrCreate);
            formatter.Serialize(stream, instance);
            stream.Flush(true);
        }

        /// <summary>
        ///     Deserializes the object from a binary file.
        /// </summary>
        /// <param name="path">The file to serialize from.</param>
        /// <returns>The deserialized object.</returns>
        public static T DeserializeFromBinaryFile<T>(string path) where T : new()
        {
            var formatter = new BinaryFormatter();
            using var stream = new FileStream(path, FileMode.Open);
            object result = formatter.Deserialize(stream);
            return (T) result;
        }
    }
}