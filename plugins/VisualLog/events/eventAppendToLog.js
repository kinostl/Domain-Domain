const id = "PT_EVENT_APPEND_VISUAL_LOG";
const groups = ["EVENT_GROUP_DIALOGUE", "Visual Log"];
const name = "Append To Log";
const description = "Adds to an existing log. Use Start Log in the scene first.";

const wrap8Bit = (val) => (256 + (val % 256)) % 256;

const decOct = (dec) => wrap8Bit(dec).toString(8).padStart(3, "0");

const fields = [{
  key: "text",
  type: "text",
  placeholder: "Text...",
  defaultValue: "",
    flexBasis: "100%",
    maxLength: 20,
    multiple: true
}]

const compile = (input, helpers) => {
  const {
    _addComment,
    _loadStructuredText,
    _displayText,
    appendRaw,
    _addNL,
    _includeHeader
  } = helpers;
  const text = Array.isArray(input.text) ? input.text.map((_text)=>_text.trim()) : [input.text || ''];

  _addComment("Log To Screen");

  const textSpdSequence = '\\001\\001';

  text.forEach((_text)=>{
    _addComment(`${_text}`);
    appendRaw(`VM_OVERLAY_WAIT .UI_NONMODAL .UI_WAIT_TEXT`);
    _loadStructuredText(`\\r${textSpdSequence}${_text}`);
    appendRaw('VM_DISPLAY_TEXT_EX .DISPLAY_PRESERVE_POS, .TEXT_TILE_CONTINUE');
  })

  _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
  waitUntilAfterInitFade: true,
  description
};
