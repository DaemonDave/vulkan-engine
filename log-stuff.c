


#include "log/log.h"
#include "engine.h"
#include "common.h"
#include "event/event.h"

#include <stdarg.h>

static const char level_chars[] = {
	[LOG_DEBUG]    = ' ',
	[LOG_INFO]     = 'i',
	[LOG_WARN]     = 'w',
	[LOG_ERROR]    = 'E',
	[LOG_CRITICAL] = 'X',
};
#pragma once 

void log_init();

/* These correspond to log_level() functions. */
enum LogLevel {
	
	LOG_DEBUG, 
	/* Not logged in release builds */

	LOG_INFO,

	LOG_WARN,
	/* Example: Missing font for a glyph */

	LOG_ERROR,
	/* Unexpected errors that don't take down the whole engine, at least 
	 * immediately. 
	 * Example: Text rendering ran out of cache or glyph count was exceeded.
	 * This doesn't need to crash the engine, but rendering will be broken.
	 */

	LOG_CRITICAL, 
	/* Use when the engine is in a critical state and logging is to be 
	 * performed as safely as possible. 
	 * Basically should only be used by engine_crash().
	 */
};

/* 
 * Event interface
 *
 * Logging fires EVENT_LOG and passes by pointer the following struct to all 
 * observers. The struct and its pointers become invalid after the callback. 
 * Events are not fired for LOG_CRITICAL.
 */

struct LogEvent {
	enum LogLevel level;
	const char   *message;
};

/* Don't use directly, use the macros below */
void _log(
	enum LogLevel,
	const char *file,
	const char *func,
	int         line,
	const char *format,
	...
) __attribute__ ((format (printf, 5, 6)));

#define log_info(...) \
	_log(LOG_INFO,     __FILE__, __func__, __LINE__, __VA_ARGS__)

#define log_warn(...) \
	_log(LOG_WARN,     __FILE__, __func__, __LINE__, __VA_ARGS__)
 
#define log_error(...) \
	_log(LOG_ERROR,    __FILE__, __func__, __LINE__, __VA_ARGS__)

#define log_critical(...) \
	_log(LOG_CRITICAL, __FILE__, __func__, __LINE__, __VA_ARGS__)

#ifndef NDEBUG
#define log_debug(...) \
	_log(LOG_DEBUG,    __FILE__, __func__, __LINE__, __VA_ARGS__)

#define LOG_FUNCTION_POINTER(name, function) \
    log_info("  %-32s = %p", \
             name, \
             (void *)(uintptr_t)(function))	

#define LOG_NK_SIZE(name, value) \
    log_info("  %-32s = %" PRIu64, \
             name, \
             (uint64_t)(value))

#define LOG_NK_UINT(name, value) \
    log_info("  %-32s = %u", \
             name, \
             (unsigned int)(value))

#define LOG_NK_INT(name, value) \
    log_info("  %-32s = %d", \
             name, \
             (int)(value))

#define LOG_NK_FLOAT(name, value) \
    log_info("  %-32s = %.9g", \
             name, \
             (double)(value))

#define LOG_NK_FLAGS(name, value) \
    log_info("  %-32s = 0x%" PRIx64, \
             name, \
             (uint64_t)(value))

#define LOG_NK_POINTER(name, value) \
    log_info("  %-32s = %p", \
             name, \
             (void *)(value))

#define LOG_NK_STRUCT(name, value) \
    log_info("  %-32s = %zu bytes at %p", \
             name, \
             sizeof(value), \
             (void *)&(value))

/*
 * Converts both pointer-based Vulkan handles and integer-based Vulkan
 * handles to a printable unsigned integer.
 */
#define VK_HANDLE_VALUE(handle) \
    ((uint64_t)(uintptr_t)(handle))

#define LOG_VK_HANDLE(name, handle) \
    log_info("  %-32s = 0x%" PRIx64, \
             name, VK_HANDLE_VALUE(handle))

#define LOG_POINTER(name, pointer) \
    log_info("  %-32s = %p", name, (void *)(pointer))

#define LOG_UINT(name, value) \
    log_info("  %-32s = %" PRIu32, name, (uint32_t)(value))

#define LOG_INT(name, value) \
    log_info("  %-32s = %d", name, (int)(value))

	
	
	
#else 
#define log_debug(...) ((void)0)
#endif



void _log(
	enum LogLevel   level,
	const char     *file,
	const char     *func,
	int             line,
	const char     *format,
	...
){
	va_list args;
	va_start(args, format);

	const char path_prefix[] = "/src/";

	char *sub = strstr(file, path_prefix);
	if (sub) 
		file = sub + sizeof(path_prefix) - 1;

	static char buffer[1024];

	int len = snprintf(buffer, sizeof(buffer), 
		"(%c) %s:%i ", 
		level_chars[level], file, line
	);

	while (len < 38) {
		buffer[len] = '.';
		len++;
	}
	buffer[len++] = ' ';
	
	vsnprintf(buffer+len, sizeof(buffer)-len, format, args);
	va_end(args);

	printf("%s\n", buffer);

	if (level != LOG_CRITICAL) {
		static struct LogEvent e;
		e.message = buffer,
		e.level = level,
		event_fire(EVENT_LOG, &e);
	}
}

