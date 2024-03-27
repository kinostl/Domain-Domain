#include "math.h"
#include <stdlib.h>
#include <types.h>
#pragma bank 255

#include "vm.h"
#include <rand.h>
#include "data/game_globals.h"

/***
 *

You need to offset the bits, otherwise there's no way to extract the individual flags. If you had flags corresponding to 1, 2, 3, & 4, and a combined value of 5, how could you tell if it was 2 & 3 or 1 & 4?

You can also do it this way, for example:

enum {
    FIRST = 1 << 0, // same as 1
    SECOND = 1 << 1, // same as 2, binary 10
    THIRD = 1 << 2, // same as 4, binary 100
    FOURTH = 1 << 3 // same as 8, binary 1000
};

Then you combine flags like so:

int flags = FIRST | THIRD | FOURTH;

And you extract them like this:

if (flags & THIRD) { ...

    https://stackoverflow.com/questions/3643681/how-do-flags-work-in-c#3643698

*/

// Choice Flags
#define C_WHITE  (1 << 0)
#define C_PURPLE (1 << 1)
#define C_BLUE   (1 << 2)
#define C_RED    (1 << 3)
#define C_GREEN  (1 << 4)

// Targets as values
#define T_WHITE  1
#define T_PURPLE 2
#define T_BLUE   3
#define T_RED    4
#define T_GREEN  5

// Required for randomization, taken from gbvm's implementation.
#define C_MASK (limit | (limit >> 1) | (limit >> 2) | (limit >> 3) | (limit >> 4) | (limit >> 5) | (limit >> 6) | (limit >> 7) | (limit >> 8) | (limit >> 9) | (limit >> 10) | (limit >> 11) | (limit >> 12) | (limit >> 13) | (limit >> 14) | (limit >> 15))


uint16_t get_cards_in_hand(void) {
    uint16_t cards_in_hand = 0;
    if(GET_GLOBAL_VAL(OPPONENT_PLAINS_HAND) > 0) {
        cards_in_hand |= C_WHITE;
    }
    if(GET_GLOBAL_VAL(OPPONENT_SWAMPS_HAND) > 0) {
        cards_in_hand |= C_PURPLE;
    }
    if(GET_GLOBAL_VAL(OPPONENT_ISLANDS_HAND) > 0) {
        cards_in_hand |= C_BLUE;
    }
    if(GET_GLOBAL_VAL(OPPONENT_MOUNTAINS_HAND) > 0) {
        cards_in_hand |= C_RED;
    }
    if(GET_GLOBAL_VAL(OPPONENT_FORESTS_HAND) > 0) {
        cards_in_hand |= C_GREEN;
    }
    return cards_in_hand;
}

uint16_t get_player_hand_slots_with_cards(void) {
    uint16_t player_hand_slots_with_cards = 0;
    if(GET_GLOBAL_VAL(PLAYER_PLAINS_HAND) > 0) {
        player_hand_slots_with_cards |= C_WHITE;
    }
    if(GET_GLOBAL_VAL(PLAYER_SWAMPS_HAND) > 0) {
        player_hand_slots_with_cards |= C_PURPLE;
    }
    if(GET_GLOBAL_VAL(PLAYER_ISLANDS_HAND) > 0) {
        player_hand_slots_with_cards |= C_BLUE;
    }
    if(GET_GLOBAL_VAL(PLAYER_MOUNTAINS_HAND) > 0) {
        player_hand_slots_with_cards |= C_RED;
    }
    if(GET_GLOBAL_VAL(PLAYER_FORESTS_HAND) > 0) {
        player_hand_slots_with_cards |= C_GREEN;
    }
    return player_hand_slots_with_cards;
}

uint16_t get_planted_player_plots(void) {
    uint16_t planted_player_plots = 0;
    if(GET_GLOBAL_VAL(PLAYER_PLAINS_SCORE) > 0) {
        planted_player_plots |= C_WHITE;
    }
    if(GET_GLOBAL_VAL(PLAYER_SWAMPS_SCORE) > 0) {
        planted_player_plots |= C_PURPLE;
    }
    if(GET_GLOBAL_VAL(PLAYER_ISLANDS_SCORE) > 0) {
        planted_player_plots |= C_BLUE;
    }
    if(GET_GLOBAL_VAL(PLAYER_MOUNTAINS_SCORE) > 0) {
        planted_player_plots |= C_RED;
    }
    if(GET_GLOBAL_VAL(PLAYER_FORESTS_SCORE) > 0) {
        planted_player_plots |= C_GREEN;
    }
    return planted_player_plots;
}

