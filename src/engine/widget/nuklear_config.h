#ifndef NUKLEAR_CONFIG_H
#define NUKLEAR_CONFIG_H

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

/*
 * Required because WidgetRenderer embeds Nuklear structures by value.
 */
#define NK_PRIVATE

/*
 * Nuklear defaults NK_API to static. That is only suitable when every
 * declaration and definition is in one translation unit.
 */
#define NK_API extern

#endif

