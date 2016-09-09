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
naviframe_pop_main_cb(void *data, Elm_Object_Item *it)
{
	ui_app_exit();
	return EINA_FALSE;
}

void
gh_main_layout_create(Evas_Object* naviframe)
{
	Evas_Object *layout;
	Elm_Object_Item *navi_item;
	layout = gh_layout_add(naviframe,"edje/gh_main.edj","main");

	navi_item =elm_naviframe_item_simple_push(naviframe,layout);
	elm_naviframe_item_pop_cb_set(navi_item, naviframe_pop_main_cb, NULL);
}
