# Autonomous-Arduino-Robot-with-Bluetooth-Control
#Hello,
#So this repo consists of two codes:

#1) Arduino code to actually program how the autonomous robot behaves

#2) Python code to activate bluetooth control over a PC

#First off, check the pic.jpg in the repo to understand what kind of a robotics setup I'm talking about.
#The robot will use Ultrasonic HC-SR04 sensors (one on the left side, one on the right side and one on the front)
#to detect any obstacles and if any obstacles lie within the threshold limit, the DC motors will respond to move away.

#This is done by identifying AFMotor objects in the code and declaring a function that will convert electrical signals from the Ultrasonic
#sensors into distance values which then will be compared to the threshold distance value.

#This code allows for the robot to have 3 different modes that can be reset anytime during operation:

#1) Manual: Control the robot through raw inputs on your keyboard - no autonomous behaviour

#2) Auto: Autonomous control - the robot decides everything - only increasing/decreasing speed and mode reset commands from the keyboard will be functional

#3) Both: 1 and 2 combined

#For bluetooth communication, I used an HC-05 bluetooth module connected to the Serial1 pins of my Arduino Mega (but Arduino Uno would work too).

#As for the Python side, I took a look at the "Computer-To-Arduino-Bluetooth" repo by huberf ( found here: "https://github.com/huberf/Computer-to-Arduino-Bluetooth")

#I took out the Tkinter GUI part of the code out for simplicity but basically you can use the compiled .py file to input commands through your command prompt
#or you can copy the code from BluetoothRobot.py and use it from the IDLE interactive interface. You will notice that bluetooth communication starts when you use
#the .connect method of the bluetooth Socket object ("sock"). After connection is established, you can input any command that is defined in the Arduino code and it should work.
