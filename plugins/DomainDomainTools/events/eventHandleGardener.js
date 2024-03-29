const id = "MHF_EVENT_HANDLE_OPPONENT_AI";
const groups = ["Garden Cards"];
const name = "Handle Opponent Card Choice";

const fields = [{
    label: "Choose the current AI's card to play"
}]

const compile = (input, helpers) => {
    const {
        _callNative
    } = helpers;

    _callNative("handleOpponentCardChoice")
};


module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};

