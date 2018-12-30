
## Install Eclipse and the Sloeber plugin (If the computer doesn't already have it)

Download the eclipse installer from here:

[https://www.eclipse.org/downloads/](https://www.eclipse.org/downloads/)

![alt text](/doc/downloadEclipseForC.png)

Run the Eclipse installer

![alt text](/doc/runEclipesInstaller.png)

Install the C developemt version. 

![alt text](/doc/selectCversion.png)

Install Eclipse on R drive if using lab machine

![alt text](/doc/installOnRDrive.png)

Once the install is done, open eclipse and go to the workbench. 

![alt text](/doc/openWorkspaceOnR.png)
![alt text](/doc/goToWorkspace.png)

Open

```
Help->Eclipse Marketplace...
```

Search for Sloeber 

![alt text](/doc/installSloeber.png)

Set the workspace to Arduino mode. In the upper right hand corner there is a button with a little yellow plus sign, and when you hover over it is says "pen Perspective". Click that button. Select Arduino. 

Eclipse will restart to load the plugin.

#### Open the Arduino Preferences:

```
Arduino -> Preferences
```

![alt text](/doc/ArduinoPreferences.png)

And start by removing both of the default values for private Hardware and Private libraries:

![alt text](/doc/removePrivatePaths.png)

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
![alt text](/doc/setPrivateFields.png)
