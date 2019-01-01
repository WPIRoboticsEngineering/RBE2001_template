# RBE2002_template
Template code for the RBE 2002 final project

# Code Documentation Doxygen

In you checked out code, open doc/html/annotated.html to see the Doxygen documentation. The best way to understand this code is to start in the Files section of the documentation, and look at the .ino file. Look at the setup and loop call graphs.


# Hardware

See: https://github.com/WPIRoboticsEngineering/RobotInterfaceBoard

# Arduino Setup and Development Computer Options 

See: https://github.com/WPIRoboticsEngineering/RobotInterfaceBoard#development-computer-options

# Set up your project

Your privete Repository has been created for you here: https://github.com/RBE200x-lab

You and your team members should find your repository made with the template code in there. 


# Develop Code for your project

## Install Eclipse on Personal Machine

 [See Eclipse install instructions in InstallEclipse.md](InstallEclipse.md)

## Clone your project

In eclipse, open 
```
Window->Show View-> Other -> Git ->Git Repositories
```
![alt text](/doc/GitRepositories.png)

In the browser, Click the clone or download button in your new project and select clone (Be sure HTTPS not SSH is selected, unless you have set up your SSH keys).

 ![alt text](/doc/cloneFromGithub.png)

Copy the clone URL.

In Eclipse, click the clone button: 

 ![alt text](/doc/cloneNewRepo.png)

If your URL is still copied in the clip board, Eclipse will autofill most the clone information for the first step. Add your username and password.

 ![alt text](/doc/startCloning.png)

Hit next and get to the Branch Selection window, change nothing and hit next.

Use the default checkout location. 

Hit Finish

## Open your project and start working

In Eclipse, Right click in the Project View and select 
```
New->Arduino Sketch
```

 ![alt text](/doc/chreateNewSketch.png)

Un-check the default location, and seclect where you just cloned your code. Mine looks like: 

```
R:\git\RBE2002Code21
```

Give it the name:

```
RBE2002Code21
```
![alt text](/doc/setNameAndSourceLocation.png)

and select the ESP32 toolchain. 
```
Board: ESP32 Dev Module
Upload Protocol: Default
Port (the port your device is on)
Core Debug Level: None
Flash Frequency 80mhz
Flash Mode: QIO
Flash Size: 4mb
Partition Scheme: Default
PSRAM: Disabled
Upload Speed: 921600
```
![alt text](/doc/ESP32-setup.png)

Then hit next and select Default ino file

![alt text](/doc/defaultINO.png)

Hit finish. 

Once the project shows up in Project Explorer tab, build index:

![alt text](/doc/rebuildIndexToAddLibs.png)

# Code theory and structure and what to edit

If find yourself saying:
 
```
Geez, thats a lot of code :/ I dont even know where to begin...
```
then start here.

