#include <device/power.h>
#include <main.h>
#include <view.h>

Eext_Circle_Surface* _circle_surface;
Evas_Object *_naviframe;

static void
create_base_gui()
{
	Evas_Object *win,*naviframe;
	Eext_Circle_Surface* circle_surface;

	win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(win, EINA_TRUE);

	naviframe = elm_naviframe_add(win);
	_naviframe = naviframe;
	circle_surface = eext_circle_surface_naviframe_add(naviframe);
	_circle_surface = circle_surface;
	elm_win_resize_object_add(win, naviframe);
	main_menu_create(naviframe);
	evas_object_show(naviframe);

	evas_object_show(win);
}

static bool
app_create(void *data EINA_UNUSED)
{
	create_base_gui();

	return true;
}

static void
app_control(app_control_h app_control EINA_UNUSED, void *data EINA_UNUSED)
{
	/* Handle the launch request. */
}

static void
app_pause(void *data EINA_UNUSED)
{
	/* Take necessary actions when application becomes invisible. */
	dlog_print(DLOG_ERROR, LOG_TAG, "app_pause");
	ui_app_exit();
}

static void
app_resume(void *data EINA_UNUSED)
{
	/* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void *data EINA_UNUSED)
{
	/* Release all resources. */
	dlog_print(DLOG_ERROR, LOG_TAG, "app_terminate");
}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void
ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void
ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int
main(int argc, char *argv[])
{
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, NULL);
	ui_app_remove_event_handler(handlers[APP_EVENT_LOW_MEMORY]);

	ret = ui_app_main(argc, argv, &event_callback, NULL);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_main() is failed. err = %d", ret);
	}

	return ret;
}
