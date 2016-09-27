#include <main.h>
#include <view.h>

static void
_main_layout_back_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	ui_app_exit();
}

static void
_chord_menu_clicked_cb(void *data EINA_UNUSED, Evas_Object *obj, const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{
	Evas_Object *naviframe = (Evas_Object*)data;
	chord_selector_create(naviframe);
}

void
main_menu_create(Evas_Object* naviframe)
{
	Evas_Object *layout;
	layout = gh_layout_add(naviframe,"edje/main.edj","main");

	elm_object_signal_callback_add(layout, "chord_menu_clicked", "",_chord_menu_clicked_cb,naviframe);

	evas_object_show(layout);

	elm_naviframe_item_simple_push(naviframe,layout);
	eext_object_event_callback_add(layout, EEXT_CALLBACK_BACK, _main_layout_back_cb, NULL);
}