uint16_t get_empty_plots(void) {
    uint16_t empty_plots = 0;
    if(GET_GLOBAL_VAL(OPPONENT_PLAINS_SCORE) == 0) {
        empty_plots |= C_WHITE;
    }
    if(GET_GLOBAL_VAL(OPPONENT_SWAMPS_SCORE) == 0) {
        empty_plots |= C_PURPLE;
    }
    if(GET_GLOBAL_VAL(OPPONENT_ISLANDS_SCORE) == 0) {
        empty_plots |= C_BLUE;
    }
    if(GET_GLOBAL_VAL(OPPONENT_MOUNTAINS_SCORE) == 0) {
        empty_plots |= C_RED;
    }
    if(GET_GLOBAL_VAL(OPPONENT_FORESTS_SCORE) == 0) {
        empty_plots |= C_GREEN;
    }
    return empty_plots;
}

uint16_t get_suffering_plots(void) {
    uint16_t weakest_plot = 5;
    uint16_t current_plot = 0;
    if(GET_GLOBAL_VAL(PLAYER_PLAINS_SCORE) > 0) {
        current_plot = GET_GLOBAL_VAL(PLAYER_PLAINS_SCORE);
        weakest_plot = MIN(weakest_plot, current_plot);
    }
    if(GET_GLOBAL_VAL(PLAYER_SWAMPS_SCORE) > 0) {
        current_plot = GET_GLOBAL_VAL(PLAYER_SWAMPS_SCORE);
        weakest_plot = MIN(weakest_plot, current_plot);
    }
    if(GET_GLOBAL_VAL(PLAYER_ISLANDS_SCORE) > 0) {
        current_plot = GET_GLOBAL_VAL(PLAYER_ISLANDS_SCORE);
        weakest_plot = MIN(weakest_plot, current_plot);
    }
    if(GET_GLOBAL_VAL(PLAYER_MOUNTAINS_SCORE) > 0) {
        current_plot = GET_GLOBAL_VAL(PLAYER_MOUNTAINS_SCORE);
        weakest_plot = MIN(weakest_plot, current_plot);
    }
    if(GET_GLOBAL_VAL(PLAYER_FORESTS_SCORE) > 0) {
        current_plot = GET_GLOBAL_VAL(PLAYER_FORESTS_SCORE);
        weakest_plot = MIN(weakest_plot, current_plot);
    }

    if (weakest_plot == 5) {
        return 0;
    }

    uint16_t suffering_plots = 0;
    if(GET_GLOBAL_VAL(PLAYER_PLAINS_SCORE) == weakest_plot) {
        suffering_plots |= C_WHITE;
    }
    if(GET_GLOBAL_VAL(PLAYER_SWAMPS_SCORE) == weakest_plot) {
        suffering_plots |= C_PURPLE;
    }
    if(GET_GLOBAL_VAL(PLAYER_ISLANDS_SCORE) == weakest_plot) {
        suffering_plots |= C_BLUE;
    }
    if(GET_GLOBAL_VAL(PLAYER_MOUNTAINS_SCORE) == weakest_plot) {
        suffering_plots |= C_RED;
    }
    if(GET_GLOBAL_VAL(PLAYER_FORESTS_SCORE) == weakest_plot) {
        suffering_plots |= C_GREEN;
    }

    return suffering_plots;
}


