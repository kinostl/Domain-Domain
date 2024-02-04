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
