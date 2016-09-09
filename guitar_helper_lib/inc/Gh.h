#ifndef _GH_LIB_H_
#define _GH_LIB_H_

/**
 * This header file is included to define _EXPORT_.
 */
#include <stdbool.h>
#include <tizen.h>
#include <Elementary.h>
#include <app.h>

#include <gh_fft.h>

#ifdef __cplusplus
extern "C" {
#endif

// This method is exported from guitar_helper_lib.so
EXPORT_API void app_get_resource(const char *edj_file_in, char *edj_path_out, int edj_path_max);

EXPORT_API Evas_Object* gh_layout_add(Evas_Object* parent,char* edj_name, const char *group);

#ifdef __cplusplus
}
#endif
#endif // _GH_LIB_H_

