# winrun
Simple Windows Executable to run commands from a file.

## About
The current [Base Camp™](https://mountain.gg/base-camp/) release does not support running commands or launching programs with custom launch options, 
while at the same time only allowing you to select .exe files to be launched. 

This program is a quick and dirty workaround for this usecase. 
I can't think of any other usecase, because usually you could just write a .bat file or something similar.

## Installation and Usage
- Download the [latest version](https://github.com/schnotzler/winrun/releases) (winrun.exe)
- Move the downloaded executable to any directory you like. I prefer to use same location as the program i want to run is in.
- Create a simple file named `winrun.cfg` in the ***same directory as winrun.exe*** 
- Add you command(s) to `winrun.cfg`. See [this example](https://github.com/schnotzler/winrun/blob/main/winrun.cfg) which would run the windows calculator app
- Now select `winrun.exe` from your directory in `Base Camp™`»`Device`»`Key Binding`»`Key`»`Function`»`Run Program`»`Link`

Note: Of course you can have multiple configuration of `winrun` in use, just make sure to use a different directory with a different `winrun.cfg`

<sub>This is provided as-is. Use this program at you own risk, i am not responsible for any problems or damages you might have due to using this program</sub>
