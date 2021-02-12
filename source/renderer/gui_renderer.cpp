#include "gui_renderer.hpp"
#include "renderer.hpp"
#include "utils.hpp"
#include "../../Include/PowerRonin/MathLib.hpp"
#include "../gui/font_headers.hpp"
#include "../gui/gui_headers.hpp"
#include "../renderer/program_loader.hpp"

#include <algorithm>

namespace PowerRonin::Renderer
{
	auto GuiRenderer::initialize(const std::uint8_t _font_size) -> bool
	{
		auto& io = ImGui::GetIO();
		const auto type = bgfx::getRendererType();

		this->gui_program_ = load_shader_program("gui_color");

		if (this->gui_program_.idx == bgfx::kInvalidHandle) [[unlikely]]
		{
			return false;
		}

		this->image_lod_enabled_ = createUniform("u_imageLodEnabled", bgfx::UniformType::Vec4);

		if (this->image_lod_enabled_.idx == bgfx::kInvalidHandle) [[unlikely]]
		{
			return false;
		}

		this->gui_image_program_ = load_shader_program("gui_image");

		if (this->gui_image_program_.idx == bgfx::kInvalidHandle) [[unlikely]]
		{
			return false;
		}

		layout.begin().add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float).
		       add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float).add(
			       bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true).
		       end();

		this->texture_uniform_ = createUniform("s_tex", bgfx::UniformType::Sampler);
		if (this->texture_uniform_.idx == bgfx::kInvalidHandle) [[unlikely]]
		{
			return false;
		}

		std::uint8_t* data = nullptr;
		std::int32_t lwidth = 0;
		std::int32_t lheight = 0;
		{
			const auto* ranges = io.Fonts->GetGlyphRangesDefault();
			ImFontConfig config;
			config.FontDataOwnedByAtlas = false;
			config.MergeMode = false;

			if (io.Fonts->AddFontFromFileTTF("fonts/jet_brains_mono_regular.ttf",
			                                 static_cast<float>(_font_size) - 3.F
			                                 , &config, ranges) == nullptr) [[unlikely]]
			{
				return false;
			}

			config.MergeMode = true;
			ImWchar glyph_ranges[3] = {};

			glyph_ranges[0] = ICON_MIN_FA;
			glyph_ranges[1] = ICON_MAX_FA;
			/*
			if (io.Fonts->AddFontFromMemoryTTF((void *)ICONS_FONT_AWESOME_TTF,
			                                   sizeof ICONS_FONT_AWESOME_TTF,
			                                   static_cast<float>(font_size) - 3.F,
			                                   &config,
			                                   glyph_ranges) == nullptr) {
			        return false;
			}
			*/
			if (!io.Fonts->AddFontFromFileTTF("fonts/font_awesome_pro_regular.ttf"
			                                  , static_cast<float>(_font_size) - 3.F, &config,
			                                  glyph_ranges)) [[unlikely]]
			{
				return false;
			}

			config.MergeMode = false;
			config.DstFont = font_;
		}

		io.Fonts->GetTexDataAsRGBA32(&data, &lwidth, &lheight);

		this->texture_ = createTexture2D(static_cast<uint16_t>(lwidth), static_cast<uint16_t>(lheight), false, 1
		                                 , bgfx::TextureFormat::BGRA8, 0, bgfx::copy(data, lwidth * lheight * 4));
		return this->texture_.idx != bgfx::kInvalidHandle;
	}

	void GuiRenderer::render(const ImDrawData* const _data) const
	{
		const auto& io = ImGui::GetIO();
		const auto width = static_cast<std::uint16_t>(io.DisplaySize.x);
		const auto height = static_cast<std::uint16_t>(io.DisplaySize.y);
		setViewMode(GUI_VIEW, bgfx::ViewMode::Sequential);
		{
			Matrix4x4<> ortho = Math::ortho(.0F, static_cast<float>(width), static_cast<float>(height), .0F, .0F,
			                                1000.F);
			bgfx::setViewTransform(GUI_VIEW, nullptr, Math::value_ptr(ortho));
			bgfx::setViewRect(GUI_VIEW, 0, 0, width, height);
		}

		for (auto i = 0; i < _data->CmdListsCount; ++i)
		{
			const auto* draw_list = _data->CmdLists[i];
			const auto vertex_count = draw_list->VtxBuffer.size();
			const auto index_count = draw_list->IdxBuffer.size();

			if (!check_available_transient_buffers(vertex_count, index_count, &layout)) [[unlikely]]
			{
				break;
			}

			bgfx::TransientVertexBuffer tvb{};
			bgfx::TransientIndexBuffer tib{};

			allocTransientVertexBuffer(&tvb, vertex_count, layout);
			allocTransientIndexBuffer(&tib, index_count);

			auto& vertices = *reinterpret_cast<ImDrawVert*const>(tvb.data);
			auto& indices = *reinterpret_cast<ImDrawIdx*const>(tib.data);

			memcpy(&vertices, draw_list->VtxBuffer.begin(), vertex_count * sizeof(ImDrawVert));
			memcpy(&indices, draw_list->IdxBuffer.begin(), index_count * sizeof(ImDrawIdx));

			std::uint32_t offset = 0;
			for (const auto *cmd = draw_list->CmdBuffer.begin(), *end = draw_list->CmdBuffer.end(); cmd != end; ++cmd)
			{
				if (cmd->UserCallback) [[unlikely]]
				{
					cmd->UserCallback(draw_list, cmd);
				}
				else if (cmd->ElemCount != 0u)
				{
					auto state = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_MSAA;

					auto textureHandle = this->texture_;
					auto program = this->gui_program_;
					if (cmd->TextureId != nullptr) [[likely]]
					{
						const union
						{
							ImTextureID ptr;

							struct
							{
								bgfx::TextureHandle handle;
								std::uint8_t flags;
								std::uint8_t mip;
							} data;
						} texture1 = {cmd->TextureId};
						state |= (0x01 & texture1.data.flags) != 0
							         ? BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
							         : BGFX_STATE_NONE;
						textureHandle = texture1.data.handle;
						if (texture1.data.mip != 0u) [[unlikely]]
						{
							const float lod_enabled[4] = {static_cast<float>(texture1.data.mip), 1.F, .0F, .0F};
							setUniform(this->image_lod_enabled_, lod_enabled);
							program = this->gui_image_program_;
						}
					}
					else
					{
						state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
					}

					const auto xx = static_cast<std::uint16_t>(std::max(cmd->ClipRect.x, .0F));
					const auto yy = static_cast<std::uint16_t>(std::max(cmd->ClipRect.y, .0F));
					bgfx::setScissor(xx, yy, static_cast<std::uint16_t>(std::min(cmd->ClipRect.z, 65535.F) - xx)
					                 , static_cast<std::uint16_t>(std::min(cmd->ClipRect.w, 65535.F) - yy));

					bgfx::setState(state);
					setTexture(0, this->texture_uniform_, textureHandle);
					setVertexBuffer(0, &tvb, 0, vertex_count);
					setIndexBuffer(&tib, offset, cmd->ElemCount);
					submit(GUI_VIEW, program);
				}
				offset += cmd->ElemCount;
			}
		}
	}

	void GuiRenderer::shutdown() const
	{
		destroy(this->texture_uniform_);
		destroy(this->image_lod_enabled_);
		destroy(this->gui_program_);
		destroy(this->gui_image_program_);
	}
} // namespace PowerRonin::renderer // namespace PowerRonin::renderer
