only reasonable way I can imagine this is with a plugin to replicate multi calling scripts but removing jumps.

so an event that'll just copy paste for me more or less.

variableInc
caseVariableValue

caseVariableValue expects an object with keys of 1,2,3,..16 and values that are of type `ScriptBuilderPathFunction`

It does what Switch does.

# Scripts with SubScripts

## Enable Player

- Reveal Opponent Hand

## End Player Turn

- Put Card In Play

## Forest - Handle

- Player Hand Increment
- Player Graveyard Decrement
- Draw Player Hand
- Draw Player Graveyard
- End Player Turn
- Player Hand Decrement
- Player Graveyard Increment

## Forest - Handle Opponent

- Opponent Hand Increment
- Opponent Graveyard Decrement
- Draw Opponent Graveyard
- Opponent Graveyard Increment

## Island - Handle Opponent

- Get Random Card
- Opponent Hand Increment

## Island - Handle Player

- Get Random Card
- Player Hand Increment
- End Player Turn

## Mountain - Handle

- Opponent Score Decrement
- Opponent Graveyard Increment
- Draw Opponent Score Area
- Draw Opponent Graveyard
- End Player Turn
- Opponent Score Increment
- Opponent Graveyard Decrement

## Mountain - Handle Opponent

- Player Score Decrement
- Player Graveyard Increment
- Clear Barrier
- Draw Player Score Area
- Draw Player Graveyard
- Player Score Increment
- Player Graveyard Decrement

## Plains - Handle

- Plains - Handle Protect
- Plains - Handle Block
- End Player Turn

## Put Card In Play

- Player Hand Decrement
- Player Score Increment
- Draw Player Score Area
- Draw Player Hand

## Reveal Opponent Hand

- Draw Opponent Hand

## Swamp - Handle

- Opponent Hand Decrement
- Opponent Graveyard Increment
- Reveal Opponent Hand
- Draw Opponent Graveyard
- End Player Turn
- Opponent Hand Increment

## Swamp - Handle Opponent

- Player Hand Decrement
- Player Graveyard Increment
- Draw Player Hand
- Draw Player Graveyard
- Player Hand Increment

I think End Player Turn's call to "Put Card In Play" might be the only 0->1->2->3 deep call

Almost every Land Handler can probably be moved to the Trigger's Script. That would make a lot of things be singular levelled.

Assume we do that the list will look like this.

# Scripts with SubScripts

## Enable Player

- Reveal Opponent Hand

## End Player Turn

- Put Card In Play

## Put Card In Play

- Player Hand Decrement
- Player Score Increment
- Draw Player Score Area
- Draw Player Hand

## Reveal Opponent Hand

- Draw Opponent Hand


## Call Grid

- Enable Player is only called in Prepare Player
- End Player Turn is in 14 places
- Put Card In Play is only in End Player Turn
- Reveal Opponent Hand is in 5 places


## Fixing

- Enable Player is not called anywhere or Prepare Player is commented out
- End Player Turn still in 14 places
- Put Card In Play moved to End Player Turn
- Reveal Opponent Hand is stil in 5 places
