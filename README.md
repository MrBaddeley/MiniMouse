# MiniMouse
Arduino code for Mini Mouse build using BLE board
This is for the software serial configuration of the board (jumpers in the B position).
As Softwareserial does conflict with the Servo libray I'm using direct PWM (analogwrite) to control the steering.
Pins D5 and D6 are used for forward / backward speed and pin D9 for steering
This uses the Softwareserial library, the dabble library and DFRobotDFPlayerMini library. 
Controls on Dabble: Joystick mode (analog) for steering and drive, Triangle to play track 1 (loop, file in the share drive) and X to pause the sound. 
Note, dabble interupts steering when buttons are pressed, hence the loop to kick off the sound and then steer. 
