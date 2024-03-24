OLDCALL tells a function to use __sdcccall(0). Without it, it uses the newer __sdcccall(1). Calling (1) seems to be perfectly fine and reports say its faster?
https://www.msx.org/forum/msx-talk/development/sdcc-4112-a-game-changer-for-c-programming?destination=node%2F62837
https://gbdk-2020.github.io/gbdk-2020/docs/api/docs_coding_guidelines.html

BANKED tells a function that it exists in a bank. Also unnecessary, as its applied by default due to #pragma 255. Also, #pragma 255 automatically determines an optimal bank for a source file. It might be important to keep this in mind if splitting a source file? I'm assuming that a well made header file might negate that issue though.
