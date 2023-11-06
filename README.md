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





