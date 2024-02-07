const id = "MHF_EVENT_RESET_VARS";
const groups = ["Garden Cards"];
const name = "Reset Some Variables";

const VARIABLE_COUNT = 128;

const fields = [
    {
        key: "items",
        label: "Number of vars to be reset",
        description: "How many vars to reset to false",
        type: "number",
        min: 1,
        max: VARIABLE_COUNT,
        defaultValue: 1,
    }
].concat(
    Array(VARIABLE_COUNT)
    .fill()
    .map(
        (x,i)=>(
            {
                key: `variable${i}`,
                description: "Variable to Reset",
                type: "variable",
                defaultValue: "LAST_VARIABLE",
                    conditions: [
                        {key: "items",gt: i}
                    ]
            }
        )
    )
);

const compile = (input, helpers) => {
    const {
        _setVariableConst,
        _addComment,
        _addNL,
        getVariableAlias
    } = helpers;
    _addComment('Reset Some Variables')
    for(let i=0; i<input['items'];i++){
        const variableAlias = getVariableAlias(input[`variable${i}`]);
        _setVariableConst(variableAlias, 0);
    }
    _addNL()
};


module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};

