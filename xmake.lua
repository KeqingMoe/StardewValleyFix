add_rules("mode.debug", "mode.release")

set_languages("c++26")
add_rules("plugin.compile_commands.autoupdate")

set_toolchains("llvm")
set_plat("mingw")
set_runtimes("c++_static")

target("StardewValleyFix")
    if is_os("windows") then
        add_defines("STARDEWVALLEY_WINDOWS")
    elseif is_os("macosx") then
        add_defines("STARDEWVALLEY_MACOS")
    else
        add_defines("STARDEWVALLEY_UNSUPPORTED")
    end
    set_kind("binary")
    add_files("src/main.cpp")
    set_policy("build.c++.modules", true)
