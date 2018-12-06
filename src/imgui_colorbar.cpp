// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2018 Jérémie Dumas <jeremie.dumas@ens-lyon.org>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include "imgui_colorbar.h"
#include <GLFW/glfw3.h>
#include <igl/opengl/glfw/Viewer.h>
#include <imgui/imgui.h>
#include <iostream>
////////////////////////////////////////////////////////////////////////////////

namespace pyviewer {

void ColorbarPlugin::init_colormaps()
{
    Eigen::MatrixXd rgb;
    for (size_t i = 0; i < igl::NUM_COLOR_MAP_TYPES; ++i) {
        GLuint id = 0;
        colormap(static_cast<igl::ColorMapType>(i), rgb);
        texture_from_colormap(rgb, id);
        colormaps_[i] = id;
    }
}

int ColorbarPlugin::draw_colormap_combo() const
{
    const char* items[] {
        "Inferno",
        "Jet",
        "Magma",
        "Parula",
        "Plasma",
        "Viridis",
    };
    static int selected_index = 5;
    static const char* current_item = items[selected_index];
    ImVec2 combo_pos = ImGui::GetCursorScreenPos();
    if (ImGui::BeginCombo("Colormap##combo", "")) {
        for (int n = 0; n < IM_ARRAYSIZE(items); ++n) {
            // You can store your selection however you want, outside or inside your objects
            bool is_selected = (current_item == items[n]);
            ImGui::PushID(n);
            if (ImGui::Selectable("", is_selected)) {
                current_item = items[n];
                selected_index = n;
            }
            ImGui::SameLine(0, 0);
            ImGui::Image(
                reinterpret_cast<ImTextureID>(colormaps_[n]),
                ImVec2(ImGui::GetTextLineHeight(), ImGui::GetTextLineHeight()),
                ImVec2(0, 0), ImVec2(1, 1));
            ImGui::SameLine();
            ImGui::Text("%s", items[n]);
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
            ImGui::PopID();
        }
        ImGui::EndCombo();
    }

    ImVec2 backup_pos = ImGui::GetCursorScreenPos();
    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::SetCursorScreenPos(ImVec2(combo_pos.x + style.FramePadding.x, combo_pos.y + style.FramePadding.y));
    float h = ImGui::GetTextLineHeight();
    ImGui::Image(
        reinterpret_cast<ImTextureID>(colormaps_[selected_index]),
        ImVec2(h, h));
    ImGui::SameLine();
    ImGui::Text("%s", current_item);
    ImGui::SetCursorScreenPos(backup_pos);

    return selected_index;
}

void ColorbarPlugin::draw_colorbar(
        const igl::ColorMapType cm,
        const double xmin, double xmax,
        const std::string label_min, const std::string label_max) const
{
    ImVec4 color(0, 0, 0, 1);

    float w = 20;
    float h = 100;
    ImGui::BeginGroup();
    ImGui::BeginGroup();
    ImGui::Text("%.3g%s", xmin, label_min.c_str());
    ImGui::Dummy(ImVec2(0, h - 2 * ImGui::GetTextLineHeightWithSpacing()));
    ImGui::Text("%.3g%s", xmax, label_max.c_str());
    ImGui::EndGroup();
    ImGui::SameLine();
    ImGui::Image(reinterpret_cast<ImTextureID>(colormaps_[cm]), ImVec2(w, h));
    ImGui::EndGroup();
}

} // namespace quadfoam
