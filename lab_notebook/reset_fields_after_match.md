I'm thinking that it might be easiest to make a plugin for this, since I will probably have a large number of things I want to reset at different points.

It should be pretty easy, and only javascript? Loop over everything in the array, and `VM_SET_CONST 0` on anything that needs it.

It was easy to do that. Now to just find a place to call it and figure out which vars need resetting.

LAST_VARIABLE actually returns the result of this:

```js
export const defaultVariableForContext = (
  context: ScriptEditorContextType
): string => {
  if (context === "script") {
    return "V0";
  }
  if (context === "entity") {
    return "L0";
  } else {
    return "0";
  }
};
```

**Reset List - Player**

~~[ ] Revealed~~ To be added later.
[x] Scores
[x] Graveyard
[x] Hand

**Reset List - Opponent**

[x] Revealed
[x] Scores
[x] Graveyard
[x] Hand

**Reset Shields**

DEPENDENCY Need to rework Forests into Shields first, to know what in this will exist and change names of.

**Reset Winner**

[x] Winner
