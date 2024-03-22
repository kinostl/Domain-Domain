`getNextLabel` will allow you to use the IDE's version of labeling within your own scripts, ensuring a unique label. This is good for things like making if statements in a custom event.

You can see the helpers here: https://github.com/chrismaltby/gb-studio/blob/develop/src/lib/compiler/scriptBuilder.ts

~~variableSetToUnionValue might be what you're looking for half the time.~~ false, does not set variables like the other set commands. Just use currying.

_declareLocal has potential to be interesting.
