#include "gui.hpp"
#include "theme.hpp"

namespace dce::gui
{
	Gui::Gui() : ISubsystem("OverlayGui", EVENTS) { }

	auto Gui::on_pre_startup(Runtime& _rt) -> bool
	{
		this->gui_context_ = ImGui::CreateContext();
		if (this->gui_context_ == nullptr) [[unlikely]]
		{
			return false;
		}

		this->plot_context_ = ImPlot::CreateContext();
		if (this->plot_context_ == nullptr) [[unlikely]]
		{
			return false;
		}

		auto& io = ImGui::GetIO();
		io.IniFilename = nullptr;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.MouseDrawCursor = true;

		auto& cfg = _rt.config().editor;
		style_apply(SystemTheme::DARK);
		style_antialiasing_apply(cfg.enable_font_anti_aliasing);
		style_alpha_apply(cfg.alpha);
		style_rounding_apply(cfg.rounding);

		if (cfg.enable_auto_font_size) [[likely]]
		{
			const auto w = _rt.config().display.resolution.width;
			const auto h = _rt.config().display.resolution.height;
			if (w <= 2560 && h <= 1440) [[unlikely]]
			{
				cfg.custom_font_size = cfg.auto_font_size_whqh;
			}
			else if (w <= 3840 && h <= 2160) [[unlikely]]
			{
				cfg.custom_font_size = cfg.auto_font_size_uhd;
			}
			else
			{
				cfg.custom_font_size = cfg.auto_font_size_fhd;
			}
		}

		cfg.custom_font_size = std::clamp<decltype(cfg.custom_font_size)>(cfg.custom_font_size, 10, 28);

		if (!this->gui_input_.initialize()) [[unlikely]]
		{
			return false;
		}

		if (!this->gui_renderer_.initialize(_rt.config().editor.custom_font_size)) [[unlikely]]
		{
			return false;
		}

		this->terminal_.initialize(_rt.protocol(), _rt.scripting_protocol());
		this->editor_.initialize(_rt);

		return true;
	}

	auto Gui::on_pre_tick(Runtime& _rt) -> bool
	{
		const auto width = _rt.config().display.resolution.width;
		const auto height = _rt.config().display.resolution.height;
		this->begin(width, height);
		return true;
	}

	auto Gui::on_post_tick(Runtime& _rt) -> bool
	{
		this->editor_.update(_rt, _rt.config().editor.show_terminal);
		if (_rt.input().is_key_down(Key::GRAVE_ACCENT)) [[unlikely]]
		{
			_rt.config().editor.show_terminal = true;
		}
		if (_rt.config().editor.show_terminal) [[unlikely]]
		{
			this->terminal_.update(_rt.config().editor.show_terminal, _rt);
		}
		this->end();

		return true;
	}

	auto Gui::on_pre_shutdown([[maybe_unused]] Runtime&) -> bool
	{
		this->gui_input_.shutdown();
		this->gui_renderer_.shutdown();
		return true;
	}

	void Gui::begin(const std::uint16_t _width, const std::uint16_t _height)
	{
		this->gui_input_.update();
		ImGui::NewFrame();
	}

	void Gui::end() const
	{
		ImGui::EndFrame();
		ImGui::Render();
		if (const ImDrawData* const data = ImGui::GetDrawData(); data) [[likely]]
		{
			this->gui_renderer_.render(data);
		}
	}
} // namespace dce::gui // namespace dce::gui
