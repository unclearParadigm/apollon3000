from __future__ import print_function

import socket
import audioop
import alsaaudio

host = "127.0.0.1"
port = 8080
audio_max_amplitude = 20000

# Initialize ALSA-Audio-Input (from Microphone)
audio_input = alsaaudio.PCM(alsaaudio.PCM_CAPTURE, alsaaudio.PCM_NONBLOCK)
audio_input.setchannels(1)
audio_input.setrate(8000)
audio_input.setformat(alsaaudio.PCM_FORMAT_S16_LE)
audio_input.setperiodsize(320)

# Initialize TCP client socket using SOCK_STREAM
tcp_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    tcp_client.connect((host, port))

    while True:
        data_length, data = audio_input.read()
        if data_length > 0:
            led_intensity = str(int(100 * audioop.max(data, 2) / audio_max_amplitude)) + "\n"
            tcp_client.send(led_intensity.encode())

finally:
    tcp_client.close()
