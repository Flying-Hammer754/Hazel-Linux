SCRIPT_NAME=$(echo $0 | xargs readlink -f)
SCRIPT_DIR=$(dirname "$SCRIPT_NAME")
if [ "$SCRIPT_DIR" = "" ]; then
    cd "../"
else
    cd "$SCRIPT_DIR/../"
fi
premake5 gmake2 && make && cd Hazelnut && ../bin/Debug-linux-x86_64/Hazelnut/Hazelnut