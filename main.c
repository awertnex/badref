/* ==== _section table =========================================================
_section_main ==================================================================
*/

/* TASKS:    [!]: done!    [x]: deleted
 * [ ] remove the little last character appended to .config/badref.conf
 */

#include <raylib.h>

#include "gui.c"
#include "dir.c"
#include "config_file_generator.c"
#include "h/main.h"

// ---- variables --------------------------------------------------------------
Camera2D camera = {0};
u16 state = 1;
u8 ModeDebug = 0;

// =============================================================================
// ==== _section_main ==========================================================
// =============================================================================

int main(void)
{
	// ---- _section_main_init -------------------------------------------------
	InitWindow(1280, 720, "badref");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowMinSize(720, 450);
	state |= STATE_RUNNING;

	camera.zoom = 1;

	init_config();

    snprintf(files[0], 22, "/home/lilya/Desktop/"); //temp
    open_directory(0);                              //temp

	init_gui();
	InitAudioDevice();

	// ---- _section_main_loop -------------------------------------------------
	while (state & STATE_RUNNING)
	{
		detect_cursor;
		listen_input();
		//printf("---- cursor layer: %d\n", cursor_lyr); /*temp*/

		BeginDrawing();
		ClearBackground(COL_BASE);
		update_gui();
		EndDrawing();
	}

	// ---- _section_main_close ------------------------------------------------
	CloseAudioDevice();
	free_gui();
	CloseWindow();
	return 0;
}

// 
void listen_input()
{
	if (IsKeyPressed(KEY_F3))
		ModeDebug = !ModeDebug;

	if (IsKeyPressed(KEY_ENTER))
		state ^= STATE_TOOLBAR;

	if (IsKeyPressed(KEY_P))
        state ^= STATE_PANE_PLAYBACK;
    if (IsKeyPressed(KEY_UP))
        state |= STATE_PANE_PLAYBACK;
    if (IsKeyPressed(KEY_DOWN))
        state &= ~STATE_PANE_PLAYBACK;

	if (IsKeyPressed(KEY_TAB))
        state ^= STATE_PANE_OUTLINER;

	if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE))
		state &= ~STATE_RUNNING;
}
