#!/bin/bash
SCRIPT_NAME=$(echo "$0" | xargs readlink -f)
PROJECT_DIR=$(dirname "$SCRIPT_NAME")
cd "$PROJECT_DIR/../"
if [ "$1" = "--help" ] || [ "$1" = "-h" ]; then
    echo "Usage: scripts/Linux_GenAppimage.sh <Arg1>"
    echo "  - <Arg1>: -"
    echo "      -h, --help: display this message."
    echo "      -q, --quiet: always choose the default options & do not print anything"
    echo "  - ------- -"
    exit
fi
if [ "$1" != "-q" ] && [ "$1" != "--quiet" ]; then
read -p "Regenerate projects? [y/N]" regenProjects
fi
if [ "$regenProjects" = "y" ] || [ "$regenProjects" = "Y" ]; then
    premake5 gmake2 && make
fi
if [ "$1" != "-q" ] && [ "$1" != "--quiet" ]; then
read -p "Regenerate all appimage files [Y/n]:" regenAllFiles
fi
if [ "$regenAllFiles" = "" ]; then
    regenAllFiles="y"
fi
if [[ ! -d "$HOME/Applications" ]] || [[ ! -f "$HOME/Applications/appimagetool-x86_64.AppImage" ]]; then
    if [ "$1" != "-q" ] && [ "$1" != "--quiet" ]; then
    read -p "appimagetool not installed! Install it? [y/N]" appImageToolInstall
    fi
    if [ "$appImageToolInstall" = "y" ] || [ "$appImageToolInstall" = "Y" ]; then
        if [[ ! -d "$HOME/Applications" ]]; then
            mkdir "$HOME/Applications"
        fi
        wget -P "$HOME/Applications" https://github.com/AppImage/AppImageKit/releases/download/13/appimagetool-x86_64.AppImage
        chmod +x "$HOME/Applications/appimagetool-x86_64.AppImage"
    fi
fi
if [ "$1" != "-q" ] && [ "$1" != "--quiet" ]; then
echo "Current directory is $PWD"
read -p "Appimage directory (default is HazelApp.AppDir):" appDir
fi
if [ "$appDir" == "" ]; then
    appDir="HazelApp.AppDir"
fi
if [[ ! -d "$appDir" ]] || [ "$regenAllFiles" = "y" ] || [ "$regenAllFiles" = "Y" ]; then
    rm -rf $appDir
    mkdir $appDir
fi
cd $appDir
if [[ ! -f "AppRun" ]] || [ "$regenAllFiles" = "y" ] || [ "$regenAllFiles" = "Y" ]; then
    rm -f AppRun
    touch AppRun
    echo "#!/bin/bash" >> ./AppRun
    echo "SCRIPT_NAME=\$(echo \"\$0\" | xargs readlink -f)" >> ./AppRun
    echo "PROJECT_DIR=\$(dirname \"\$SCRIPT_NAME\")" >> ./AppRun
    echo "chmod +x \"\$PROJECT_DIR/usr/bin/HazelApp\"" >> ./AppRun
    echo "\$PROJECT_DIR/usr/bin/HazelApp \$PROJECT_DIR/HazelApp \$OWD" >> ./AppRun
    echo "rm -f Hazel.log imgui.ini HazelProfile-Startup.json HazelProfile-Runtime.json HazelProfile-Shutdown.json" >> ./AppRun
    echo "read -t 10 -p \"Delete assets directory? [Y/n]:\" delAssets" >> ./AppRun
    echo "if [ \"$delAssets\" = \"\" ] || [ \"$delAssets\" = \"y\" ] || [ \"$delAssets\" = \"Y\" ]; then" >> ./AppRun
    echo "  rm -rf assets" >> ./AppRun
    echo "fi" >> ./AppRun
    chmod a+x AppRun
fi

if [[ ! -f "HazelApp.desktop" ]] || [ "$regenAllFiles" = "y" ] || [ "$regenAllFiles" = "Y" ]; then
    rm -f HazelApp.desktop
    touch HazelApp.desktop
    echo "[Desktop Entry]" >> ./HazelApp.desktop
    if [ "$1" != "-q" ] && [ "$1" != "--quiet" ]; then
    read -p "Application Name (default is HazelApp):" appName
    fi
    if [ "$appName" = "" ]; then
        appName="HazelApp"
    fi
    echo "Name=$appName" >> ./HazelApp.desktop
    echo "Exec=HazelApp" >> ./HazelApp.desktop
    echo "Icon=HazelApp" >> ./HazelApp.desktop
    echo "Type=Application" >> ./HazelApp.desktop
    echo "Categories=Game;" >> ./HazelApp.desktop
fi

if [[ ! -d "usr" ]] || [ "$regenAllFiles" = "y" ] || [ "$regenAllFiles" = "Y" ]; then
    rm -rf usr
    mkdir usr
fi
if [[ ! -d "usr/bin" ]] || [ "$regenAllFiles" = "y" ] || [ "$regenAllFiles" = "Y" ]; then
    rm -rf "usr/bin"
    mkdir "usr/bin"
