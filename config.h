/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx    = 0;        /* border pixel of windows */
static const unsigned int gappx       = 5;        /* gaps between windows */
static const unsigned int snap        = 0;       /* snap pixel */
static const int showbar              = 1;        /* 0 means no bar */
static const int topbar               = 1;        /* 0 means bottom bar */
static const char *fonts[]            = { "DejaVu:size=10" };
static const char dmenufont[]         = "DejaVu:size=12";
static const unsigned int baralpha    = 0;
static const unsigned int borderalpha = OPAQUE;
static const char col_black[]         = "#030303";
static const char col_blue[]          = "#4169e1";
static const char col_red[]           = "#FF0000";
static const char col_white[]         = "#FFFFFF";
static const char *colors[][3]        = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_blue, col_black, col_black },
        [SchemeSel]  = { col_red, col_black, col_black },
};
static const unsigned int alphas[][3] = {
        [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
        [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2" };

static const char ptagf[] = "[%s %s]";	/* format of a tag label */
static const char etagf[] = "[%s]";	/* format of an empty tag */
static const int lcaselbl = 0;		/* 1 means make tag label lowercase */

static const Rule rules[] = {NULL};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = {"dmenu_run", NULL };
static const char *termcmd[] = { "terminator", NULL};

static const Key keys[] = {
	/* modifier                     key        	function        argument */
	{ MODKEY,			XK_p,		spawn,		SHCMD ( "dmenu_run")},
	{ MODKEY|ShiftMask,	        XK_Return, 	spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      	spawn,          SHCMD ( "firefox" ) },
	{ 0,				XK_F2,		spawn,		SHCMD ("brightnessctl --device=asus\:\:kbd_backlight set 0")},
	{ 0, 				XK_F3,		spawn,		SHCMD ("brightnessctl --device=asus\:\:kbd_backlight set 3")},
	{ 0,                            XK_F8,	 	spawn,          SHCMD ("brightnessctl s 5%+")},
	{ 0,				XK_F7,		spawn,          SHCMD ("brightnessctl s 5%-")},
	{ 0,                            0x1008ff11, 	spawn,          SHCMD ("amixer sset Master 5%- unmute")},
	{ 0,                            0x1008ff12, 	spawn,          SHCMD ("amixer sset Master $(amixer get Master | grep -q '\\[on\\]' && echo 'mute' || echo 'unmute')")},
	{ 0,                            0x1008ff13, 	spawn,          SHCMD ("amixer sset Master 5%+ unmute")},
	{ MODKEY,                       XK_b,      	togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_c,      	killclient,     {0} },
	{ MODKEY,                       XK_0,      	view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      	tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      	0)
	TAGKEYS(                        XK_2,                      	1)
	{ MODKEY,		        XK_q,      	quit,           {0} },
	{ MODKEY,			XK_s,		spawn,		SHCMD ("systemctl poweroff")},
	{ MODKEY,			XK_r,		spawn,		SHCMD ("systemctl reboot")},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

