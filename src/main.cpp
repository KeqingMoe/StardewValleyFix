import std;

namespace fs = std::filesystem;

auto main() -> int
{
    auto home_path = std::string{std::getenv("USERPROFILE")};

    auto reg_find = std::regex{R"(^(?!SaveGameInfo)(?!.*(_old|\.vdf|\.bak)$).+$)"};
    auto path     = std::format(R"({}\AppData\Roaming\StardewValley\Saves)", home_path);
    auto saves    = std::vector<fs::path>{};
    for (auto& dir_entry : fs::recursive_directory_iterator(path)) {
        if (!dir_entry.is_regular_file()) {
            continue;
        }
        if (!regex_match(dir_entry.path().filename().string(), reg_find)) {
            continue;
        }
        saves.emplace_back(dir_entry.path());
    }

    for (auto&& path : saves) {
        auto reg_fix  = std::regex{R"(<userID>\d*</userID>)"};
        auto bak_path = format("{}.bak", path.string());
        fs::copy_file(path, bak_path, fs::copy_options::overwrite_existing);

        using is_it = std::istreambuf_iterator<char>;
        using os_it = std::ostreambuf_iterator<char>;

        auto fin = std::ifstream{bak_path};
        auto beg = is_it{fin};
        auto end = is_it{};
        auto ctx = std::string{beg, end};

        auto fout = std::ofstream{path};
        auto it   = os_it{fout};

        std::regex_replace(it, ctx.begin(), ctx.end(), reg_fix, "<userID />");
    }
}
