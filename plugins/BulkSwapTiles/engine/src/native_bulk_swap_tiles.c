#pragma bank 255

#include <gbdk/platform.h>
#include "vm.h"

void putCurrentIndexOnStack(SCRIPT_CTX * THIS) OLDCALL BANKED {
    int16_t *currentIndex = (int16_t*)VM_REF_TO_PTR(FN_ARG0);
    int16_t skipRows     = *(int16_t*)VM_REF_TO_PTR(FN_ARG1);
    int16_t swapX = *(int16_t*)VM_REF_TO_PTR(FN_ARG2);
    int16_t swapY = *(int16_t*)VM_REF_TO_PTR(FN_ARG3);
    int16_t tileLength = *(int16_t*)VM_REF_TO_PTR(FN_ARG4);

    *currentIndex = (swapY * tileLength) + swapX + skipRows;
}

void handleBlockModeForCurrentIndex(SCRIPT_CTX * THIS) OLDCALL BANKED {
    int16_t *currentIndex = (int16_t*)VM_REF_TO_PTR(FN_ARG0);
    int16_t skipRows     = *(int16_t*)VM_REF_TO_PTR(FN_ARG1);
    int16_t swapX = *(int16_t*)VM_REF_TO_PTR(FN_ARG2);
    int16_t swapY = *(int16_t*)VM_REF_TO_PTR(FN_ARG3);
    int16_t tileLength = *(int16_t*)VM_REF_TO_PTR(FN_ARG4);

    *currentIndex = ((swapY + 1)) * tileLength + swapX + skipRows;
}

void handleTileEdge(SCRIPT_CTX * THIS) OLDCALL BANKED {
    int16_t *currentIndex = (int16_t*)VM_REF_TO_PTR(FN_ARG0);
    int16_t *skipRows     = (int16_t*)VM_REF_TO_PTR(FN_ARG1);
    int16_t tileLength = *(int16_t*)VM_REF_TO_PTR(FN_ARG4);

    if(((*currentIndex + 1) % tileLength) == 0){
        *skipRows+=tileLength;
    }else{
        *currentIndex+=1;
    }
}

void incrementCurrentIndex(SCRIPT_CTX * THIS) OLDCALL BANKED {
    int16_t *currentIndex = (int16_t*)VM_REF_TO_PTR(FN_ARG0);
    *currentIndex+=1;
}
