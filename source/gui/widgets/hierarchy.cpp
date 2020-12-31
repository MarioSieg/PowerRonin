#include "hierarchy.hpp"
#include "../gui_headers.hpp"
#include "../window_names.hpp"
#include "../../../include/dce/comcollections.hpp"

using namespace ImGui;

namespace dce::gui::widgets {
	void Hierarchy::update(bool& _show, Registry& _registry) {
		SetNextWindowSize({300, 800}, ImGuiCond_FirstUseEver);
		[[likely]] if (Begin(HIERARCHY_NAME, &_show)) {
			[[unlikely]] if(Button(ICON_FA_PLUS_CIRCLE)) {
				const auto new_entity = _registry.create();
				_registry.emplace<MetaData>(new_entity).name = "New Entity " + std::to_string(++this->entity_counter_);
				_registry.emplace<Transform>(new_entity);	
				this->selected_ = new_entity;
			}

			[[unlikely]] if(IsItemHovered()) {
				BeginTooltip();
				TextUnformatted("Add new entity");
				EndTooltip();
			}

			SameLine();

			[[unlikely]]
			if((Button(ICON_FA_MINUS_CIRCLE) || IsKeyPressed(GetKeyIndex(ImGuiKey_Delete))) && _registry.valid(this->selected_)) {
				_registry.destroy(this->selected_);
				if(_registry.valid(static_cast<ERef>(static_cast<std::uint64_t>(this->selected_) + 1))) {
					this->selected_ = static_cast<ERef>(static_cast<std::uint64_t>(this->selected_) + 1);
				}
			}

			[[unlikely]] if (IsItemHovered()) {
				BeginTooltip();
				TextUnformatted("Delete selected entity");
				EndTooltip();
			}

			Separator();
			
			const auto footer_height_to_reserve = GetStyle().ItemSpacing.y + GetFrameHeightWithSpacing();
			[[likely]] if (BeginChild("", {.0, -footer_height_to_reserve}, false)) {
				_registry.view<MetaData>().each([this](const ERef _ref, MetaData& _meta) {
					PushID(&_meta.layer);
					[[unlikely]] if (Button(_meta.name.c_str())) {
						this->selected_ = _ref;
					}
					PopID();
				});
				EndChild();
			}
		}
		End();
	}

	auto Hierarchy::get_selected() const noexcept -> ERef {
		return this->selected_;
	}
}
