# RBE2001_template
Template code for the RBE 2001 final project

# Arduino and the ESP32 Toolchain

## Driver

https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers


## Personal Computer install Windows  
download:

http://users.wpi.edu/~glipin/.uploads/RBE-arduino.zip

And extract it somewhare on your computer. Run Arduino in the extracted folder.

## Personal Computer install Linux / Mac 

see: https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md

## Arduino Libraries
### HOWTO
For detailed instructions on how libraries work, see: https://www.arduino.cc/en/Guide/Libraries

Open Arduino and select Sketch->Libraries -> Manage Libraries
### Which Libraries
Search for and install:

ESP32Servo

Esp32SimplePacketComs

SimplePacketComs

EspWii

WiiChuck

# Set up your project

## Create your private repository (Once per term per team)

In the browser, click the "+" button next to your user Icon in the upper right corner of any github page. 

Select Import repository. 

Use the URL:
```
https://github.com/WPIRoboticsEngineering/RBE2001_template
```

BE SURE TO SELECT PRIVATE! 

If private is not an option, follow these instructions: https://help.github.com/articles/applying-for-a-student-developer-pack/


Set the name during the import step as "RBE2001". **Do Not put anything different from that exact string**, Arduino uses directory names to find header files, and this project needs the name to be exactly "RBE2001". Change only if you and your team have all had exprence with Arduino Library develoment.  

## Add your team mates as collaborators

In your new repository, under 
```
Settings -> Collaborators
```
Search and add your team mates. 

# Develop Code for your project

## Install Eclipse and the Sloeber plugin (If the computer doesn't already have it)

Download the eclipse installer from here:

https://www.eclipse.org/downloads/

Install the C developemt version. 

Once the install is done, open eclipse and go to the workbench. Open
```
Help->Eclipse Marketplace...
```
Search for Sloeber 

Install "The Arduino Eclipse IDE named Sloeber" and restart eclipse. 

Set the workspace to Arduino mode. In the upper right hand corner there is a button with a little yellow plus sign, and when you hover over it is says "pen Perspective". Click that button. Select Arduino. 

Open the Arduino Preferences:
```
Arduino -> Preferences
```

Under Private Hardware Path, select New.. and search for (where you extracted Arduino)/hardware/ 

Mine looks like:
```
C:\WPIAPPS\arduino-1.8.3\hardware\
```

Under Private Library path, select New.. and search for your user library directory. It is usually in (your users home)\Documents\Arduino\libraries for Windows, or (your users home)/Arduino/libraries for Unix systems. You know you have the right one if the folder contains ESP32Servo, Esp32SimplePacketComs, SimplePacketComs, EspWii and WiiChuck Directories from the library install step above. Remember the location of this folder, it will be where you clone your code in a coming step. 

Mine looks like:
```
C:\Users\harrington\Documents\Arduino\libraries
```

## Clone your project

In eclipse, open 
```
Window->Show View-> Other -> Git ->Git Repositories
```

In the browser, Click the clone or download button in your new project and select clone (Be sure HTTPS not SSH is selected, unless you have set up your SSH keys). 

Copy the clone URL.

In Eclipse, right click in the git repositories and select clone. If your URL is still copied in the clip board, Eclipse will autofill most the clone information for the first step. Add your username and password.

Hit next and get to the Branch Selection window, change nothing and hit next.

Set the Destination Directory to your Arduino libraries folder (the folder you are still remembering from above). It is usually in (your users home)\Documents\Arduino\libraries for Windows, or (your users home)/Arduino/libraries for Unix systems. 

Mine looks like:
```
C:\Users\harrington\Documents\Arduino\libraries\RBE2001
```

Hit Finish

## Open your project and start working

To open the project you will be using Sloeber and the "Linked Example" development model. Your code is set up as a library. your launch file is the .ino, which is found in your projects "examples" directory. 

In Eclipse, Right click in the Project View and select 
```
New->Arduino Sketch
```
Give it a name, and select the ESP32 toolchain. 
```
Board: ESP32 Dev Module
Upload Protocol: Default
Port (the port your device is on)
Core Debug Level: None
Flash Frequency 80mhz
Flash Mode: QIO
Flash Size: 4mb
Partition Scheme: Default
Upload Speed: 921600
```
Then hit next

Select Sample sketch in the "Select Code:" dropdown. Select "Link to selected examples" and check the check box for
```
RBE2001 examples ->Final Project
```
Hit finish. The code that you should edit is in your project under libraries/RBE2001/



# Commit your changes

### Unfamiliar with Git?

run through this tutorial: https://resources.github.com/videos/github-best-practices/

### Familiar with Git?
When you make a change to any line of code, you should commit your changes. If you have worked for ~1 hour, then you should make a commit with a message describing your work. To do so, go back to 

Git Repositories

Expand it and right click on Working Tree and select Add to Index. This loads your changes into the git module.

Finally right click on RBE2001[master]->Commit

Be sure to set the "Author" and "Committer" fields sould both contain the same data like this:
```
Kevin Harrington <harrington@wpi.edu>
```

Messages should consist of 60 charrectors of short description describing what changed, 2 new lines, then a t least one full sentance describing the justification for the change. If you have more than one fime, only commit one at a time. using the "+" and "-" buttons in the Git Staging section. 

