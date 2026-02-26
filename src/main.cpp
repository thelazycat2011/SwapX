#include <imgui-cocos.hpp>
#include <Geode/Geode.hpp>
#include "global.hpp"
using namespace geode::prelude;

void setup() {
    auto& io = ImGui::GetIO();
    auto fontPath = geode::Mod::get()->getResourcesDir() / "Muli-SemiBold.ttf";
    io.Fonts->AddFontFromFileTTF(fontPath.string().c_str(), 16.0f);
    auto& style = ImGui::GetStyle();
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowBorderSize = 0;

    auto colors = style.Colors;
    colors[ImGuiCol_FrameBg] = ImVec4(0.31f, 0.31f, 0.31f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.59f, 0.59f, 0.59f, 0.40f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.61f, 0.61f, 0.61f, 0.67f);
    colors[ImGuiCol_TitleBg] = colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.0f, 0.5f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.89f, 0.89f, 0.89f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.71f, 0.71f, 0.71f, 0.35f);
}
void draw() {
    constexpr float border = 25;
    Globals& g = Globals::instance();
    ImGui::SetNextWindowPos({ border, border });
    // ImGui::SetNextWindowSizeConstraints({0, 0}, {frame_size.width, frame_size.height - border * 2.f});
    ImGui::SetNextWindowBgAlpha(0.75f);
    g.lvllistRefresh();
    if (ImGui::Begin("SwapX", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize)) {
        if (ImGui::BeginCombo("Level", g.lvllist[g.lvll_ptr].c_str())) {
            for (int n = 0; n < g.lvllist.size(); n++)
            {
                bool is_selected = (g.lvll_ptr == n);
                if (ImGui::Selectable(g.lvllist[n].c_str(), is_selected))
                    g.lvll_ptr = n;

                if (is_selected)
                    ImGui::SetItemDefaultFocus(); // optional: keep focus on selected
            }
            ImGui::EndCombo();
        }
        ImGui::Checkbox("Swapping", &g.swap);
        ImGui::Checkbox("Only swap on specified ID", &g.swapID);
        ImGui::InputText("ID", g.id, 10, ImGuiInputTextFlags_CharsDecimal);
        ImGui::End();
    }
}

$on_mod(Loaded) {
    ImGuiCocos::get()
    .setup(setup).draw(draw)
    .setVisible(false); /* We don't want our ImGui interface to be visible by default. */
}

$execute {
    listenForKeybindSettingPresses("swap-toggle", [](Keybind const& keybind, bool down, bool repeat, double timestamp) {
        Globals& g = Globals::instance();
        if (down && !repeat) g.swap_toggle();
    });
    listenForKeybindSettingPresses("toggle-menu", [](Keybind const& keybind, bool down, bool repeat, double timestamp) {
        if (down && !repeat) ImGuiCocos::get().toggle();
    });
}
