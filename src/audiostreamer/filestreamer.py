from __future__ import print_function

import socket
import audioop
import alsaaudio

host = "127.0.0.1"
port = 8080
audio_max_amplitude = 20000

# Initialize ALSA-Audio-Output
audio_output = alsaaudio.PCM(alsaaudio.PCM_PLAYBACK)
audio_output.setchannels(1)
audio_output.setrate(44100)
audio_output.setformat(alsaaudio.PCM_FORMAT_S32_LE)

# Initialize TCP client socket using SOCK_STREAM
tcp_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
with open('hth.wav', 'rb') as wav_file:
    try:
        tcp_client.connect((host, port))

        audio_output.setperiodsize(160)
        data = wav_file.read(320)

        while data:
            # Write read bits of Audio-File to Sound-Card
            audio_output.write(data)
            data = wav_file.read(320)
            led_intensity = str(int(100 * audioop.max(data, 2) / audio_max_amplitude)) + "\n"
            tcp_client.send(led_intensity.encode())

    except Exception as exc:
        print(exc)
    finally:
        tcp_client.close()
