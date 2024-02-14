# Visual Log

Displays rolling text on the bottom of the screen. Does not (officially) support variables, so that your log doesn't suddenly break.

## Start Log

Use this at the start of your scene, or when you want to start logging. Prepares the overlay window and moves it into position for logging, then prints your first line to the bottom of it.

### First Line

What to put at the start of the log. Defaults to a blank space.

### Line Count

How many lines you want to dedicate to logging.

### Background Color

Whether you want to print onto a black screen (default) or a white screen. I recommend you invert your font files if you intend to use a black screen.

## Append To Log

Use only after `Start Log`. Pushes the previous logs up 1, then prints to the bottom of it. Accepts multiple lines, each line repeats this process.
