#pragma bank 255

#include "vm.h"
#include "vm_gameboy.h"
#include <rand.h>
#include <stdlib.h>

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

#define C_WHITE (1 << 0)
#define C_BLACK (1 << 1)
#define C_BLUE  (1 << 2)
#define C_RED   (1 << 3)
#define C_GREEN (1 << 4)

#define T_WHITE 1
#define T_BLACK 2
#define T_BLUE  3
#define T_RED   4
#define T_GREEN 5

#define C_MASK (limit | (limit >> 1) | (limit >> 2) | (limit >> 3) | (limit >> 4) | (limit >> 5) | (limit >> 6) | (limit >> 7) | (limit >> 8) | (limit >> 9) | (limit >> 10) | (limit >> 11) | (limit >> 12) | (limit >> 13) | (limit >> 14) | (limit >> 15))

uint16_t sample(uint16_t* choices, uint16_t limit){

    uint16_t value = randw() & C_MASK;
    if (value >= limit) value -= limit;
    if (value >= limit) value -= limit;

    return choices[value];
}

uint16_t get_random_card(uint16_t cards_in_hand){
        uint16_t choices_size = 0;
        uint16_t choices[5];
        if(cards_in_hand & C_WHITE){
            choices[choices_size] = T_WHITE;
            choices_size++;
        }
        if(cards_in_hand & C_BLACK){
            choices[choices_size] = T_BLACK;
            choices_size++;
        }
        if(cards_in_hand & C_BLUE){
            choices[choices_size] = T_BLUE;
            choices_size++;
        }
        if(cards_in_hand & C_RED){
            choices[choices_size] = T_RED;
            choices_size++;
        }
        if(cards_in_hand & C_GREEN){
            choices[choices_size] = T_GREEN;
            choices_size++;
        }

        if(choices_size == 0){return -1;}
        if(choices_size == 1){return choices[0];}

        uint16_t choice = sample(choices, choices_size);
        return choice;
}

void handleCirno(SCRIPT_CTX * THIS) OLDCALL BANKED {
    /*
     * Blue AI - Garden
     * Action Priority:
     *  1. Play Blue
     *  2. Play Randomly
    */

    uint16_t cards_in_hand = *(uint16_t *) VM_REF_TO_PTR(FN_ARG0);
    uint16_t * card_choice = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);

    if(cards_in_hand & C_BLUE){
        *card_choice = T_BLUE;
    }else{
        *card_choice = get_random_card(cards_in_hand);
    }
}