uint16_t get_suffering_player_cards(void) {
    uint16_t weakest_card = 5;
    if(GET_GLOBAL_VAL(PLAYER_PLAINS_HAND) > 0) {
        weakest_card = MIN(weakest_card, GET_GLOBAL_VAL(PLAYER_PLAINS_HAND));
    }
    if(GET_GLOBAL_VAL(PLAYER_SWAMPS_HAND) > 0) {
        weakest_card = MIN(weakest_card, GET_GLOBAL_VAL(PLAYER_SWAMPS_HAND));
    }
    if(GET_GLOBAL_VAL(PLAYER_ISLANDS_HAND) > 0) {
        weakest_card = MIN(weakest_card, GET_GLOBAL_VAL(PLAYER_ISLANDS_HAND));
    }
    if(GET_GLOBAL_VAL(PLAYER_MOUNTAINS_HAND) > 0) {
        weakest_card = MIN(weakest_card, GET_GLOBAL_VAL(PLAYER_MOUNTAINS_HAND));
    }
    if(GET_GLOBAL_VAL(PLAYER_FORESTS_HAND) > 0) {
        weakest_card = MIN(weakest_card, GET_GLOBAL_VAL(PLAYER_FORESTS_HAND));
    }

    uint16_t suffering_cards = 0;
    if(GET_GLOBAL_VAL(PLAYER_PLAINS_HAND) == weakest_card) {
        suffering_cards |= C_WHITE;
    }
    if(GET_GLOBAL_VAL(PLAYER_SWAMPS_HAND) == weakest_card) {
        suffering_cards |= C_PURPLE;
    }
    if(GET_GLOBAL_VAL(PLAYER_ISLANDS_HAND) == weakest_card) {
        suffering_cards |= C_BLUE;
    }
    if(GET_GLOBAL_VAL(PLAYER_MOUNTAINS_HAND) == weakest_card) {
        suffering_cards |= C_RED;
    }
    if(GET_GLOBAL_VAL(PLAYER_FORESTS_HAND) == weakest_card) {
        suffering_cards |= C_GREEN;
    }

    return suffering_cards;
}

uint16_t get_suffering_cards(void) {
    uint16_t weakest_card = 5;
    if(GET_GLOBAL_VAL(OPPONENT_PLAINS_HAND) > 0) {
        weakest_card = MIN(weakest_card, GET_GLOBAL_VAL(OPPONENT_PLAINS_HAND));
    }
    if(GET_GLOBAL_VAL(OPPONENT_SWAMPS_HAND) > 0) {
        weakest_card = MIN(weakest_card, GET_GLOBAL_VAL(OPPONENT_SWAMPS_HAND));
    }
    if(GET_GLOBAL_VAL(OPPONENT_ISLANDS_HAND) > 0) {
        weakest_card = MIN(weakest_card, GET_GLOBAL_VAL(OPPONENT_ISLANDS_HAND));
    }
    if(GET_GLOBAL_VAL(OPPONENT_MOUNTAINS_HAND) > 0) {
        weakest_card = MIN(weakest_card, GET_GLOBAL_VAL(OPPONENT_MOUNTAINS_HAND));
    }
    if(GET_GLOBAL_VAL(OPPONENT_FORESTS_HAND) > 0) {
        weakest_card = MIN(weakest_card, GET_GLOBAL_VAL(OPPONENT_FORESTS_HAND));
    }

    uint16_t suffering_cards = 0;
    if(GET_GLOBAL_VAL(OPPONENT_PLAINS_HAND) == weakest_card) {
        suffering_cards |= C_WHITE;
    }
    if(GET_GLOBAL_VAL(OPPONENT_SWAMPS_HAND) == weakest_card) {
        suffering_cards |= C_PURPLE;
    }
    if(GET_GLOBAL_VAL(OPPONENT_ISLANDS_HAND) == weakest_card) {
        suffering_cards |= C_BLUE;
    }
    if(GET_GLOBAL_VAL(OPPONENT_MOUNTAINS_HAND) == weakest_card) {
        suffering_cards |= C_RED;
    }
    if(GET_GLOBAL_VAL(OPPONENT_FORESTS_HAND) == weakest_card) {
        suffering_cards |= C_GREEN;
    }

    return suffering_cards;
}

uint16_t random(uint16_t limit){

    uint16_t value = randw() & C_MASK;
    if (value >= limit) value -= limit;
    if (value >= limit) value -= limit;

    return value;
}

uint16_t sample(uint16_t* choices, uint16_t limit){

    uint16_t value = randw() & C_MASK;
    if (value >= limit) value -= limit;
    if (value >= limit) value -= limit;

    return choices[value];
}

