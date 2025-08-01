@echo off

echo Generating resource embedding code
pushd ..
py Scripts/FileEmbedder.py Resources/Embeds/ PongGame/Source/
popd

echo Running Premake
pushd ..
Vendor\Binaries\Premake\Windows\premake5.exe --file=Build.lua vs2022
popd
pause