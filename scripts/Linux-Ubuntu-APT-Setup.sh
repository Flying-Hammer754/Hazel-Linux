echo "Installing Dependencies..."
sudo apt-get install spirv-tools glslang-dev spirv-headers libvulkan-dev git cmake python gcc make g++
cd ~/
echo "    ---- Current working directory is $PWD ----    "
read -p "Choose the directory to clone spirv-cross into (eg. tmp/spirv-cross)" -i "tmp/spirv-cross"
echo "Cloning spirv-cross repository"
git clone https://github.com/KhronosGroup/SPIRV-Cross.git $REPLY
cd $REPLY
cmake -Bbuild
cd build
make install
cd ~/
rm -rf $REPLY
echo "    ---- Current working directory is $PWD ----    "
read -p "Choose the directory to clone shaderc into (eg. tmp/shaderc)" -i "tmp/shaderc"
echo "Cloning shaderc repository"
git clone https://github.com/google/shaderc.git $REPLY
cd $REPLY
cmake -Bbuild
cd build
make install
cd ~/
rm -rf $REPLY