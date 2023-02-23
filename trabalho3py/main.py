from tkinter import *
from tkinter import colorchooser
import serial
import time

def change_servo():
    value = spinbox.get()
    array = [2, int(value), 0, 0]
    arduino.write(bytes(array))

def change_color():
    try:
        color = colorchooser.askcolor(title="Selecione uma cor")[0]
        array = [0, color[0], color[1], color[2]]
        arduino.write(bytes(array))
    except TypeError:
        pass

def read_temperature():
    array = [1, 0, 0, 0]
    arduino.write(bytes(array))
    response = arduino.readline()
    try:
        temperature = float(response.decode('utf-8').strip())
        temperature_label.config(text='Temperatura: ' + str(temperature) + ' °C')
    except ValueError:
        pass
    root.after(500, read_temperature)


arduino = serial.Serial("COM7", 115200)
time.sleep(5)

root = Tk()
root.title('Comunicação Serial')

button = Button(root, text="Selecione a cor", command=change_color)
button.pack()

temperature_label = Label(root, text='Temperatura: ')
temperature_label.pack()
read_temperature()

spinbox = Spinbox(root, from_=0, to=180, command=change_servo)
spinbox.pack()

root.geometry("300x200")
root.mainloop()

arduino.close()
