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
    char id[16];
    int lvll_ptr = 0;
    std::vector<std::string> lvllist = {"No Selection"};
    std::vector<std::string> internalLvlList = {""};

    void lvllistRefresh() {
        lvllist = {"No Selection"};
        internalLvlList = {""};
        std::filesystem::path path = geode::Mod::get()->getSettingValue<std::filesystem::path>("level-folder");

        auto directory = geode::utils::file::readDirectory(path, false);
        if (directory.ok()) {
            for (auto file : directory.unwrap()) {
                if (geode::utils::string::pathToString(file.extension()) == ".gmd") {
                    internalLvlList.push_back(geode::utils::string::pathToString(file));
                    lvllist.push_back(geode::utils::string::pathToString(file.filename().stem()));
                }
            }
        }
        else geode::log::error("Error reading file : {}", directory.unwrap());
    }

    Globals(const Globals&) = delete;
    Globals& operator=(const Globals&) = delete;

private:
    Globals() = default;
};