The first thing to dig into is not the code, but the documentation. The template code that you all got copies of is documented using [Doxygen](https://mesos.readthedocs.io/en/latest/c++-style-guide/) a code auto-documentation tool. It generates a rather nice website of hyperlinked documentation of all the code in this repository. Besides the normal text based documentation, it also will generate very nice graphs such as

Include graphs:

![include graphs](/doc/html/StudentsRobot_8h__incl.png) 

function call graphs:

![function call graphs](/doc/html/template_8ino_afe461d27b9c48d5921c00d521181f12f_cgraph.png)

and collaboration graphs:

![collaboration graphs](doc/html/classRobotControlCenter__coll__graph.png)

To access the full documentation, after cloning the code to your disk, open the doc/html/annotated.html file to start. Opening any of the .html files will get you into the mini website as well. This web site is all the code you will have access to while working on your robot. 

There are only 2 classes you need to edit to do all of your labs,  StudentsRobot and RBEPID. Use the Doxygen to search for them and navigate the Doxygen pages to learn about what these 2 classes are and how the code uses them. 

PIDMotor is a helper class that you will use but not have to modify (unless you want to, then go for it!). This class will use your PID implementation (it is defaulted to a simple p controller). It provides helper functions and structure for your PID controller. This class is also used by the communication layer to view and edit the PID controller from Java. PIDMotor has 2 subclasses

![PIDMotor](doc/html/classPIDMotor__inherit__graph.png)

HBridgeEncoderPIDMotor wrapps the ESP32Encoder and an h-Bridge control using ESP32PWM and digitalWrite().

ServoEncoderPIDMotor wrapps the ESP32Encoder and the ESP32Servo objects.

Both classes can be used interchangably using the methods in PIDMotor. You can set setpoints using startInterpolationDegrees, or set the motor to run at a velocity using setVelocityDegreesPerSecond. You can read the position of the motor using getAngleDegrees and its velocity using getVelocityDegreesPerSecond.  Use the Doxygen pages to look up usage information. 

Your robot's program will go in StudentsRobot. This class will get passed the PIDMotor objects to attach. This class will then be passes those same objects again each time the loop is called via the pidLoop method. After each pidLoop, the updateStateMachine is called and the motor objects are passed in.  


Your PID code will go in RBEPID. You will implement a PID controller in one of your labs and tune it for your robots motors. By default there is a simple P controller in the compute function. Note that you will need to implement both calc and clearIntegralBuffer. 

### Commands

Commands from Java are sent over the WiFi. For the WiFi to work the computer running the Java application and the ESP32 need to have the same subnet. This means out of the 4 number IP address printed by the ESP32's serial port when it connects:

```
WiFi connected! IP address: 192.168.1.116
```

the first 3 match the computer that the Java application is running on. The lab ESP32's are pre-configured to connect to the special FI103-Robots Wifi network, putting htem on the same subnet as the lab computers and any conputer plugged into the spare ethernet cables on the benchtops. NOTE WPI-Wireless is a *different* subnet and they will not be able to talk to each other.  

To search for your device, type the name you set in your .ino file. Use the control application to search for that device. If it finds it, it will open up the controls and you can send commands from the Java application to your robot. Those commands will call the associated method in StudentsRobot object. 

### Alternate WiFi connections using Android Phone or Home WIfi

Connecting to a hotspot or home wifi can be don with the esp32 and the serial moniter. Make sure the serial moniter is not using any line endings and open at 115200 and you can see the print statements of the core running. Type the name of the WiFi network you want to connect to into the serial send bar and once ita all there, hit enter. Wait for the WifiManager to prompt you for the password, then type that in as well and hit enter. 

Android phones hotspot mode works well. the Iphone hotspot does not work and seems to filter the communication packets out. 




# Commit your changes

### Unfamiliar with Git?

run through this tutorial: https://resources.github.com/videos/github-best-practices/

Also check out this cheat sheet: http://overapi.com/git

### Familiar with Git?
When you make a change to any line of code, you should commit your changes. If you have worked for ~1 hour, then you should make a commit with a message describing your work. To do so, go back to 

Finally right click on your project
```
Team->Commit
```
Be sure to set the "Author" and "Committer" fields sould both contain the same data like this:
```
Kevin Harrington <harrington@wpi.edu>
```

Messages should consist of 60 charrectors of short description describing what changed, 2 new lines, then a t least one full sentance describing the justification for the change. If you have more than one file, only commit one at a time. using the "+" and "-" buttons in the Git Staging section. 

When you have chages to share with your team, first Right click on the repository and select "Pull". Merge any changes your team mates made and published to upstream. Then commit the merge (or commit nothing if the merge was clean) and push your changes to the upstream server.

Once you have pushed your changes, be sure to verify that they are on GitHub. On your repository, go to
```
Insights->Network
```
and verify your changes are there. 



# Troubleshooting

## arduinoPlugin\tools\make\make not found in PATH

There can be a currupted download to the Make tools, if this error comes up follow these instructions to correct it
Follow the instructions here : https://github.com/Sloeber/arduino-eclipse-plugin/issues/767





