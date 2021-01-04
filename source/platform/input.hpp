#pragma once

struct GLFWcursor;

namespace power_ronin::platform
{
	class GuiInput final
	{
	public:
		auto initialize() -> bool;
		void update();
		void shutdown();
		void update_mouse();
		void update_cursor();
		void update_gamepads();
		void install_callback_procedures() const;

	private:
		bool mouse_buttons[5] = {};
		GLFWcursor* cursors[9] = {};
		double timer = .0;
		void* window = nullptr;
	};
} // namespace power_ronin::platform // namespace power_ronin::platform
