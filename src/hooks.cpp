#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJGameLevel.hpp>
#include <hjfod.gmd-api/include/GMD.hpp>
#include "global.hpp"
using namespace geode::prelude;

class $modify(PlayLayer) {
    bool init (GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        Globals& g = Globals::instance();
        std::string mockedlevel;
        auto lvl_string = level->m_levelString;
        GJLevelType orig_type = level->m_levelType;
        if (g.swap && (!g.swapID || atoi(g.id) == level->m_levelID)) {
            if (g.lvll_ptr != 0) {
                auto levelobj = gmd::importGmdAsLevel(g.lvllist[g.lvll_ptr].c_str());
                if (levelobj) mockedlevel = levelobj.unwrap()->m_levelString;
            }
            level->m_levelString = mockedlevel;
            level->m_levelType = GJLevelType::Editor;
        }
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        this->m_passedIntegrity = true;
        level->m_levelString = lvl_string;
        level->m_levelType = orig_type;
        return true;
    }
};

