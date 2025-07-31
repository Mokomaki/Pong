project "PongGame"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files {
        "Source/**.h",
        "Source/**.hpp",
        "Source/**.cpp",
        "Source/**.cxx",
        "Source/**.cc",
        "Source/**.c"
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
       defines { "DEBUG", "SFML_STATIC"}
       runtime "Debug"
       symbols "On"
       links
       {
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
       defines { "RELEASE", "SFML_STATIC"}
       runtime "Release"
       optimize "On"
       symbols "On"
        links
       {
            "sfml-audio-s.lib",
            "sfml-graphics-s.lib",
            "sfml-system-s.lib",
            "sfml-window-s.lib",
            "freetype.lib",
            "FLAC.lib",
            "ogg.lib",
            "vorblis.lib",
            "vorbisfile.lib",
            "vorbisenc.lib"
       }