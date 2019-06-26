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

function filejoin { 
  local IFS="$1"; 
  shift; 
  buildfiles="$*";
}

filejoin " " "${FILES[@]}"
echo "FILES TO BUILD: $buildfiles"

if [ "$platform" = "x86_64" ]; then
  # / Desktop Build for CLI
  gcc $buildfiles maincli.c -DBUILD_DESKTOP -std=gnu99 -lpthread -Wall --pedantic -o "$outputdirectory/apollon3000"
  # / Desktop Build for Remote Control
  gcc $buildfiles rcmain.c -DBUILD_DESKTOP -std=gnu99 -lpthread -Wall --pedantic -o "$outputdirectory/apollon3000rc"
fi

if [ "$platform" = "armhf" ] || [ "$platform" = "armv6" ] || [ "$platform" = "armv7" ]; then
  # / RaspberryPI Build for CLI
  gcc $buildfiles maincli.c -DBUILD_RASPBERRY -std=gnu99 -lwiringPi -lpthread -Wall --pedantic -o "$outputdirectory/apollon3000"
  # / RaspberryPI Build for Remote Control
  gcc $buildfiles rcmain.c -DBUILD_RASPBERRY -std=gnu99 -lpthread -Wall --pedantic -o "$outputdirectory/apollon3000rc"
fi
