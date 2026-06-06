function cpptNewProject(projectName, src)
    -- Manage project's source directory when it in a subfolder (example: Exercises/E01_Functions i this workspace)
    srcdir = projectName
    if src ~= nil then
        srcdir = src
    end

    project (projectName)
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        targetdir "%{wks.location}/build/bin/%{cfg.architecture}-%{cfg.buildcfg}"
        objdir "%{wks.location}/build/obj/%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"
        
        -- old way: location "%{wks.location}/%{prj.name}"
        location ("%{wks.location}/".. srcdir)

        files { 
            "%{prj.location}/**.h", "%{prj.location}/**.hpp", "%{prj.location}/**.hh", "%{prj.location}/**.hxx",   
            "%{prj.location}/**.c", "%{prj.location}/**.cpp", "%{prj.location}/**.cc", "%{prj.location}/**.cxx",   
            "%{prj.location}/**.lua", "%{prj.location}/**.txt", "%{prj.location}/**.md", "%{prj.location}/**.ini",    
        }

        -- Custom include directories
        includedirs {"%{wks.location}", "%{prj.location}"}
        
        -- Simply defines which projects has been currently build
        defines {"__%{prj.name}_BUILD"}

        filter "configurations:Debug"
            defines { "DEBUG", "_DEBUG" }
            symbols "On"
        filter{}
        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
        filter{}
end

-- *********************** Support configuration for Libraryies ***********************
-- Add the function below in build.lua file for a project that will be compiled as shared library
function cpptSetSharedLib()
    kind "SharedLib"

    -- Add defines to say that we are building a DLL to control windows' __declspec(dllimport) or __declspec(dllexport)
    -- Using __ as a prefix, because project's name starts with a number
    defines{"__%{prj.name}_BUILD_DLL"}
end
