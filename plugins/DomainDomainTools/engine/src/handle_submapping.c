#pragma bank 255

#include "vm.h"
#include <gb/gb.h>
#include "data_manager.h"

#define FACE_TOP_Y 18
#define FACE_BOT_Y 19

#define BASE_PLOT_X 2
#define BASE_PLOT_Y 4


void changePlot(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    uint8_t bkg_tile;

    uint16_t face = (*(uint16_t *) VM_REF_TO_PTR(FN_ARG2));
    uint16_t row =  (*(uint16_t *) VM_REF_TO_PTR(FN_ARG1));
    uint16_t col =  (*(uint16_t *) VM_REF_TO_PTR(FN_ARG0));

    uint8_t f_x, p_x, p_y;

    //Top Left
    f_x = face * 2;

    p_x = BASE_PLOT_X + (col * 2);
    p_y = BASE_PLOT_Y + (row * 2);

    bkg_tile = get_bkg_tile_xy(f_x, FACE_TOP_Y);
    set_bkg_tile_xy(p_x, p_y, bkg_tile);

    //Bottom Left
    bkg_tile = get_bkg_tile_xy(f_x, FACE_BOT_Y);
    set_bkg_tile_xy(p_x, p_y + 1, bkg_tile);

    f_x+=1;
    p_x+=1;

    //Top Right
    bkg_tile = get_bkg_tile_xy(f_x, FACE_TOP_Y);
    set_bkg_tile_xy(p_x, p_y, bkg_tile);


    //Bottom Right
    bkg_tile = get_bkg_tile_xy(f_x, FACE_BOT_Y);
    set_bkg_tile_xy(p_x, p_y + 1, bkg_tile);
}
