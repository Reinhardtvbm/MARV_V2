import sys
import pyqtgraph as pg
from PyQt6.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget
import numpy as np
import time
import socket
import math

HOST = "192.168.137.1"
PORT = 3000

NUM_POINTS = 1000

x_data = np.arange(0, NUM_POINTS)

MAG_FULL_SCALE = 49.152
GYRO_DPS = 2000
ACC_FULL_SCALE = 4

class RealTimePlotApp(QMainWindow):
    def __init__(self):
        super().__init__()

        self.curr_time = time.time()
        self.FPS = 0
        self.setup_ui()

        self.UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
        self.UDPServerSocket.bind((HOST, PORT))

        self.file = open("data.txt", "w")

    def setup_ui(self):
        # Create a central widget and a QVBoxLayout to hold the plot
        central_widget = QWidget(self)
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout(central_widget)

        # Create the 3 plotwidgets with 3 subplots each
        self.plot_widget = pg.PlotWidget()

        layout.addWidget(self.plot_widget)

        # Initialize data for the 3 plots (3 subplots for each)
        self.y_data = np.zeros(NUM_POINTS)

        # Define colors for each subplot
        color = (0, 0, 0)
        name = 'Line Position'
                 
        self.plot_widget.addLegend(offset = (0, 0))
        # Create curve items for the plots with different colors
        self.curve = self.plot_widget.plot(x_data, self.y_data, pen=pg.mkPen(color=color), name=name)


        # Start a timer to update the plot
        self.timer = pg.QtCore.QTimer()
        self.timer.timeout.connect(self.update_plot)
        self.timer.start(3)  # Update plot every 50 milliseconds (20 FPS)

        self.plot_widget.setTitle("MARV SENSOR")
        self.plot_widget.setYRange(0, 6000)

        # Set the background color to white
        self.plot_widget.setBackground('w')

        # Set up the window
        self.setWindowTitle("Real-Time Plot")
        self.setGeometry(100, 100, 800, 600)

    def update_plot(self):
        print('updating')
        reading = self.UDPServerSocket.recv(32)

        if len(reading) >= 4:
            reading = process_raw_reading(reading)
            print(reading)

            # Update the plot
            y_new = reading
            self.y_data     = np.roll(self.y_data, -1)
            self.y_data[-1] = y_new
            self.curve.setData(x_data, self.y_data)
        else:
            self.curve.setData(x_data, self.y_data)
                    
    def get_label_text(self, color):
        if color == (255, 0, 0):
            return "X"
        elif color == (0, 255, 0):
            return "Y"
        elif color == (0, 0, 255):
            return "Z"
        else:
            return ""

def process_raw_reading(reading) -> float:
    import struct 
    print(reading)
    reading = struct.unpack('<f', reading)[0]
    return reading

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = RealTimePlotApp()
    window.show()
    sys.exit(app.exec())