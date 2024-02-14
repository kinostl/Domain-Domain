const id = "PT_EVENT_START_VISUAL_LOG";
const groups = ["EVENT_GROUP_DIALOGUE", "Visual Log"];
const name = "Start Log";
const description = "Prepares the Scene for displaying a log."

const fields = [{
  key: "text",
  label: 'First Line',
  type: "text",
  placeholder: "Text...",
  defaultValue: "",
    flexBasis: "100%",
    maxLength: 20
},{
  key: 'line_count',
  label: 'Line Count',
  defaultValue: 3,
  type: 'slider',
  max: 18,
  min: 1
},{
  label: 'Warning: Displaying more than 116 Letters on GBC screen causes corruption.',
  conditions: [
    {
      key: "line_count",
      gte: 5
    }
  ]
},{
  key: 'bg_color',
  label: 'Background Color',
  defaultValue: '.UI_COLOR_BLACK',
  type: 'select',
  options: [
    ['.UI_COLOR_BLACK', 'Black'],
    ['.UI_COLOR_WHITE', 'White']
  ]
}];


const wrap8Bit = (val) => (256 + (val % 256)) % 256;

const decOct = (dec) => wrap8Bit(dec).toString(8).padStart(3, "0");

const compile = (input, helpers) => {
  const {
    _addComment,
    appendRaw,
    _addNL,
    _includeHeader,
    _loadStructuredText,
    _displayText
  } = helpers;
  _addComment("Initiate Log To Screen");
  const y = decOct(input.line_count);

  appendRaw(`VM_OVERLAY_SHOW       0, ${18 - input.line_count}, ${input.bg_color}, .UI_AUTO_SCROLL`);
  _loadStructuredText(`\\003\\001\\${y}\\001\\001${input.text || ''}`);
  _displayText();

  _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
  waitUntilAfterInitFade: false,
  description
};
