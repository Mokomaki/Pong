-- premake5.lua
workspace "Pong"
   architecture "x64"
   configurations { "Debug", "Release"}
   startproject "PongGame"
   flags("MultiProcessorCompile")

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group ""

include "PongGame/Build-Pong.lua"