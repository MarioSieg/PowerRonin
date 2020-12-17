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
using System.Xml.Serialization;

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
        public static string Serialize(in T instance)
        {
            var serializer = new XmlSerializer(typeof(T));
            using (var stream = new StringWriter())
            {
                serializer.Serialize(stream, instance);
                return stream.ToString();
            }
        }

        /// <summary>
        ///     Serializes T into a XML string and writes it into a file.
        /// </summary>
        /// <param name="instance">The instance to serialize.</param>
        /// <param name="fileName">The file to serialize into.</param>
        public static void SerializeToFile(in T instance, string fileName)
        {
            var serializer = new XmlSerializer(typeof(T));
            using (var stream = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                serializer.Serialize(stream, instance);
                stream.Flush(true);
            }
        }

        /// <summary>
        ///     Serializes T into a binary file.
        /// </summary>
        /// <param name="instance">The instance to serialize.</param>
        /// <param name="fileName">The file to serialize into.</param>
        public static void SerializeToBinaryFile(in T instance, string fileName)
        {
            var formatter = new BinaryFormatter();
            using (var stream = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                formatter.Serialize(stream, instance);
                stream.Flush(true);
            }
        }
    }
}