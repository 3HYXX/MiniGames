add_rules("mode.debug", "mode.release")

set_languages("c++17")
set_rundir("$(projectdir)")
set_toolchains("clang-cl")

add_requires("libsdl", "libsdl_image")

if (is_os("windows")) then 
    add_defines("_CRT_SECURE_NO_WARNINGS")
    if (is_mode("release")) then
        set_runtimes("MD")
    elseif (is_mode("debug")) then
        add_ldflags("/subsystem:console")
        set_runtimes("MDd")
    end
end

target("Pong")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("libsdl", "libsdl_image")

