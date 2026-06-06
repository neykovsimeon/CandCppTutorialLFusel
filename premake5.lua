-- **************************** Common includes ***********************************
include "candcpptutorial.lua"

-- ************************* Workspace configuration ******************************
workspace "CandCppTutorial"
    configurations { "Debug", "Release" }
    architecture "x64"
    location "./"

-- ********************* Projects configurations links ****************************
    include "./01_VS_SimpleCApp/build.lua"
    include "./02_Pointers/build.lua"
    include "./02_02_PointersAndStructs/build.lua"
    include "./02_03_PointersStructsAndTypeDef/build.lua"
    include "./03_MemoryUtilitys/build.lua"
    include "./04_Strings/build.lua"
    include "./04_02_INIParser/build.lua"
    include "./05_INIExplorer/build.lua"
    include "./06_SimpleCppApp/build.lua"
    include "./07_CatsAndDogs/build.lua"
    include "./08_CppINIParser/build.lua"
    
    group "Exercises"
        include "./Exercises/E01_Functions/build.lua"
    group ""

