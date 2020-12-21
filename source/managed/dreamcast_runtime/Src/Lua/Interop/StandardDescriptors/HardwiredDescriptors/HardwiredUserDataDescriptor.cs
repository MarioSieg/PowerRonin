using System;
using Dreamcast.Lua.Interpreter.Interop.BasicDescriptors;

namespace Dreamcast.Lua.Interpreter.Interop.StandardDescriptors.HardwiredDescriptors
{
    public abstract class HardwiredUserDataDescriptor : DispatchingUserDataDescriptor
    {
        protected HardwiredUserDataDescriptor(Type T) :
            base(T, "::hardwired::" + T.Name)
        {
        }
    }
}