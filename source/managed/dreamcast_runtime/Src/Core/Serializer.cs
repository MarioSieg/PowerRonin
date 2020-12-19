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

using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using Dreamcast.Json;
using Dreamcast.Json.Converters;

namespace Dreamcast.Core
{
    /// <summary>
    ///     Contains helpers for de/serialization.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public static class Serializer<T>
    {
        /// <summary>
        ///     Serializes T into a XML string.
        /// </summary>
        /// <param name="instance">The instance to serialize.</param>
        /// <returns></returns>
        public static string SerializeToJsonString(in T instance)
        {
            return JsonConvert.SerializeObject(instance, Formatting.Indented, new StringEnumConverter());
        }

        /// <summary>
        ///     Deserializes the object from a XML string.
        /// </summary>
        /// <param name="data">The XML string.</param>
        /// <returns>The deserialized object.</returns>
        public static T DeserializeFromJsonString(string data)
        {
            return (T) JsonConvert.DeserializeObject(data);
        }

        /// <summary>
        ///     Serializes T into a XML file.
        /// </summary>
        /// <param name="instance">The instance to serialize.</param>
        /// <param name="path">The file to serialize into.</param>
        public static void SerializeToJsonFile(in T instance, string path)
        {
            File.WriteAllText(path, JsonConvert.SerializeObject(instance, Formatting.Indented, new StringEnumConverter()));
        }

        /// <summary>
        ///     Deserializes the object from a XML file.
        /// </summary>
        /// <param name="path">The file to serialize from.</param>
        /// <returns>The deserialized object.</returns>
        public static T DeserializeFromJsonFile(string path)
        {
            return (T) JsonConvert.DeserializeObject(File.ReadAllText(path));
        }

        /// <summary>
        ///     Serializes T into a binary file.
        /// </summary>
        /// <param name="instance">The instance to serialize.</param>
        /// <param name="path">The file to serialize into.</param>
        public static void SerializeToBinaryFile(in T instance, string path)
        {
            var formatter = new BinaryFormatter();
            using (var stream = new FileStream(path, FileMode.OpenOrCreate))
            {
                formatter.Serialize(stream, instance);
                stream.Flush(true);
            }
        }

        /// <summary>
        ///     Deserializes the object from a binary file.
        /// </summary>
        /// <param name="path">The file to serialize from.</param>
        /// <returns>The deserialized object.</returns>
        public static T DeserializeFromBinaryFile(string path)
        {
            object result;
            var formatter = new BinaryFormatter();
            using (var stream = new FileStream(path, FileMode.Open))
            {
                result = formatter.Deserialize(stream);
            }

            return (T) result;
        }
    }
}