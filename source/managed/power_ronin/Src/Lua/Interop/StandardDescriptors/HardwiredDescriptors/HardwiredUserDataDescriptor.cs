using System;
using PowerRonin.Lua.Interpreter.Interop.BasicDescriptors;

namespace PowerRonin.Lua.Interpreter.Interop.StandardDescriptors.HardwiredDescriptors
{
    public abstract class HardwiredUserDataDescriptor : DispatchingUserDataDescriptor
    {
        protected HardwiredUserDataDescriptor(Type T) :
            base(T, "::hardwired::" + T.Name)
        {
        }
    }
}