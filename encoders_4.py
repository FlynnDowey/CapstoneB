import time
import pigpio
import rotary_encoder

pos = [0, 0, 0, 0]  # Position for each encoder

# Define callback functions for each encoder
def callback_encoder1(way):
    global pos
    pos[0] += way
    print("Encoder 1 - Position: {}".format(pos[0]))

def callback_encoder2(way):
    global pos
    pos[1] += way
    print("Encoder 2 - Position: {}".format(pos[1]))

def callback_encoder3(way):
    global pos
    pos[2] += way
    print("Encoder 3 - Position: {}".format(pos[2]))

def callback_encoder4(way):
    global pos
    pos[3] += way
    print("Encoder 4 - Position: {}".format(pos[3]))

pi = pigpio.pi()

# Create instances of the `decoder` class for each encoder
decoder1 = rotary_encoder.decoder(pi, 7, 8, callback_encoder1)
decoder2 = rotary_encoder.decoder(pi, 9, 10, callback_encoder2)
decoder3 = rotary_encoder.decoder(pi, 11, 12, callback_encoder3)
decoder4 = rotary_encoder.decoder(pi, 13, 14, callback_encoder4)

time.sleep(300)

# Cancel the decoders
decoder1.cancel()
decoder2.cancel()
decoder3.cancel()
decoder4.cancel()

pi.stop()
