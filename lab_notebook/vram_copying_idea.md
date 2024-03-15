# VRAM Copying Instead of Tile Swapping

This little proof of concept shows that it was possible to draw some symbols off screen and copy them onto the screen, similar to how we were previously using tile swapping.

This is faster, and allows for more tiles. It can also possibly make it easier to make a plugin that can make my life easier more easily.

See Scene 7 for a reference image, if its still there.

```c
#pragma bank 255

#include "vm.h"
#include <gb/gb.h>
#include "data_manager.h"

void handleSubmap(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    uint8_t bkg_tile;
    bkg_tile = get_bkg_tile_xy(0, 18);
    set_bkg_tile_xy(2, 4, bkg_tile);
    bkg_tile = get_bkg_tile_xy(1, 18);
    set_bkg_tile_xy(3, 4, bkg_tile);
    bkg_tile = get_bkg_tile_xy(0, 19);
    set_bkg_tile_xy(2, 5, bkg_tile);
    bkg_tile = get_bkg_tile_xy(1, 19);
    set_bkg_tile_xy(3, 5, bkg_tile);
}
```

## Plugin Idea

Make an event with a function like this that takes a number, column, and row. It sets that col/row to that number. -1 for blank.
