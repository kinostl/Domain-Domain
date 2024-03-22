const id = "MHF_EVENT_HANDLE_OPPONENT_AI";
const groups = ["Garden Cards"];
const name = "Handle Opponent AI";

const fields = [{
    label: "Run the Current Opponent's AI"
}]

const compile = (input, helpers) => {
    const {
        _callNative
    } = helpers;

    _callNative("handleOpponentTurn")
};


module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};

