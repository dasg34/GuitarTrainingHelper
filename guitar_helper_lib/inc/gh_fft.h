/* libfft.h - include file for fast Fourier transform library
**
** Copyright (C) 1989 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/


#ifndef _GH_FFT_H_
#define _GH_FFT_H_

#include <tizen.h>

#ifdef __cplusplus
extern "C" {
#endif

EXPORT_API void *initfft(int bits);

EXPORT_API void destroyfft( void *fft );

EXPORT_API void applyfft( void * fft, float *xr, float *xi, int inv );

#ifdef __cplusplus
}
#endif
#endif // _GH_FFT_H_
