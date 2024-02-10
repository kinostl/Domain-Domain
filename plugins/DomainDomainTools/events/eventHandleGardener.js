const id = "MHF_EVENT_HANDLE_GARDENER_AI";
const groups = ["Garden Cards"];
const name = "Handle Gardener AI";

const fields = [
    {
        key: "validChoices",
        label: "Valid Choices",
        description: "Flag of Valid Choices.\n 1. White\n2. Black\n3. Blue\n4. Red\n5. Green",
        type: "variable",
        defaultValue: "LAST_VARIABLE"
    },
    {
        key: "targetCard",
        label: "Where to Store Choice",
        description: "Variable holding card choice",
        type: "variable",
        defaultValue: "LAST_VARIABLE"
    },
    {
        key: "currentOpponent",
        label: "Current Opponent",
        type: "variable",
        defaultValue: "LAST_VARIABLE"
    },

];

const compile = (input, helpers) => {
    const {
        _callNative,
        _setVariable,
        _setToVariable,
        _stackPop,
        _reserve
    } = helpers;


    const stackSize = 3;
    _reserve(stackSize);
    _setToVariable(".ARG0", input.validChoices);
    _setToVariable(".ARG1", input.targetCard);
    _setToVariable(".ARG2", input.currentOpponent)
    _callNative("handleDebugCirno");
    _setVariable(input.targetCard, ".ARG1");
    _reserve(stackSize * -1);
};


module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};

