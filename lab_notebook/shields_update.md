# Green Shields

Place a green shield on a plant you control. The next time it is targetted, counter it and grow that plant.

# White Shields

Place a white shield on a plant your opponent controls. The next time they would play that color, they don't.

# Both Shields

After a shield counters, that shield is deactivated.

# Need To Figure Out

At the moment White Shields are setup to be on both sides instead of just the opponent's side. The backup shields compare against current shields check is setup for that. Need to check if its still safe to use that method for both of them. Might be? Issue with that will be that I can't do the easy == I think, it'd have to be a >=? But not sure if that'll work as I expect.


I might be able to just repurpose Handle Protect and Handle Block. That would let me focus everything onto the card playing checks instead.

## Shield Values

1 to 5 is "Protect"
6 to 10 is "Block"

White = Block
Green = Protect

# Clean Up

Need to simplify the setter function now, it isn't doing comparisons or complex movement anymore.

Simplified it enough. Still need to add the logic for the opponents'.

Opponent Check For White Shields Good

Need to Check for Green Shields?

Okay looks like I already changed Forest to be a shield for Opponents.

Opponent Setup for playing their own shields, need to update Opponent to be countered correctly. The need to do the same for player.

Need to update the checker for Mountain and Skull

Skull complete. Need to do Flame now.

Did it by making a "Check for Green Shields" script, and making the counter effect be playerhandinc + playerscoreinc & drawings

Mountain handled. Disable old counter check, added another "Player Score Increment" to the counter state.
