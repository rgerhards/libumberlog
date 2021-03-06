/* umberlog_preload.c -- CEE-enhanced syslog API, LD_PRELOAD version
 *
 * Copyright (c) 2012 BalaBit IT Security Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY BALABIT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL BALABIT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#define _GNU_SOURCE 1

#define __UL_PRELOAD__ 1

#include "umberlog.c"

#if HAVE___SYSLOG_CHK
void
__syslog_chk (int __pri, int __flag, __const char *__fmt, ...)
{
  va_list ap;

  va_start (ap, __fmt);
  ul_legacy_vsyslog (__pri, __fmt, ap);
  va_end (ap);
}

void
__vsyslog_chk (int __pri, int __flag, __const char *__fmt, va_list ap)
{
  ul_legacy_vsyslog (__pri, __fmt, ap);
}
#endif

void openlog (const char *ident, int option, int facility)
  __attribute__((alias ("ul_openlog")));

void closelog (void)
  __attribute__((alias ("ul_closelog")));

#undef syslog
void syslog (int priority, const char *msg_format, ...)
  __attribute__((alias ("ul_legacy_syslog")));

#undef vsyslog
void vsyslog (int priority, const char *msg_format, va_list ap)
  __attribute__((alias ("ul_legacy_vsyslog")));
