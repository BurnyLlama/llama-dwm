/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 1;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad 			= 4; 		/* Vertical outside pading for statbar */
static const int sidepad 			= 4; 		/* Side -""- */
static const int horizpadbar        = 6;        /* horizontal padding for statusbar */
static const int vertpadbar         = 6;        /* vertical padding for statusbar */
static const char *fonts[]          = { "Noto Sans:size=12", "Noto Color Emoji" };
static const char dmenufont[]       = "Noto Sans:size=10";
/*static const char col_gray1[]       = "#181818";
static const char col_gray2[]       = "#232323";
static const char col_gray3[]       = "#4b4bff"; //  Keeping default names for compatability (LAZINESS)... :/  
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#4b4bff";*/
static const unsigned int baralpha = 0x88;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#ddddff", "#181818", "#181818" },
	[SchemeSel]  = { "#ffffff", "#4b4bff",  "#4b4bff"  },
	[SchemeStatus]  = { "#ddddff", "#181818",  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { "#eeeeee", "#4b4bff",  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { "#ddddff", "#181818",  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { "#ffffff", "#111111",  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { "#eeeeee", "#000000",  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeStatus]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]  = { OPAQUE, OPAQUE, borderalpha },
	[SchemeTagsNorm]  = { OPAQUE, baralpha, borderalpha },
	[SchemeInfoSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeInfoNorm]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "H", "T", "W", "C", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals, 0 makes it aestechillay good, I think. */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ NULL, 	  NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu-app-runner"};
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,	spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, 	spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      	togglebar,      {0} },
	{ MODKEY,                       XK_Left,	focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Right,	focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Up,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_Down,	incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,				XK_Left,	setmfact,       {.f = -0.005} },
	{ MODKEY|ShiftMask,				XK_Right,	setmfact,       {.f = +0.005} },
	{ MODKEY|ShiftMask,				XK_Return,	zoom,           {0} },
	{ MODKEY,                       XK_Tab,		view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,		killclient,     {0} },
	{ MODKEY,                       XK_t,		setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,		setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_m,		setlayout,      {.v = &layouts[2]} },
	{ ALTKEY,						XK_space,  	cyclelayout,    {.i = -1 } },
	{ ALTKEY|ShiftMask,           	XK_space, 	cyclelayout,    {.i = +1 } },
	{ ALTKEY|ControlMask,           XK_space,	setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,	togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,		togglefullscr,  {0} },
	{ MODKEY,                       XK_0,		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,		tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,	focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,	focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,	tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,	tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,	setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_plus,	setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,	setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_r,      quit,           {1} }, 
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

