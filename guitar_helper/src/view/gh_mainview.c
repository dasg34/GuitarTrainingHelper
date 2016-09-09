/*
 * gh_mainview.c
 *
 *  Created on: Sep 4, 2016
 *      Author: lee
 */

#include "gh_main.h"
#include "gh_view.h"

#include <Gh.h>

static void
_main_layout_back_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	ui_app_exit();
}

void
gh_main_layout_create(Evas_Object* naviframe)
{
	Evas_Object *layout;
	layout = gh_layout_add(naviframe,"edje/gh_main.edj","main");

	elm_naviframe_item_simple_push(naviframe,layout);
	eext_object_event_callback_add(layout, EEXT_CALLBACK_BACK, _main_layout_back_cb, NULL);
}
