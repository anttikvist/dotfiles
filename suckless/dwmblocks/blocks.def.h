//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/				/*Update Interval*/	/*Update Signal*/
	{"Oulu: ",	"~/.scripts/weather",			1800,			0},
	{"",		"~/.scripts/updates",			1800,			0},
	{"",		"~/.scripts/memory",			5,			0},
	{"",		"~/.scripts/disk",			30,			0},
	{"",		"~/.scripts/battery",			10,			0},
	{"", 		"~/.scripts/volume",			0,			10},	
	{"", 		"date '+%a %d. %Bta %H:%M'",		5,			0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;