uint16_t get_random_choice(uint16_t options){
        uint16_t choices_size = 0;
        uint16_t choices[5];
        if(options & C_WHITE){
            choices[choices_size] = T_WHITE;
            choices_size++;
        }
        if(options & C_PURPLE){
            choices[choices_size] = T_PURPLE;
            choices_size++;
        }
        if(options & C_BLUE){
            choices[choices_size] = T_BLUE;
            choices_size++;
        }
        if(options & C_RED){
            choices[choices_size] = T_RED;
            choices_size++;
        }
        if(options & C_GREEN){
            choices[choices_size] = T_GREEN;
            choices_size++;
        }

        if(choices_size == 0){return -1;}
        if(choices_size == 1){return choices[0];}

        uint16_t choice = sample(choices, choices_size);
        return choice;
}

void handleDebugCirno(void) {
    /*
     * Debug AI - Garden or Flower
     * Action Priority:
     *  1. Play Chosen Color
     *  2. Play Randomly
    */

    uint16_t cards_in_hand = get_cards_in_hand();
    uint16_t * card_choice = GET_GLOBAL_REF(OPPONENT_LAST_CHOICE);
    uint16_t color_pref = GET_GLOBAL_VAL(CURRENT_OPPONENT);
    uint16_t has_color_pref = 0;
    switch(color_pref){
        case T_WHITE:
            if(cards_in_hand & C_WHITE){
                *card_choice = T_WHITE;
                has_color_pref = 1;
            }
            break;
        case T_PURPLE:
            if(cards_in_hand & C_PURPLE){
                *card_choice = T_PURPLE;
                has_color_pref = 1;
            }
            break;
        case T_BLUE:
            if(cards_in_hand & C_BLUE){
                *card_choice = T_BLUE;
                has_color_pref = 1;
            }
            break;
        case T_RED:
            if(cards_in_hand & C_RED){
                *card_choice = T_RED;
                has_color_pref = 1;
            }
            break;
        case T_GREEN:
            if(cards_in_hand & C_GREEN){
                *card_choice = T_GREEN;
                has_color_pref = 1;
            }
            break;
    }

    if(has_color_pref == 0){
        *card_choice = get_random_choice(cards_in_hand);
    }


}

/*
    * Blue AI - Garden or Flower
    * Action Priority:
    *  1. Play Blue
    *  2. Play Randomly
    *
    * Played by Cirno
*/
void handleBlueAiCardChoice(void) {
    uint16_t cards_in_hand = get_cards_in_hand();
    uint16_t * card_choice = GET_GLOBAL_REF(OPPONENT_LAST_CHOICE);

    if(cards_in_hand & C_BLUE){
        *card_choice = T_BLUE;
    }else{
        *card_choice = get_random_choice(cards_in_hand);
    }
}

/*
    ```
    Green AI - Bloom Green and Garden Balance
    Action Priority:
    1. Play Green
    2. Protect Unprotected
    3. Fill Empty Plots
    ```

    Green now protects your colors with "The next time this would wither, it will bloom instead."

    Green Smart AI should protect whatever is lowest in hand at the moment

    Played by Yuuka
*/
void handleGreenAiCardChoice(void) {
    uint16_t cards_in_hand = get_cards_in_hand();
    uint16_t empty_plots = get_empty_plots();
    uint16_t cards_in_hand_with_empty_plots = cards_in_hand & empty_plots;

    uint16_t * card_choice = GET_GLOBAL_REF(OPPONENT_LAST_CHOICE);

    if(cards_in_hand & C_GREEN){
        *card_choice = T_GREEN;
    }else{
        if(cards_in_hand_with_empty_plots > 0){
            *card_choice = get_random_choice(cards_in_hand_with_empty_plots);
        }else{
            *card_choice = get_random_choice(cards_in_hand);
        }
    }
}

void handleGreenAiChooseTarget(void) {
    uint16_t unprotected_cards = ~(GET_GLOBAL_VAL(OPPONENT_SHIELDS)); //Inversion of the Protected Cards
    uint16_t suffering_cards = get_suffering_cards();
    uint16_t * card_choice = GET_GLOBAL_REF(TARGETED_CARD);

    *card_choice = get_random_choice(unprotected_cards & suffering_cards);
}

