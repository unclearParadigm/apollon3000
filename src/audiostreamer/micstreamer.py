import sys
import math
import socket

import audioop
import alsaaudio

input = alsaaudio.PCM(alsaaudio.PCM_CAPTURE,alsaaudio.PCM_NONBLOCK)
input.setchannels(1)
input.setrate(8000)
input.setformat(alsaaudio.PCM_FORMAT_S16_LE)
input.setperiodsize(320)

audio_maxval = 20000

host =  "127.0.0.1"
port = 8080

tcp_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    tcp_client.connect((host, port))

    while True:
        len, data = input.read()
        if len > 0:
            y = str(int(100 * audioop.max(data, 2) / audio_maxval)) + "\n"
            tcp_client.send(y.encode())

finally:
    tcp_client.close()