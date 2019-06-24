platform=$(eval uname -i)
outputdirectory="../build/$platform"

echo "=============================================="
echo "APOLLON 3000 BUILD-SUITE"
echo "(C) Rehberger Raffael"
echo "(C) Sarcevic Lejla"
echo "=============================================="
echo "Target Platform       :       $platform"
echo "Output Directory      :       $outputdirectory"
echo "=============================================="

mkdir -p $outputdirectory

if [ "$platform" = "x86_64" ]; then
  # Plain Desktop Build
  gcc main.c -lpthread -Wall --pedantic -std=c99 -o "$outputdirectory/apollon3000"
fi

if [ "$platform" = "armhf" ] || [ "$platform" = "armv6" ] || [ "$platform" = "armv7" ]; then
    # Raspberry PI Build
    gcc main.c -lwiringPi -lpthread -Wall --pedantic -std=c99 -o "$outputdirectory/apollon3000"
fi
