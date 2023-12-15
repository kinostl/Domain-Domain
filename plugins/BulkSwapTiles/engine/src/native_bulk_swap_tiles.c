#pragma bank 255

#include "vm.h"
#include "vm_gameboy.h"
#include "gbs_types.h"

int16_t *currentIndex;

uint8_t swapX, swapY, tileLength;
uint8_t sax, say, sbx, sby;
uint8_t tax, tay, tbx, tby;
uint8_t iax, iay, ibx, iby;

uint8_t tileset_bank;
const tileset_t * tileset;

void setupTileSwap(SCRIPT_CTX * THIS) OLDCALL BANKED {
    swapX = *(uint8_t*)VM_REF_TO_PTR(FN_ARG0);
    swapY = *(uint8_t*)VM_REF_TO_PTR(FN_ARG1);
    tileLength = *(uint8_t*)VM_REF_TO_PTR(FN_ARG2);
}

void setupTileMap(SCRIPT_CTX * THIS) OLDCALL BANKED {
    tileset_bank = *(uint8_t *) VM_REF_TO_PTR(FN_ARG0);
    tileset = *(tileset_t **) VM_REF_TO_PTR(FN_ARG1);
}

void setupIndex(SCRIPT_CTX * THIS) OLDCALL BANKED {
    currentIndex = (int16_t*)VM_REF_TO_PTR(FN_ARG2);
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
    sax = swapX;
    say = swapY;
    sbx = swapX + 1;
    sby = swapY + 1;

    for(tax = iax; tax <= ibx; tax+=2){
        tbx = tax + 1;
        for(tay = iay; tay <= iby; tay+=2){
            tby = tay + 1;

            *currentIndex = (say * tileLength) + sax;
            vm_replace_tile_xy(THIS, tax, tay, tileset_bank, tileset, FN_ARG2);

            *currentIndex = (say * tileLength) + sbx;
            vm_replace_tile_xy(THIS, tbx, tay, tileset_bank, tileset, FN_ARG2);

            *currentIndex = (sby * tileLength) + sax;
            vm_replace_tile_xy(THIS, tax, tby, tileset_bank, tileset, FN_ARG2);

            *currentIndex = (sby * tileLength) + sbx;
            vm_replace_tile_xy(THIS, tbx, tby, tileset_bank, tileset, FN_ARG2);
        }
    }
}

void incrementIndex(){
    if((*currentIndex + 1) % tileLength == 0){
        say += 1;
        *currentIndex = (say * tileLength);
    }else{
        *currentIndex += 1;
    }
}

void drawForConsecutiveMode(SCRIPT_CTX * THIS) OLDCALL BANKED {
    sax = swapX;
    say = swapY;

    for(tax = iax; tax <= ibx; tax+=2){
        tbx = tax + 1;
        for(tay = iay; tay <= iby; tay+=2){
            tby = tay + 1;

            *currentIndex = (say * tileLength) + sax;
            vm_replace_tile_xy(THIS, tax, tay, tileset_bank, tileset, FN_ARG2);

            incrementIndex();
            vm_replace_tile_xy(THIS, tbx, tay, tileset_bank, tileset, FN_ARG2);

            incrementIndex();
            vm_replace_tile_xy(THIS, tax, tby, tileset_bank, tileset, FN_ARG2);

            incrementIndex();
            vm_replace_tile_xy(THIS, tbx, tby, tileset_bank, tileset, FN_ARG2);
        }
    }

}

void drawForSingleMode(SCRIPT_CTX * THIS) OLDCALL BANKED {
    uint16_t * target_col = (uint16_t *) VM_REF_TO_PTR(FN_ARG0);
    uint16_t * target_row = (uint16_t *) VM_REF_TO_PTR(FN_ARG1);

    sax = swapX;
    say = swapY;

    *currentIndex = (say * tileLength) + sax;

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
