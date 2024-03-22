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
#define C_WHITE (1 << 0)
#define C_BLACK (1 << 1)
#define C_BLUE  (1 << 2)
#define C_RED   (1 << 3)
#define C_GREEN (1 << 4)

// Targets as values
#define T_WHITE 1
#define T_BLACK 2
#define T_BLUE  3
#define T_RED   4
#define T_GREEN 5

// Required for randomization, taken from gbvm's implementation.
#define C_MASK (limit | (limit >> 1) | (limit >> 2) | (limit >> 3) | (limit >> 4) | (limit >> 5) | (limit >> 6) | (limit >> 7) | (limit >> 8) | (limit >> 9) | (limit >> 10) | (limit >> 11) | (limit >> 12) | (limit >> 13) | (limit >> 14) | (limit >> 15))

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
        if(options & C_BLACK){
            choices[choices_size] = T_BLACK;
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

void handleDebugCirno(SCRIPT_CTX * THIS) OLDCALL BANKED {
    /*
     * Debug AI - Garden or Flower
     * Action Priority:
     *  1. Play Chosen Color
     *  2. Play Randomly
    */

    uint16_t cards_in_hand = *(uint16_t *) VM_REF_TO_PTR(FN_ARG0);
    uint16_t * card_choice = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);
    uint16_t color_pref = *(uint16_t *) VM_REF_TO_PTR(FN_ARG2);
    uint16_t has_color_pref = 0;
    switch(color_pref){
        case T_WHITE:
            if(cards_in_hand & C_WHITE){
                *card_choice = T_WHITE;
                has_color_pref = 1;
            }
            break;
        case T_BLACK:
            if(cards_in_hand & C_BLACK){
                *card_choice = T_BLACK;
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
void handleBlueAiCardChoice(SCRIPT_CTX * THIS) OLDCALL BANKED {

    uint16_t cards_in_hand = *(uint16_t *) VM_REF_TO_PTR(FN_ARG0);
    uint16_t * card_choice = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);

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
*/
void handleGreenAiCardChoice(SCRIPT_CTX * THIS) OLDCALL BANKED {
    uint16_t cards_in_hand = *(uint16_t *) VM_REF_TO_PTR(FN_ARG0);
    uint16_t * card_choice = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);
    uint16_t empty_plots = ~(*(uint16_t *) VM_REF_TO_PTR(FN_ARG2)); //Inversion of filled plots
    uint16_t cards_in_hand_with_empty_plots = cards_in_hand & empty_plots;

    if(cards_in_hand & C_GREEN){
        *card_choice = T_GREEN;
    }else{
        if(cards_in_hand_with_empty_plots > 0){
            //Choose random plot that we have cards for
            *card_choice = get_random_choice(cards_in_hand & empty_plots);
        }else{
            *card_choice = get_random_choice(cards_in_hand);
        }
    }
}

void handleGreenChooseTarget(SCRIPT_CTX * THIS) OLDCALL BANKED {
    uint16_t unprotected_cards = ~(*(uint16_t *) VM_REF_TO_PTR(FN_ARG0)); //Inversion of the Protected Cards
    uint16_t * card_choice = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);
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
*/
void handleWhiteAiCardChoice(SCRIPT_CTX * THIS) OLDCALL BANKED {
    uint16_t cards_in_hand = *(uint16_t *) VM_REF_TO_PTR(FN_ARG0);
    uint16_t * card_choice = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);

    if(cards_in_hand & C_WHITE){
        *card_choice = T_WHITE;
    }else{
        *card_choice = get_random_choice(cards_in_hand);
    }
}

void handleWhiteAiChooseTarget(SCRIPT_CTX * THIS) OLDCALL BANKED {
    uint16_t unblocked_cards = ~(*(uint16_t *) VM_REF_TO_PTR(FN_ARG0)); //Inversion of the Protected Cards
    uint16_t * card_choice = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);
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
```
*/
void handlePurpleAiCardChoice(SCRIPT_CTX * THIS) OLDCALL BANKED {
    uint16_t cards_in_hand = *(uint16_t *) VM_REF_TO_PTR(FN_ARG0);
    uint16_t * card_choice = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);

    if(cards_in_hand & C_BLACK){
        *card_choice = T_BLACK;
    }else{
        *card_choice = get_random_choice(cards_in_hand);
    }
}

void handlePurpleAiChooseTarget(SCRIPT_CTX * THIS) OLDCALL BANKED {
    uint16_t suffering_cards = *(uint16_t *) VM_REF_TO_PTR(FN_ARG0); //Cards with the lowest values > 0
    uint16_t * card_choice = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);
    *card_choice = get_random_choice(suffering_cards);
}

/*
```
Red AI - ???

Original design was dependant on Green's recover feature.'

Aim to have a Garden win by outpacing the opponent, aiming to remove their plots and reduce their blooms.
```
*/
void handleRedAiCardChoice(SCRIPT_CTX * THIS) OLDCALL BANKED {
    uint16_t cards_in_hand = *(uint16_t *) VM_REF_TO_PTR(FN_ARG0);
    uint16_t * card_choice = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);
    uint16_t empty_plots = ~(*(uint16_t *) VM_REF_TO_PTR(FN_ARG2)); //Inversion of filled plots
    uint16_t cards_in_hand_with_empty_plots = cards_in_hand & empty_plots;

    if(cards_in_hand & C_RED){
        *card_choice = T_RED;
    }else{
        if(cards_in_hand_with_empty_plots > 0){
            //Choose random plot that we have cards for
            *card_choice = get_random_choice(cards_in_hand & empty_plots);
        }else{
            *card_choice = get_random_choice(cards_in_hand);
        }
    }
}

void handleRedAiChooseTarget(SCRIPT_CTX * THIS) OLDCALL BANKED {
    uint16_t suffering_plots = *(uint16_t *) VM_REF_TO_PTR(FN_ARG0); //Plots with the lowest values > 0
    uint16_t * card_choice = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);
    *card_choice = get_random_choice(suffering_plots);
}

/*
```
Garden AI - Garden
Action Priority:
1. Play Empty Plots
2. Optimize every play's choices?

Alternative concept:

Choose random empty plot. Play that color optimally.
```
*/

void handleOpponentTurn(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;

    uint16_t * target_card = GET_GLOBAL_REF(TARGETED_CARD);
    *target_card = 96;
}
