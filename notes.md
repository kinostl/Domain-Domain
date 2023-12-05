work arounds

islands automatically counter anything targetting you, then removes 1 of whichever card you have the most of?

Hidden shield mechanic. You play an island, then choose a land type. If its your own, it counters the next thing targeting it. If its your opponent's, you counter the next time they play that.

forest = draw a card

plains = get a card from grave yard to hand

mountain = stone rain

swamp = opponent discards a card

island = no etb effect but can be pitched along with another land to act as a force of will to counter their play.

---
So I'm implementing an MtG Minigame called Domain into a Gameboy Color Videogame. Its a game where you have a deck of 10 of each basic land type. Your goals is to play 1 of each color or 5 of any color. When you play a land, you get an effect.

Plains - Return target land from your graveyard to your hand
Swamps - Opponent Discards a Card
Mountains - Destroy Target Land
Forest - Draw a Card

Islands are weird. You can pitch one and another land to counter a land being played. That won't adapt well to the videogame, because I don't want to have a popup any time you have an island asking if you want to counter a spell. It'd get cumbersome and lead to poorly thought out plays just to get rid of it. I'm trying to figure out non-realtime actions that an Island can cause instead.

So far I'm thinking it could put shields down. Like called shots. You don't need to pitch a land but you need to predict a play accurately. Put a shield on one of your lands to protect it from the next spell targeting it. Put a shield on one of your opponent's lands to counter the next time they play it.

I'm curious if anyone has any other ideas I should consider. I can't do bouncing because its too similar to what Mountains do. I'm open to making Islands Draw, and reworking Forests to do something else as well.
---

Consider reworking the interface to not use numbers. Theres enough space to fit 8 marbles in a row. First to 5 wins, so entering the enemy territory to win would feel good.
