#pragma once
#include <Geode/Geode.hpp>
struct Globals {
    static Globals& instance() {
        static Globals g;
        return g;
    }

    bool login = false;
    bool swap = false;
    bool swapID = false;
    void swap_toggle() {swap = !swap;}
    char id[10];
    int lvll_ptr = 0;
    std::vector<std::string> lvllist = {"No Selection"};
    std::vector<std::string> internalLvlList = {""};

    void lvllistRefresh() {
        lvllist = {"No Selection"};
        std::filesystem::path path = geode::Mod::get()->getSettingValue<std::filesystem::path>("level-folder");
        try {
            if (!std::filesystem::exists(path)) {
                std::filesystem::create_directory(path);
            }

            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                if (entry.path().extension().string() == ".gmd") {
                    internalLvlList.push_back(entry.path().string());
                    lvllist.push_back(entry.path().filename().string());
                }
            }
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    Globals(const Globals&) = delete;
    Globals& operator=(const Globals&) = delete;

private:
    Globals() = default;
};
