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
    }
];

const compile = (input, helpers) => {
    const {
        _callNative,
        _setVariable,
        _setToVariable,
        _stackPop,
        _stackPushConst
    } = helpers;


    const stackSize = 2;

    for(let i=0;i<stackSize;i++){_stackPushConst(0)}
    _setToVariable(".ARG0", input.validChoices);
    _setToVariable(".ARG1", input.targetCard);
    _callNative("handleCirno");
    _setVariable(input.targetCard, ".ARG1");
    _stackPop(stackSize);
};


module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};

