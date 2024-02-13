#pragma bank 255

#include "vm.h"
#include <gb/gb.h>
#include "data_manager.h"

void handleSubmap(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    const uint8_t tiles[6*1];
    get_bkg_tiles(0,  0, 6, 1, tiles);
    set_bkg_tiles(40, 0, 6, 1, tiles);
    //scroll_bkg(0, 32);
}
