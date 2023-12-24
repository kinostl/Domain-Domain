#pragma bank 255

#include "vm.h"
#include "vm_gameboy.h"
#include "gbs_types.h"

uint8_t swapX, swapY, tileLength;

uint8_t iax, iay, ibx, iby;

uint8_t tileset_bank;
const tileset_t * tileset;

void setupTileSwap(SCRIPT_CTX * THIS) OLDCALL BANKED {
    swapX = *(uint8_t*)VM_REF_TO_PTR(FN_ARG0);
    swapY = *(uint8_t*)VM_REF_TO_PTR(FN_ARG1);
    tileLength   = *(uint8_t*)VM_REF_TO_PTR(FN_ARG2);
}

void setupTileMap(SCRIPT_CTX * THIS) OLDCALL BANKED {
    tileset_bank = *(uint8_t *) VM_REF_TO_PTR(FN_ARG0);
    tileset = *(tileset_t **) VM_REF_TO_PTR(FN_ARG1);
}

void setupIterationStart(SCRIPT_CTX * THIS) OLDCALL BANKED {
    iax = *(uint8_t*)VM_REF_TO_PTR(FN_ARG0);
    iay = *(uint8_t*)VM_REF_TO_PTR(FN_ARG1);
}

void setupIterationStop(SCRIPT_CTX * THIS) OLDCALL BANKED {
    ibx = *(uint8_t*)VM_REF_TO_PTR(FN_ARG0);
    iby = *(uint8_t*)VM_REF_TO_PTR(FN_ARG1);
}

void drawForBlockMode(SCRIPT_CTX * THIS) OLDCALL BANKED {
    uint16_t * target_col    = (uint16_t *) VM_REF_TO_PTR(FN_ARG0);
    uint16_t * target_row    = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);
    uint16_t * current_index = (uint16_t *) VM_REF_TO_PTR(FN_ARG2);

    const uint8_t sax = swapX;
    const uint8_t say = swapY;
    const uint8_t sbx = swapX + 1;
    const uint8_t sby = swapY + 1;

    const uint8_t top_left     = (say * tileLength) + sax;
    const uint8_t bottom_left  = (sby * tileLength) + sax;

    uint8_t tay;
    bool top = true;

    for(tay = iay; tay <= iby; tay+=1){
        *target_col = iax;
        *target_row = tay;
        vm_get_tile_xy(THIS, FN_ARG0, FN_ARG0, FN_ARG1);
        if(top){
            *current_index = top_left;
            top = !!!top;
        }else{
            *current_index = bottom_left;
            top = !!!top;
        }
        vm_replace_tile(THIS, FN_ARG0, tileset_bank, tileset, FN_ARG2, 2);
    }
}

void drawForConsecutiveMode(SCRIPT_CTX * THIS) OLDCALL BANKED {
    const uint8_t origin = (swapY * tileLength) + swapX;
    uint16_t * target_col    = (uint16_t *) VM_REF_TO_PTR(FN_ARG0);
    uint16_t * target_row    = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);
    uint16_t * current_index = (uint16_t *) VM_REF_TO_PTR(FN_ARG2);
    uint8_t say = swapY;

    uint8_t tay;
    bool top = true;

    for(tay = iay; tay <= iby; tay+=1){
        *target_col = iax;
        *target_row = tay;
        vm_get_tile_xy(THIS, FN_ARG0, FN_ARG0, FN_ARG1);
        if(top){
            *current_index = origin;
            top = !!!top;
        }else{
            *current_index = origin+2;
            top = !!!top;
        }
        vm_replace_tile(THIS, FN_ARG0, tileset_bank, tileset, FN_ARG2, 2);
    }

}

void drawForSingleMode(SCRIPT_CTX * THIS) OLDCALL BANKED {
    uint16_t * target_col    = (uint16_t *) VM_REF_TO_PTR(FN_ARG0);
    uint16_t * target_row    = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);
    uint16_t * current_index = (uint16_t *) VM_REF_TO_PTR(FN_ARG2);

    const uint8_t sax = swapX;
    const uint8_t say = swapY;

    *current_index = (say * tileLength) + sax;

    uint8_t tax, tay;

    for(tay = iay; tay <= iby; tay+=1){
        *target_col = iax;
        *target_row = tay;
        vm_get_tile_xy(THIS, FN_ARG0, FN_ARG0, FN_ARG1);
        for(tax = iax; tax <= ibx; tax+=1){
            vm_replace_tile(THIS, FN_ARG0, tileset_bank, tileset, FN_ARG2, 1);
            *target_col += 1;
        }
    }
}
