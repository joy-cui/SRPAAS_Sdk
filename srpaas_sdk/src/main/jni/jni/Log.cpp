#include "Log.h"
#include <android/log.h>
void Log(const char * format, ...) {
	va_list apptr;
	va_start(apptr, format);
	__android_log_vprint(ANDROID_LOG_DEBUG, "sdk_log", format, apptr);
	va_end(apptr);
}

