# Logging

Purpose: Add some lines to the bottom of the screen that inform the player of whats happening and past actions.

## Contemplation

Just find a way to put all the logging into the Decrease/Increase/etc Scripts, and make wrappers for them where necessary? That might be easier than trying to put the logging into every single trigger and AI Script. Add a bit of logic maybe if necessary.

Currently, we have logs all over the triggers and its already getting cumbersome.


# Extend Logging

It might be possible to make an expandable overlay that can show the last few actions using some Write on BG magic or some sub mapping magic. A variable can easily store all the information known about a turn by using flags. Then we just need a script to interpret those, write them to bg, and then move to that section of the screen or scene swap or something like that.
