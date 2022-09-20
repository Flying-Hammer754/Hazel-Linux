#!/bin/bash

#SCRIPT_FILE=$"(echo \"$0\" | xargs readlink -f)"
#SCRIPT_DIRECTORY=$(dirname "$SCRIPT_FILE")
echo "Installing Dependencies..."
sudo pacman -S --needed git cmake python base-devel gcc-libs shaderc premake vulkan-headers vulkan-tools spirv-tools glslang spirv-headers xdg-desktop-portal
cd ~/
echo "Cloning spirv-cross AUR"
echo "    ---- Current working directory is: $PWD ----    "
read -p "Choose the directory to clone spirv-cross into (eg. tmp/spirv-cross): " -i "tmp/spirv-cross"
git clone https://aur.archlinux.org/spirv-cross.git $REPLY
cd $REPLY
makepkg -s -i -c --needed --nocheck -r
cd ~/
rm -rf $REPLY