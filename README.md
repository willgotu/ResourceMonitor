# CMPE 220 Resource Monitor

This is a project intended for CMPE 220. The CMPE 220 Resource Monitor is a barebones Linux Resource monitor intended to teach students on how the inner working of how a Linux system gathers its resources and displays it on an interface.

### Features

Currently, the program supports the following:
* Monitor current CPU frequency
* Monitor current RAM statistics
* Monitor current Disk statistics

### Running the Project

To compile the project, there is a Makefile listed in the src directory. Simply run the command

>make

This will create an executable called `ResourceMonitor` in the project. Once you run the executable, you should see the CMPE 220 Resource Monitor running.

To clean up the project, simply run the command

>make clean

### Future Works

In future revisions, the hope is to add other capabilities such as monitor processes running on the system and monitor network activities such as receiving and sending packets.