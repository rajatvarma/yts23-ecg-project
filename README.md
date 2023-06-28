# YTS 2023: ECG Project

## Description

Usually, ECG machines are available only in hospitals and cost thousands of dollars. This makes regular heart checkups inaccessible and unaffordable. The aim of the ECG project was to understand the working of an ECG machine, and to build a low cost, accessible model. We built a 3-lead ECG machine along with a pulse sensor, using the following:

- ESP32 Microcontroller
- AD8232/WallySci E3K-ECG module
- 3 electrode + lead configuration
- 128x64 OLED screen

## Walkthrough

1. First, the pulse sensor was introduced to the students, along with its theory/working. They were asked to write basic code to filter the pulse sensor output and calculate BPM.
2. Then, the students were taught the theory of electrical signals in the body, and how an ECG machine works.
3. After being given the ECG module, the students were asked to write code to read the ECG output and display it on the serial monitor.
4. Next, the students were asked to display the output on the OLED screen.
5. Finally, the students were tasked with recording ECG data using python, graphing it, and calculating the BPM, along with average R-R interval time.

## Media

<video src="media/vid1.mp4" controls title="ECG on OLED-1" height="400px"></video>

<video src="media/vid2.mp4" controls title="ECG on OLED-2" height="400px"></video>
