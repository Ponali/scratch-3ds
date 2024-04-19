#include <stdbool.h>
static int blockColor[10][2] = {{0,17},{18,37},{38,46},{47,54},{55,65},{66,83},{84,101},{102,106},{107,107}};
static char blockText[105][36] =
{"move 10 steps",
"turn clockwise 15 degrees",
"turn counterclockwise 15 degrees",
"go to random position",
"go to x:0 y:0",
"glide 1 secs to random position",
"glide 1 secs to x:0 y:0",
"point in direction 90",
"point towards mouse-pointer",
"change x by 10",
"set x to 0",
"change y by 10",
"set y to 0",
"if on edge, bounce",
"set rotation style left-right",
"x position",
"y position",
"direction",
"say Hello! for 2 seconds",
"say Hello!",
"think Hmm... for 2 seconds",
"think Hmm...",
"switch costume to costume2",
"next costume",
"switch backdrop to backdrop1",
"next backdrop",
"change size by 10",//i wish you could do that irl iykwim
"set size to 100%",
"change color effect by 25",
"set color effect to 0",
"clear graphic effects",
"show",
"hide",
"go to front layer",
"go forward 1 layers",
"costume number",
"backdrop number",
"size",
"play sound Meow until done",
"start sound Meow",
"stop all sounds",
"change pitch effect by 10",
"set pitch effect to 100",
"clear sound effects",
"change volume by -10",
"set volume to 100",
"volume",
"when flag clicked",
"when space key pressed",
"when this sprite clicked",
"when backdrop switches to backdrop1",
"when loudness > 10",
"when I receive message1",
"broadcast message1",
"broadcast message1 and wait",
"wait 1 seconds",
"repeat 10",
"forever",
"if < > then",
"if < > then else",
"wait until < >",
"repeat until < >",
"stop all",
"when I start as a clone",
"create clone of myself",
"delete this clone",
"touching mouse pointer?",
"touching color?",
"color is touching color?",
"distance to mouse-pointer",
"ask What's your name? and wait",
"answer",
"key space pressed?",
"mouse down?",
"mouse x",
"mouse y",
"set drag mode draggable",
"loudness",
"timer", //timer till i fucking lose it
"reset timer",
"backdrop # of stage",
"current year",
"days since 2000",
"username",
"( ) + ( )",
"( ) - ( )",
"( ) * ( )",
"( ) / ( )",
"pick random 1 to 10",
"( ) > 50",
"( ) < 50",
"( ) = 50",
"< > and < >",
"< > or < >",
"not < >",
"join apple banana",
"letter 1 of apple",
"length of apple",
"apple contains a?",
"( ) mod ( )",
"( ) round",
"abs of ( )",
"my variable",
"set my variable to 0",
"change my variable by 1",
"show variable my variable",
"hide variable my variable",
"placeholder block"};
static bool blockHat[105]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static bool blockEnd[105]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static bool reporter[105]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0};
static int getBlockColor(int idxA,int idxB){return blockColor[idxA][idxB];};
static char* getBlockText(int idx){return blockText[idx];};
static bool getBlockHat(int idx){return blockHat[idx];};
static bool getBlockEnd(int idx){return blockEnd[idx];};
static bool getReporter(int idx){return reporter[idx];};