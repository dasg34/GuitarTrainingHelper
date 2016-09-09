/*
 * gh_mainview.c
 *
 *  Created on: Sep 4, 2016
 *      Author: lee
 */

#include "gh_main.h"
#include "gh_view.h"

#include <Gh.h>

static Eina_Bool
_main_layout_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
	return EINA_FALSE;
}

void
gh_main_layout_create(Evas_Object* naviframe)
{
	Evas_Object *layout;
	layout = gh_layout_add(naviframe,"edje/gh_main.edj","main");

	elm_naviframe_item_simple_push(naviframe,layout);
	eext_object_event_callback_add(layout, EEXT_CALLBACK_BACK, _main_layout_back_cb, NULL);
}