fi
if [[ ! -f "usr/bin/HazelApp" ]] || [ "$regenAllFiles" = "y" ] || [ "$regenAllFiles" = "Y" ]; then
    rm -f "usr/bin/HazelApp"
    if [ "$1" != "-q" ] && [ "$1" != "--quiet" ]; then
    echo "Current working directory is $PWD"
    read -p "Executable file (default is ../bin/Debug-linux-x86_64/Sandbox/Sandbox)" appExec
    fi
    if [ "$appExec" = "" ] || [[ ! -f "$appExec" ]]; then
        appExec="../bin/Debug-linux-x86_64/Sandbox/Sandbox"
        if [[ ! -f "$appExec" ]]; then
            echo "Error: $appExec not found!"
            exit
        fi
    fi
    cp -f "$appExec" "usr/bin/HazelApp"
fi
if [[ ! -d "usr/share" ]] || [ "$regenAllFiles" = "y" ] || [ "$regenAllFiles" = "Y" ]; then
    rm -rf "usr/share"
    mkdir "usr/share"
fi
if [[ ! -d "usr/share/icons" ]] || [ "$regenAllFiles" = "y" ] || [ "$regenAllFiles" = "Y" ]; then
    rm -rf "usr/share/icons"
    mkdir "usr/share/icons"
fi
if [[ ! -f "usr/share/icons/HazelApp.*" ]] || [ "$regenAllFiles" = "y" ] || [ "$regenAllFiles" = "Y"]; then
    rm -f "usr/share/icons/HazelApp.*"
    if [ "$1" != "-q" ] && [ "$1" != "--quiet" ]; then
    echo "Current working directory is $PWD"
    read -p "Icon file (default is ../Resources/Branding/Hazel_Logo_Text_Light_Square.png):" appIcon
    fi
    if [ "$appIcon" = "" ] || [[ ! -f "$appIcon" ]]; then
        appIcon="../Resources/Branding/Hazel_Logo_Text_Light_Square.png"
    fi
    if [ "$1" != "-q" ] && [ "$1" != "--quiet" ]; then
    echo "Icon file extension autodetect failed. Manual input required."
    read -p "Icon file extension (default is .png):" appIconExt
    fi
    if [ "$appIconExt" = "" ]; then
        appIconExt=".png"
    fi
    cp $appIcon "usr/share/icons/HazelApp$appIconExt"
    cp $appIcon "HazelApp$appIconExt"
fi
if [[ ! -d "HazelApp" ]] || [ "$regenAllFiles" = "y" ] || [ "$regenAllFiles" = "Y" ]; then
    rm -rf "HazelApp"
    mkdir HazelApp
fi
if [[ ! -d "HazelApp/assets" ]] || [ "$regenAllFiles" = "y" ] || [ "$regenAllFiles" = "Y" ]; then
    rm -rf HazelApp/assets
    mkdir HazelApp/assets
    if [ "$1" != "-q" ] && [ "$1" != "--quiet" ]; then
    echo "Current working directory is $PWD"
    read -p "Application Assets folder (default is ../Sandbox/assets)" appAssets
    fi
    if [ "$appAssets" = "" ] || [[ ! -d "$appAssets" ]]; then
        appAssets="../Sandbox/assets"
        if [[ ! -d "$appAssets" ]]; then
            echo "Error: $appAssets not found!"
            exit
        fi
    fi
    cp -r $appAssets "HazelApp/"
fi

if [[ ! -d "Hazelnut" ]] || [ "$regenAllFiles" = "y" ] || [ "$regenAllFiles" = "Y" ]; then
    rm -rf "Hazelnut"
    mkdir "Hazelnut"
fi
if [[ ! -d "Hazelnut/assets" ]] || [ "$regenAllFiles" = "y" ] || [ "$regenAllFiles" = "Y" ]; then
    rm -rf "Hazelnut/assets"
    mkdir "Hazelnut/assets"
    if [ "$1" != "-q" ] && [ "$1" != "--quiet" ]; then
    echo "Current working directory is $PWD"
    read -p "Engine Assets folder (default is ../Hazelnut/assets)" engineAssets
    fi
    if [ "$engineAssets" = "" ] || [[ ! -d "$engineAssets" ]]; then
        engineAssets="../Hazelnut/assets"
    fi
    cp -r $engineAssets "Hazelnut/"
fi

if [[ ! -d "Hazelnut/Resources" ]] || [ "$regenAllFiles" = "y"] || [ "$regenAllFiles" = "Y" ]; then
    if [ "$1" != "-q" ] && [ "$1" != "--quiet" ]; then
    read -p "Copy Engine Resources? (../Hazelnut/Resources) [y/N]:" cpEngineResources
    fi
    if [ "$cpEngineResources" = "y" ] || [ "$cpEngineResources" = "Y" ]; then
        rm -rf "Hazelnut/Resources"
        mkdir "Hazelnut/Resources"
        if [ "$1" != "-q" ] && [ "$1" != "--quiet" ]; then
        echo "Current working directory is $PWD"
        read -p "Engine Resources folder (default is ../Hazelnut/Resources)" engineResources
        fi
        if [ "$engineResources" = "" ] || [[ ! -d "$engineResources" ]]; then
            engineResources="../Hazelnut/Resources"
        fi
        cp $engineResources "Hazelnut/"
    fi
fi

$HOME/Applications/appimagetool-x86_64.AppImage .