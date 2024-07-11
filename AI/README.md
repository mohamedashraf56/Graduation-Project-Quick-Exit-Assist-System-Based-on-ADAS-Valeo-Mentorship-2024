# AI Object Detection 

This Partion contains the files and code related to the AI-based object detection components of our graduation project on Advanced Driver Assistance Systems (ADAS) using Embedded Linux, with support from Valeo. These components aim to enhance vehicle safety by detecting objects. Feel free to explore the repository for the specific files and code related to these functionalities.

# 1- Pre-Trained Model

## we began by utilizing a pre-trained YOLOv8 Nano model trained on the COCO dataset. 

#### This initial pre-training phase gave our model a broad understanding of various object categories and real-world image variations. To tailor its knowledge to our specific application domain, we fine-tuned the model, ensuring optimal performance and accuracy.


![image](https://github.com/mohamedashraf56/GP-ADAS-Using-Embedded-Linux/assets/110823285/9c3fcb11-d0f1-43e8-b215-221daf5d5919)


![Untitled4](https://github.com/mohamedashraf56/GP-ADAS-Using-Embedded-Linux/assets/110823285/6182c155-3e91-420f-b404-134e1f216ca4)



https://github.com/mohamedashraf56/GP-ADAS-Using-Embedded-Linux/assets/110823285/623ffae6-498d-46c1-a1a8-55c129e25e5a


# 2- Transition to Custom Model
we transitioned from the pre-trained YOLOv8 Nano to a custom model to enhance system performance. By incorporating domain-specific optimizations, we refined accuracy and efficiency for our specific application contexts!


## Object Detection Custom Model

Objective: Enhance Advanced Driver Assistance Systems (ADAS) by accurately identifying critical objects on the road.

Model Focus: Detect six essential classes:
Car , Person ,Speed limit,Stop , Traffic cone , Traffic light

![image](https://github.com/user-attachments/assets/85033cc8-5f28-48ad-a253-26ab15f0aff2)

## Dataset

#### We collected 7,000 diverse images representing various traffic conditions, times of day, and weather scenarios. The balanced distribution of approximately 1,200 images per class captures the real-world variability and complexity of traffic situations.


## Labelling

#### Labeling process using Roboflow.
![image](https://github.com/user-attachments/assets/11a240f2-58ff-4970-a1cd-b1fe1b535945)          ![image](https://github.com/user-attachments/assets/914025eb-b69d-4691-98ef-4f6cf3d1f9e5)


## Dataset Augmentation

#### To further enhance the dataset, we applied various augmentation techniques.
 These techniques included: 

•Rotation: Rotating images to simulate different camera angles. 
•Scaling: Adjusting the size of the objects to reflect varying distances. 
•Brightness and Contrast Adjustments: Modifying lighting conditions to mimic different times of day and weather conditions.


![image](https://github.com/user-attachments/assets/18244939-527a-4e65-82b4-fb234eff3ddf)     ![image](https://github.com/user-attachments/assets/1404b26d-2a0a-44f4-9816-184f148a0e07)   ![image](https://github.com/user-attachments/assets/67884024-9bce-4a4a-8d11-5c13f20a7cc1)


# Results

![image](https://github.com/user-attachments/assets/4071c547-ccc6-4ee5-a6fe-073edb087ab6)     ![image](https://github.com/user-attachments/assets/58ebba10-e912-4c83-94ba-0cc1507c9902)


## Confusion Matrix

![image](https://github.com/user-attachments/assets/4a2719ed-3a99-498e-b056-9266a3354abe)


## Precision Curve

![image](https://github.com/user-attachments/assets/1e86c71a-8b66-43a2-adf0-704de9972535)


## Recall Curve

![image](https://github.com/user-attachments/assets/a62a8ce1-69e1-4b45-96b9-cb3248e54d17)

## F1 Score Curve

![image](https://github.com/user-attachments/assets/d7ea0a18-66d7-4ff1-adb9-548681c545ac)


## mAP50

![image](https://github.com/user-attachments/assets/7f6ece2b-a661-45f4-a96c-dae663598afd)


# Hardware

## Raspberry Pi 4 , LCD Touch Screen , Camera Module , Buzzer, LEDS.


![image](https://github.com/user-attachments/assets/5810565c-e21b-4467-a575-699b8dc391a3)







