#!/bin/bash

pushd ..
python3 ./Scripts/FileEmbedder.py Resources/Embeds PongGame/Source
popd

pushd ..
Vendor/Binaries/Premake/Linux/premake5 --cc=clang --file=Build.lua gmake2
popd
