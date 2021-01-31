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

#include <string_view>

namespace PowerRonin
{
	/// <summary>
	/// Represents the style of a message box.
	/// </summary>
	enum class MessageBoxStyle
	{
		/// <summary>
		/// Info style.
		/// </summary>
		Info,

		/// <summary>
		/// Warning style.
		/// </summary>
		Warning,

		/// <summary>
		/// Error style.
		/// </summary>
		Error,

		/// <summary>
		/// Question style.
		/// </summary>
		Question
	};

	/// <summary>
	/// Type of buttons.
	/// </summary>
	enum class MessageBoxButtons
	{
		/// <summary>
		/// Ok button.
		/// </summary>
		Ok,

		/// <summary>
		/// Ok and cancel button.
		/// </summary>
		OkCancel,

		/// <summary>
		/// Yes and no button.
		/// </summary>
		YesNo
	};

	/// <summary>
	/// Return type of message box type.
	/// </summary>
	enum class MessageBoxSelection
	{
		/// <summary>
		/// Used pressed ok.
		/// </summary>
		Ok,

		/// <summary>
		/// Used pressed cancel.
		/// </summary>
		Cancel,

		/// <summary>
		/// Used pressed yes.
		/// </summary>
		Yes,

		/// <summary>
		/// Used pressed no.
		/// </summary>
		No,

		/// <summary>
		/// Used pressed none.
		/// </summary>
		None
	};

	/// <summary>
	/// Shows an os-specific message box.
	/// </summary>
	/// <param name="msg"></param>
	/// <param name="title"></param>
	/// <param name="style"></param>
	/// <param name="buttons"></param>
	/// <returns></returns>
	[[nodiscard]]
	extern auto ShowMessageBox(const std::string_view msg, const std::string_view title, const MessageBoxStyle style, const MessageBoxButtons buttons) -> MessageBoxSelection;
}
