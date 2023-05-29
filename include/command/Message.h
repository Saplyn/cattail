#ifndef MESSAGE_H
#define MESSAGE_H

#define INFO_MSG "\
     cattail, version 1.0.6\n\
  The ANU-SDUW C++ OOP Assignment\n\
 _________________________________\n\
|                                 |\n\
|    __  __  _|_ _|_  __  - |     |\n\
|   /   /  |  |   |  /  | | |     |\n\
|   \\__ \\_/|  |/  |/ \\_/| | |/    |\n\
|_________________________________|\n\
"

#define HELP_MSG "\
cattail, version 1.0.6\n\
ANU-SDUW C++ OOP Assignment\n\
\n\
set  - Set program status.\n\
new  - Instantiate new shape object,\n\
       store it in temporary memory.\n\
tmp  - View temporary memory object.\n\
stk  - Perform stack operation.\n\
exit - Exit the program.\n\
"

#define SET_HELP_MSG "\
Usage: set [property] [value]\n\
Set program status.\n\
\n\
Possible command format:\n\
  set verbose [vlevel]       -  Set verbose level\n\
  set color [true/false]     -  Set output color\n\
"

#define SET_VERBOSE_HELP_MSG "\
Usage: set verbose [vlevel]\n\
Set output verbose level.\n\
\n\
vlevel can be the following value:\n\
  - silent  : outputs nothing\n\
  - report  : error and alert only\n\
  - concise : basic \n\
  - detailed: outputs nothing\n\
"

#define SET_COLOR_HELP_MSG "\
Usage: set color [true/false]\n\
Set output color.\n\
"

#define NEW_HELP_MSG "\
Usage: new [shape] [property]\n\
Instantiate new shape object, store it in temporary memory.\n\
\n\
Possible command format:\n\
  new circ [r]          -  Instantiate a circle\n\
  new rect [l] [w]      -  Instantiate a rectangle\n\
  new tria [a] [b] [c]  -  Instantiate a triangle\n\
"

#define STK_HELP_MSG "\
Usage: stk [operation]\n\
stk - Perform stack operation.\n\
\n\
Possible command format:\n\
  stk push   -  Push the temporary object into stack\n\
  stk pop    -  Pop the stack top\n\
  stk top    -  Retrieve the stack top\n\
  stk state  -  Display stack status\n\
"

#define EXIT_MSG "\
Terminate program normally.\n\
"

#endif