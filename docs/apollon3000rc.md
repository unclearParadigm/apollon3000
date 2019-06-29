# Apollon3000 RC (Remote-Control)

opens up a TCP-Socket on Port 8080 listening for Stream-Clients to connect.
Streamer-Clients just send plain Integer-Values which are mapped to LED-Intensity-values by apllon3000rc.

# Build-Example
```bash
cd src/apollon3000
# Add Exectuable permissions for Build-Script (needs to be done only once)
chmod +x build.sh
./build.sh
```

# Visualize Audio with LEDs on RaspberryPI

* find IP-Address of Rasperry PI (use ```ip addr```)
* start apollon3000rc (see build-directory)
* start one of the audiostreamer-scripts (filestreamer.py, micstreamer.py)


# AudioStreamer Dependencies

AudioStreamer-Scripts are running on Python2 and Python3. If you are using a Debian-based distribution you need
to start the Scripts with Python2 instead of Python3, as there is no python-alsaaudio for Python3 packaged. In
general make sure that you have run the Raspberry-Setup-Script.
