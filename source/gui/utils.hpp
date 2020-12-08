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
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

#include "gui_headers.hpp"
#include "../../include/dce/texture.hpp"
#include "../renderer/gl_headers.hpp"
#include <cstdint>

namespace dce::gui {
	constexpr auto imgui_rgba(const std::uint8_t _r
	                          , const std::uint8_t _g
	                          , const std::uint8_t _b
	                          , const std::uint8_t _a = 0xFF) noexcept -> std::uint32_t {
		return static_cast<std::uint32_t>(_r) << 0 | static_cast<std::uint32_t>(_g) << 8 | static_cast<std::uint32_t>(_b) << 16 |
			static_cast<std::uint32_t>(_a) << 24;
	}

	inline auto imgui_rgba_to_norm_vec4(const std::uint8_t _r
	                                    , const std::uint8_t _g
	                                    , const std::uint8_t _b
	                                    , const std::uint8_t _a = 0xFF) noexcept -> ImVec4 {
		return ImVec4{_r / 255.f, _g / 255.f, _b / 255.f, _a / 255.f,};
	}

	inline auto to_imgui_id(const bgfx::TextureHandle handle, const std::uint8_t flags, const std::uint8_t mip) -> ImTextureID {
		union {
			struct {
				bgfx::TextureHandle handle_s;
				std::uint8_t flags_s;
				std::uint8_t mip_s;
			} data;

			ImTextureID id;
		} tex;
		tex.data.handle_s = handle;
		tex.data.flags_s = flags;
		tex.data.mip_s = mip;
		return tex.id;
	}

	inline void image(const bgfx::TextureHandle handle
	                  , const std::uint8_t flags
	                  , const std::uint8_t mip
	                  , const ImVec2& size
	                  , const ImVec2& uv0 = ImVec2(0.0F, 0.0F)
	                  , const ImVec2& uv1 = ImVec2(1.0F, 1.0F)
	                  , const ImVec4& tint_col = ImVec4(1.0F, 1.0F, 1.0F, 1.0F)
	                  , const ImVec4& border_col = ImVec4(0.0F, 0.0F, 0.0F, 0.0F)) noexcept {
		ImGui::Image(to_imgui_id(handle, flags, mip), size, uv0, uv1, tint_col, border_col);
	}

	inline auto image(const bgfx::TextureHandle handle
	                  , const ImVec2& size
	                  , const ImVec2& uv0 = ImVec2(0.0F, 0.0F)
	                  , const ImVec2& uv1 = ImVec2(1.0F, 1.0F)
	                  , const ImVec4& tint_col = ImVec4(1.0F, 1.0F, 1.0F, 1.0F)
	                  , const ImVec4& border_col = ImVec4(0.0F, 0.0F, 0.0F, 0.0F)) noexcept -> void {
		image(handle, UINT8_C(0x01), 0, size, uv0, uv1, tint_col, border_col);
	}

	inline auto image(const RRef<Texture>& texture
	                  , const ImVec2& size
	                  , const ImVec2& uv0 = ImVec2(0.0F, 0.0F)
	                  , const ImVec2& uv1 = ImVec2(1.0F, 1.0F)
	                  , const ImVec4& tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
	                  , const ImVec4& border_col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)) noexcept -> void {
		image({texture->get_texel_buffer_id()}, UINT8_C(0x01), 0, size, uv0, uv1, tint_col, border_col);
	}

	inline auto image_button(const bgfx::TextureHandle handle
	                         , const std::uint8_t flags
	                         , const std::uint8_t mip
	                         , const ImVec2& size
	                         , const ImVec2& uv0 = ImVec2(0.0F, 0.0F)
	                         , const ImVec2& uv1 = ImVec2(1.0F, 1.0F)
	                         , const int frame_padding = -1
	                         , const ImVec4& bg_col = ImVec4(0.0F, 0.0F, 0.0F, 0.0F)
	                         , const ImVec4& tint_col = ImVec4(1.0F, 1.0F, 1.0F, 1.0F)) noexcept -> bool {
		return ImGui::ImageButton(to_imgui_id(handle, flags, mip), size, uv0, uv1, frame_padding, bg_col, tint_col);
	}

	inline auto image_button(const bgfx::TextureHandle handle
	                         , const ImVec2& size
	                         , const ImVec2& uv0 = ImVec2(0.0F, 0.0F)
	                         , const ImVec2& uv1 = ImVec2(1.0F, 1.0F)
	                         , const int frame_padding = -1
	                         , const ImVec4& bg_col = ImVec4(0.0F, 0.0F, 0.0F, 0.0F)
	                         , const ImVec4& tint_col = ImVec4(1.0F, 1.0F, 1.0F, 1.0F)) noexcept -> bool {
		return image_button(handle, UINT8_C(0x01), 0, size, uv0, uv1, frame_padding, bg_col, tint_col);
	}

	inline auto image_button(const RRef<Texture>& texture
	                         , const ImVec2& size
	                         , const ImVec2& uv0 = ImVec2(0.0F, 0.0F)
	                         , const ImVec2& uv1 = ImVec2(1.0F, 1.0F)
	                         , const int frame_padding = -1
	                         , const ImVec4& bg_col = ImVec4(0.0F, 0.0F, 0.0F, 0.0F)
	                         , const ImVec4& tint_col = ImVec4(1.0F, 1.0F, 1.0F, 1.0F)) noexcept -> bool {
		return image_button({texture->get_texel_buffer_id()}, UINT8_C(0x01), 0, size, uv0, uv1, frame_padding, bg_col, tint_col);
	}

	inline auto is_mouse_over_area() noexcept -> bool {
		return ImGui::IsAnyItemHovered() || ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
	}

	inline auto embedded_button(const char* const _txt) -> bool {
		ImGui::PushStyleColor(ImGuiCol_Button, 0x00000000);
		const auto result = ImGui::SmallButton(_txt);
		ImGui::PopStyleColor();
		return result;
	}
} // namespace dce::gui // namespace dce::gui
