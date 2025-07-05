import std;

auto saves_path() -> std::string
{
#ifdef STARDEWVALLEY_WINDOWS
    return std::format(R"({}\AppData\Roaming\StardewValley\Saves)", std::getenv("USERPROFILE"));
#endif
#ifdef STARDEWVALLEY_MACOS
    return std::format("{}/.config/StardewValley/Saves", std::getenv("HOME"));
#endif
#ifdef STARDEWVALLEY_UNSUPPORTED
#error 不支持的平台
#endif
}

namespace fs = std::filesystem;

auto main() -> int
{
    auto reg_find = std::regex{R"(^(?!SaveGameInfo)(?!.*(_old|\.vdf|\.bak)$).+$)"};
    auto path     = saves_path();

    std::println("正在扫描存档所在目录：{}", path);

    auto saves = std::vector<fs::path>{};
    for (auto& dir_entry : fs::recursive_directory_iterator(path)) {
        if (!dir_entry.is_regular_file()) {
            continue;
        }
        if (!regex_match(dir_entry.path().filename().string(), reg_find)) {
            continue;
        }
        saves.emplace_back(dir_entry.path());
    }

    std::println(
        "扫描完毕，一共有 {} 个存档，接下来会逐个询问是否需要修复，若需要则输入 y 或 Y，输入其他内容则不修复。",
        saves.size());
    for (auto&& save : saves) {
        std::println();

        auto rel = save.lexically_relative(path).string();
        std::println("是否需要修复 {}", rel);

        auto op = std::string{};
        std::getline(std::cin, op);
        if (op != "y" && op != "Y") {
            std::println("跳过 {}", rel);
            continue;
        }

        auto reg_fix  = std::regex{R"(<userID>\d*</userID>)"};
        auto bak_path = format("{}.bak", save.string());
        fs::copy_file(save, bak_path, fs::copy_options::overwrite_existing);

        using is_it = std::istreambuf_iterator<char>;
        using os_it = std::ostreambuf_iterator<char>;

        auto fin = std::ifstream{bak_path};
        auto beg = is_it{fin};
        auto end = is_it{};
        auto ctx = std::string{beg, end};

        auto fout = std::ofstream{path};
        auto it   = os_it{fout};

        std::regex_replace(it, ctx.begin(), ctx.end(), reg_fix, "<userID />");

        std::println("已修复 {0} 并将原存档备份至 {0}.bak", rel);
    }
}
