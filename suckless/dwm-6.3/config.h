/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     	/* 0 means no systray */
static const unsigned int gappih    = 14;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 14;       /* vert inner gap between windows */
static const unsigned int gappoh    = 14;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 14;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:size=11", "Noto Color Emoji:pixelsize=11:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrains Mono:size=11";
static const char col_gray1[]       = "#1a1b26";
static const char col_gray2[]       = "#1a1b26";
static const char col_gray3[]       = "#f8f8f2";
static const char col_gray4[]       = "#f8f8f2";
static const char col_gray5[]       = "#aaaaaa";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray5  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    title       tags mask     isfloating   monitor */
	{ "Gimp",		NULL,	    NULL,	0,	    	1,	    -1 },
	{ "Google-chrome",	NULL,       NULL,       1 << 1,     	0,          -1 },
	{ "Spotify",	  	NULL,       NULL,       1 << 2,     	0,          -1 },
	{ "heroic",	  	NULL,       NULL,       1 << 3,     	0,          -1 },
	{ "Steam",		NULL,       NULL,       1 << 3,     	0,          -1 },
	{ "TeamViewer",	  	NULL,       NULL,       1 << 4,     	1,          -1 },
	{ "Signal",		NULL,       NULL,       1 << 5,     	0,          -1 },
	{ "Galculator",		NULL,       NULL,	0,		1,	    -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,	                XK_r,      spawn,          SHCMD("rofi -modi drun -show drun -show-icons") },
	{ MODKEY,	                XK_period, spawn,          SHCMD("rofi -modi emoji -show emoji") },
	{ MODKEY,			XK_comma,  spawn,	   SHCMD("rofi -show calc -modi calc -no-show-match -no-sort") },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,			XK_w,	   spawn,	   SHCMD("google-chrome-stable") },
	{ MODKEY,			XK_m,	   spawn,	   SHCMD("spotify") },
	{ MODKEY,			XK_p,	   spawn,	   SHCMD("steam") },
	{ MODKEY|ShiftMask,		XK_p,	   spawn,	   SHCMD("heroic") },
	{ MODKEY,			XK_u,	   spawn,	   SHCMD("teamviewer") },
	{ MODKEY,			XK_i,	   spawn,	   SHCMD("signal-desktop") },
	{ MODKEY,			XK_g,	   spawn,	   SHCMD("mousepad") },
	{ MODKEY,			XK_e,	   spawn,	   SHCMD("thunar") },
	{ MODKEY|ShiftMask,		XK_c,	   spawn,          SHCMD("alacritty -e calcurse") },
	{ MODKEY|ShiftMask,		XK_e,	   spawn,	   SHCMD("alacritty -e ranger") },
	{ MODKEY,			XK_F4,	   spawn,	   SHCMD("feh --randomize --bg-fill ~/Dropbox/Kuvat/Taustakuvat/*") },
	{ MODKEY,			XK_F8,	   spawn,	   SHCMD("alacritty -e htop") },
	{ MODKEY|ShiftMask,		XK_x,	   spawn,	   SHCMD("/home/antti/.scripts/power") },
	{ MODKEY|ShiftMask,		XK_w,	   spawn,	   SHCMD("/home/antti/.scripts/get-weather") },
	{ MODKEY|ShiftMask,		XK_n,	   spawn,	   SHCMD("/home/antti/.config/rofi/rofi-network-manager.sh") },
	{ MODKEY|ShiftMask,		XK_u,	   spawn,	   SHCMD("/home/antti/.scripts/get-updates") },
	{ MODKEY,			XK_v,	   spawn,	   SHCMD("/home/antti/.scripts/get-volume") },
	{ MODKEY,			XK_s,	   spawn,	   SHCMD("/home/antti/.scripts/get-song") },
	{ MODKEY|ControlMask,           XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,   rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Right,  rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Left,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Right,  focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_plus,   zoom,           {0} },
	{ MODKEY,			XK_a,	   togglegaps,	   {0} },
	{ MODKEY|ShiftMask,		XK_a,	   defaultgaps,	   {0} },
	{ MODKEY|ShiftMask,		XK_b,	   incrgaps,       {.i = +3 } },
	{ MODKEY|ShiftMask,		XK_v,	   incrgaps,	   {.i = -3 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_F1,     setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_F2,     setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,	                XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,		XK_s,	   togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,			XK_z,      spawn,	   SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.PlayPause") },
	{ MODKEY,			XK_c,      spawn,	   SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Next") },
	{ MODKEY,			XK_x,      spawn,	   SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Previous") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
	{ 0, XF86XK_AudioMute,			   spawn,	   SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") }, 
	{ 0, XF86XK_AudioRaiseVolume,		   spawn,	   SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") }, 
	{ 0, XF86XK_AudioLowerVolume,		   spawn,	   SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") }, 
	{ 0, XF86XK_Calculator,			   spawn,	   SHCMD("galculator") },
	{ 0, XK_Print,				   spawn,	   SHCMD("xfce4-screenshooter") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
