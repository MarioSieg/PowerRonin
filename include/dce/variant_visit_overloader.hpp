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

namespace dce
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
