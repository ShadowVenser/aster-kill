#include "Gui.h"
#include <bit>
#include <string>
#include "imgui.h"


void Gui::BindGui(my_game::GuiBinder& binder)
{
    _world = binder.world;
    _visible = binder.isGuiVisible;
    _renderer = binder.renderer;

    _meanTime = binder.meanTime;
    _stdTime = binder.stdTime;

    _meanTimeBorders.x = 0.5f * (*_meanTime);
    _meanTimeBorders.y = 1.5f * (*_meanTime);

    _stdTimeBorders.x = (2.f / 2.5f) * (*_stdTime);
    _stdTimeBorders.y = (3.f / 2.5f) * (*_stdTime);

    _spawner = binder.spawner;
}

void Gui::UpdateGui()
{
    if (*_visible)
    {
        auto delta = _deltaClock.restart();
        ImGui::SFML::Update(*_renderer, delta);

        ImGui::Begin("Aster Gui");

        ImGui::SliderFloat("Mean spawn time", _meanTime, _meanTimeBorders.x, _meanTimeBorders.y, "Mean = %.1f");
        ImGui::SliderFloat("STD spawn time", _stdTime, _stdTimeBorders.x, _stdTimeBorders.y, "STD = %.1f");

        if (ImGui::Button("Spawn asteroid"))
        {
            *_spawner = true;
        }

        if (ImGui::TreeNode("Entities"))
        {
            for (const auto& entity: _world->GetEntities())
            {
                if (_world->IsEntityAlive(entity.Id))
                {
                    ImGui::PushID(entity.Id);
                    if (ImGui::TreeNode("", "Entity #%d", entity.Id))
                    {
                        auto components = entity.Components();
                        while (components)
                        {
                            auto storageId = std::countr_zero(components);
                            components &= components - 1;
                            ImGui::BulletText("%s", _GetDemangleNameById(storageId).c_str());
                        }
                        ImGui::TreePop();
                    }
                    ImGui::PopID();
                }
            }
            ImGui::TreePop();
        }

        ImGui::End();
        _prepared = true;
    }
}

void Gui::DrawGui()
{
    if (*_visible && _prepared)
    {
        ImGui::SFML::Render(*_renderer);
        _prepared = false;
    }
}

std::string Gui::_GetDemangleNameById(int storageId)
{
    static int status {0};
    auto ptr = _world->GetStorageById(storageId).get();
    auto mangleName = typeid(*ptr).name();
    char* name = abi::__cxa_demangle(mangleName, 0, 0, &status);
    std::string output { status ? mangleName : name };
    free(name);
    return output;
}
