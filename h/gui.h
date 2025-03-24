#ifndef GUI_H

#include <raylib.h>

#ifndef VECTOR2_TYPES
    #define VECTOR2_TYPES
#endif
#ifndef VECTOR4_TYPES
    #define VECTOR4_TYPES
#endif

#include <defines.h>

// ---- definitions ------------------------------------------------------------
#define WIDTH 1280
#define HEIGHT 720
#define MARGIN 3
#define color(r, g, b, v, a) (Color){((f32)r/255)*v, ((f32)g/255)*v, ((f32)b/255)*v, a}

enum SortTypes
{
	SORT_LIST =		0x00,
	SORT_BOXES =	0x01,
}; /* SortTypes */

enum ButtonStates
{
	BUTTON_INACTIVE	 = 0,
	BUTTON_LISTENING = 1,
	BUTTON_PRESSED	 = 2,
	BUTTON_RELEASED	 = 3,
}; /* ButtonStates */

typedef struct BadPane
{
	v2i16 pos;
	v2i16 scl;
	u8 lyr;
} BadPane;

typedef struct BadPaneGrid
{
	u8 sort_type;
	u8 lyr;
	u8 button_states[1024];
	u16 items;			// list item count
	f32 spacing;		// space between items (no MARGIN applied)
	v2i16 unit;			// scale of each item
} BadPaneGrid;

typedef struct BadVertex
{
	v2i16 tl, br;
} BadVertex;

typedef struct Images
{
    Image file_collapsed;
    Image file_expanded;
    Image file_loaded;
    Image file_refresh;
    Image file_settings;
    Image file_usable;

    Image playback_back;
    Image playback_fwd;
    Image playback_head;
    Image playback_loop_off;
    Image playback_loop_on;
    Image playback_paused;
    Image playback_playing;
} Images;

// ---- colors -----------------------------------------------------------------
#define COL_BASE		color(0xFF, 0xFF, 0xFF, 0x36, 0xFF)
#define COL_PANE		color(0xFF, 0xFF, 0xFF, 0x28, 0xFF)
#define COL_ITEM		color(0xFF, 0xFF, 0xFF, 0x26, 0xFF)
#define COL_ITEM_HOVER	color(0xFF, 0xFF, 0xFF, 0x30, 0xFF)
#define COL_ITEM_PRESS	color(0xFF, 0xFF, 0xFF, 0x22, 0xFF)
#define COL_FFFF		color(0xFF, 0xFF, 0xFF, 0xFF, 0xFF)
#define COL_TEXT_MAIN	color(0xFF, 0xFF, 0xFF, 0xC0, 0xFF)
#define COL_TEXT_DARK	color(0xFF, 0xFF, 0xFF, 0x20, 0xFF)

// ---- variables --------------------------------------------------------------
extern Vector2 cursor;
#define detect_cursor cursor = GetMousePosition();

extern v2u16 ren_scl;
extern u16 cursor_lyr;
struct badFonts
{
	u8 size_headers;
	u8 size_general;
	Font regular, bold, term;
};
extern BadPane pane_toolbar;
extern BadPane pane_outliner;
extern BadPane pane_playback;
extern BadPane pane_playlist;
extern BadPaneGrid pane_grid_outliner;
extern BadPaneGrid pane_grid_playback;
extern BadPaneGrid pane_grid_playlist;
extern BadVertex vertex_grid_outliner;
extern BadVertex vertex_grid_playback;
extern BadVertex vertex_grid_playlist;
extern f32 margin_item;

#define IMAGE_COUNT 32
extern Image Img[IMAGE_COUNT];

// ---- signatures -------------------------------------------------------------
void init_gui();
void update_gui();
void free_gui();
void draw_list_items(BadPaneGrid *badPaneGrid, BadPane *parentPane, BadVertex *badVertex);
void draw_text(Font font, const str *str, v2i16 pos, f32 font_size, f32 spacing, Color tint, v2u8 center);
float get_str_width(Font font, const str *str, f32 font_size, f32 spacing);
b8 detect_cursor_overlap(v2i16 tl, v2i16 br, u8 lyr, u8 *button_state);
void evaluate_cursor_layer(u8 lyr);

#define GUI_H
#endif
