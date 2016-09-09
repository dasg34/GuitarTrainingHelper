/**
 * This file contains the exported symbol.
 */
#include "Gh.h"

void
app_get_resource(const char *edj_file_in, char *edj_path_out, int edj_path_max)
{
	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(edj_path_out, edj_path_max, "%s%s", res_path, edj_file_in);
		free(res_path);
	}
}

Evas_Object*
gh_layout_add(Evas_Object* parent,char* edj_name, const char *group)
{
	Evas_Object* layout;
	char edj_path[PATH_MAX] = {0, };

	app_get_resource(edj_name, edj_path, (int)PATH_MAX);
	layout=elm_layout_add(parent);
	elm_layout_file_set(layout, edj_path, group);

	return layout;
}
