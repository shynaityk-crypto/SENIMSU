from flask import Flask, jsonify
import serial
import threading
import time

app = Flask(__name__)

# Change COM port to match your Arduino (Windows: COM3, Linux: /dev/ttyUSB0)
arduino = serial.Serial('COM3', 9600, timeout=1)

current_depth = 0

# Thread to continuously read Arduino
def read_serial():
    global current_depth
    while True:
        try:
            line = arduino.readline().decode().strip()
            if line:
                depth = int(line)
                current_depth = max(0, min(100, depth))  # clamp 0-100
        except:
            pass
        time.sleep(0.1)

threading.Thread(target=read_serial, daemon=True).start()

@app.route("/api/depth")
def get_depth():
    return jsonify({"depth": current_depth})

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
