#include "../../Include/PowerRonin/MessageBox.hpp"
#include "../../Include/PowerRonin/Platform.hpp"

#if OS_WINDOWS

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace PowerRonin
{
	static inline auto get_icon(const MessageBoxStyle _style) noexcept -> UINT
	{
		switch (_style)
		{
			case MessageBoxStyle::Info:
				return MB_ICONINFORMATION;
			case MessageBoxStyle::Warning:
				return MB_ICONWARNING;
#undef ERROR
			case MessageBoxStyle::Error:
#define ERROR 0
				return MB_ICONERROR;
			case MessageBoxStyle::Question:
				return MB_ICONQUESTION;
		}
	}

	static inline auto get_buttons(const MessageBoxButtons _buttons) noexcept -> UINT
	{
		switch (_buttons)
		{
			case MessageBoxButtons::Ok:
				return MB_OK;
			case MessageBoxButtons::OkCancel:
				return MB_OKCANCEL;
			case MessageBoxButtons::YesNo:
				return MB_YESNO;
		}
	}

	static inline auto get_selection(const int _response) noexcept -> MessageBoxSelection
	{
		switch (_response)
		{
			case IDOK:
				return MessageBoxSelection::Ok;
			case IDCANCEL:
				return MessageBoxSelection::Cancel;
			case IDYES:
				return MessageBoxSelection::Yes;
			case IDNO:
				return MessageBoxSelection::No;
			default:
				return MessageBoxSelection::None;
		}
	}

	static inline auto ShowMessageBox(const std::string_view msg, const std::string_view title, const MessageBoxStyle style, const MessageBoxButtons buttons) -> MessageBoxSelection
	{
		UINT flags = MB_TASKMODAL;

		flags |= get_icon(style);
		flags |= get_buttons(buttons);

		return get_selection(MessageBox(nullptr, msg.data(), title.data(), flags));
	}
}


#endif

#if OS_LINUX
#include <gtk/gtk.h>

namespace PowerRonin
{
    static inline auto get_icon(const MessageBoxStyle _style) noexcept -> GtkMessageType
    {
        switch (_style) {
        case MessageBoxStyle::INFO:
            return GTK_MESSAGE_INFO;
        case MessageBoxStyle::WARNING:
            return GTK_MESSAGE_WARNING;
        case MessageBoxStyle::ERROR:
            return GTK_MESSAGE_ERROR;
        case MessageBoxStyle::QUESTION:
            return GTK_MESSAGE_INFO;
        }
    }

    static inline auto get_buttons(const MessageBoxButtons _buttons) noexcept -> GtkButtonsType
    {
        switch (_buttons) {
        case MessageBoxButtons::OK:
            return GTK_BUTTONS_OK;
        case MessageBoxButtons::OK_CANCEL:
            return GTK_BUTTONS_OK_CANCEL;
        case MessageBoxButtons::YES_NO:
            return GTK_BUTTONS_YES_NO;
        }
    }

    static inline auto get_selection(const gint _response) noexcept -> MessageBoxSelection
    {
        switch (_response) {
        case GTK_RESPONSE_OK:
            return MessageBoxSelection::OK;
        case GTK_RESPONSE_CANCEL:
            return MessageBoxSelection::CANCEL;
        case GTK_RESPONSE_YES:
            return MessageBoxSelection::YES;
        case GTK_RESPONSE_NO:
            return MessageBoxSelection::NO;
        default:
            return MessageBoxSelection::NONE;
        }
    }

    auto show_message_box(const std::string_view _msg, const std::string_view _title, const MessageBoxStyle _style, const MessageBoxButtons _buttons) -> MessageBoxSelection
    {
        if (!gtk_init_check(0, nullptr)) {
            return MessageBoxSelection::NONE;
        }

        auto* const dialog = gtk_message_dialog_new(nullptr,
            GTK_DIALOG_MODAL,
            get_icon(_style),
            get_buttons(_buttons),
            "%s",
            _msg.data());
        gtk_window_set_title(GTK_WINDOW(dialog), _title.data());
        auto selection = get_selection(gtk_dialog_run(GTK_DIALOG(dialog)));

        gtk_widget_destroy(GTK_WIDGET(dialog));
        while (g_main_context_iteration(nullptr, false));

        return selection;
    }
}


#endif