void chooseRandomGreenTarget(void) {
    uint16_t unprotected_cards = ~(GET_GLOBAL_VAL(OPPONENT_SHIELDS)); //Inversion of the Protected Cards
    uint16_t * card_choice = GET_GLOBAL_REF(TARGETED_CARD);
    *card_choice = get_random_choice(unprotected_cards);
}

/*
    ```
    Yellow AI - Garden and Bloom Yellow
    Action Priority:
    1. Play White
    2. Block Unblocked
    ```

    Yellow no longer has the ability to protect. It can only block.

    Played by Marissa? Or Reimu?
*/
void handleWhiteAiCardChoice(void) {
    uint16_t cards_in_hand = get_cards_in_hand();
    uint16_t * card_choice = GET_GLOBAL_REF(OPPONENT_LAST_CHOICE);

    if(cards_in_hand & C_WHITE){
        *card_choice = T_WHITE;
    }else{
        *card_choice = get_random_choice(cards_in_hand);
    }
}

void handleWhiteAiChooseTarget(void) {
    uint16_t unblocked_cards = ~(GET_GLOBAL_VAL(OPPONENT_SHIELDS)) >> 5; //Inversion of the Protected Cards
    uint16_t * card_choice = GET_GLOBAL_REF(TARGETED_CARD);
    if(unblocked_cards & C_RED){
        *card_choice = T_RED;
    }else{
        *card_choice = get_random_choice(unblocked_cards);
    }
}

void chooseRandomWhiteTarget(void) {
    uint16_t unblocked_cards = ~(GET_GLOBAL_VAL(OPPONENT_SHIELDS)) >> 5; //Inversion of the Protected Cards
    uint16_t * card_choice = GET_GLOBAL_REF(TARGETED_CARD);
    *card_choice = get_random_choice(unblocked_cards);
}

/*
```
Purple AI - Bloom
Action Priority:
1. Play Purple
2. Prevent Opponent's Options
  a. Remove a card that has an empty plot
  b. Remove a card that opponent has the least of

Played by Patchouli
```
*/
void handlePurpleAiCardChoice(void) {
    uint16_t cards_in_hand = get_cards_in_hand();
    uint16_t * card_choice = GET_GLOBAL_REF(OPPONENT_LAST_CHOICE);

    if(cards_in_hand & C_PURPLE){
        *card_choice = T_PURPLE;
    }else{
        *card_choice = get_random_choice(cards_in_hand);
    }
}

void handlePurpleAiChooseTarget(void) {
    uint16_t suffering_cards = get_suffering_player_cards(); //Cards with the lowest values > 0
    uint16_t * card_choice = GET_GLOBAL_REF(TARGETED_CARD);
    /**
     * This should reflect Patchouli's personality.
     *
     * She doesn't have a very proactive personality, but rather always walks her own path.
     * However, she's always interested where knowledge is concerned and will proactively go and try to acquire it.
     * She does everything by the book, but still makes a lot of mistakes.
     * She's also described as very dark and taciturn, which in this case means she is introverted and silent in expression and manner.
     **/
    if(suffering_cards & C_RED){
        *card_choice = T_RED;
    }else{
        *card_choice = get_random_choice(suffering_cards);
    }
}

/*
```
Red AI - ???

Original design was dependant on Green's recover feature.'

Aim to have a Garden win by outpacing the opponent, aiming to remove their plots and reduce their blooms.

Played by Marissa? Or Reimu?
```
*/
void handleRedAiCardChoice(void) {
    uint16_t cards_in_hand = get_cards_in_hand();
    uint16_t empty_plots = get_empty_plots();
    uint16_t cards_in_hand_with_empty_plots = cards_in_hand & empty_plots;

    uint16_t * card_choice = GET_GLOBAL_REF(OPPONENT_LAST_CHOICE);

    if(cards_in_hand & C_RED){
        *card_choice = T_RED;
    }else{
        if(cards_in_hand_with_empty_plots > 0){
            //Choose random plot that we have cards for
            *card_choice = get_random_choice(cards_in_hand_with_empty_plots);
        }else{
            *card_choice = get_random_choice(cards_in_hand);
        }
    }
}

