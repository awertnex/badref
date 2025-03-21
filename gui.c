/* ==== _section table =========================================================
_section_gui_setup =============================================================
_section_drawing ===============================================================
_section_logic =================================================================
*/

/* TASKS:    [!]: done!    [x]: deleted
 * [ ] evaluate layers under cursor and assign highest layer to cursor
 * [ ] fix final list item hover dimensions
 * [ ] implement scrolling
 * [x] navigate into and out of directories (Mar.18.2025)
 * [ ] display file info: name, extention, audio length, versions available
 * [ ] do anti-aliasing
 */

#include <stdio.h>
#include <string.h>

#include <raylib.h>
#include <rlgl.h>

#include "h/gui.h"
#include "h/dir.h"
#include "h/main.h"

// ---- variables --------------------------------------------------------------
Vector2 cursor;
v2u16 ren_scl;
u16 cursor_lyr = 0;
struct badFonts bad_fonts =
{
	.size_headers = 28,
	.size_general = 18,
};
BadPane pane_toolbar;
BadPane pane_outliner;
BadPane pane_playback;
BadPane pane_playlist;
BadPaneGrid pane_grid_outliner =
{
	.sort_type = 0,
	.lyr = 1,
	.button_states = {0},
	.items = 0,
	.spacing = 3,
};
BadPaneGrid pane_grid_playback =
{
	.sort_type = 0,
	.lyr = 1,
	.button_states = {0},
	.items = 0,
	.spacing = 0,
};
BadPaneGrid pane_grid_playlist =
{
	.sort_type = 0,
	.lyr = 1,
	.button_states = {0},
	.items = 0,
	.spacing = 1,
};
BadVertex vertex_grid_outliner = {0};
BadVertex vertex_grid_playback = {0};
BadVertex vertex_grid_playlist = {0};
f32 margin_item = 10;

// =============================================================================
// ==== _section_gui_setup =====================================================
// =============================================================================
void init_gui()
{
	bad_fonts.regular = LoadFont("fonts/natural_mono_regular.ttf");
	bad_fonts.bold = LoadFont("fonts/natural_mono_bold.ttf");
	bad_fonts.term = LoadFont("fonts/terminal_f4.ttf");

	// ---- layer: 0 -----------------------------------------------------------
	pane_outliner.pos = (v2i16){0};
	pane_outliner.scl = (v2i16){320, HEIGHT};
	pane_outliner.lyr = 0;

	pane_playlist.pos = (v2i16){320, 0};
	pane_playlist.scl = (v2i16){WIDTH - 320, HEIGHT};
	pane_playlist.lyr = 0;

	pane_playback.pos = (v2i16){0, HEIGHT - 150};
	pane_playback.scl = (v2i16){WIDTH, 150};
	pane_playback.lyr = 0;

	// ---- layer: 1 -----------------------------------------------------------
	pane_grid_outliner.unit = (v2i16){pane_outliner.scl.x - (margin_item*2), 25};
}

