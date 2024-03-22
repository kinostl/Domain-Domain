const id = "MHF_EVENT_MAKE_GLOBALS_H";
const groups = ["Garden Cards"];
const name = "Make Globals Header";
const description = "Creates 'data/game_globals.h'."
const fields = [{
    label: description
}];

const compile = (input, helpers) => {
    const {
        writeAsset,
        variablesLookup,
        variableAliasLookup
    } = helpers;
    const var_names = {};
    for(const x of Object.values(variablesLookup)){
        var_names[x.symbol.toUpperCase()] = x.name.toUpperCase().replace(/[^A-Z0-9]/g,"_")
    }

    let __output = "#ifndef _GAME_GLOBALS_H_INCLUDE\n"
    __output+="#define _GAME_GLOBALS_H_INCLUDE\n"
    __output+=`#include "vm.h"\n`

    __output += Object.values(variableAliasLookup)
      .map((str, stringIndex) => {
          //const alias = var_names[str]
        return `#define ${str} ${stringIndex}\n`;
      })
      .join("")

    __output+="#define GET_GLOBAL_VAL(idx) *(uint16_t *) script_memory + (idx)\n"
    __output+="#define GET_GLOBAL_REF(idx) (uint16_t *) script_memory + (idx)\n"
    __output+="#endif"

    writeAsset("game_globals.h", __output)
};


module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
    description,
    waitUntilAfterInitFade: true
};

