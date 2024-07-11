#!/usr/bin/python3
import serial
import tkinter as tk
from datetime import datetime, timezone, timedelta
import time
import threading
import sys

# Function to update the date and time
def update_date_time():
    ismailia_timezone = timezone(timedelta(hours=2))
    ismailia_time = datetime.now(ismailia_timezone)
    date = ismailia_time.strftime("%Y-%m-%d")
    time_str = ismailia_time.strftime("%H:%M:%S")

    date_label.config(text=f"Date: {date}", fg="white", bg="black")
    time_label.config(text=f"Time: {time_str}", fg="white", bg="black")

    window.after(1000, update_date_time)

# Function to select mode based on received character and perform GSM actions
def select_mode(mode):
    mode_label.config(text=f"Mode: {mode}", fg="red")

    if mode == "Submerged" or mode == "Rollover":
        make_call("01552274661")  # Change the number to the desired one
        latitude, longitude = get_gps_coordinates()
        if latitude is not None and longitude is not None:
            message = "Help! My car has had a {} accident. Location: {}, {}".format(mode, latitude, longitude)
            send_message("+201552274661", message)  # Change the number to the desired one
            print("Location message sent.")
        else:
            print("Failed to retrieve GPS coordinates.")

# Function to exit the program
def exit_program():
    window.destroy()
    ser.close()
    gsm_ser.close()
    print("Serial ports closed.")

# Function to read data from UART
def read_uart():
    while True:
        if ser.in_waiting > 0:
            received_data = ser.read(ser.in_waiting).decode().strip()
            print(f"Received: {received_data}")
            if received_data == 'S':
                select_mode("Submerged")
            elif received_data == 'R':
                select_mode("Rollover")
            elif received_data == 'E':
                select_mode("Emergency Brake")
            elif received_data == 'B':
                select_mode("Blind Spot")
            elif received_data == 'D':
                select_mode("Don't Pass")    
        time.sleep(0.1)

# Function to send AT commands to the GSM module
def send_command(command, timeout=1):
    try:
        gsm_ser.write((command + '\r\n').encode())
        time.sleep(timeout)
        response = gsm_ser.read(gsm_ser.in_waiting).decode().strip()
        return response
    except Exception as e:
        print("Error:", e)
        return None

# Function to make a call
def make_call(number):
    try:
        send_command('ATD{};'.format(number))  # Dial the number
        print("Call initiated to", number)
        # Wait for 10 seconds to simulate a longer ringing period
        time.sleep(10)
        # Hang up the call
        send_command('ATH')
    except Exception as e:
        print("Error making call:", e)

# Function to retrieve GPS coordinates
def get_gps_coordinates():
    try:
        # Send command to retrieve GPS coordinates
        gps_data = send_command('AT+CGPSINF=0')  # Example command for GPS data
        # Parse GPS data to extract latitude and longitude
        # Modify this part based on the format of the GPS data received
        if gps_data:
            # Example parsing logic (modify based on actual GPS data format)
            parts = gps_data.split(',')
            latitude = parts[1]  # Placeholder, replace with actual parsing logic
            longitude = parts[2]  # Placeholder, replace with actual parsing logic
            return latitude, longitude
        else:
            return None, None
    except Exception as e:
        print("Error retrieving GPS coordinates:", e)
        return None, None

# Function to send SMS
def send_message(phone_number, message):
    try:
        send_command('AT+CMGF=1')  # Set SMS text mode
        send_command('AT+CMGS="{}"'.format(phone_number), timeout=2)  # Set recipient phone number
        send_command(message + chr(26), timeout=2)  # Send message and terminate with Ctrl+Z
    except Exception as e:
        print("Error sending message:", e)

# Initialize serial connection for UART (dashboard)
try:
    ser = serial.Serial('/dev/ttyAMA2', 9600, timeout=1)  # Adjust the UART port as needed
    print("Serial port (dashboard) opened successfully.")
except Exception as e:
    print("Error opening serial port (dashboard):", e)
    sys.exit(1)

# Initialize serial connection with GSM module
try:
    gsm_ser = serial.Serial('/dev/ttyAMA4', 9600, timeout=1)
    print("Serial port (GSM) opened successfully.")
except Exception as e:
    print("Error opening serial port (GSM):", e)
    sys.exit(1)

# Create the main window
window = tk.Tk()
window.title("Car Dashboard")
window.attributes('-fullscreen', True)  # Set the window to full screen
window.configure(bg="black")

screen_width = window.winfo_screenwidth()
screen_height = window.winfo_screenheight()
center_x = int(screen_width / 2)
center_y = int(screen_height / 2)

