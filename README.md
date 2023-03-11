# winrun

Simple Windows Executable to run commands from a file.

## About

The current [Base Camp™](https://mountain.gg/base-camp/) release does not support running commands or launching programs with custom launch options, while at the same time only allowing you to select .exe files to be launched.

This program is a quick and dirty workaround for this usecase.

Sometimes it may be desired to launch applications in the background, without giving focus to them. ***winrun*** allows for this.

## Installation and Usage

- Download the [latest version](https://github.com/schnotzler/winrun/releases) (winrun.exe)
- Move the downloaded executable to any directory you like. I prefer to use same location as the program i want to run is in.
- Create a simple file named `winrun.cfg` in the ***same directory as winrun.exe***
- Add the process(es) you wish to run `winrun.cfg`. See [this example](https://github.com/schnotzler/winrun/blob/main/winrun.cfg) which would run the windows editor (notepad.exe). Have a look at section [Advanced Usage](#detailed-usage-of-cfg) for more information
- Now select `winrun.exe` from your directory in `Base Camp™`»`Device`»`Key Binding`»`Key`»`Function`»`Run Program`»`Link`

Note: Of course you can have multiple configurations of `winrun` in use, just make sure to use a different directory with a different `winrun.cfg`

## Detailed usage of `.cfg`

### General

The winrun.cfg file is parsed line by line.
Each line is executed one after another.
Empty lines are skipped.
It is therefore possible to open multiple programs in one go.

### Leading whitespaces
Leading spaces or tabs are ignored.
So each one of the lines below is valid in a `winrun.cfg` and is going to give the same result.

```txt
notepad.exe winrun.cfg
 notepad.exe winrun.cfg
		notepad.exe winrun.cfg
  	  notepad.exe winrun.cfg
```

### Running in background

The default behaviour if not specified is, that the newly launched Program will receive focus.

But it is possible to start programs in the background, without giving focus to them, as well.
However some applications give focus to themselves on launch, so your mileage may vary here.

To mark program, to be run without focus, just add `#NOFOCUS` before the command.

Whitespace handling is quite lenient here as well.

So each one of the lines below is valid in a `winrun.cfg` and is going to give the same result, that is opening notepad without giving focus to the new window.


```txt
#NOFOCUSnotepad.exe  winrun.cfg
#NOFOCUS notepad.exe  winrun.cfg
 #NOFOCUS notepad.exe  winrun.cfg
 #NOFOCUSnotepad.exe  winrun.cfg
#NOFOCUS     	     notepad.exe  winrun.cfg
 		 #NOFOCUS 	notepad.exe  winrun.cfg
 	#NOFOCUSnotepad.exe  winrun.cfg
```

Analog to `#NOFOCUS` there is also support for `#FOCUS`, which as you may have guessed gives focus to the new window.
`#FOCUS` may be omitted, since it is the default behaviour anyway.

You can mix and match `#NOFOCUS`, `#FOCUS`, and no explicit specification in the same `winrun.cfg` to your liking on a per-line-basis.

Example for a mixed `winrun.cfg`, that would start 2 instances of notepad in the background and 2 in the foreground (only the last one will retain focus obviously). 2 of the editors will be empty, while 2 opened winrun.cfg. With the empty notepad launched by line 3 having focus.

```txt
#NOFOCUSnotepad.exe  winrun.cfg
#FOCUS   notepad.exe  winrun.cfg
notepad.exe
#NOFOCUS notepad.exe
```

## Troubleshooting

- If you have problems running your program, try using the absolute file path of your program `C:\WINDOWS\system32\notepad.exe` for example
- Open an Issue only **after** you have read this `Readme.md` entirely

<sub>This is provided as-is. Use this program at you own risk, i am not responsible for any problems or damages you might have due to using this program</sub>