When you have chages to share with your team, first Right click on the repository and select "Pull". Merge any changes your team mates made and published to upstream. Then commit the merge (or commit nothing if the merge was clean) and push your changes to the upstream server.

Once you have pushed your changes, be sure to verify that they are on GitHub. On your repository, go to
```
Insights->Network
```
and verify your changes are there. 

# Code Structure

Your code for your robot is now set up as what Arduino calls a "Library". Libraries are collections of source code with example uses of that cource code. For your labs, the "examples" directory contains .ino files. The .ion file launched the code and should be as tiny as possible, less than 40 lines total. In general, students shouldn't change the .ino examples. 

Student code lives entirely in the "RBE2001" folder under libraries in eclipse. You should modify only code in that directory. 

## .h and .cpp files

Header files, ending in .h, contain function definitions. Executable code nd memory allocations do not belong in here. Class definitions and function definitions do belong in here.

Source files, ending in .cpp, contain executable code. This is code that will execute or declare memory usage. Class function definitions and method definitions belong in this file.

Naming conventions insist that the .h and .cpp files have the same base name, and that name match the name of the class defined inside. 

SimplePacketComs library is the core communication library to pass data from the Field Controller application and Esp32. Data is passed as a call and response from the application to the Esp32 and back. The call comes in as a UDP packet on port 1865. The response goes back to the host as a responding UDP packet. The first 4 bytes of a command contain an integer representing the command ID. THe next 60 bytes are data. Responses have the same command ID bytes, and data comign from the ESP32 back to the Application.

SimplePacketComs library is initialized with: 

```
launchControllerServer();
```

Commands are added to the SimplePacketComs library with:

```
addServer(PacketEventAbstract *) 
```

SimplePacketComs library loop will connect and maintain connection to the WiFi, listen to incomming commands, and route the commands to the approprate server object. Loop is called with:

```
loopServer();
```
## DO Change

MyRobot is the main class that defines your robot. All the code associated with the robot belongs in that class. The name of your robot is defined in this class. ALl memory used by your robot should be declared in the MyRobot class definition, and all robot methods belong in the MyRObot class.

Commands are single function classes that represent one command that comes in from the control application. Each command has a function called 
```
event(float*)
```
that is called by the SimplePacketComs library when that command is recived from the WiFi connection.


## DO NOT Change

The .ino file, any library besides RBE2001 or sloeber.ino.cpp. 

# 2001 control application
The application to control your robot over the WIFi is located here:

https://github.com/WPIRoboticsEngineering/RBE2001_template/releases

To use it, download 2001FieldController.jar and right click and run as Java application. 

You can also run it from the command line from the windows terminal:

```
javaw.exe -jar 2001FieldController.jar
```


# 2001 Final Project Commands

## Warehouse Robot
### E-Stop 

| |ID | byte |
|--- |--- | --- |
| downstream Bytes |4 | 0 |
| Contents downstream |1989 | --- |
| upstream Bytes |4 | 0 |
| Contents upstream |1989 | ---|

Set an E-Stop fault on the robot. No data is transmitted, but the state of the robot should be effected. The robot should freeze all motor functions within a 10ms of receiving this command. 

### Get Status
| |ID | byte |
|--- |--- | --- |
| downstream Bytes |4 | 0 |
| Contents downstream |2012 | --- |
| upstream Bytes |4 | 1 |
| Contents upstream |2012 | status value|

Request the status of the robot. The byte value represents the robot state.

| State description | value |
|--- |--- |
| Ready for new task | 0 |
| Heading to pickup | 1 |
| Waiting for approval to pickup | 2 |
| Picking up | 3 |
| Heading to Dropoff | 4 |
| Dropping off | 5 |
| Heading to safe zone| 6 |
| Fault: failed pickup| 7 |(Bonus Points)
| Fault: failed dropoff| 8 |(Bonus Points)
| Fault: excessive load| 9 |(Bonus Points)
| Fault: obstructed path| 10 |(Bonus Points)
| Fault: E Stop pressed | 11 |

### Clear Faults 

| |ID | byte |
|--- |--- | --- |
| downstream Bytes |4 | 0 |
| Contents downstream |1871 | --- |
| upstream Bytes |4 | 0 |
| Contents upstream |1871 | ---|

Clear all faults on the robot. No data is transmitted, but the state of the robot should be effected. The robot should bring it's self online. 
### Approve 

| |ID | byte |
|--- |--- | --- |
| downstream Bytes |4 | 0 |
| Contents downstream |1994 | --- |
| upstream Bytes |4 | 0 |
| Contents upstream |1994 | ---|

When the robot is in "Waiting for approval to pickup" state, this command is issued to advance the state machine. 
 
### Pick Order

| |ID | float |float |float |
|--- |--- | --- |--- | --- |
| downstream Bytes |4 | 4 | 4 | 4 |
| Contents downstream |1936 | pickup material | dropoff angle | dropoff position | 
| upstream Bytes |4 | 0 |
| Contents upstream |1936 | ---|

| Material Type | value |
|--- |--- |
| Aluminum | 0 |
| Plastic | 1 |


An order is placed with the robot. The first 3 values are the pickup material, followed by the drop off angle and the drop off position.



