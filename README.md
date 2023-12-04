# Introduction To Robotics
Homework assignments for the Robotics laboratory course in the third year at the University of Bucharest's Faculty of Mathematics and Computer Science consist of a set of tasks. Each assignment is accompanied by specific instructions, implementation guidelines, as well as code and image files.


<details>
<summary> <h2>Homework 2</h2> </summary>
<br>

### Task: Use a separate potentiometer for controlling each color of the RGB LED: Red, Green, and Blue. This control must leverage digital electronics. Specifically, you need to read the potentiometer’s value with Arduino and then write a mapped value to the LED pins.
### Code: [click here](https://github.com/Manu19x/IntroductionToRobotics/blob/main/sketch_oct22a.ino)
### Youtube video that shows how it works: [click here](https://youtube.com/shorts/qbaVMSnJ_Oc?si=G8W4escGwkBlPvqt)
![380233526_720468693258691_6219869733053416340_n](https://github.com/Manu19x/IntroductionToRobotics/assets/104021556/7cb6e894-ae49-4d40-9882-a22b18a49daf)

</details>

<details>
<summary> <h2>Homework 3</h2> </summary>
<br>
  
### Task: Design a control system that simulates a 3-floor elevator using the Arduino platform. 
Here are the specific requirements:
<ul>
  <li> LED Indicators: Each of the 3 LEDs should represent one of the 3 floors.
The LED corresponding to the current floor should light up. Additionally,
another LED should represent the elevator’s operational state. It should
blink when the elevator is moving and remain static when stationary.
 </li>
  <li>• Buttons: Implement 3 buttons that represent the call buttons from the
3 floors. When pressed, the elevator should simulate movement towards
the floor after a short interval (2-3 seconds).</li>
  <li> Buzzer (optional for Computer Science, mandatory for CTI):
The buzzer should sound briefly during the following scenarios:
– Elevator arriving at the desired floor (something resembling a ”cling”).
– Elevator doors closing and movement (pro tip: split them into 2
different sounds)
  </li>
  <li>State Change & Timers: If the elevator is already at the desired floor,
pressing the button for that floor should have no effect. Otherwise, after
a button press, the elevator should ”wait for the doors to close” and then
”move” to the corresponding floor. If the elevator is in movement, it
should either do nothing or it should stack its decision (get to the first
programmed floor, open the doors, wait, close them and then go to the
next desired floor).
 </li>
  <li>Debounce: Remember to implement debounce for the buttons to avoid
unintentional repeated button presses</li>
</ul>

### Code: [clickhere](https://github.com/Manu19x/IntroductionToRobotics/blob/main/homework_3elevator.ino)
### Youtube video that shows how it works: [click here](https://www.youtube.com/shorts/_G_iey8m5Zs)
![homerwork3](https://github.com/Manu19x/PCshopDataBase/assets/104021556/a7d00ddb-17c4-498f-814d-838a581f78fa)
</details>


<details>
<summary> <h2>Homework 4</h2> </summary>
<br>

### Task:  - 7 segment display drawing - Start with the dot point. The current position keeps flashing no matter if the part is turned on or off. You can use the joystick to hop around to nearby positions. A quick press of the button switches the part from on to off, or from off to on. If you hold the button for a while, it clears the whole display by turning off all the parts and putting the current position back at the dot. Interruptions are needed.
### Code: [click here](https://github.com/Manu19x/IntroductionToRobotics/blob/main/Homework4/homework4_7_seg.ino)
### Youtube video that shows how it works: [click here](https://youtu.be/1q8kYQo0aAA?si=I4LZ1vaigVZacQml)
![Screenshot_5](https://github.com/Manu19x/IntroductionToRobotics/assets/104021556/4d44520f-f498-4840-b825-3f26ce835bb5)



</details>


<details>
<summary> <h2>Homework 5</h2> </summary>
<br>

### Task:  - 4x 7 segment display stopwatch - Requirements:

The 4-digit 7-segment display should start with "000.0".
Buttons do the following:
Button 1: Starts or pauses the timer.
Button 2: Resets (if paused) or resets saved laps (if viewing laps).
Button 3: Saves a lap (when counting), cycles through the last 4 saved laps.
How it works:

The display starts with "000.0". Pressing Start begins the timer.
During the timer, pressing Lap saves that time, up to 4 laps. The 5th press overwrites the 1st. Reset does nothing during the timer, and Pause stops the timer.
In Pause mode, Lap doesn't work. Pressing Reset resets the timer to "000.0".
After reset, press Lap to cycle through saved laps. Continuous pressing cycles through laps. Reset in this state clears all flags and resets the timer to "000.0".
### Code: [click here](https://github.com/Manu19x/IntroductionToRobotics/tree/main/homework5)
### Youtube video that shows how it works: [click here](https://youtu.be/eQzjr2Uz1xY?si=lWtQG_9xk1qdMVWs)
![7687f603-be5d-4a21-a94f-c15229d5fd4e](https://github.com/Manu19x/IntroductionToRobotics/assets/104021556/043b106a-eda0-4e15-836f-7cc701498288)

</details>

<details>
<summary> <h2>Homework 6</h2> </summary>
<br>

### Task:  - Pseudo-smart Environment Monitor and Logger - Requirements:

The Smart Environment Monitor and Logger is a comprehensive system built around an Arduino microcontroller designed to collect and record diverse environmental data. Equipped with various sensors, this system captures information vital to understanding environmental conditions.

How It Works: Menu Structure
1. Sensor Settings
1.1 Sensors Sampling Interval: User input for the sensor sampling rate (between 1 and 10 seconds).
1.2 Ultrasonic Alert Threshold: Set threshold value for the ultrasonic sensor to trigger alerts.
1.3 LDR Alert Threshold: Set threshold value for the LDR sensor to trigger alerts.
1.4 Back: Return to the main menu.
2. Reset Logger Data
2.1 Yes: Confirm to delete all data.
2.2 No: Cancel data reset.
3. System Status
3.1 Current Sensor Readings: Continuous display of sensor readings at the set sampling rate; includes an exit option.
3.2 Current Sensor Settings: Displays sampling rate and threshold values for all sensors.
3.3 Display Logged Data: Displays the last 10 sensor readings for all sensors.
3.4 Back: Return to the main menu.
4. RGB LED Control
4.1 Manual Color Control: Set RGB LED colors manually.
4.2 LED: Toggle Automatic ON/OFF: Automatic mode: LED is GREEN if no sensor exceeds threshold; otherwise, RED. Manual mode uses last saved RGB values.
4.3 Back: Return to the main menu.


### Code: [click here](https://github.com/Manu19x/IntroductionToRobotics/blob/main/Homework6/environmentmonitor/environmentmonitor.ino)
### Youtube video that shows how it works: [click here](https://youtu.be/WZWiCGBvInU?si=FYIGRsdd3OByDrMv)
![5da47eb5-59ba-422e-a379-f8e8026a1069](https://github.com/Manu19x/IntroductionToRobotics/assets/104021556/02563942-e0f7-4ea1-9a76-597e5d05680d)


</details>

<details>
<summary> <h2>Homework 7</h2> </summary>
<br>

### Task:  - Pseudo Bomberman game
### How it works: The games start by generating the map and the player, as the game goes on you cand move around where there is no wall and you can destroy the walls by placing bombs.

### Youtube video that shows how it works: [click here](https://youtu.be/d4nvDhrWsQA)
### Code: [click here](https://github.com/Manu19x/IntroductionToRobotics/blob/main/h7/h7.ino)

![h7](https://github.com/Manu19x/IntroductionToRobotics/assets/104021556/dd8a5efa-98af-4be5-83ba-2ffca001b749)


</details>




