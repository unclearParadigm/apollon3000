platform=$(eval uname -i)
outputdirectory="../build/$platform"

clear
echo "=============================================="
echo "APOLLON 3000 BUILD-SUITE"
echo "(C) Rehberger Raffael"
echo "(C) Sarcevic Lejla"
echo "=============================================="
echo "Target Platform       :       $platform"
echo "Output Directory      :       $outputdirectory"
echo "=============================================="
echo ""

mkdir -p $outputdirectory

declare -a FILES
FILES=( boolean.h constants.h cmdargs/cmdargs.h cmdargs/cmdargs.c hal/hal.h hal/desktop.c hal/raspberry.c )

declare -a FLAGS
FLAGS=( -Wall --pedantic -std=gnu99 )

function filejoin { 
  local IFS="$1"; 
  shift; 
  buildfiles="$*";
}

function flagjoin { 
  local IFS="$1"; 
  shift; 
  buildflags="$*";
}

filejoin " " "${FILES[@]}"
echo "Files: $buildfiles"
flagjoin " " "${FLAGS[@]}"
echo "Flags: $buildflags"

if [ "$platform" = "x86_64" ]; then
  # / Desktop Build for CLI
  gcc $buildfiles maincli.c $buildflags -DBUILD_DESKTOP -lpthread -o "$outputdirectory/apollon3000"
  # / Desktop Build for Remote Control
  gcc $buildfiles rcmain.c $buildflags -DBUILD_DESKTOP -lpthread -o "$outputdirectory/apollon3000rc"
fi

if [ "$platform" = "armhf" ] || [ "$platform" = "armv6" ] || [ "$platform" = "armv7" ]; then
  # / RaspberryPI Build for CLI
  gcc $buildfiles maincli.c $buildflags -DBUILD_RASPBERRY -lwiringPi -lpthread -o "$outputdirectory/apollon3000"
  # / RaspberryPI Build for Remote Control
  gcc $buildfiles rcmain.c $buildflags -DBUILD_RASPBERRY -lpthread -o "$outputdirectory/apollon3000rc"
fi

echo ""
echo "Build Completed!"
echo "=============================================="