void handleRedAiChooseTarget(void) {
    uint16_t suffering_plots = get_suffering_plots(); //Plots with the lowest values > 0
    uint16_t * target_choice = GET_GLOBAL_REF(TARGETED_CARD);
    if(suffering_plots > 0) {
        *target_choice = get_random_choice(suffering_plots);
    }else{
        *target_choice = 0;
    }
}

void chooseRandomRedTarget(void) {
    uint16_t valid_plots = get_planted_player_plots(); //Plots with values > 0
    uint16_t * target_choice = GET_GLOBAL_REF(TARGETED_CARD);
    if(valid_plots > 0) {
        *target_choice = get_random_choice(valid_plots);
    }else{
        *target_choice = 0;
    }
}

void chooseRandomPurpleTarget(void) {
    uint16_t valid_hand_slots = get_player_hand_slots_with_cards(); //Hand Slots with values > 0
    uint16_t * target_choice = GET_GLOBAL_REF(TARGETED_CARD);
    if(valid_hand_slots > 0) {
        *target_choice = get_random_choice(valid_hand_slots);
    }else{
        *target_choice = 0;
    }
}

void handleRainbowBadAiCardChoice(void) {
    uint16_t cards_in_hand = get_cards_in_hand();

    uint16_t * card_choice = GET_GLOBAL_REF(OPPONENT_LAST_CHOICE);

    *card_choice = get_random_choice(cards_in_hand);
}


/*
```
Garden AI - Garden
Action Priority:
1. Play Empty Plots
2. Optimize every play's choices?

Alternative concept:

Choose random empty plot. Play that color optimally.

Also played by Yuuka?
```
*/
void handleOpponentCardChoice(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    uint16_t current_opponent = GET_GLOBAL_VAL(CURRENT_OPPONENT);
    if(current_opponent == 6) {
        current_opponent = random(5) + 1;
    }

    switch (current_opponent) {
        case T_WHITE:
            // White
            handleWhiteAiCardChoice();
            break;
        case T_PURPLE:
            // Purple
            handlePurpleAiCardChoice();
        case T_BLUE:
            // Blue
            handleBlueAiCardChoice();
            break;
        case T_RED:
            handleRedAiCardChoice();
            break;
        case T_GREEN:
            handleGreenAiCardChoice();
            break;
        default:
            handleRainbowBadAiCardChoice();
            break;
    }
}

uint16_t * get_random_opp_hand_slot(void) {
    uint16_t card_to_draw = random(5) + 1;
    switch (card_to_draw) {
        case T_WHITE: return GET_GLOBAL_REF(OPPONENT_PLAINS_HAND);
        case T_PURPLE: return GET_GLOBAL_REF(OPPONENT_SWAMPS_HAND);
        case T_BLUE: return GET_GLOBAL_REF(OPPONENT_ISLANDS_HAND);
        case T_RED: return GET_GLOBAL_REF(OPPONENT_MOUNTAINS_HAND);
        case T_GREEN: return GET_GLOBAL_REF(OPPONENT_FORESTS_HAND);
    }
    return 0;
}

uint16_t * get_opp_hand_slot(uint16_t card_choice) {
    switch (card_choice) {
        case T_WHITE: return GET_GLOBAL_REF(OPPONENT_PLAINS_HAND);
        case T_PURPLE: return GET_GLOBAL_REF(OPPONENT_SWAMPS_HAND);
        case T_BLUE: return GET_GLOBAL_REF(OPPONENT_ISLANDS_HAND);
        case T_RED: return GET_GLOBAL_REF(OPPONENT_MOUNTAINS_HAND);
        case T_GREEN: return GET_GLOBAL_REF(OPPONENT_FORESTS_HAND);
    }
    return 0;
}

