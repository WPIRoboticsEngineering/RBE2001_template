# RBE2002_template
Template code for the RBE 2002 final project

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
C:\Users\harrington\git\RBE2002Code21
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

# Code Documentation Doxygen

In you checked out code, open doc/html/annotated.html to see the Doxygen documentation. 

# Troubleshooting

## arduinoPlugin\tools\make\make not found in PATH

There can be a currupted download to the Make tools, if this error comes up follow these instructions to correct it
Follow the instructions here : https://github.com/Sloeber/arduino-eclipse-plugin/issues/767





