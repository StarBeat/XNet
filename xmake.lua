---
compress_mode={
    None = "",
    Lz4 = "lz4",
    Zlib = "zlib"
}

dep_module={
    xtemplate = true,
    xalgorithm = true
}
---

target("xnet")
    set_languages("c11", "c++20")
    add_rules("mode.debug", "mode.release")
    set_kind("shared")

    --- process common include
    s = get_config("global_include")
    if s and type(s) == "string" then
        common_includes = s:deserialize()
        for key, value in pairs(common_includes) do
            if dep_module[key] ~= nil then
                add_includedirs(value)
            end
        end
    elseif not os.isdir("../XTemplate") then
        --git.clone("https://github.com/StarBeat/XTemplate.git", {depth = 1, branch = "main", outputdir = "../"})
        print("缺少依赖项")
    elseif os.isdir("../XTemplate") then
        add_includedirs("../XTemplate/include")
    end
    ---

    if get_config("compress") == compress_mode.Lz4 then
        add_requires("lz4")
    elseif get_config("compress") == compress_mode.Zlib then
        add_requires("zlib")
    end

    add_includedirs("include/")
    add_headerfiles("include/*.h")
    add_headerfiles("include/*.inl")

    add_files("src/*.cpp")
target_end()

target("xnet_test")
    set_languages("c11", "c++20")
    add_rules("mode.debug", "mode.release")
    set_kind("binary")
    
    add_deps("xnet")

    add_includedirs("include/")
    add_files("test/*.cpp")

    if is_mode("debug") then
        -- 添加DEBUG编译宏
        add_defines("DEBUG")
        -- 启用调试符号
        set_symbols("debug")
        -- 禁用优化
        set_optimize("none")
    elseif is_mode("release") then
        -- 隐藏符号
        set_symbols("hidden")
        -- strip所有符号
        set_strip("all")
        -- 开启优化为：最快速度模式
        set_optimize("fastest")
        -- 忽略帧指针
        if is_plat("linux") then
            add_cxflags("-fomit-frame-pointer")
        elseif is_plat("windows") then
            add_cxflags("/Oy")
        end
    end
target_end()