void update_gui()
{
	ren_scl = (v2u16){GetRenderWidth(), GetRenderHeight()};

	// ---- set pane dimensions ------------------------------------------------
	pane_outliner.scl =
		(v2i16){
			320,
		ren_scl.y - ((pane_playback.scl.y + MARGIN)*(bool)(state & STATE_PANE_PLAYBACK))
		};
	pane_playlist.pos =
		(v2i16){
			(pane_outliner.scl.x + MARGIN)*(bool)(state & STATE_PANE_OUTLINER), 0
		};
	pane_playlist.scl =
		(v2i16){
			ren_scl.x - (pane_outliner.scl.x + MARGIN)*(bool)(state & STATE_PANE_OUTLINER),
			ren_scl.y - (pane_playback.scl.y + MARGIN)*(bool)(state & STATE_PANE_PLAYBACK)
		};
	pane_playback.pos = (v2i16){0, ren_scl.y - pane_playback.scl.y};
	pane_playback.scl = (v2i16){ren_scl.x, 80};

	// ---- set debug vertices -------------------------------------------------
	vertex_grid_outliner.tl =
		(v2i16){
			pane_outliner.pos.x + margin_item,
			pane_outliner.pos.y + margin_item
		};
	vertex_grid_outliner.br =
		(v2i16){
			pane_outliner.pos.x + pane_outliner.scl.x - margin_item,
			pane_outliner.pos.y + pane_outliner.scl.y - margin_item,
		};

	vertex_grid_playback.tl =
		(v2i16){
			pane_playback.pos.x + margin_item,
			pane_playback.pos.y + margin_item
		};
	vertex_grid_playback.br =
		(v2i16){
			pane_playback.pos.x + pane_playback.scl.x - margin_item,
			pane_playback.pos.y + pane_playback.scl.y - margin_item,
		};

	vertex_grid_playlist.tl =
		(v2i16){
			pane_playlist.pos.x + margin_item,
			pane_playlist.pos.y + margin_item
		};
	vertex_grid_playlist.br =
		(v2i16){
			pane_playlist.pos.x + pane_playlist.scl.x - margin_item,
			pane_playlist.pos.y + pane_playlist.scl.y - margin_item,
		};

	// ---- pane: outliner -----------------------------------------------------
	pane_grid_outliner.items = file_count;
	if (state & STATE_PANE_OUTLINER)
	{
		if (pane_grid_outliner.button_states[0] == 0)
			memset(pane_grid_outliner.button_states, 1 ,sizeof(pane_grid_outliner.button_states));
		DrawRectangleV(
				(Vector2){0},
				(Vector2){pane_outliner.scl.x, pane_outliner.scl.y},
				COL_PANE);
		draw_list_items(
				&pane_grid_outliner,
				&pane_outliner,
				&vertex_grid_outliner);

		for (u16 i = 0; i < sizeof(pane_grid_outliner.button_states); ++i)
		{
			if (pane_grid_outliner.button_states[i] == 0)
				break;
			if (pane_grid_outliner.button_states[i] == BUTTON_RELEASED)
			{
				update_path(contents[content_index]);
				parse_path();
				pane_grid_outliner.button_states[i] = BUTTON_LISTENING;
				break;
			}
		}
	}
	else
	{
		if (pane_grid_outliner.button_states[0] > 0)
			memset(pane_grid_outliner.button_states, 0 ,sizeof(pane_grid_outliner.button_states));
	}

	// ---- pane: playback -----------------------------------------------------
	if (state & STATE_PANE_PLAYBACK)
	{
		DrawRectangleV(
				(Vector2){0, ren_scl.y - pane_playback.scl.y},
				(Vector2){pane_playback.scl.x, pane_playback.scl.y},
				COL_PANE);
		if (ModeDebug)
		{
			DrawCircleV((Vector2){vertex_grid_playback.tl.x, vertex_grid_playback.tl.y}, 1.5f, GREEN);
			DrawCircleV((Vector2){vertex_grid_playback.tl.x, vertex_grid_playback.br.y}, 1.5f, GREEN);
			DrawCircleV((Vector2){vertex_grid_playback.br.x, vertex_grid_playback.tl.y}, 1.5f, GREEN);
			DrawCircleV((Vector2){vertex_grid_playback.br.x, vertex_grid_playback.br.y}, 1.5f, GREEN);
		}
	}
	else
	{
	}

	// ---- pane: playlist -----------------------------------------------------
	DrawRectangleV(
			(Vector2){pane_playlist.pos.x, pane_playlist.pos.y},
			(Vector2){pane_playlist.scl.x, pane_playlist.scl.y},
			COL_PANE);

	if (state & STATE_CONTENTS_AVAILABLE)
	{
		draw_text(
				bad_fonts.term,
				path,
				(v2i16){
				pane_playlist.pos.x + 40,
				40
				},
				bad_fonts.size_general,
				(f32)bad_fonts.size_headers/20,
				COL_TEXT_MAIN, (v2u8){0, 1});
		/* temp
		draw_list_items(
				&pane_grid_playlist,
				&pane_playlist,
				&vertex_grid_playlist);
				*/
	}
	else
	{
	}
	draw_text(
			bad_fonts.term,
			"Nothing to Display Here",
			(v2i16){
			pane_playlist.pos.x + (pane_playlist.scl.x/2),
			pane_playlist.scl.y/2
			},
			bad_fonts.size_headers,
			(f32)bad_fonts.size_headers/20,
			COL_TEXT_DARK, (v2u8){1, 1});

	pane_grid_outliner.unit = (v2i16){pane_outliner.scl.x - (margin_item*2), 50};
}

void free_gui()
{
	UnloadFont(bad_fonts.regular);
	UnloadFont(bad_fonts.bold);
}

