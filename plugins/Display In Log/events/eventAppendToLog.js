const id = "PT_EVENT_APPEND_VISUAL_LOG";
const groups = ["EVENT_GROUP_DIALOGUE", "Visual Log"];
const name = "Log";

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

const textX = 0;
const textY = 2;
const textHeight = 3;

const compile = (input, helpers) => {
  const {
    _addComment,
    _loadStructuredText,
    _displayText,
    appendRaw,
    _addNL,
  } = helpers;

  const text = Array.isArray(input.text) ? input.text.map((_text)=>_text.trim()) : [input.text || ''];

  const x = decOct(1 + textX);
  const y = decOct(1 + textY);
  const textPosSequence = `\\003\\${x}\\${y}`;
  const textSpdSequence = '\\001\\001';

  _addComment("Log To Screen");

  text.forEach((_text)=>{
    _addComment(`${_text}`);
    appendRaw(`VM_OVERLAY_WAIT .UI_NONMODAL .UI_WAIT_TEXT`);
    appendRaw(`VM_OVERLAY_SCROLL 0, 0, 20, 3, .UI_COLOR_BLACK`);
    _loadStructuredText(
      `${textPosSequence}${textSpdSequence}${_text}`,
      null,
      textHeight
    );
    _displayText();
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
};
