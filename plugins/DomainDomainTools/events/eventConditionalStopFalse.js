const id = "MHF_EVENT_HANDLE_CONDITIONAL_STOP_False";
const groups = ["Garden Cards"];
const name = "Stop Script If False";

const fields = [
    {
        key: "stopCheck",
        label: "Stop if",
        description: "Stops if",
        type: "variable",
        defaultValue: "LAST_VARIABLE"
    }
];

const compile = (input, helpers) => {
    const {
        _stop,
        _ifConst,
        _push,
        _label,
        _addComment,
        getNextLabel,
        getVariableAlias
    } = helpers;

    const variableAlias = getVariableAlias(input.stopCheck);
    const label = getNextLabel();
    _addComment('Stop Script If False')
    _ifConst('.EQ', variableAlias, 0, label, 0);
    _stop();
    _label(label);
};


module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};

