#pragma bank 255

#include "vm.h"
#include "vm_gameboy.h"
#include "gbs_types.h"

int16_t *currentIndex;

uint8_t swapX, swapY, targetX, targetY, tileLength;
uint8_t sax, say, sbx, sby;
uint8_t tax, tay, tbx, tby;

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

void setupTarget(SCRIPT_CTX * THIS) OLDCALL BANKED {
    targetX = *(uint8_t*)VM_REF_TO_PTR(FN_ARG0);
    targetY = *(uint8_t*)VM_REF_TO_PTR(FN_ARG1);
}

void handleBlockDraw(SCRIPT_CTX * THIS) OLDCALL BANKED {

    *currentIndex = (say * tileLength) + sax;
    vm_replace_tile_xy(THIS, tax, tay, tileset_bank, tileset, FN_ARG2);

    *currentIndex = (say * tileLength) + sbx;
    vm_replace_tile_xy(THIS, tbx, tay, tileset_bank, tileset, FN_ARG2);

    *currentIndex = (sby * tileLength) + sax;
    vm_replace_tile_xy(THIS, tax, tby, tileset_bank, tileset, FN_ARG2);

    *currentIndex = (sby * tileLength) + sbx;
    vm_replace_tile_xy(THIS, tbx, tby, tileset_bank, tileset, FN_ARG2);

}

void drawForBlockMode(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    sax = swapX;
    say = swapY;
    sbx = swapX + 1;
    sby = swapY + 1;

    tax = targetX;
    tay = targetY;
    tbx = targetX + 1;
    tby = targetY + 1;

    handleBlockDraw(THIS);
}

void drawForConsecutiveMode(SCRIPT_CTX * THIS) OLDCALL BANKED {
    sax = swapX;
    say = swapX + 1;
    sbx = swapX + 2;
    sby = swapX + 3;

    tax = targetX;
    tay = targetY;
    tbx = targetX + 1;
    tby = targetY + 1;

    handleBlockDraw(THIS);
}

void drawForSingleMode(SCRIPT_CTX * THIS) OLDCALL BANKED {
    sax = swapX;
    say = swapY;

    tax = targetX;
    tay = targetY;

    *currentIndex = (say * tileLength) + sax;
    vm_replace_tile_xy(THIS, tax, tay, tileset_bank, tileset, FN_ARG2);
}
