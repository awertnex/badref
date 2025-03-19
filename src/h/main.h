#ifndef BAD_REFERENCER_H

#include <types.h>

// ---- variables --------------------------------------------------------------
extern u16 state;
extern u8 ModeDebug;

enum BadStates
{
	STATE_RUNNING =				0x001,
	STATE_PLAYBACK =			0x002,
	STATE_TOOLBAR =				0x004,
	STATE_PANE_OUTLINER =		0x008,
	STATE_PANE_PLAYBACK =		0x010,
	STATE_CONTENTS_AVAILABLE =	0x020,

}; /* BadStates */

// ---- signatures -------------------------------------------------------------
void listen_input();

#define BAD_REFERENCER_H
#endif