# Create gear state graphics
gear_canvas = tk.Canvas(window, width=350, height=150, bg="black", highlightthickness=0)
gear_canvas.place(relx=0.7, rely=0.2, anchor=tk.CENTER)

# Define the positions for gear labels
gear_positions = [(50, 50), (100, 50), (150, 50), (200, 50)]

# Draw gear labels
gear_canvas.create_text(gear_positions[0], text="P", font=("Arial", 52), fill="white")
gear_canvas.create_text(gear_positions[1], text="R", font=("Arial", 52), fill="white")
gear_canvas.create_text(gear_positions[2], text="N", font=("Arial", 52), fill="white")
gear_canvas.create_text(gear_positions[3], text="D", font=("Arial", 52), fill="Green")

# Create "Valeo" label on the same line as the gear state graphics
valeo_font = ("Arial", 52)  # Match the font size of gear labels
valeo_frame = tk.Frame(window, bg="black")
valeo_frame.place(relx=0.15, rely=0.2, anchor=tk.CENTER)

# Create "V" and "aleo" labels
v_label = tk.Label(valeo_frame, text="V", font=valeo_font, fg="green", bg="black")
v_label.pack(side=tk.LEFT)

aleo_label = tk.Label(valeo_frame, text="aleo", font=valeo_font, fg="white", bg="black")
aleo_label.pack(side=tk.LEFT)

# Create car function lights graphics
light_canvas = tk.Canvas(window, width=100, height=400, bg="black", highlightthickness=0)
light_canvas.place(relx=0.1, rely=0.6, anchor=tk.CENTER)

# Draw car function lights
def create_light_icon(canvas, position, color, shape="circle"):
    if shape == "circle":
        canvas.create_oval(position[0] - 20, position[1] - 20, position[0] + 20, position[1] + 20, fill=color)
    elif shape == "rectangle":
        canvas.create_rectangle(position[0] - 20, position[1] - 10, position[0] + 20, position[1] + 10, fill=color)

# Positions for light icons
light_positions = [(50, 50), (50, 150), (50, 250), (50, 350)]

# Draw light icons
create_light_icon(light_canvas, light_positions[0], "yellow", "circle")  # Headlight
light_canvas.create_text(light_positions[0][0], light_positions[0][1] + 40, text="Headlight", fill="white")

create_light_icon(light_canvas, light_positions[1], "red", "circle")  # Battery
light_canvas.create_text(light_positions[1][0], light_positions[1][1] + 40, text="Battery", fill="white")

create_light_icon(light_canvas, light_positions[2], "orange", "circle")  # Oil Pressure
light_canvas.create_text(light_positions[2][0], light_positions[2][1] + 40, text="Oil", fill="white")

create_light_icon(light_canvas, light_positions[3], "red", "circle")  # Seat Belt
light_canvas.create_text(light_positions[3][0], light_positions[3][1] + 40, text="Seat Belt", fill="white")

# Create labels
date_label = tk.Label(window, text="Date: -", font=("Arial", 25), fg="white", bg="black")
date_label.place(relx=0.5, rely=0.4, anchor=tk.CENTER)

time_label = tk.Label(window, text="Time: -", font=("Arial", 25), fg="white", bg="black")
time_label.place(relx=0.5, rely=0.45, anchor=tk.CENTER)

speed_label = tk.Label(window, text="Speed: - km/h", font=("Arial", 25), fg="cyan", bg="black")
speed_label.place(relx=0.5, rely=0.5, anchor=tk.CENTER)

rpm_label = tk.Label(window, text="RPM: -", font=("Arial", 25), fg="magenta", bg="black")
rpm_label.place(relx=0.5, rely=0.55, anchor=tk.CENTER)

mode_label = tk.Label(window, text="Mode: -", font=("Arial", 30), fg="red", bg="black")
mode_label.place(relx=0.5, rely=0.6, anchor=tk.CENTER)

# Create temperature indicator
temperature_canvas = tk.Canvas(window, width=120, height=120, bg="black", highlightthickness=0)
temperature_canvas.place(relx=0.5, rely=0.75, anchor=tk.CENTER)
temperature_canvas.create_arc(10, 10, 110, 110, start=0, extent=180, style=tk.ARC, outline="white", width=5)
temperature_canvas.create_text(60, 60, text="25°C", font=("Arial", 22), fill="white")

# Create exit button
exit_button = tk.Button(window, text="Exit", font=("Arial", 18), command=exit_program)
exit_button.place(relx=0.95, rely=0.95, anchor=tk.SE)

# Start updating the date and time
update_date_time()

# Start the UART reading thread
uart_thread = threading.Thread(target=read_uart, daemon=True)
uart_thread.start()

# Start the GUI event loop
window.mainloop()

