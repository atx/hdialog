hdialog
=======

Xdialog clone for Haiku

This tool can be used to display GUI dialogs from shell scripts.

#### Installation

```bash
$ git clone git@github.com:atalax/hdialog.git
$ cd hdialog
$ make OBJ_DIR=objects
$ cp objects/hdialog ~/config/non-packaged/bin/
```

#### Usage
```
Usage:
    hdialog <type> [arguments]...
Display a GUI dialog.

      --help       display this help
  -w, --width      width of the dialog
  -h, --height     height of the dialog
  -t, --title      title of the window
  -m, --modal      set the type of the window to modal

Dialog types:
  --info text...
  --input text...
  --status text...
  --radio text opt1 opt2 opt3...
  --checkbox text opt1 opt2 opt3...
  --status text...
  --color text...

GitHub: https://github.com/atalax/hdialog
```
#### Examples

You can create standard `alert`-like dialogs:

```
$ hdialog -m --info "Finished downloading all files."
```

![simple-info](https://cloud.githubusercontent.com/assets/3966931/5182640/0e5cbe4a-74a5-11e4-8ab9-78c47e3dfabe.png)

```
$ hdialog -m --yesno "Do you really want to delete ~ ?"
```

![yesno](https://cloud.githubusercontent.com/assets/3966931/5184287/6d79a2ba-74b6-11e4-96be-2b91be477471.png)

Ask for textual input:

```
$ hdialog -m --input "Hello, what's yout name? :)"
```

![name-input](https://cloud.githubusercontent.com/assets/3966931/5182914/b51a726a-74a8-11e4-80f3-d3ffefd7ed8c.png)

You can also do selections from multiple items:

```
$ hdialog -m --radio "Which is your favourite color?" Red Yellow Green Orange Blue
```

![radio-colors](https://cloud.githubusercontent.com/assets/3966931/5182967/5eeefe14-74a9-11e4-9673-3a9fd40033da.png)

Or pick color:

```
$ hdialog -m --color Choose the color of your pony:
```

![hdialog-color](https://cloud.githubusercontent.com/assets/3966931/5802318/1310114c-9ff4-11e4-810f-9a4279c7b147.png)

You can remove the -m switch and get the standard non-modal window look:

```
$ hdialog --title Animals --checkbox "Which of the following are animals?" House Cow Dog Pencil Cat
```
![checkbox](https://cloud.githubusercontent.com/assets/3966931/5182989/c7cfb342-74a9-11e4-8b85-0a534ed9afe3.png)

The results are then returned using the standard output.

For displaying progress, `--status` can be used:

```
$ hdialog -m -h 70 -w 300 --status Downloading...
```

![status](https://cloud.githubusercontent.com/assets/3966931/5183014/1bd38f2c-74aa-11e4-84d6-b9df41b60034.png)

You can control the status bar by piping percentages to stdin and terminate it by `quit` like this:

```
$ (for x in $(seq 0 100); do echo $x; sleep 0.1; done; echo quit) | hdialog --status Counting...
```
