const id = "FO_EVENT_BULK_SWAP_TILES";
const groups = ["Plugins"];
const name = "Bulk Swap Tiles";

const MAX_TILES = 50;

const fields = [].concat(
  [
    {
      key: "tileAmount",
      label: "Tile Size",
      description: "Choose the size of the tiles you wish to animate.",
      type: "select",
      width: "50%",
      options: [
      ["single", "8x8"],
      ["four", "16x16"]
      ],
      defaultValue: "single",
    },

    {
      key: "tileMode",
      label: "Tile sheet mode",
      description: "Are your tiles ordered consequtively or as a 16x16 block",
      type: "select",
      width: "50%",
      options: [
      ["consecutive", "consecutive"],
      ["block", "16x16 block"]
      ],
      defaultValue: "consecutive",
    },

    {
      type: "break"
    },

    {
      key: `swap_x`,
      label: `Tileset X of Tile`,
      description: "X coordinate of the starting tile in the tileset you will be swapping to.",
      type: "union",
      types: ["number", "variable"],
      defaultType: "number",
      defaultValue: {
        number: 0,
        variable: "LAST_VARIABLE",
      },
      min: 0,
      width: "50%"
    },
    {
      key: `swap_y`,
      label: `Tileset Y of Tile`,
      description: "Y coordinate of the starting tile in the tileset you will be swapping to.",
      type: "union",
      types: ["number", "variable"],
      defaultType: "number",
      defaultValue: {
        number: 0,
        variable: "LAST_VARIABLE",
      },
      min: 0,
      width: "50%"
    },

    {
      type: "break"
    },

    {
      key: "items",
      label: "Number of sections to be swapped",
      description: "How many unique sections to be swapped in one loop",
      type: "number",
      min: 1,
      max: MAX_TILES,
      defaultValue: 1,
    },

    {
      type: "break",
    },

    {
      key: "waitFrames",
      label: "Frames to wait between swaps",
      description: "The duration in frames until the next frame of animation is swapped.",
      type: "number",
      min: 0,
      width: "50%",
      defaultValue: 0,
    },
    {
      key: "backgroundId",
      label: "Tilemap",
      description: "The tilemap is the background image with the tiles you want to swap in.",
      type: "background",
      defaultValue: "",
      flexBasis: "100%",
    },

    {
      type: "break",
    },

    ...Array(MAX_TILES)
      .fill()
      .reduce((arr, _, i) => {
        const index = i + 1;
        arr.push(
          {
            key: `collapseTile${index}`,
            label: `Section ${index}`,
            conditions: [
              {
                key: "items",
                gte: index,
              }
            ],
            type: "collapsable",
          },
          {
            key: `tile${index}_x_start`,
            label: `Unique Tile ${index}'s First X`,
            type: "number",
            defaultValue: 0,
            width: "50%",
            conditions: [
              {
                key: "items",
                gte: index,
              },
              {
                key: `collapseTile${index}`,
                ne: true
              },
            ],
          },
          {
            key: `tile${index}_y_start`,
            label: `Unique Tile ${index}'s First Y`,
            type: "number",
            defaultValue: 0,
            width: "50%",
            conditions: [
              {
                key: "items",
                gte: index,
              },
              {
                key: `collapseTile${index}`,
                ne: true
              },
            ],
          },


          {
            type: "break",
            conditions: [
              {
                key: "items",
                gte: index,
              },
              {
                key: `collapseTile${index}`,
                ne: true
              },
            ],
          },

          {
            key: `tile${index}_x_end`,
            label: `Unique Tile ${index}'s Last X`,
            type: "number",
            defaultValue: 0,
            width: "50%",
            conditions: [
              {
                key: "items",
                gte: index,
              },
              {
                key: `collapseTile${index}`,
                ne: true
              },
            ],
          },

          {
            key: `tile${index}_y_end`,
            label: `Unique Tile ${index}'s Last Y`,
            type: "number",
            defaultValue: 0,
            width: "50%",
            conditions: [
              {
                key: "items",
                gte: index,
              },
              {
                key: `collapseTile${index}`,
                ne: true
              },
            ],
          },


          {
            type: "break",
            conditions: [
              {
                key: "items",
                gte: index,
              },
              {
                key: `collapseTile${index}`,
                ne: true
              },
            ],
          }
        );
        return arr;
      }, []),
  ]
);

const compile = (input, helpers) => {
    const {
        appendRaw,
        wait,
        warnings,
        _callNative,
        _setConst,
        _setToVariable,
        _stackPop,
        _stackPushConst,
        _reserve,
        backgrounds
    } = helpers;

    const loopAmount =  input.tileAmount === "single" ? 1 : 4;
    const iterAmount =  input.tileAmount === "single" ? 1 : 2;
    const isBlockMode = input.tileMode === "block";
    const hasWait = input.waitFrames != 0
    const items = input.items;
    const skipAmount = isBlockMode ? 2 : loopAmount;

    const swapX = input[`swap_x`];
    const swapY = input[`swap_y`];
    const bgInfo = backgrounds.find((b) => b.id === input.backgroundId)
    const tileLength = bgInfo.width
    const bgSymbol = bgInfo.symbol

    for(let i=0;i<5;i++){_stackPushConst(0)}

    if(swapX.type == "number"){
      _setConst(".ARG2", swapX.value) //swapX
    }

    if(swapX.type == "variable"){
      _setToVariable(".ARG2", swapX.value) //swapX
    }

    if(swapY.type == "number"){
      _setConst(".ARG3", swapY.value) //swapY
    }

    if(swapY.type == "variable"){
      _setToVariable(".ARG3", swapY.value) //swapY
    }

    _setConst(".ARG4", tileLength) //tileLength
    for(let j = 1; j <= items; j++){

      const x_start = input[`tile${j}_x_start`];
      const y_start = input[`tile${j}_y_start`];
      const x_end = input[`tile${j}_x_end`];
      const y_end = input[`tile${j}_y_end`];

      for(let y = y_start ; y <= y_end; y+=iterAmount){
        for(let x = x_start; x <= x_end; x+=iterAmount){
          _setConst(".ARG1", 0) //skipRows
          _callNative("putCurrentIndexOnStack")
          const currentX = [x, x + 1, x,     x + 1];
          const currentY = [y, y    , y + 1, y + 1];
          for(let k = 0; k < loopAmount; k++) {
            appendRaw(`VM_REPLACE_TILE_XY ${currentX[k]}, ${currentY[k]}, ___bank_${bgSymbol}_tileset, _${bgSymbol}_tileset, .ARG0`);
              if(isBlockMode && k==1){
                _callNative("handleBlockModeForCurrentIndex")
              }else if(isBlockMode && k == 3){
                _callNative("handleTileEdge")
              }else{
                _callNative("incrementCurrentIndex")
              }
          }
        }
      }
      if(hasWait) wait(input.waitFrames)
    }
    _stackPop(5)
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
  };

