#include <bpf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define PACKET_BUFFER_SIZE 4096
unsigned char stub_features[] =
	"qSupported:multiprocess-;swbreak+;hwbreak-;qRelocInsn-;fork-events-;vfork-events-;exec-events-;vContSupported-;QThreadEvents-;no-resumed-";

unsigned char get_regs[] = {
127,69,76,70,2,1,1,0,0,0,0,0,0,0,0,0,1,0,247,0,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
128,25,0,0,0,0,0,0,0,0,0,0,64,0,0,0,0,0,64,0,
19,0,1,0,191,22,0,0,0,0,0,0,183,1,0,0,37,0,0,0,
107,26,254,255,0,0,0,0,191,161,0,0,0,0,0,0,7,1,0,0,
254,255,255,255,183,7,0,0,0,0,0,0,183,2,0,0,2,0,0,0,
183,3,0,0,0,0,0,0,183,4,0,0,0,0,0,0,183,5,0,0,
0,0,0,0,133,0,0,0,6,0,0,0,183,1,0,0,82,0,0,0,
107,26,252,255,0,0,0,0,191,161,0,0,0,0,0,0,7,1,0,0,
252,255,255,255,183,2,0,0,2,0,0,0,183,3,0,0,0,0,0,0,
183,4,0,0,0,0,0,0,183,5,0,0,0,0,0,0,133,0,0,0,
6,0,0,0,7,6,0,0,16,0,0,0,183,8,0,0,123,125,0,0,
183,9,0,0,0,0,0,0,107,138,248,255,0,0,0,0,115,122,250,255,
0,0,0,0,191,97,0,0,0,0,0,0,15,145,0,0,0,0,0,0,
121,19,0,0,0,0,0,0,191,161,0,0,0,0,0,0,7,1,0,0,
248,255,255,255,183,2,0,0,3,0,0,0,183,4,0,0,0,0,0,0,
183,5,0,0,0,0,0,0,133,0,0,0,6,0,0,0,7,9,0,0,
8,0,0,0,21,9,1,0,0,1,0,0,5,0,242,255,0,0,0,0,
183,1,0,0,35,0,0,0,107,26,246,255,0,0,0,0,191,161,0,0,
0,0,0,0,7,1,0,0,246,255,255,255,183,6,0,0,0,0,0,0,
183,2,0,0,2,0,0,0,183,3,0,0,0,0,0,0,183,4,0,0,
0,0,0,0,183,5,0,0,0,0,0,0,133,0,0,0,6,0,0,0,
183,1,0,0,48,48,0,0,107,26,242,255,0,0,0,0,115,106,244,255,
0,0,0,0,191,161,0,0,0,0,0,0,7,1,0,0,242,255,255,255,
183,2,0,0,3,0,0,0,183,3,0,0,0,0,0,0,183,4,0,0,
0,0,0,0,183,5,0,0,0,0,0,0,133,0,0,0,6,0,0,0,
183,0,0,0,0,0,0,0,149,0,0,0,0,0,0,0,123,125,0,48,
48,0,0,0,0,0,0,0,0,0,16,0,0,0,0,0,0,0,1,0,
81,16,0,0,0,0,0,0,0,168,0,0,0,0,0,0,0,1,0,86,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,0,
0,0,0,0,24,0,0,0,0,0,0,0,3,0,16,37,159,24,0,0,
0,0,0,0,0,184,0,0,0,0,0,0,0,2,0,122,14,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,96,0,0,0,0,0,0,
0,104,0,0,0,0,0,0,0,3,0,16,82,159,104,0,0,0,0,0,
0,0,184,0,0,0,0,0,0,0,2,0,122,12,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,160,0,0,0,0,0,0,0,184,0,
0,0,0,0,0,0,3,0,17,0,159,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,48,1,0,0,0,0,0,0,56,1,0,0,0,
0,0,0,3,0,16,35,159,56,1,0,0,0,0,0,0,216,1,0,0,
0,0,0,0,2,0,122,6,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,1,17,1,37,14,19,5,3,14,16,23,27,14,17,1,18,
6,0,0,2,52,0,3,14,73,19,58,11,59,11,0,0,3,15,0,73,
19,0,0,4,21,1,73,19,39,25,0,0,5,5,0,73,19,0,0,6,
36,0,3,14,62,11,11,11,0,0,7,38,0,73,19,0,0,8,46,1,
17,1,18,6,64,24,151,66,25,3,14,58,11,59,11,39,25,73,19,63,
25,0,0,9,5,0,2,23,3,14,58,11,59,11,73,19,0,0,10,11,
1,85,23,0,0,11,52,0,2,23,3,14,58,11,59,11,73,19,0,0,
12,11,1,17,1,18,6,0,0,13,52,0,2,24,3,14,58,11,59,11,
73,19,0,0,14,1,1,73,19,0,0,15,33,0,73,19,55,11,0,0,
16,36,0,3,14,11,11,62,11,0,0,17,19,1,3,14,11,5,58,11,
59,11,0,0,18,13,0,3,14,73,19,58,11,59,11,56,11,0,0,19,
19,1,11,5,58,11,59,11,0,0,20,13,0,73,19,58,11,59,11,56,
11,0,0,21,23,1,11,5,58,11,59,11,0,0,22,13,0,3,14,73,
19,58,11,59,11,56,5,0,0,23,22,0,73,19,3,14,58,11,59,11,
0,0,0,94,3,0,0,4,0,0,0,0,0,8,1,0,0,0,0,12,
0,45,0,0,0,0,0,0,0,56,0,0,0,0,0,0,0,0,0,0,
0,216,1,0,0,2,124,0,0,0,53,0,0,0,1,7,3,58,0,0,
0,4,89,0,0,0,5,96,0,0,0,5,89,0,0,0,5,113,0,0,
0,5,113,0,0,0,5,113,0,0,0,0,6,143,0,0,0,5,4,3,
101,0,0,0,7,106,0,0,0,6,147,0,0,0,6,1,6,152,0,0,
0,5,8,8,0,0,0,0,0,0,0,0,216,1,0,0,1,90,161,0,
0,0,2,4,89,0,0,0,9,0,0,0,0,195,0,0,0,2,4,56,
1,0,0,10,0,0,0,0,11,54,0,0,0,170,0,0,0,2,5,85,
3,0,0,0,10,48,0,0,0,11,111,0,0,0,170,0,0,0,2,6,
85,3,0,0,0,12,160,0,0,0,0,0,0,0,136,0,0,0,11,168,
0,0,0,129,1,0,0,2,8,89,0,0,0,10,96,0,0,0,13,2,
145,8,170,0,0,0,2,9,37,1,0,0,0,0,10,144,0,0,0,11,
205,0,0,0,170,0,0,0,2,11,85,3,0,0,0,10,192,0,0,0,
13,2,145,2,170,0,0,0,2,12,37,1,0,0,0,0,14,101,0,0,
0,15,49,1,0,0,3,0,16,175,0,0,0,8,7,3,61,1,0,0,
17,114,1,0,0,32,1,3,10,18,199,0,0,0,55,3,0,0,3,11,
0,18,235,0,0,0,55,3,0,0,3,12,8,18,241,0,0,0,106,1,
0,0,3,53,16,19,16,1,3,13,20,119,1,0,0,3,14,0,21,0,
1,3,14,18,244,0,0,0,73,3,0,0,3,15,0,18,249,0,0,0,
148,1,0,0,3,49,0,19,0,1,3,16,18,1,1,0,0,55,3,0,
0,3,17,0,18,6,1,0,0,55,3,0,0,3,18,8,18,9,1,0,
0,55,3,0,0,3,19,16,18,12,1,0,0,55,3,0,0,3,20,24,
18,15,1,0,0,55,3,0,0,3,21,32,18,18,1,0,0,55,3,0,
0,3,22,40,18,21,1,0,0,55,3,0,0,3,23,48,18,24,1,0,
0,55,3,0,0,3,24,56,18,27,1,0,0,55,3,0,0,3,25,64,
18,30,1,0,0,55,3,0,0,3,26,72,18,33,1,0,0,55,3,0,
0,3,27,80,18,36,1,0,0,55,3,0,0,3,28,88,18,39,1,0,
0,55,3,0,0,3,29,96,18,42,1,0,0,55,3,0,0,3,30,104,
18,45,1,0,0,55,3,0,0,3,31,112,18,48,1,0,0,55,3,0,
0,3,32,120,18,51,1,0,0,55,3,0,0,3,33,128,18,54,1,0,
0,55,3,0,0,3,34,136,18,57,1,0,0,55,3,0,0,3,35,144,
18,60,1,0,0,55,3,0,0,3,36,152,18,63,1,0,0,55,3,0,
0,3,37,160,18,66,1,0,0,55,3,0,0,3,38,168,18,69,1,0,
0,55,3,0,0,3,39,176,18,72,1,0,0,55,3,0,0,3,40,184,
18,75,1,0,0,55,3,0,0,3,41,192,18,78,1,0,0,55,3,0,
0,3,42,200,18,81,1,0,0,55,3,0,0,3,43,208,18,85,1,0,
0,55,3,0,0,3,44,216,18,89,1,0,0,55,3,0,0,3,45,224,
18,92,1,0,0,55,3,0,0,3,46,232,18,95,1,0,0,55,3,0,
0,3,47,240,18,98,1,0,0,55,3,0,0,3,48,248,0,0,22,101,
1,0,0,55,3,0,0,3,51,0,1,22,109,1,0,0,55,3,0,0,
3,52,8,1,0,0,23,66,3,0,0,228,0,0,0,3,4,6,205,0,
0,0,7,8,14,55,3,0,0,15,49,1,0,0,32,0,14,101,0,0,
0,15,49,1,0,0,2,0,0,16,0,0,0,0,0,0,0,32,0,0,
0,0,0,0,0,48,0,0,0,0,0,0,0,96,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,96,0,0,
0,0,0,0,0,112,0,0,0,0,0,0,0,120,0,0,0,0,0,0,
0,160,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,184,0,0,0,0,0,0,0,232,0,0,0,0,0,0,
0,240,0,0,0,0,0,0,0,16,1,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,48,1,0,0,0,0,0,
0,128,1,0,0,0,0,0,0,152,1,0,0,0,0,0,0,160,1,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,128,1,0,0,0,0,0,0,152,1,0,0,0,0,0,0,160,1,0,
0,0,0,0,0,200,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,85,98,117,110,116,117,32,99,108,97,110,
103,32,118,101,114,115,105,111,110,32,49,50,46,48,46,48,45,51,117,98,
117,110,116,117,49,126,50,48,46,48,52,46,53,0,103,101,116,95,114,101,
103,115,46,99,0,47,104,111,109,101,47,111,115,108,97,98,47,114,67,111,
114,101,45,84,117,116,111,114,105,97,108,45,118,51,45,101,66,80,70,47,
114,67,111,114,101,45,84,117,116,111,114,105,97,108,45,118,51,47,117,115,
101,114,47,101,98,112,102,47,107,101,114,110,0,95,95,98,112,102,95,116,
114,97,99,101,95,112,114,105,110,116,107,0,105,110,116,0,99,104,97,114,
0,108,111,110,103,32,105,110,116,0,98,112,102,95,112,114,111,103,0,95,
102,109,116,0,95,95,65,82,82,65,89,95,83,73,90,69,95,84,89,80,
69,95,95,0,99,116,120,0,112,116,121,112,101,0,108,111,110,103,32,108,
111,110,103,32,117,110,115,105,103,110,101,100,32,105,110,116,0,115,105,122,
101,95,116,0,112,97,100,100,114,0,116,102,0,114,101,103,115,0,103,101,
110,101,114,97,108,0,122,101,114,111,0,114,97,0,115,112,0,103,112,0,
116,112,0,116,48,0,116,49,0,116,50,0,115,48,0,115,49,0,97,48,
0,97,49,0,97,50,0,97,51,0,97,52,0,97,53,0,97,54,0,97,
55,0,115,50,0,115,51,0,115,52,0,115,53,0,115,54,0,115,55,0,
115,56,0,115,57,0,115,49,48,0,115,49,49,0,116,51,0,116,52,0,
116,53,0,116,54,0,115,115,116,97,116,117,115,0,115,101,112,99,0,107,
112,114,111,98,101,95,98,112,102,95,99,116,120,0,105,0,159,235,1,0,
24,0,0,0,0,0,0,0,144,2,0,0,144,2,0,0,118,2,0,0,
0,0,0,0,0,0,0,2,2,0,0,0,1,0,0,0,3,0,0,4,
32,1,0,0,16,0,0,0,3,0,0,0,0,0,0,0,22,0,0,0,
3,0,0,0,64,0,0,0,28,0,0,0,5,0,0,0,128,0,0,0,
31,0,0,0,0,0,0,8,4,0,0,0,38,0,0,0,0,0,0,1,
8,0,0,0,64,0,0,0,0,0,0,0,3,0,0,4,16,1,0,0,
0,0,0,0,6,0,0,0,0,0,0,0,61,0,0,0,3,0,0,0,
0,8,0,0,69,0,0,0,3,0,0,0,64,8,0,0,0,0,0,0,
2,0,0,5,0,1,0,0,74,0,0,0,7,0,0,0,0,0,0,0,
79,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
0,0,0,0,3,0,0,0,8,0,0,0,32,0,0,0,87,0,0,0,
0,0,0,1,4,0,0,0,32,0,0,0,0,0,0,0,32,0,0,4,
0,1,0,0,107,0,0,0,3,0,0,0,0,0,0,0,112,0,0,0,
3,0,0,0,64,0,0,0,115,0,0,0,3,0,0,0,128,0,0,0,
118,0,0,0,3,0,0,0,192,0,0,0,121,0,0,0,3,0,0,0,
0,1,0,0,124,0,0,0,3,0,0,0,64,1,0,0,127,0,0,0,
3,0,0,0,128,1,0,0,130,0,0,0,3,0,0,0,192,1,0,0,
133,0,0,0,3,0,0,0,0,2,0,0,136,0,0,0,3,0,0,0,
64,2,0,0,139,0,0,0,3,0,0,0,128,2,0,0,142,0,0,0,
3,0,0,0,192,2,0,0,145,0,0,0,3,0,0,0,0,3,0,0,
148,0,0,0,3,0,0,0,64,3,0,0,151,0,0,0,3,0,0,0,
128,3,0,0,154,0,0,0,3,0,0,0,192,3,0,0,157,0,0,0,
3,0,0,0,0,4,0,0,160,0,0,0,3,0,0,0,64,4,0,0,
163,0,0,0,3,0,0,0,128,4,0,0,166,0,0,0,3,0,0,0,
192,4,0,0,169,0,0,0,3,0,0,0,0,5,0,0,172,0,0,0,
3,0,0,0,64,5,0,0,175,0,0,0,3,0,0,0,128,5,0,0,
178,0,0,0,3,0,0,0,192,5,0,0,181,0,0,0,3,0,0,0,
0,6,0,0,184,0,0,0,3,0,0,0,64,6,0,0,187,0,0,0,
3,0,0,0,128,6,0,0,191,0,0,0,3,0,0,0,192,6,0,0,
195,0,0,0,3,0,0,0,0,7,0,0,198,0,0,0,3,0,0,0,
64,7,0,0,201,0,0,0,3,0,0,0,128,7,0,0,204,0,0,0,
3,0,0,0,192,7,0,0,0,0,0,0,1,0,0,13,11,0,0,0,
207,0,0,0,1,0,0,0,211,0,0,0,0,0,0,1,4,0,0,0,
32,0,0,1,215,0,0,0,1,0,0,12,10,0,0,0,0,107,112,114,
111,98,101,95,98,112,102,95,99,116,120,0,112,116,121,112,101,0,112,97,
100,100,114,0,116,102,0,115,105,122,101,95,116,0,108,111,110,103,32,108,
111,110,103,32,117,110,115,105,103,110,101,100,32,105,110,116,0,115,115,116,
97,116,117,115,0,115,101,112,99,0,114,101,103,115,0,103,101,110,101,114,
97,108,0,95,95,65,82,82,65,89,95,83,73,90,69,95,84,89,80,69,
95,95,0,122,101,114,111,0,114,97,0,115,112,0,103,112,0,116,112,0,
116,48,0,116,49,0,116,50,0,115,48,0,115,49,0,97,48,0,97,49,
0,97,50,0,97,51,0,97,52,0,97,53,0,97,54,0,97,55,0,115,
50,0,115,51,0,115,52,0,115,53,0,115,54,0,115,55,0,115,56,0,
115,57,0,115,49,48,0,115,49,49,0,116,51,0,116,52,0,116,53,0,
116,54,0,99,116,120,0,105,110,116,0,98,112,102,95,112,114,111,103,0,
46,116,101,120,116,0,47,104,111,109,101,47,111,115,108,97,98,47,114,67,
111,114,101,45,84,117,116,111,114,105,97,108,45,118,51,45,101,66,80,70,
47,114,67,111,114,101,45,84,117,116,111,114,105,97,108,45,118,51,47,117,
115,101,114,47,101,98,112,102,47,107,101,114,110,47,103,101,116,95,114,101,
103,115,46,99,0,105,110,116,32,98,112,102,95,112,114,111,103,40,115,116,
114,117,99,116,32,107,112,114,111,98,101,95,98,112,102,95,99,116,120,32,
42,99,116,120,41,32,123,0,32,32,98,112,102,95,116,114,97,99,101,95,
112,114,105,110,116,107,40,34,37,34,44,32,48,44,32,48,44,32,48,41,
59,32,47,47,82,117,115,116,32,70,111,116,109,97,116,33,32,0,32,32,
98,112,102,95,116,114,97,99,101,95,112,114,105,110,116,107,40,34,82,34,
44,32,48,44,32,48,44,32,48,41,59,32,0,32,32,102,111,114,32,40,
105,110,116,32,105,32,61,32,48,59,32,105,32,60,32,51,50,59,32,43,
43,105,41,32,123,0,32,32,32,32,98,112,102,95,116,114,97,99,101,95,
112,114,105,110,116,107,40,34,123,125,34,44,32,99,116,120,45,62,116,102,
46,114,101,103,115,91,105,93,44,32,48,44,32,48,41,59,0,32,32,98,
112,102,95,116,114,97,99,101,95,112,114,105,110,116,107,40,34,35,34,44,
32,48,44,32,48,44,32,48,41,59,0,32,32,98,112,102,95,116,114,97,
99,101,95,112,114,105,110,116,107,40,34,48,48,34,44,32,48,44,32,48,
44,32,48,41,59,32,47,47,116,111,100,111,58,32,109,111,100,117,108,111,
32,50,53,54,32,99,104,101,99,107,115,117,109,0,32,32,114,101,116,117,
114,110,32,48,59,0,159,235,1,0,32,0,0,0,0,0,0,0,20,0,
0,0,20,0,0,0,76,1,0,0,96,1,0,0,0,0,0,0,8,0,
0,0,224,0,0,0,1,0,0,0,0,0,0,0,12,0,0,0,16,0,
0,0,224,0,0,0,20,0,0,0,0,0,0,0,230,0,0,0,53,1,
0,0,0,16,0,0,16,0,0,0,230,0,0,0,96,1,0,0,3,20,
0,0,32,0,0,0,230,0,0,0,0,0,0,0,0,0,0,0,48,0,
0,0,230,0,0,0,96,1,0,0,3,20,0,0,96,0,0,0,230,0,
0,0,146,1,0,0,3,24,0,0,112,0,0,0,230,0,0,0,0,0,
0,0,0,0,0,0,120,0,0,0,230,0,0,0,146,1,0,0,3,24,
0,0,160,0,0,0,230,0,0,0,181,1,0,0,3,32,0,0,184,0,
0,0,230,0,0,0,214,1,0,0,5,36,0,0,232,0,0,0,230,0,
0,0,0,0,0,0,0,0,0,0,240,0,0,0,230,0,0,0,214,1,
0,0,5,36,0,0,16,1,0,0,230,0,0,0,181,1,0,0,21,32,
0,0,24,1,0,0,230,0,0,0,181,1,0,0,3,32,0,0,48,1,
0,0,230,0,0,0,9,2,0,0,3,44,0,0,64,1,0,0,230,0,
0,0,0,0,0,0,0,0,0,0,80,1,0,0,230,0,0,0,9,2,
0,0,3,44,0,0,128,1,0,0,230,0,0,0,43,2,0,0,3,48,
0,0,152,1,0,0,230,0,0,0,0,0,0,0,0,0,0,0,160,1,
0,0,230,0,0,0,43,2,0,0,3,48,0,0,200,1,0,0,230,0,
0,0,106,2,0,0,3,52,0,0,0,0,12,0,0,0,255,255,255,255,
4,0,8,0,8,124,11,0,20,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,216,1,0,0,0,0,0,0,162,0,0,0,4,0,57,0,
0,0,8,1,1,251,14,13,0,1,1,1,1,0,0,0,1,0,0,1,
46,0,0,98,112,102,46,104,0,1,0,0,103,101,116,95,114,101,103,115,
46,99,0,0,0,0,107,112,114,111,98,101,46,104,0,1,0,0,0,4,
2,0,9,2,0,0,0,0,0,0,0,0,21,5,3,10,47,6,27,65,
83,6,38,6,3,122,32,52,6,90,6,3,120,32,5,5,6,3,9,46,
5,0,6,3,119,102,5,5,3,9,32,5,21,6,73,5,3,6,32,3,
120,46,6,3,11,32,6,3,117,32,3,11,60,3,117,88,6,3,12,32,
5,0,6,3,116,60,5,3,3,12,32,6,89,2,2,0,1,1,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,142,0,0,0,4,0,241,255,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,181,0,0,0,0,0,2,0,184,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,174,0,0,0,0,0,2,0,
40,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,3,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,3,0,5,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,3,0,8,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,9,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,0,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,3,0,15,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,75,0,0,0,18,0,2,0,0,0,0,0,0,0,0,0,
216,1,0,0,0,0,0,0,6,0,0,0,0,0,0,0,10,0,0,0,
6,0,0,0,12,0,0,0,0,0,0,0,10,0,0,0,8,0,0,0,
18,0,0,0,0,0,0,0,10,0,0,0,8,0,0,0,22,0,0,0,
0,0,0,0,10,0,0,0,10,0,0,0,26,0,0,0,0,0,0,0,
10,0,0,0,8,0,0,0,30,0,0,0,0,0,0,0,1,0,0,0,
4,0,0,0,43,0,0,0,0,0,0,0,10,0,0,0,8,0,0,0,
90,0,0,0,0,0,0,0,10,0,0,0,8,0,0,0,107,0,0,0,
0,0,0,0,10,0,0,0,8,0,0,0,114,0,0,0,0,0,0,0,
10,0,0,0,8,0,0,0,121,0,0,0,0,0,0,0,1,0,0,0,
4,0,0,0,135,0,0,0,0,0,0,0,10,0,0,0,8,0,0,0,
146,0,0,0,0,0,0,0,10,0,0,0,5,0,0,0,150,0,0,0,
0,0,0,0,10,0,0,0,8,0,0,0,161,0,0,0,0,0,0,0,
10,0,0,0,7,0,0,0,166,0,0,0,0,0,0,0,10,0,0,0,
5,0,0,0,170,0,0,0,0,0,0,0,10,0,0,0,8,0,0,0,
182,0,0,0,0,0,0,0,10,0,0,0,7,0,0,0,187,0,0,0,
0,0,0,0,10,0,0,0,5,0,0,0,191,0,0,0,0,0,0,0,
10,0,0,0,8,0,0,0,203,0,0,0,0,0,0,0,1,0,0,0,
4,0,0,0,216,0,0,0,0,0,0,0,10,0,0,0,5,0,0,0,
220,0,0,0,0,0,0,0,10,0,0,0,8,0,0,0,231,0,0,0,
0,0,0,0,10,0,0,0,7,0,0,0,239,0,0,0,0,0,0,0,
10,0,0,0,8,0,0,0,252,0,0,0,0,0,0,0,10,0,0,0,
7,0,0,0,1,1,0,0,0,0,0,0,10,0,0,0,5,0,0,0,
5,1,0,0,0,0,0,0,10,0,0,0,8,0,0,0,17,1,0,0,
0,0,0,0,10,0,0,0,7,0,0,0,25,1,0,0,0,0,0,0,
10,0,0,0,8,0,0,0,50,1,0,0,0,0,0,0,10,0,0,0,
8,0,0,0,62,1,0,0,0,0,0,0,10,0,0,0,8,0,0,0,
71,1,0,0,0,0,0,0,10,0,0,0,8,0,0,0,83,1,0,0,
0,0,0,0,10,0,0,0,8,0,0,0,95,1,0,0,0,0,0,0,
10,0,0,0,8,0,0,0,125,1,0,0,0,0,0,0,10,0,0,0,
8,0,0,0,137,1,0,0,0,0,0,0,10,0,0,0,8,0,0,0,
154,1,0,0,0,0,0,0,10,0,0,0,8,0,0,0,166,1,0,0,
0,0,0,0,10,0,0,0,8,0,0,0,178,1,0,0,0,0,0,0,
10,0,0,0,8,0,0,0,190,1,0,0,0,0,0,0,10,0,0,0,
8,0,0,0,202,1,0,0,0,0,0,0,10,0,0,0,8,0,0,0,
214,1,0,0,0,0,0,0,10,0,0,0,8,0,0,0,226,1,0,0,
0,0,0,0,10,0,0,0,8,0,0,0,238,1,0,0,0,0,0,0,
10,0,0,0,8,0,0,0,250,1,0,0,0,0,0,0,10,0,0,0,
8,0,0,0,6,2,0,0,0,0,0,0,10,0,0,0,8,0,0,0,
18,2,0,0,0,0,0,0,10,0,0,0,8,0,0,0,30,2,0,0,
0,0,0,0,10,0,0,0,8,0,0,0,42,2,0,0,0,0,0,0,
10,0,0,0,8,0,0,0,54,2,0,0,0,0,0,0,10,0,0,0,
8,0,0,0,66,2,0,0,0,0,0,0,10,0,0,0,8,0,0,0,
78,2,0,0,0,0,0,0,10,0,0,0,8,0,0,0,90,2,0,0,
0,0,0,0,10,0,0,0,8,0,0,0,102,2,0,0,0,0,0,0,
10,0,0,0,8,0,0,0,114,2,0,0,0,0,0,0,10,0,0,0,
8,0,0,0,126,2,0,0,0,0,0,0,10,0,0,0,8,0,0,0,
138,2,0,0,0,0,0,0,10,0,0,0,8,0,0,0,150,2,0,0,
0,0,0,0,10,0,0,0,8,0,0,0,162,2,0,0,0,0,0,0,
10,0,0,0,8,0,0,0,174,2,0,0,0,0,0,0,10,0,0,0,
8,0,0,0,186,2,0,0,0,0,0,0,10,0,0,0,8,0,0,0,
198,2,0,0,0,0,0,0,10,0,0,0,8,0,0,0,210,2,0,0,
0,0,0,0,10,0,0,0,8,0,0,0,222,2,0,0,0,0,0,0,
10,0,0,0,8,0,0,0,234,2,0,0,0,0,0,0,10,0,0,0,
8,0,0,0,246,2,0,0,0,0,0,0,10,0,0,0,8,0,0,0,
2,3,0,0,0,0,0,0,10,0,0,0,8,0,0,0,14,3,0,0,
0,0,0,0,10,0,0,0,8,0,0,0,28,3,0,0,0,0,0,0,
10,0,0,0,8,0,0,0,41,3,0,0,0,0,0,0,10,0,0,0,
8,0,0,0,60,3,0,0,0,0,0,0,10,0,0,0,8,0,0,0,
67,3,0,0,0,0,0,0,10,0,0,0,8,0,0,0,44,0,0,0,
0,0,0,0,0,0,0,0,4,0,0,0,64,0,0,0,0,0,0,0,
0,0,0,0,4,0,0,0,80,0,0,0,0,0,0,0,0,0,0,0,
4,0,0,0,96,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,
112,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,128,0,0,0,
0,0,0,0,0,0,0,0,4,0,0,0,144,0,0,0,0,0,0,0,
0,0,0,0,4,0,0,0,160,0,0,0,0,0,0,0,0,0,0,0,
4,0,0,0,176,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,
192,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,208,0,0,0,
0,0,0,0,0,0,0,0,4,0,0,0,224,0,0,0,0,0,0,0,
0,0,0,0,4,0,0,0,240,0,0,0,0,0,0,0,0,0,0,0,
4,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,4,0,0,0,
16,1,0,0,0,0,0,0,0,0,0,0,4,0,0,0,32,1,0,0,
0,0,0,0,0,0,0,0,4,0,0,0,48,1,0,0,0,0,0,0,
0,0,0,0,4,0,0,0,64,1,0,0,0,0,0,0,0,0,0,0,
4,0,0,0,80,1,0,0,0,0,0,0,0,0,0,0,4,0,0,0,
96,1,0,0,0,0,0,0,0,0,0,0,4,0,0,0,112,1,0,0,
0,0,0,0,0,0,0,0,4,0,0,0,20,0,0,0,0,0,0,0,
10,0,0,0,9,0,0,0,24,0,0,0,0,0,0,0,1,0,0,0,
4,0,0,0,72,0,0,0,0,0,0,0,1,0,0,0,4,0,0,0,
0,46,100,101,98,117,103,95,97,98,98,114,101,118,0,46,116,101,120,116,
0,46,114,101,108,46,66,84,70,46,101,120,116,0,46,100,101,98,117,103,
95,114,97,110,103,101,115,0,46,100,101,98,117,103,95,115,116,114,0,46,
114,101,108,46,100,101,98,117,103,95,105,110,102,111,0,98,112,102,95,112,
114,111,103,0,46,108,108,118,109,95,97,100,100,114,115,105,103,0,46,114,
101,108,46,100,101,98,117,103,95,108,105,110,101,0,46,114,101,108,46,100,
101,98,117,103,95,102,114,97,109,101,0,46,100,101,98,117,103,95,108,111,
99,0,103,101,116,95,114,101,103,115,46,99,0,46,115,116,114,116,97,98,
0,46,115,121,109,116,97,98,0,46,66,84,70,0,76,66,66,48,95,50,
0,76,66,66,48,95,49,0,46,114,111,100,97,116,97,46,115,116,114,49,
46,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,153,0,0,0,3,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,176,24,0,0,
0,0,0,0,203,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,0,0,0,
1,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
64,0,0,0,0,0,0,0,216,1,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
188,0,0,0,1,0,0,0,50,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,24,2,0,0,0,0,0,0,6,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
0,0,0,0,131,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,30,2,0,0,0,0,0,0,6,1,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,36,3,0,0,0,0,0,0,
23,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,63,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,59,4,0,0,
0,0,0,0,98,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,59,0,0,0,
9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
160,18,0,0,0,0,0,0,144,4,0,0,0,0,0,0,18,0,0,0,
6,0,0,0,8,0,0,0,0,0,0,0,16,0,0,0,0,0,0,0,
34,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,157,7,0,0,0,0,0,0,240,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,48,0,0,0,1,0,0,0,48,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,141,8,0,0,0,0,0,0,131,1,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,169,0,0,0,1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,16,10,0,0,0,0,0,0,
30,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,46,15,0,0,
0,0,0,0,128,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,0,0,0,
9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
48,23,0,0,0,0,0,0,80,1,0,0,0,0,0,0,18,0,0,0,
11,0,0,0,8,0,0,0,0,0,0,0,16,0,0,0,0,0,0,0,
118,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,176,16,0,0,0,0,0,0,40,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,114,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,128,24,0,0,0,0,0,0,32,0,0,0,
0,0,0,0,18,0,0,0,13,0,0,0,8,0,0,0,0,0,0,0,
16,0,0,0,0,0,0,0,102,0,0,0,1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,216,16,0,0,0,0,0,0,
166,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,98,0,0,0,9,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,160,24,0,0,
0,0,0,0,16,0,0,0,0,0,0,0,18,0,0,0,15,0,0,0,
8,0,0,0,0,0,0,0,16,0,0,0,0,0,0,0,84,0,0,0,
3,76,255,111,0,0,0,128,0,0,0,0,0,0,0,0,0,0,0,0,
176,24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,0,0,0,
0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
161,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,128,17,0,0,0,0,0,0,32,1,0,0,0,0,0,0,
1,0,0,0,11,0,0,0,8,0,0,0,0,0,0,0,24,0,0,0,
0,0,0,0,
};


