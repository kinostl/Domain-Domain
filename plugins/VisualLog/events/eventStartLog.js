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
  defaultValue: '.UI_COLOR_WHITE',
  type: 'select',
  options: [
    ['.UI_COLOR_BLACK', 'Black'],
    ['.UI_COLOR_WHITE', 'White']
  ]
},{
  key: "color",
  label: "Palette",
  type: "togglebuttons",
  options: [
    ['010','BG 1'],['001','BG 2'],['002','BG 3'],['003','BG 4'],['004','BG 5'],['005','BG 6'],['006','DMG'],['007','UI']
  ],
  defaultValue: '007'
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
  const speed = '\\001\\003';
  const color = `\\013\\${input.color}`;
  const text = input.text || '';

  appendRaw(`VM_OVERLAY_SHOW       0, ${18 - input.line_count}, ${input.bg_color}, .UI_AUTO_SCROLL`);
  _loadStructuredText(`${color}\\003\\001\\${y}${speed}${text.padEnd(20,' ')}`);
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
