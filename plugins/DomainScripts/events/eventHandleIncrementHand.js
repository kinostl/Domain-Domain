const id = "MHF_EVENT_HANDLE_INCREMENT_HAND";
const groups = ["Garden Cards"];
const name = "Increment Hand";

const fields = [
    {
        key: "targetCard",
        label: "Variable",
        type: "variable",
        defaultValue: "LAST_VARIABLE"
    }
];

const compile = (input, helpers) => {
    const {
        variableInc,
        caseVariableValue
    } = helpers;

    caseVariableValue();
};


module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};
