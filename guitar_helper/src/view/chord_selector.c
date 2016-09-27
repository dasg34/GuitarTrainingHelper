#include <main.h>
#define CHORD_NUM 7
static char chords[CHORD_NUM] = { 'C' , 'D' , 'E' , 'F' , 'G' , 'A' , 'B' };

void
chord_selector_create(Evas_Object *naviframe)
{
	Evas_Object *scroller, *box, *circle_scroller;

	scroller = elm_scroller_add(naviframe);
	elm_object_style_set(scroller, "effect");
	elm_scroller_loop_set(scroller, EINA_FALSE, EINA_FALSE);
	elm_scroller_page_size_set(scroller, 360, 360);
	elm_object_scroll_lock_y_set(scroller, EINA_FALSE);
	evas_object_show(scroller);

	circle_scroller = eext_circle_object_scroller_add(scroller,NULL);
	eext_rotary_object_event_activated_set(scroller,EINA_TRUE);

	box = elm_box_add(scroller);
	evas_object_show(box);

	for(int i=0;i<CHORD_NUM;i++)
	{
		Evas_Object *layout = gh_layout_add(box,"edje/chord_selector.edj","main");
		evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

		char text[10];
		snprintf(text,10,"%c chord",chords[i]);
		elm_object_part_text_set(layout,"title",text);
		snprintf(text,10,"%c",chords[i]);
		elm_object_part_text_set(layout,"text.1",text);
		snprintf(text,10,"%cm",chords[i]);
		elm_object_part_text_set(layout,"text.2",text);
		snprintf(text,10,"%c7",chords[i]);
		elm_object_part_text_set(layout,"text.3",text);
		snprintf(text,10,"%cM7",chords[i]);
		elm_object_part_text_set(layout,"text.4",text);
		snprintf(text,10,"%cm7",chords[i]);
		elm_object_part_text_set(layout,"text.5",text);

		evas_object_show(layout);

		elm_box_pack_end(box,layout);
	}

	elm_object_content_set(scroller, box);

	elm_naviframe_item_simple_push(naviframe,scroller);
}
