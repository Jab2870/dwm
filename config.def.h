/* See LICENSE file for copyright and license details. */

//The media and volume keys
//usr/include/X11/XF86keysym.h
#include "X11/XF86keysym.h"

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Iosevka:size=10" };
static const char dmenufont[]       = "Iosevka:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                  instance    title                 tags mask     isfloating   isterminal noswallow  nofakefullscreen   monitor */
	//{ "Gimp",               NULL,       NULL,                 0,            0,           0,         0,         0,                 -1 },
	//{ "Firefox",            NULL,       NULL,                 1 << 8,       0,           0,         0,         0,                 -1 },
	{ "xterm-256color",       NULL,       NULL,                 0,            0,           1,         1,         0,                 -1 },
	{ "Thunderbird",          NULL,       NULL,                 1 << 8 ,      0,           0,         0,         0,                 -1 },
	{ NULL,                   NULL,       "Event Tester",       0,            0,           0,         1,         0,                 -1 }

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static int attachbelow = 0;    /* 1 means attach after the currently active window */

#include "tcl.c"
#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|||",      tcl },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
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
static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "folder-shell", NULL };

static const char *lfcmd[]  = { "folder-shell", "lf", NULL };

static const char *fullscreenshot[] = { "screenshot",  NULL };
static const char *activescreenshot[] = { "screenshot", "window", NULL };
static const char *selectscreenshot[] = { "screenshot", "select", NULL };

static const char *greenclip[] = { "rofi", "-modi", "clipboard:greenclip print", "-show", "clipboard", "-run-command", "{cmd}", NULL };

static const char *qutebrowser[] = { "qutebrowser", NULL };
static const char *surf[] = { "tabbed", "-c", "surf", "-e", NULL };
static const char *chromium[] = { "chromium", NULL };
static const char *bigchromium[] = { "chromium", "--force-device-scale-factor=2", NULL };
static const char *firefox[] = { "firefox-developer-edition", NULL };

static const char *date[] = { "datetime", NULL };
static const char *battery[] = { "battery", NULL };

static const char *unicode[] = { "unicode-character-select", NULL };
static const char *youtube[] = { "open-youtube", NULL };

static const char *playpause[] = { "playerctl", "play-pause", NULL };

static const char *logout[] = { "rofi-shutdown", NULL };

static const char *offlineArchWiki[] = { "offline-aw", NULL };
static const char *manPages[] = { "man-page-pdf", NULL };
static const char *ports[] = { "ports", NULL };

static const char *project[] = { "project", "switch", "--rofi", NULL };
static const char *whichproject[] = { "project", "current", "--notify", NULL };

static const char *screenlayout[] = { "screenlayout", NULL };

static const char *pass[] = { "password-manager", NULL };

static const char *volumeUp[] = { "volume", "up", NULL };
static const char *volumeDown[] = { "volume", "down", NULL };
static const char *volumeToggle[] = { "volume", "toggle", NULL };

static const char *setBackgroundRandom[] = { "rofi-background", "--earth", NULL };
static const char *backgroundDetails[] = { "background", "--only-notify", NULL };

static const char *unity_hud[] = { "hud-menu.py" };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key                        function        argument */
	{ MODKEY,                       XK_p,                      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,                 spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_Return,                 spawn,          {.v = lfcmd } },
	{ MODKEY,                       XK_b,                      togglebar,      {0} },
	{ MODKEY,                       XK_j,                      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,                      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_i,                      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,                      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,                      spawn,          {.v = logout} },
	{ MODKEY|ShiftMask,             XK_Return,                 zoom,           {0} },
	{ MODKEY,                       XK_Tab,                    toggleAttachBelow,           {0} },
	{ MODKEY,                       XK_q,                      killclient,     {0} },
	{ MODKEY,                       XK_t,                      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,                      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_t,                      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_f,                      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_f,                      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_space,                  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                  togglefloating, {0} },
	{ MODKEY,                       XK_0,                      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                 tagmon,         {.i = +1 } },
	{ 0,                            XK_Print,                  spawn,          {.v = fullscreenshot } },
	{ ControlMask,                  XK_Print,                  spawn,          {.v = activescreenshot } },
	{ ShiftMask,                    XK_Print,                  spawn,          {.v = selectscreenshot } },
	{ 0,                            XF86XK_AudioPlay,          spawn,          {.v = playpause } },
	{ MODKEY|ShiftMask,             XK_d,                      spawn,          {.v = date } },
	{ MODKEY|ShiftMask,             XK_b,                      spawn,          {.v = battery} },
	{ MODKEY|ShiftMask,             XK_Insert,                 spawn,          {.v = greenclip } },
	//Applications
	{ MODKEY|ShiftMask,             XK_q,                      spawn,          {.v = qutebrowser } },
	{ MODKEY          ,             XK_s,                      spawn,          {.v = surf } },
	{ MODKEY,                       XK_c,                      spawn,          {.v = firefox } },
	{ MODKEY|ShiftMask,             XK_c,                      spawn,          {.v = chromium } },
	//Dmenu / Rofi
	{ MODKEY,                       XK_u,                      spawn,          {.v = unicode } },
	{ MODKEY,                       XK_y,                      spawn,          {.v = youtube } },
	{ MODKEY,                       XK_a,                      spawn,          {.v = offlineArchWiki } },
	{ MODKEY|ShiftMask,             XK_a,                      spawn,          {.v = screenlayout } },
	{ MODKEY|ShiftMask,             XK_m,                      spawn,          {.v = manPages } },
	{ MODKEY|ShiftMask,             XK_p,                      spawn,          {.v = ports } },
	{ MODKEY,                       XK_w,                      spawn,          {.v = whichproject } },
	{ MODKEY|ShiftMask,             XK_w,                      spawn,          {.v = project } },
	{ MODKEY,                       XK_d,                      spawn,          {.v = pass } },
	{ MODKEY,                       XK_x,                      spawn,          {.v = unity_hud } },
	//Background
	{ MODKEY,                       XK_e,                      spawn,          {.v = setBackgroundRandom } },
	{ MODKEY|ControlMask,           XK_e,                      spawn,          {.v = backgroundDetails } },
	//Special keys
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,          {.v = volumeUp } },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,          {.v = volumeDown } },
	{ 0,                            XF86XK_AudioMute,          spawn,          {.v = volumeToggle } },
	TAGKEYS(                        XK_1,                                      0)
	TAGKEYS(                        XK_2,                                      1)
	TAGKEYS(                        XK_3,                                      2)
	TAGKEYS(                        XK_4,                                      3)
	TAGKEYS(                        XK_5,                                      4)
	TAGKEYS(                        XK_6,                                      5)
	TAGKEYS(                        XK_7,                                      6)
	TAGKEYS(                        XK_8,                                      7)
	TAGKEYS(                        XK_9,                                      8)
	{ MODKEY|ShiftMask,             XK_r,                      quit,           {0} },
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

