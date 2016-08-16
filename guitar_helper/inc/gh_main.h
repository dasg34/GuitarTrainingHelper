#ifndef __voicetest_H__
#define __voicetest_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "voicetest"

#if !defined(PACKAGE)
#define PACKAGE "org.example.voicetest"
#endif

#define EDJ_FILE "edje/voicetest.edj"
#define GRP_MAIN "main"


#endif /* __voicetest_H__ */
