Heres the code that looks for new engine json files.

Type can only be "number", "slider", "checkbox", or "select".
cType can only be "UBYTE", "UWORD", "BYTE", "WORD", or "define"

Example engine.json from platformer plus after the code.

Group can be anything, it'll define the header. Label and Key work how they do in scripts.

```js
import { createSlice, PayloadAction } from "@reduxjs/toolkit";

export type EngineFieldType = "number" | "slider" | "checkbox" | "select";

export type EngineFieldCType = "UBYTE" | "UWORD" | "BYTE" | "WORD" | "define";

export type EngineFieldSchema = {
  key: string;
  label: string;
  group: string;
  type: EngineFieldType;
  cType: EngineFieldCType;
  defaultValue: number | string | boolean | undefined;
  min?: number;
  max?: number;
  options?: [number, string][];
};

export interface EngineState {
  fields: EngineFieldSchema[];
}

export const initialState: EngineState = {
  fields: [],
};

const engineSlice = createSlice({
  name: "engine",
  initialState,
  reducers: {
    setEngineFields: (state, action: PayloadAction<EngineFieldSchema[]>) => {
      state.fields = action.payload;
    },
  },
});

export const { actions, reducer } = engineSlice;

export default reducer;
```

```json
{
  "version": "3.1.0-e15",

  "fields": [
    {
      "key": "plat_camera_follow",
      "label": "Camera Follow Directions",
      "group": "Platformer Plus Level Controls",
      "type": "select",
      "options": [
        [15, "All"],
        [1, "Right"],
        [9, "Right and Up"],
        [5, "Right and Down"],
        [13, "Right, Up and Down"],
        [2, "Left"],
        [10, "Left and Up"],
        [6, "Left and Down"],
        [14, "Left, Up and Down"],
        [3, "Left and Right"],
        [8, "Up"],
        [11, "Up, Left and Right"],
        [4, "Down"],
        [7, "Down, Left and Right"],
        [12, "Up and Down"],
        [0, "None"]
      ],
      "cType": "UBYTE",
      "defaultValue": 15
    }

  ]
}
```