uint16_t * get_opp_discard_slot(uint16_t card_choice) {
    switch (card_choice) {
        case T_WHITE: return GET_GLOBAL_REF(OPPONENT_PLAINS_GRAVEYARD);
        case T_PURPLE: return GET_GLOBAL_REF(OPPONENT_SWAMPS_GRAVEYARD);
        case T_BLUE: return GET_GLOBAL_REF(OPPONENT_ISLANDS_GRAVEYARD);
        case T_RED: return GET_GLOBAL_REF(OPPONENT_MOUNTAINS_GRAVEYARD);
        case T_GREEN: return GET_GLOBAL_REF(OPPONENT_FORESTS_GRAVEYARD);
    }
    return 0;
}

uint16_t * get_opp_play_slot(uint16_t card_choice) {
    switch (card_choice) {
        case T_WHITE: return GET_GLOBAL_REF(OPPONENT_PLAINS_SCORE);
        case T_PURPLE: return GET_GLOBAL_REF(OPPONENT_SWAMPS_SCORE);
        case T_BLUE: return GET_GLOBAL_REF(OPPONENT_ISLANDS_SCORE);
        case T_RED: return GET_GLOBAL_REF(OPPONENT_MOUNTAINS_SCORE);
        case T_GREEN: return GET_GLOBAL_REF(OPPONENT_FORESTS_SCORE);
    }
    return 0;
}

uint16_t * get_player_play_slot(uint16_t card_choice) {
    switch (card_choice) {
        case T_WHITE: return GET_GLOBAL_REF(PLAYER_PLAINS_SCORE);
        case T_PURPLE: return GET_GLOBAL_REF(PLAYER_SWAMPS_SCORE);
        case T_BLUE: return GET_GLOBAL_REF(PLAYER_ISLANDS_SCORE);
        case T_RED: return GET_GLOBAL_REF(PLAYER_MOUNTAINS_SCORE);
        case T_GREEN: return GET_GLOBAL_REF(PLAYER_FORESTS_SCORE);
    }
    return 0;
}

uint16_t * get_player_hand_slot(uint16_t card_choice) {
    switch (card_choice) {
        case T_WHITE: return GET_GLOBAL_REF(PLAYER_PLAINS_HAND);
        case T_PURPLE: return GET_GLOBAL_REF(PLAYER_SWAMPS_HAND);
        case T_BLUE: return GET_GLOBAL_REF(PLAYER_ISLANDS_HAND);
        case T_RED: return GET_GLOBAL_REF(PLAYER_MOUNTAINS_HAND);
        case T_GREEN: return GET_GLOBAL_REF(PLAYER_FORESTS_HAND);
    }
    return 0;
}

uint16_t * get_player_gy_slot(uint16_t card_choice) {
    switch (card_choice) {
        case T_WHITE: return GET_GLOBAL_REF(PLAYER_PLAINS_GRAVEYARD);
        case T_PURPLE: return GET_GLOBAL_REF(PLAYER_SWAMPS_GRAVEYARD);
        case T_BLUE: return GET_GLOBAL_REF(PLAYER_ISLANDS_GRAVEYARD);
        case T_RED: return GET_GLOBAL_REF(PLAYER_MOUNTAINS_GRAVEYARD);
        case T_GREEN: return GET_GLOBAL_REF(PLAYER_FORESTS_GRAVEYARD);
    }
    return 0;
}

void opp_discard_card(uint16_t card_choice) {
    uint16_t * hand_slot = get_opp_hand_slot(card_choice);
    uint16_t * disc_slot = get_opp_discard_slot(card_choice);

    *hand_slot = *hand_slot - 1;
    *disc_slot = *disc_slot + 1;
}

void opp_play_card(uint16_t card_choice) {
    uint16_t * hand_slot = get_opp_hand_slot(card_choice);
    uint16_t * play_slot = get_opp_play_slot(card_choice);

    *hand_slot = *hand_slot - 1;
    *play_slot = *play_slot + 1;
}

bool playerHasWhiteBarrier(void) {
    uint16_t card_choice = GET_GLOBAL_VAL(OPPONENT_LAST_CHOICE);
    uint16_t player_shields = GET_GLOBAL_VAL(PLAYER_SHIELDS);
    card_choice = 1 << (4 + card_choice);
    return player_shields & card_choice;
}

