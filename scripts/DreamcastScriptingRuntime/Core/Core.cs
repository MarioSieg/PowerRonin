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

namespace Dreamcast.Core
{
    /// <summary>
    ///     Engine core class.
    /// </summary>
    public static class Core
    {
        private static void OnPreStartup()
        {
            CommandDB.RegisterCommonCommands();
            CommandDB.Execute("info");
            Configuration.Deserialize();
            Configuration.Current.Apply();
        }

        private static void OnPostStartup()
        {
        }

        private static void OnPreTick()
        {
            Input.Update();
        }

        private static void OnPostTick()
        {
        }

        private static void OnPreShutdown()
        {
        }

        private static void OnPostShutdown()
        {
        }
    }
}