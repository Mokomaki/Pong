import os
import sys
from pathlib import Path

asset_names = []
file_names = []

def main() -> None:
    if(len(sys.argv) != 3):
        print("Usage: python FileEmbedder.py <path_to_files> <output_folder>")
        return

    in_path = sys.argv[1]
    out_path = sys.argv[2]
    print(f"Embedding files from '{in_path}' to '{out_path}'")

    for file in os.listdir(in_path):
        with open(os.path.join(in_path, file), "rb") as f:
            make_file_embed(out_path, os.path.splitext(file)[0], f.read())

    write_loader_file(out_path)
    print("File embedding completed.")
    print("Generated files:")
    for file in file_names:
        print(f" - {file}")


def make_file_embed(out_dir_name : str, file_name : str, file_data : bytearray) -> None:

    file_name = file_name.replace(".", "_")
    file_name = file_name.capitalize()
    
    asset_names.append(file_name+ "Embed")

    file_string = f'''#pragma once\nnamespace {file_name}Embed {{
    constexpr unsigned int {file_name}EmbedSize = {len(file_data)};
    constexpr unsigned char {file_name}EmbedData [] = 
    {{\n'''

    for i in range(len(file_data)):
        file_string += hex((file_data[i]))
        file_string += ", "
        if(i % 100 == 0):
            file_string += "\n"

    file_string += "};\n}\n"

    try:
        Path.mkdir(out_dir_name + "/ResInclude/", False, False)
    except  FileExistsError as e:
        print("/ResInclude/ directory found")

    resincl_path = r"\ResInclude\\"
    res_path = os.path.join(out_dir_name, resincl_path)

    try:
        with open(res_path + file_name + "Embed.h", "w") as file:
            file.write(file_string)
            file_names.append(file_name + "Embed.h")
    except Exception as e:
        print(f"Failed to write embed file: {e}")

def write_loader_file(path : str) -> None:

    print("Writing PongAssets.h")
    #Write header file
    header_file_string = "#pragma once\n"
    header_file_string += "\n"
    header_file_string += "namespace PongAssets {\n"
    for asset_name in asset_names:
        header_file_string += f"unsigned char const* Get{asset_name}Data();\n"
        header_file_string += f"unsigned int Get{asset_name}Size();\n"
    header_file_string += "}\n"

    try:
        with open(path + "PongAssets.h", "w") as file:
            file.write(header_file_string)
    except Exception as e:
        print(f"Failed to write pongassets header file: {e}")
    
    print("Writing PongAssets.cpp")
    # Write source file
    source_file_string = ""
    for cur_file in file_names:
        source_file_string += f"#include \"ResInclude/{cur_file}\"\n"
    #source_file_string = "#include \"PongAssets.h\"\n"
    source_file_string += "namespace PongAssets {\n"
    for i in range(len(asset_names)):
        source_file_string += f"unsigned char const* Get{asset_names[i]}Data()\n{{\n    return {asset_names[i]}::{asset_names[i]}Data;\n"
        source_file_string += "}\n"
        source_file_string += f"unsigned int Get{asset_names[i]}Size()\n{{\n    return {asset_names[i]}::{asset_names[i]}Size;\n"
        source_file_string += "}\n"
    source_file_string += "}\n"

    try:
        with open(path + "PongAssets.cpp", "w") as file:
            file.write(source_file_string)
    except Exception as e:
        print(f"Failed to write pongassets source file: {e}")
    
    file_names.append("PongAssets.h")
    file_names.append("PongAssets.cpp")

if (__name__ == "__main__"):
        main()
