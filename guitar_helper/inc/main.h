#ifndef __GH_MAIN_H__
#define __GH_MAIN_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <Gh.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "guitar_helper"

#if !defined(PACKAGE)
#define PACKAGE "org.guitar.helper"
#endif

#endif /* __GH_MAIN_H__ */
