project "PongGame"
   language "C++"
   cppdialect "C++17"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"
   entrypoint "WinMainCRTStartup"

   files {
        "Source/**.h",
        "Source/**.cpp"
    }


   includedirs
   {
      "Source",
      "../Vendor/SFML/Include"
   }

   libdirs
   {
        "../Vendor/SFML/Lib"
   }

   links
   {
          "winmm.lib",
          "opengl32.lib",
          "gdi32.lib"
   }


   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS", "SFML_STATIC"}

   filter "configurations:Debug"
       kind "ConsoleApp"
       defines { "DEBUG", "SFML_STATIC"}
       runtime "Debug"
       symbols "On"
       links
       {
            "sfml-main-s-d.lib",
            "sfml-audio-s-d.lib",
            "sfml-graphics-s-d.lib",
            "sfml-system-s-d.lib",
            "sfml-window-s-d.lib",
            "freetyped.lib",
            "FLACd.lib",
            "oggd.lib",
            "vorbisd.lib",
            "vorbisfiled.lib",
            "vorbisencd.lib"
       }

   filter "configurations:Release"
       kind "WindowedApp"
       defines { "RELEASE", "SFML_STATIC"}
       runtime "Release"
       optimize "On"
       symbols "On"
        links
       {
            "sfml-main-s.lib",
            "sfml-audio-s.lib",
            "sfml-graphics-s.lib",
            "sfml-system-s.lib",
            "sfml-window-s.lib",
            "freetype.lib",
            "FLAC.lib",
            "ogg.lib",
            "vorbis.lib",
            "vorbisfile.lib",
            "vorbisenc.lib"
       }