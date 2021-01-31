// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#pragma once

/* Helper to do stuff like:

	int main()
	{
	    std::variant<Fluid, LightItem, HeavyItem, FragileItem> package;

	    std::visit(overload{
	        [](Fluid& ) { cout << "fluid\n"; },
	        [](LightItem& ) { cout << "light item\n"; },
	        [](HeavyItem& ) { cout << "heavy item\n"; },
	        [](FragileItem& ) { cout << "fragile\n"; }
	    }, package);
	}
	
 */

namespace PowerRonin
{
	/// <summary>
	/// std::visit helper to implement the overload pattern on std::variant
	/// 
	/// </summary>
	/// <typeparam name="...Ts"></typeparam>
	template <class... Ts>
	struct overload : Ts...
	{
		using Ts::operator()...;
	};

	template <class... Ts>
	overload(Ts ...) -> overload<Ts...>;
}
