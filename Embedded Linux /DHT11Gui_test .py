# This code to test the sensor using the advantage of Embedded Linux to show it On GUI 
import Adafruit_DHT
import tkinter as tk

# Configure DHT sensor
sensor = Adafruit_DHT.DHT11
pin = 6

# Create the main window
window = tk.Tk()
window.title("DHT11 Sensor GUI")

sensor_label = tk.Label(window, text='Temp=  Humidity=', font=('Arial', 24))
sensor_label.pack(pady=20)

def update_sensor_data():
    humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)
    if humidity is not None and temperature is not None:
        sensor_label.config(text='Temp={0}*C  Humidity={1}%'.format(temperature, humidity))
    else:
        sensor_label.config(text='Failed to get reading. Try again!')

    window.after(2000, update_sensor_data)

update_sensor_data()

window.mainloop()
