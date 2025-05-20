add_rules("mode.debug", "mode.release")

set_languages("c++26")
add_rules("plugin.compile_commands.autoupdate")

set_toolchains("clang")
set_plat("mingw")
set_runtimes("c++_static")

target("StardewValleyFix")
    set_kind("binary")
    add_files("src/main.cpp")
    set_policy("build.c++.modules", true)
