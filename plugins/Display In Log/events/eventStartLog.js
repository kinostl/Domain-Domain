const id = "PT_EVENT_START_VISUAL_LOG";
const groups = ["EVENT_GROUP_DIALOGUE", "Visual Log"];
const name = "Start Log";

const fields = [{
  label: "Prepares the Scene for displaying a log."
}]

const compile = (input, helpers) => {
  const {
    _addComment,
    appendRaw,
    _addNL,
  } = helpers;
_addComment("Initiate Log To Screen");

  appendRaw(`VM_OVERLAY_SHOW       0, 15, 0, 0`);
  appendRaw(`VM_OVERLAY_SET_SCROLL 0, 2, 0, 3, .UI_COLOR_BLACK`);

  _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
  waitUntilAfterInitFade: false
};
