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
            type: "union",
            types: ["number", "variable"],
            defaultType: "number",
            defaultValue: {
              number: 0,
              variable: "LAST_VARIABLE",
            },
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
            type: "union",
            types: ["number", "variable"],
            defaultType: "number",
            defaultValue: {
              number: 0,
              variable: "LAST_VARIABLE",
            },
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
            type: "union",
            types: ["number", "variable"],
            defaultType: "number",
            defaultValue: {
              number: 0,
              variable: "LAST_VARIABLE",
            },
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
            type: "union",
            types: ["number", "variable"],
            defaultType: "number",
            defaultValue: {
              number: 0,
              variable: "LAST_VARIABLE",
            },
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
        wait,
        warnings,
        _callNative,
        _setConst,
        _setToVariable,
        _getInd,
        _stackPop,
        _stackPushConst,
        backgrounds
    } = helpers;

    const loopAmount =  input.tileAmount === "single" ? 1 : 4;
    const iterAmount =  input.tileAmount === "single" ? 1 : 2;
    const isBlockMode = input.tileAmount === "four" && input.tileMode === "block";
    const isConsecutiveMode = input.tileAmount === "four" && input.tileMode === "consecutive";
    const hasWait = input.waitFrames != 0
    const items = input.items;
    const skipAmount = isBlockMode ? 2 : loopAmount;

    const swapX = input[`swap_x`];
    const swapY = input[`swap_y`];
    const bgInfo = backgrounds.find((b) => b.id === input.backgroundId)
    const tileLength = bgInfo.width
    const bgSymbol = bgInfo.symbol
    const stackSize = 3

    for(let i=0;i<stackSize;i++){_stackPushConst(0)}

    if(swapX.type == "number"){
      _setConst(".ARG0", swapX.value) //swapX
    }

    if(swapX.type == "variable"){
      _setToVariable(".ARG0", swapX.value) //swapX
    }

    if(swapY.type == "number"){
      _setConst(".ARG1", swapY.value) //swapY
    }

    if(swapY.type == "variable"){
      _setToVariable(".ARG1", swapY.value) //swapY
    }

    _setConst(".ARG2", tileLength) //tileLength
    _callNative("setupTileSwap")

    _setConst(".ARG0", `___bank_${bgSymbol}_tileset`)
    _setConst(".ARG1", `_${bgSymbol}_tileset`)

    _callNative("setupTileMap")
    _callNative("setupIndex")

    let handleDraw

    if(isBlockMode){
      handleDraw = () => { _callNative("drawForBlockMode") }
    }else if(isConsecutiveMode){
      handleDraw = ()=>{ _callNative("drawForConsecutiveMode") }
    }else{
      handleDraw = ()=>{ _callNative("drawForSingleMode") }
    }

    for(let j = 1; j <= items; j++){

      const x_start = input[`tile${j}_x_start`];
      if(x_start.type == "number"){
        _setConst(".ARG0", x_start.value) //swapX
      }

      if(x_start.type == "variable"){
        _setToVariable(".ARG0", x_start.value) //swapX
      }

      const y_start = input[`tile${j}_y_start`];
      if(y_start.type == "number"){
        _setConst(".ARG1", y_start.value) //swapX
      }

      if(y_start.type == "variable"){
        _setToVariable(".ARG1", y_start.value) //swapX
      }

      _callNative("setupIterationStart")

      const x_stop = input[`tile${j}_x_end`];
      if(x_stop.type == "number"){
        _setConst(".ARG0", x_stop.value) //swapX
      }

      if(x_stop.type == "variable"){
        _setToVariable(".ARG0", x_stop.value) //swapX
      }

      const y_stop = input[`tile${j}_y_end`];
      if(y_stop.type == "number"){
        _setConst(".ARG1", y_stop.value) //swapX
      }

      if(y_stop.type == "variable"){
        _setToVariable(".ARG1", y_stop.value) //swapX
      }

      _callNative("setupIterationStop")

      handleDraw()

      if(hasWait) wait(input.waitFrames)
    }

    _stackPop(stackSize)
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
  };

