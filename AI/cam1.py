import cv2
from picamera2 import Picamera2
import pandas as pd
from ultralytics import YOLO
import cvzone
import numpy as np
import RPi.GPIO as GPIO

# Setup GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(27, GPIO.OUT)

picam2 = Picamera2()
picam2.preview_configuration.main.size = (640, 480)
picam2.preview_configuration.main.format = "RGB888"
picam2.preview_configuration.align()
picam2.configure("preview")
picam2.start()

model = YOLO('best.pt')

my_file = open("New Text Document.txt", "r")
data = my_file.read()
class_list = data.split("\n")
count = 0

# Set the score threshold for detection results
score_threshold = 0.3

try:
    while True:
        im = picam2.capture_array()
        
        count += 1
        if count % 3 != 0:
            continue
        
        im = cv2.flip(im, -1)
        results = model.predict(im)
        a = results[0].boxes.data
        px = pd.DataFrame(a).astype("float")
        
        stop_detected = False
        
        for index, row in px.iterrows():
            x1 = int(row[0])
            y1 = int(row[1])
            x2 = int(row[2])
            y2 = int(row[3])
            d = int(row[5])
            score = row[4]
            c = class_list[d]
            
            # Draw boundary boxes for all classes
            if score > score_threshold:
                cv2.rectangle(im, (x1, y1), (x2, y2), (0, 0, 255), 2)
                cvzone.putTextRect(im, f'{c} {score:.2f}', (x1, y1), 1, 1)
                
                # Check if the detected class is "Stop"
                if c == "Stop":
                    stop_detected = True
        
        if stop_detected:
            GPIO.output(27, GPIO.HIGH)
        else:
            GPIO.output(27, GPIO.LOW)
        
        cv2.imshow("Camera", im)
        if cv2.waitKey(1) == ord('q'):
            break

finally:
    cv2.destroyAllWindows()
    GPIO.cleanup()
