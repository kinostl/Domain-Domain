const id = "MHF_EVENT_CHANGE_PLOT";
const groups = ["Garden Cards"];
const name = "Change Plot";

const plotSideOptions = ['Player', 'Opponent']
const columnOpts = ['Hand', 'Graveyard', 'Score']
const rowOpts = ['Plains', 'Swamps', 'Islands', 'Mountains', 'Forests']

const fields = [
    {
        key: "plotSide",
        label: "Plot Side",
        type: "select",
        defaultValue: 0,
        options: plotSideOptions.map((x,i)=>[i,x])
    },
    {
        key: "column",
        label: "Column",
        type: "select",
        defaultValue: 0,
        options: columnOpts.map((x,i)=>[i,x])
    },
    {
        key: "row",
        label: "Row",
        type: "select",
        defaultValue: 0,
        options: rowOpts.map((x,i)=>[i,x])
    },
    {
        key: "face",
        label: "Value",
        type: "union",
        types: ["number", "variable"],
        defaultType: "number",
        defaultValue: {
            number: 0,
            variable: "LAST_VARIABLE",
        },
        min: 0,
        max: 5,
    },

];

const autoLabel = (fetchArg, args) => {
    const plotSideStr = plotSideOptions[fetchArg("plotSide")]
    const columnStr = columnOpts[fetchArg("column")]
    const rowStr = rowOpts[fetchArg("row")]
    const faceStr = `${fetchArg("face")}`
    return `Plot ${plotSideStr}-${columnStr},${rowStr}: ${faceStr}`
};

const curryVariableToUnion = (_setConst, _setToVariable) => {

    const setVariableToUnion = (vm_var, i_val) => {
        if(i_val.type == "number"){
            _setConst(vm_var, i_val.value)
        }

        if(i_val.type == "variable"){
            _setToVariable(vm_var, i_val.value)
        }
    }

    return setVariableToUnion
}

const compile = (input, helpers) => {
    const {
        _callNative,
        _stackPop,
        _reserve,
        variableSetToUnionValue,
        variableDec,
        _setConst,
        _setToVariable
    } = helpers;


    const stackSize = 3;
    const setVariableToUnion = curryVariableToUnion(_setConst, _setToVariable);
    let column = 0;
    if(input.plotSide == 0) {
        column = input.column;
    } else {
        column = 7 - input.column;

    }

    _reserve(stackSize);

    _setConst(".ARG0", column);
    _setConst(".ARG1", input.row);
    setVariableToUnion(".ARG2", input.face);

    _callNative("changePlot");

    _reserve(stackSize * -1);
};


module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
    autoLabel
};

