# arduino

Here are some of the IoT demo apps I created using Arduino.

Each IoT demo is made of 3 products:

1. A device or a Thing as known in IoT terminology - which is an electronic device with a sensor and ability to connect to internet
2. An IoT Platform - which is a server-side service to collect data from sensors, process data as per application requirements, and create instructions for other set of devices that we call smart devices. Most of these demo use Sensligence Platform (www.sensligence.com).
3. Smart Devices - these devices help deliver user experience. For our demo we use standard computer monitors or LCD projectors. We can also use Smart TVs.

##Smart Marketing Demo

Here is item lists required for deployment of this demo.

**List of Electronics Components for building a prototype of the Device or Thing:**

1. Arduino Uno R3 prototype board (https://store.arduino.cc/product/A000066)
2. Ethernet Shield (https://store.arduino.cc/product/A000072) or WiFi Shield (https://store.arduino.cc/product/A000058)
3. Ultrasonic Distance Measuring Module (http://www.dx.com/p/hc-sr04-ultrasonic-sensor-distance-measuring-module-133696)
4. Male-to_Female Jumper Wires (http://www.dx.com/p/diy-male-to-female-dupont-breadboard-jumper-wires-black-multi-color-40-pcs-10cm-339078#.VcjmqU3bLVI)
5. USB cable type A/B (https://store.arduino.cc/product/M000006)

**Network Environment:**
Internet connectivity by either Ethernet (no credential) or WiFi (security mode WPA/WPA2 only)

**Server-side IoT Platform:**
This demo uses Sensligence (www.sensligence.com). 

**Development Machine:**
A computer is required so that to update the programs and load into Arduino board. You may find basic steps to configure Arduino IDE on Mac or Windows computer on Arduino website https://www.arduino.cc/en/Guide/HomePage. 

**Following is steps to configure the Arduino for our demo:**

1. Arduino Sketch for the demo is available for download at https://github.com/go2santosh/arduino. Choose any of these two files:
(a) ultrasoundDistance_ethernet_demo.ino uses Arduino Uno R3 prototype board with Ethernet shield
(b) ultrasoundDistance_wifi_demo.ino uses Arduino Uno R3 prototype board with WiFi shield
2. If you are using WiFi shield then you need to update YOUR_WIFI_SSID and YOUR_WIFI_PASSWORD in the Arduino Sketch.
3. Update YOUR_API_KEY in the Arduino Sketch with the Sensligence API Key. You can request an API Key at www.sensligence.com.
4. Here is how you should connect Ultrasonic Distance Sensor pins to Arduino pins:
VCC -> 5V VCC
GND -> GND
Trig -> Pin 2
Echo -> Pin 4

**Following is steps to configure a demo on Sensligence:**

1. Open this URL on Internet Explorer or Safari or Chrome browser: http://sensligence.com/views/smartActionsTest.html 
2. Enter your API Key
3. Click on "Get Smart Actions" button and you will see the default configurations. You can change the values as per use cases.

**Following is steps to configure Smart Devices:**

1. Open following URL in HTML5 compliant latest browser(IE/Safari/Chrome): http://sensligence.com/views/smartDemo.html 
2. Enter your API Key and press "Submit" button

That's all. If everything goes right then the Arduino will start uploading sensor data to Sensligence. Sensligence will start creating smart actions for Smart Devices based on sensor data. And, smart devices will start playing the instructions from Sensligence. 

Following YouTube video shows how this all looks when I configure it on my work desk: https://www.youtube.com/watch?v=D6s_mpXZ0F4

