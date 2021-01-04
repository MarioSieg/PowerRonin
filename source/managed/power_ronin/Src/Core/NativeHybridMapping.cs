using System;

namespace PowerRonin.Core
{
    [AttributeUsage(AttributeTargets.Struct)]
    internal sealed class NativeHybridMapping : Attribute
    {
        public NativeHybridMapping(string nativeName, string nativeFile)
        {
            NativeStructName = nativeName;
            NativeFileName = nativeFile;
        }

        public string NativeStructName { get; }
        public string NativeFileName { get; }
    }
}