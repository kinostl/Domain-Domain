const id = "MHF_EVENT_CHECK_FLAG";
const groups = ["Garden Cards"];
const autoLabel = (fetchArg) => {
    return "Stop If "+fetchArg("variable")+" Has Flag " + String(Number(fetchArg("flag")) + 1);
};
const l10n = (_var) => _var;

const fields = [
  {
    key: "variable",
    label: l10n("FIELD_VARIABLE"),
    description: l10n("FIELD_VARIABLE_DESC"),
    type: "variable",
    defaultValue: "LAST_VARIABLE",
  },
  {
    key: "flag",
    label: l10n("FIELD_FLAG"),
    description: l10n("FIELD_FLAG_CHECK_DESC"),
    type: "select",
    options: [
      [0, l10n("FIELD_FLAG_1")],
      [1, l10n("FIELD_FLAG_2")],
      [2, l10n("FIELD_FLAG_3")],
      [3, l10n("FIELD_FLAG_4")],
      [4, l10n("FIELD_FLAG_5")],
      [5, l10n("FIELD_FLAG_6")],
      [6, l10n("FIELD_FLAG_7")],
      [7, l10n("FIELD_FLAG_8")],
      [8, l10n("FIELD_FLAG_9")],
      [9, l10n("FIELD_FLAG_10")],
      [10, l10n("FIELD_FLAG_11")],
      [11, l10n("FIELD_FLAG_12")],
      [12, l10n("FIELD_FLAG_13")],
      [13, l10n("FIELD_FLAG_14")],
      [14, l10n("FIELD_FLAG_15")],
      [15, l10n("FIELD_FLAG_16")],
    ],
    defaultValue: 0,
  }
];

const compile = (input, helpers) => {
  const { _rpn, _stop, getNextLabel, _ifConst, _label, _addComment } = helpers;
  const contLabel = getNextLabel();
  const truePath = 'VM_STOP';
  const falsePath = [];
  let flags = 0;
  if (input.flag == 0) flags = 0x0001;
  if (input.flag == 1) flags = 0x0002;
  if (input.flag == 2) flags = 0x0004;
  if (input.flag == 3) flags = 0x0008;
  if (input.flag == 4) flags = 0x0010;
  if (input.flag == 5) flags = 0x0020;
  if (input.flag == 6) flags = 0x0040;
  if (input.flag == 7) flags = 0x0080;
  if (input.flag == 8) flags = 0x0100;
  if (input.flag == 9) flags = 0x0200;
  if (input.flag == 10) flags = 0x0400;
  if (input.flag == 11) flags = 0x0800;
  if (input.flag == 12) flags = 0x1000;
  if (input.flag == 13) flags = 0x2000;
  if (input.flag == 14) flags = 0x4000;
  if (input.flag == 15) flags = 0x8000;
  _addComment("Stop If Variable Has Flag")
  _rpn()
      .refVariable(input.variable)
      .int16(flags)
      .operator(".B_AND")
      .stop();
      _ifConst(".EQ", ".ARG0", 0, contLabel, 1);
      _stop();
      _label(contLabel);

};

module.exports = {
    id,
    autoLabel,
    groups,
    fields,
    compile,
};

