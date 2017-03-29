#!/usr/bin/env python3
import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import QCoreApplication, pyqtSignal, Qt
import serial

SER_PORT = '/dev/ttyACM0'

authorized_commands = {
        'Toggle LEDs': 'toggle_leds',
        'Turn ON motor rotation': 'motor '
        }

class MainApp(QWidget):

    def __init__(self):
        super().__init__()

        self.ser = None
        self.cur_item = None
        self.cur_value = None

        self.handle_connect_slot()
        self.connect_slots()
        self.initUI()

    def connect_slots(self):
        self.connect_slot.connect(self.handle_connect_slot)
        self.send_action_slot.connect(self.handle_send_action_slot)

    def initUI(self):
        """ Inits the User Interface
        """

        connect_btn = QPushButton('Connect', self)
        connect_btn.clicked.connect(self.connect_slot)

        list_commands = QListWidget(self)
        for description, command in authorized_commands.items():
            item = QListWidgetItem(description)
            list_commands.addItem(item)
        list_commands.currentItemChanged.connect(self.handle_command_changed)

        send_btn = QPushButton('Send Command', self)
        send_btn.clicked.connect(self.send_action_slot)

        slider = QSlider(Qt.Horizontal, self)
        slider.setFocusPolicy(Qt.NoFocus)
        slider.valueChanged[int].connect(self.handle_slider_changed)

        self.pgess = QProgressBar(self)

        hbox = QHBoxLayout()
        hbox.addStretch(1)
        hbox.addWidget(connect_btn)
        hbox.addWidget(list_commands)

        vboxSlides = QVBoxLayout()
        vboxSlides.addWidget(slider)
        vboxSlides.addWidget(self.pgess)

        hbox.addLayout(vboxSlides)

        self.setLayout(hbox)
        self.setWindowTitle('Nuclear Dash')
        self.show()

    # Slots are defined using pyqtSignal
    connect_slot = pyqtSignal()
    send_action_slot = pyqtSignal()

    # Slots handlers
    def handle_progress_change(self, new_val):
        """ Handler called when the progress bar needs to be updated
        """
        self.pgess.update(new_val)

    def handle_slider_changed(self, new_val):
        """ Handler called when the slider value changes
        """
        self.cur_value = new_val

    def handle_command_changed(self, cur, prev):
        """ Handler called when the selected command changes
        """
        self.cur_item = cur.text()

    def handle_connect_slot(self):
        """ Handler for connect button
            Should try to open a new serial connection and close the existing
        """

        # Close serial port if already open
        if self.ser is not None:
            self.ser.close()

        # Start new connection
        try:
            self.ser = serial.Serial(SER_PORT)
        except:
            self.ser = None
            print("Serial port " + SER_PORT + " unavailable")

    def handle_send_action_slot(self):
        """ Handler for Send button
            Should send the command through the serial port
        """

        # Check for serial port
        if self.ser is None:
            print("No Connection available")
            return

        if self.cur_item is None:
            print("No selected command")
            return

        command_send = authorized_commands[self.cur_item]
        if self.cur_value is not None:
            command_send += str(self.cur_value)

        print("sending command: " + command_send)

        command_send += "\r\n"

        self.ser.write(command_send.encode('ascii'))

if __name__ == '__main__':
    app = QApplication(sys.argv)
    mainApp = MainApp()
    sys.exit(app.exec_())
