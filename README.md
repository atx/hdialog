hdialog
=======

Xdialog clone for Haiku

This tool can be used to display GUI dialogs from shell scripts.

#### Installation

```bash
$ git clone git@github.com:atalax/hdialog.git
$ cd hdialog
$ make
$ cp *objects/hdialog ~/config/non-packaged/bin/
```

#### Usage
```
Usage:
    hdialog <type> [arguments]...
Display a GUI dialog.

  -h, --help       display this help
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

GitHub: https://github.com/atalax/hdialog
```
#### Examples

You can create standard `alert`-like dialogs:

```
$ hdialog -h 80 --title Done! --info Finished downloading all files
```

![simple-info](https://cloud.githubusercontent.com/assets/3966931/5158219/cf1e59f2-7335-11e4-97d7-103d1a317c71.png)

```
$ hdialog --title "Delete" --yesno "Do you really want to delete ~ ?"
```

![yesno](https://cloud.githubusercontent.com/assets/3966931/5158310/e762d076-7338-11e4-9e06-4e9071083554.png)

Ask for textual input:

```
$ hdialog --title Hello! --input "Hello, what's yout name? :)"
```

![name-input](https://cloud.githubusercontent.com/assets/3966931/5158244/68c1650e-7336-11e4-97ce-f762f3d42cf5.png)

You can also do selections from multiple items:

```
$ hdialog -h 260 --title "Colors" --radio "Which is your favourite color?" Red Yellow Green Orange Blue
```

![radio-colors](https://cloud.githubusercontent.com/assets/3966931/5158294/35171ca6-7338-11e4-8cb2-d8aa5ca9d90d.png)

![checkbox](https://cloud.githubusercontent.com/assets/3966931/5158321/657f4a48-7339-11e4-94ee-dca9cb2831a7.png)

The results are then returned using the standard output.

For displaying progress, `--status` can be used:

```
$ hdialog -h 80 -w 170 --title Download --status Downloading...
```

![status](https://cloud.githubusercontent.com/assets/3966931/5158348/3c2e0e94-733a-11e4-8146-b3e1e3c94eec.png)

You can control the status bar by piping percentages to stdin and terminate it by `quit` like this:

```
$ (for x in $(seq 0 100); do echo $x; sleep 0.1; done; echo quit) | hdialog --status Counting...
```

There is also the `--modal` switch which changes the way the dialog looks:

```
$ hdialog -w 220 --info --modal Nuclear meltdown imminent!
```

![modal](https://cloud.githubusercontent.com/assets/3966931/5158395/d3172d94-733b-11e4-8799-7a79acdd1f0b.png)


