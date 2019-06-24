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
FILES=( boolean.h constants.h cmdargs/cmdargs.h cmdargs/cmdargs.c hal/hal.h )

function filejoin { 
  local IFS="$1"; 
  shift; 
  buildfiles="$*";
}

filejoin " " "${FILES[@]}"
echo "FILES TO BUILD: $buildfiles"

if [ "$platform" = "x86_64" ]; then
  # Plain Desktop Build
  gcc $buildfiles hal/desktop.c maintest.c -DBUILD_DESKTOP -lpthread -Wall --pedantic -std=c99 -o "$outputdirectory/apollon3000"
fi

if [ "$platform" = "armhf" ] || [ "$platform" = "armv6" ] || [ "$platform" = "armv7" ]; then
  # Raspberry PI Build
  gcc $buildfiles hal/raspberry.c maintest.c -DRASPBERRY -lwiringPi -lpthread -Wall --pedantic -std=c99 -o "$outputdirectory/apollon3000"
fi