bool playerHasGreenBarrier(void) {
    uint16_t target_card = GET_GLOBAL_VAL(TARGETED_CARD);
    uint16_t player_shields = GET_GLOBAL_VAL(PLAYER_SHIELDS);
    target_card = 1 << (target_card - 1);
    return player_shields & target_card;
}

void doBlueEffect(void) {
    uint16_t * random_hand_slot = get_random_opp_hand_slot();
    *random_hand_slot = *random_hand_slot + 1;
}

void player_green_barrier_effect(uint16_t card_choice, uint16_t target_choice) {
    uint16_t * shield_triggered = GET_GLOBAL_REF(SHIELD_TRIGGERED);
    uint16_t * target_play_slot = get_player_play_slot(target_choice);

    *shield_triggered = target_choice;
    *target_play_slot = *target_play_slot + 1;

    opp_discard_card(card_choice);
}

void wither_player_plot(uint16_t target_choice) {
    uint16_t * target_play_slot = get_player_play_slot(target_choice);
    uint16_t * target_gy_slot = get_player_gy_slot(target_choice);

    *target_play_slot = *target_play_slot - 1;
    *target_gy_slot = *target_gy_slot + 1;
}

void doRedEffect(void) {
    uint16_t target_choice = GET_GLOBAL_VAL(TARGETED_CARD);
    if(target_choice == 0) return;

    if (playerHasGreenBarrier()) {
        player_green_barrier_effect(T_RED, target_choice);
        return;
    }

    wither_player_plot(target_choice);
}

void player_discard_card(uint16_t target_choice) {
    uint16_t * target_hand_slot = get_player_hand_slot(target_choice);
    uint16_t * target_gy_slot = get_player_gy_slot(target_choice);

    *target_hand_slot = *target_hand_slot - 1;
    *target_gy_slot = *target_gy_slot + 1;
}


void doPurpleEffect(void) {
    uint16_t target_choice = GET_GLOBAL_VAL(TARGETED_CARD);
    if(target_choice == 0) return;

    if (playerHasGreenBarrier()) {
        player_green_barrier_effect(T_PURPLE, target_choice);
        return;
    }

    player_discard_card(target_choice);
}

void doGreenEffect(void) {
    uint16_t * opponent_shields = GET_GLOBAL_REF(OPPONENT_SHIELDS);
    uint16_t target_card = GET_GLOBAL_VAL(TARGETED_CARD);

    target_card = 1 << (target_card - 1);
    *opponent_shields = *opponent_shields | target_card;
}

void doWhiteEffect(void) {
    uint16_t * opponent_shields = GET_GLOBAL_REF(OPPONENT_SHIELDS);
    uint16_t target_card = GET_GLOBAL_VAL(TARGETED_CARD);

    target_card = 1 << (4 + target_card);
    *opponent_shields = *opponent_shields | target_card;
}

void handleOpponentTurn(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;

    uint16_t card_choice = GET_GLOBAL_VAL(OPPONENT_LAST_CHOICE);
    if (playerHasWhiteBarrier()) {
        uint16_t * shield_triggered = GET_GLOBAL_REF(SHIELD_TRIGGERED);
        *shield_triggered = card_choice + 5;
        opp_discard_card(card_choice);
        return;
    }

    uint16_t current_opponent = GET_GLOBAL_VAL(CURRENT_OPPONENT);

    if(current_opponent == 6) {
        current_opponent = card_choice;
    }

    switch (card_choice) {
        case T_WHITE:
            if(current_opponent == T_WHITE) handleWhiteAiChooseTarget();
            else chooseRandomWhiteTarget();
            doWhiteEffect();
        break;
        case T_PURPLE:
            if(current_opponent == T_PURPLE) handlePurpleAiChooseTarget();
            else chooseRandomPurpleTarget();
            doPurpleEffect();
        break;
        case T_BLUE:
            doBlueEffect();
        break;
        case T_RED:
            // Drafted
            if(current_opponent == T_RED) handleRedAiChooseTarget();
            else chooseRandomRedTarget();
            doRedEffect();
        break;
        case T_GREEN:
            if(current_opponent == T_GREEN) handleGreenAiChooseTarget();
            else chooseRandomGreenTarget();
            doGreenEffect();
        break;
    }
    opp_play_card(card_choice);
}
