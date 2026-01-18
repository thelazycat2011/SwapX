#pragma once
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

    void lvllistRefresh() {
        lvllist = {"No Selection"};
        std::string path = "leveldb";
        try {
            if (!std::filesystem::exists(path)) {
                std::filesystem::create_directory(path);
            }

            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                lvllist.push_back(entry.path().string());
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
