const id = "MHF_EVENT_CHANGE_BARRIER_STATE";
const groups = ["Garden Cards"];
const name = "Change Barrier State";

const stateOpts = ['Forest', 'Plains']
const rowOpts = ['Plains', 'Swamps', 'Islands', 'Mountains', 'Forests']

const fields = [
    {
        key: "state",
        label: "State",
        type: "select",
        defaultValue: 0,
        options: stateOpts.map((x,i)=>[i,x])
    },
    {
        key: "row",
        label: "Row",
        type: "select",
        defaultValue: 0,
        options: rowOpts.map((x,i)=>[i,x])
    }
];

const autoLabel = (fetchArg, args) => {
    const stateStr = stateOpts[fetchArg("state")]
    const rowStr = rowOpts[fetchArg("row")]
    return `Set ${rowStr} to ${stateStr}`
};

const compile = (input, helpers) => {
    const {
        _callNative,
        _reserve,
        _setConst,
    } = helpers;


    const stackSize = 2;

    _reserve(stackSize);

    _setConst(".ARG0", input.state);
    _setConst(".ARG1", input.row);

    _callNative("changeBarrierState");

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