// =============================================================================
// ==== _section_drawing =======================================================
// =============================================================================
void draw_list_items(BadPaneGrid *badPaneGrid, BadPane *parentPane, BadVertex *badVertex)
{
	Color color = COL_ITEM;
	u16 i = 0,
		j = badVertex->tl.y;
	for (;
			i < badPaneGrid->items;
			++i, j += (badPaneGrid->unit.y + badPaneGrid->spacing))
	{
		if (detect_cursor_overlap(
					(v2i16){badVertex->tl.x, j},
					(v2i16){badVertex->br.x, j + badPaneGrid->unit.y},
					badPaneGrid->lyr,
					&badPaneGrid->button_states[i]))
		{
			if (IsMouseButtonPressed(0))
			{
				badPaneGrid->button_states[i] = BUTTON_PRESSED;
				content_index = i;
			}
			if (IsMouseButtonReleased(0))
			{
				badPaneGrid->button_states[i] = BUTTON_RELEASED;
			}
			if (IsMouseButtonDown(0))
				color = COL_ITEM_PRESS;
			if (IsMouseButtonUp(0))
				color = COL_ITEM_HOVER;
		}
		else color = COL_ITEM;

		if (j + badPaneGrid->unit.y > badVertex->br.y)
		{
			DrawRectangleV(
					(Vector2){
					badVertex->tl.x,
					badVertex->tl.y + ((badPaneGrid->unit.y + badPaneGrid->spacing)*i*(bool)i)},
					(Vector2){
					badPaneGrid->unit.x,
					badPaneGrid->unit.y - (j + badPaneGrid->unit.y - badVertex->br.y)},
					color);
			break;
		}
		DrawRectangleV(
				(Vector2){
				badVertex->tl.x,
				parentPane->pos.y + margin_item + ((badPaneGrid->unit.y + badPaneGrid->spacing)*i*(bool)i)},
				(Vector2){
				badPaneGrid->unit.x,
				badPaneGrid->unit.y},
				color);
		draw_text(
				bad_fonts.term,
				contents[i],
				(v2i16){
				badVertex->tl.x + margin_item,
				j + (badPaneGrid->unit.y/2)
				},
				bad_fonts.size_general,
				(f32)bad_fonts.size_general/20,
				COL_TEXT_MAIN, (v2u8){0, 1});
	};
	if (ModeDebug)
	{
		DrawCircleV((Vector2){badVertex->tl.x, badVertex->tl.y}, 1.5f, GREEN);
		DrawCircleV((Vector2){badVertex->tl.x, badVertex->br.y}, 1.5f, GREEN);
		DrawCircleV((Vector2){badVertex->br.x, badVertex->tl.y}, 1.5f, GREEN);
		DrawCircleV((Vector2){badVertex->br.x, badVertex->br.y}, 1.5f, GREEN);
	}
}
// raylib/rtext.c/DrawTextEx refactored
void draw_text(Font font, const str *str, v2i16 pos, f32 font_size, f32 spacing, Color tint, v2u8 center)
{
    if (font.texture.id == 0) font = GetFontDefault();
    u16 size = TextLength(str);

	if (center.x) pos.x -= (get_str_width(font, str, font_size, spacing)/2);
	if (center.y) pos.y -= (font_size/1.8f);

    f32 textOffsetY = 0;
    f32 textOffsetX = 0.0f;
    f32 scaleFactor = font_size/font.baseSize;
    for (u16 i = 0; i < size;)
    {
        i32 codepointByteCount = 0;
        u16 codepoint = GetCodepointNext(&str[i], &codepointByteCount);
        u8 index = GetGlyphIndex(font, codepoint);

        if (codepoint == '\n')
        {
            textOffsetY += (font_size + 2);
            textOffsetX = 0.0f;
        }
        else
        {
			if ((codepoint != ' ') && (codepoint != '\t'))
			{
				DrawTextCodepoint(font, codepoint,
						(Vector2){pos.x + textOffsetX, pos.y + textOffsetY},
						font_size, tint);
			}
            if (font.glyphs[index].advanceX == 0)	textOffsetX += ((f32)font.recs[index].width*scaleFactor + spacing);
            else									textOffsetX += ((f32)font.glyphs[index].advanceX*scaleFactor + spacing);
        }
        i += codepointByteCount;
    }
}

// =============================================================================
// ==== _section_logic =========================================================
// =============================================================================
float get_str_width(Font font, const str *str, f32 font_size, f32 spacing)
{
	f32 result = 0;
    f32 textOffsetX = 0.0f;
    f32 scaleFactor = font_size/font.baseSize;
    for (u16 i = 0; i < TextLength(str);)
	{
		i32 codepointByteCount = 0;
		u16 codepoint = GetCodepointNext(&str[i], &codepointByteCount);
		u8 index = GetGlyphIndex(font, codepoint);

        if (codepoint == '\n')
            textOffsetX = 0.0f;
        else
        {
			if (font.glyphs[index].advanceX == 0)
			{
				result += font.recs[index].width*scaleFactor + spacing;
				textOffsetX += ((f32)font.recs[index].width*scaleFactor + spacing);
			}
			else
			{
				result += font.glyphs[index].advanceX*scaleFactor + spacing;
				textOffsetX += ((f32)font.glyphs[index].advanceX*scaleFactor + spacing);
			}
        }
        i += codepointByteCount;
	}
	return result + 4;
}

bool detect_cursor_overlap(v2i16 tl, v2i16 br, u8 lyr, u8 *button_state)
{
	if (cursor.x > tl.x && cursor.x < br.x && cursor.y > tl.y && cursor.y < br.y)
	{
		evaluate_cursor_layer(lyr);
		if (button_state)
			return true;
	}
	else cursor_lyr &= ~lyr;
	return false;
}

void evaluate_cursor_layer(u8 lyr)
{
	if (cursor_lyr < (cursor_lyr | lyr))
		cursor_lyr |= lyr;
}
