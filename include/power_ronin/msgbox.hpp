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

namespace power_ronin
{
	/// <summary>
	/// Represents the style of a message box.
	/// </summary>
	enum class MessageBoxStyle
	{
		/// <summary>
		/// Info style.
		/// </summary>
		INFO,

		/// <summary>
		/// Warning style.
		/// </summary>
		WARNING,

		/// <summary>
		/// Error style.
		/// </summary>
		ERROR,

		/// <summary>
		/// Question style.
		/// </summary>
		QUESTION
	};

	/// <summary>
	/// Type of buttons.
	/// </summary>
	enum class MessageBoxButtons
	{
		/// <summary>
		/// Ok button.
		/// </summary>
		OK,

		/// <summary>
		/// Ok and cancel button.
		/// </summary>
		OK_CANCEL,

		/// <summary>
		/// Yes and no button.
		/// </summary>
		YES_NO
	};

	/// <summary>
	/// Return type of message box type.
	/// </summary>
	enum class MessageBoxSelection
	{
		/// <summary>
		/// Used pressed ok.
		/// </summary>
		OK,

		/// <summary>
		/// Used pressed cancel.
		/// </summary>
		CANCEL,

		/// <summary>
		/// Used pressed yes.
		/// </summary>
		YES,

		/// <summary>
		/// Used pressed no.
		/// </summary>
		NO,

		/// <summary>
		/// Used pressed none.
		/// </summary>
		NONE
	};

	/// <summary>
	/// Shows an os-specific message box.
	/// </summary>
	/// <param name="_msg"></param>
	/// <param name="_title"></param>
	/// <param name="_style"></param>
	/// <param name="_buttons"></param>
	/// <returns></returns>
	[[nodiscard]]
	extern auto show_message_box(const std::string_view _msg, const std::string_view _title, const MessageBoxStyle _style, const MessageBoxButtons _buttons) -> MessageBoxSelection;
}
