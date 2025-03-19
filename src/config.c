#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include <types.h>

// ---- variables --------------------------------------------------------------
str config_path[32] = {0};
str config_tokens[32][84] =
{
	"@path_home:",
	"@current_project:",
	"@recent_project_00:",
	"@recent_project_01:",
	"@recent_project_02:",
	"@recent_project_03:",
	"@recent_project_04:",
	"@recent_project_05:",
	"@recent_project_06:",
	"@recent_project_07:",
	"@recent_project_08:",
	"@recent_project_09:",
	"@render_width:",
	"@render_height:",
	"@pane_outliner_width:",
	"@pane_outliner_sort_type:",
	"@playback_loop_state:",
	"@playback_volume_level:",
};
str config_contents[32][84] =
{
	"------- config file for bad_referencer.c ---------------------------------------\n\n",
	"@path_home:\n",
	"@current_project:\n",
	"@recent_project_00:\n",
	"@recent_project_01:\n",
	"@recent_project_02:\n",
	"@recent_project_03:\n",
	"@recent_project_04:\n",
	"@recent_project_05:\n",
	"@recent_project_06:\n",
	"@recent_project_07:\n",
	"@recent_project_08:\n",
	"@recent_project_09:\n\n",
	"@render_width:\n",
	"@render_height:\n\n",
	"@pane_outliner_width:\n",
	"@pane_outliner_sort_type:\n",
	"@playback_loop_state:\n",
	"@playback_volume_level:\n",
};
FILE *config;

void init_config()
{
	snprintf(config_path, 31, "%s/.config/", getenv("HOME"));

	if (!(config = fopen("/home/lilya/.config/badref.conf", "r")))
	{
		config = fopen("/home/lilya/.config/badref.conf", "w");
		for (u16 i = 0; i < 48 && config_tokens[i]; ++i)
		{
			fwrite(config_contents[i], strlen(config_contents[i]), 1, config);
		}
		fclose(config);
	}
}

str *update_config()
{
	str *str;
	return str;
}
