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

#include <cstdint>
#include "mathlib.hpp"

namespace PowerRonin
{
	/* Represents a keyboard key. */
	enum class Key : std::int16_t
	{
		Unknown = - 1

		/* Printable keys */

		,
		Space = 32,
		Apostrophe = 39 /* ' */
		,
		Comma = 44 /* , */
		,
		Minus = 45 /* - */
		,
		Period = 46 /* . */
		,
		Slash = 47 /* / */
		,
		N0 = 48,
		N1 = 49,
		N2 = 50,
		N3 = 51,
		N4 = 52,
		N5 = 53,
		N6 = 54,
		N7 = 55,
		N8 = 56,
		N9 = 57,
		Semicolon = 59 /* ; */
		,
		Equal = 61 /* = */
		,
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		LeftBracket = 91 /* [ */
		,
		Backslash = 92 /* \ */
		,
		RightBracket = 93 /* ] */
		,
		GraveAccent = 96 /* ` */
		,
		World1 = 161 /* non-US #1 */
		,
		World2 = 162 /* non-US #2 */

		/* Function keys */

		,
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,
		Keypad0 = 320,
		Keypad1 = 321,
		Keypad2 = 322,
		Keypad3 = 323,
		Keypad4 = 324,
		Keypad5 = 325,
		Keypad6 = 326,
		Keypad7 = 327,
		Keypad8 = 328,
		Keypad9 = 329,
		KeypadDecimal = 330,
		KeypadDivide = 331,
		KeypadMultiply = 332,
		KeypadSubtract = 333,
		KeypadAdd = 334,
		KeypadEnter = 335,
		KeypadEqual = 336,
		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	};

	/* Represents a mouse button. */
	enum class MouseButton : std::uint8_t
	{
		Left = 0,
		Right = 1,
		Middle = 2,
	};

	/* Contains input methods and helpers. */
	class Input final
	{
	public:
		[[nodiscard]] auto IsKeyDown(Key key) const noexcept -> bool;

		[[nodiscard]] auto IsMouseButtonDown(MouseButton mouseButton) const noexcept -> bool;

		[[nodiscard]] auto MousePosition() const noexcept -> Vector2<>;
	};
}
