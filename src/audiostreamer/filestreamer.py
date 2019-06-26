import sys
import time
import socket

from sys import argv

import audioop
import alsaaudio

def usage():
    print('usage: playbacktest.py [-d <device>] <file>', file=sys.stderr)
    sys.exit(2)

if __name__ == '__main__':
    device = 'default'

    out = alsaaudio.PCM(alsaaudio.PCM_PLAYBACK, device=device)
    out.setchannels(1)
    out.setrate(44100)
    out.setformat(alsaaudio.PCM_FORMAT_S32_LE)

    audio_maxval = 20000

    host_ip =  "127.0.0.1"
    server_port = 8080

    # Initialize a TCP client socket using SOCK_STREAM
    tcp_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:

        tcp_client.connect((host_ip, server_port))

        with open(argv[1], 'rb') as f:
            # The period size controls the internal number of frames per period.
            # The significance of this parameter is documented in the ALSA api.
            out.setperiodsize(160)

            # Read data from stdin
            data = f.read(320)
            while data:
                out.write(data)
                data = f.read(320)
                y = str(int((100 * int(audioop.max(data, 2))) / audio_maxval) + "\n"
                tcp_client.send(y.encode())

    except Exception as exc:
        print(exc)
    finally:
        tcp_client.close()
            
        