void write_4bit(unsigned char n)
{
	if (n < 10 && n >= 0) {
		uart1_write(n + 48);
	} else if (10 <= n && n < 16) {
		uart1_write(n - 10 + 65);
	} else {
		printf("NOT 4bit!\n");
	}
}
void write_byte_as_hex(unsigned char b)
{
	write_4bit(b >> 4);
    write_4bit(b % 16);
}
int write_packet(unsigned char *buf, int len)
{
	uart1_write('$');
	for (int i = 0; i < len; i++) {
		uart1_write(buf[i]);
	}
	uart1_write('#');
	unsigned char checksum;
	size_t i;
	for (i = 0, checksum = 0; i < len; ++i)
		checksum += buf[i];
	write_byte_as_hex(checksum);
}
unsigned char packet_buffer[PACKET_BUFFER_SIZE] = { 0 };
void print_packet_buffer(){
	printf("Full Packet data (in a disgusting form because printf doesn't support %c):\n");
	for (size_t i = 0; i < PACKET_BUFFER_SIZE; i++) {
		printf("%x ", packet_buffer[i]);
	}
}
void flush_packet_buffer()
{
	for (size_t i = 0; i < PACKET_BUFFER_SIZE; i++) {
		packet_buffer[i] = 0;
	}
}
void read_packet()
{
	flush_packet_buffer();
	size_t end_count = PACKET_BUFFER_SIZE;
	for (size_t i = 0; end_count; i++, end_count--) {
		packet_buffer[i] = uart1_read();
		if (packet_buffer[i] == '#') {
			end_count = 3;
		}
	}
	uart1_write('+');
	printf("Received Packet:\n%s\n", packet_buffer);
}
void process_packet()
{
	int daoler = -1; //dollar
	for (size_t i = 0; i < PACKET_BUFFER_SIZE; i++) {
		if (packet_buffer[i] == '$')
			daoler = i;
	}
    if (packet_buffer[daoler + 1] == '?') {
		write_packet("S05",3);
	}else if (packet_buffer[daoler + 1] == 'g') {
		print_packet_buffer();
		uart1_write('$');
		for (size_t i = 0; i < 512+16; i++)
		{
			uart1_write('0');
		}
		uart1_write('#');
		uart1_write('0');
		uart1_write('0');

		
	} else if (packet_buffer[daoler + 1] == 'm') {
		printf("MMM command");
	} else if (packet_buffer[daoler + 1] == 'q') {
        write_packet("", 0);
		//write_packet(stub_features, strlen(stub_features));
	} else if (packet_buffer[daoler + 1] == 'v') {
		if (packet_buffer[daoler + 2] == 'T' && packet_buffer[daoler + 3] == 'R'){ // vTR = v_Tracepoint_then_get_Registers
			unsigned *p = (unsigned *)get_regs;
			int prog_size = 7744; //hardcoded. this is so stupid
			struct bpf_map_fd_entry map_array[] = {}; // empty
			int bpf_fd = bpf_prog_load_ex(p, prog_size, map_array, 0);
			const char *target = "kprobe$<linux_syscall::Syscall>::sys_openat";//todo: any str
			uint32_t str_len = strlen(target);
			bpf_prog_attach(target, str_len, bpf_fd);
			write_packet("OK",2);
			if (fork()==0){
				int n = 4;
				printf("busy loop for %d times\n", n);
				while (n) {
					printf("open from user\n");
					int fd = open("./ebpf_user_maptest", O_RDONLY);
					sleep(1000);
					n--;
				}
				exit(0);
			}else{

			}

		}
	}else if (packet_buffer[daoler + 1] == 'H') {
        write_packet("", 0);
        // if(packet_buffer[daoler + 2] == 'g'){
        //     write_packet("OK", 2);
        // }
    } 
    else {
		printf("Unsupported command %d\n", packet_buffer[daoler + 1]);
		print_packet_buffer();
        write_packet("", 0);
	}
}
int main()
{
	while (1) {
		read_packet();
		process_packet();
		flush_packet_buffer();
	}
}