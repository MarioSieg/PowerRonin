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

namespace Dreamcast.Lua.Interpreter
{
    /// <summary>
    ///     Common interface for all resources which are uniquely bound to a script.
    /// </summary>
    public interface IScriptPrivateResource
    {
        /// <summary>
        ///     Gets the script owning this resource.
        /// </summary>
        /// <value>
        ///     The script owning this resource.
        /// </value>
        Script OwnerScript { get; }
    }

    internal static class ScriptPrivateResource_Extension
    {
        public static void CheckScriptOwnership(this IScriptPrivateResource containingResource, DynValue[] values)
        {
            foreach (DynValue v in values)
                CheckScriptOwnership(containingResource, v);
        }


        public static void CheckScriptOwnership(this IScriptPrivateResource containingResource, DynValue value)
        {
            if (value != null)
            {
                var otherResource = value.GetAsPrivateResource();

                if (otherResource != null) CheckScriptOwnership(containingResource, otherResource);
            }
        }

        public static void CheckScriptOwnership(this IScriptPrivateResource resource, Script script)
        {
            if (resource.OwnerScript != null && resource.OwnerScript != script && script != null) throw new ScriptRuntimeException("Attempt to access a resource owned by a script, from another script");
        }

        public static void CheckScriptOwnership(this IScriptPrivateResource containingResource, IScriptPrivateResource itemResource)
        {
            if (itemResource != null)
            {
                if (containingResource.OwnerScript != null && containingResource.OwnerScript != itemResource.OwnerScript && itemResource.OwnerScript != null)
                    throw new ScriptRuntimeException("Attempt to perform operations with resources owned by different scripts.");
                if (containingResource.OwnerScript == null && itemResource.OwnerScript != null) throw new ScriptRuntimeException("Attempt to perform operations with a script private resource on a shared resource.");
            }
        }
    }
}