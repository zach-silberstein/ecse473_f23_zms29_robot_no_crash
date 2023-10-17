# LAB4

### This project is a basic example using the Simple Two-Dimensional Robot (STDR) Simulator

#### Usage: 
To run the project, run the launcer.launch file by:  
`roslaunch robot_no_crash launcher.launch`   

The launch file has the following args:
- robot_ns
- rqt_gui

> robot_ns (string, default = "robot0")  
Specifies the name space to be launced in  
  
> rqt_gui (boolean, default = "true")  
If true, then the rqt_gui is launched
To control the robot using the gui:  
Add a Robot Steering Plugin and change the topic to **"/des_vel"**
