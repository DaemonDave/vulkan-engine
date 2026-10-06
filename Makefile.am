##
## Description  : vk_renderer - Makefile.am
## Author       : DRE 2024
## Purpose      : main Makefile
## Revision     : $Id: Makefile.am,v 1.12 2008/12/02 20:49:08 cvsuser Exp $
##

# DRE 2022 : the subdirectories alert for automake 
# NOTE: Every line ends in a Carriage Return
SUBDIRS = 

#SUBDIRS = src src/glsl src/engine src/game lib src/tests



ACLOCAL_AMFLAGS = -I m4


bin_PROGRAMS = engine

engine_SOURCES = main.c

engine_LDADD = \
	libengine.la \
	$(top_builddir)/game/libgame.la


# main library adding up convenience sub-libs
lib_LTLIBRARIES = 

GLSLC = glslc

AM_CFLAGS = \
    -I$(top_srcdir)/src \
    -I$(top_srcdir)/src/engine \
    -I$(top_srcdir)/src/engine/event \
    -I$(top_srcdir)/src/engine/gfx \
    -I$(top_srcdir)/src/engine/handle \
    -I$(top_srcdir)/src/engine/log \
    -I$(top_srcdir)/src/engine/mem \
    -I$(top_srcdir)/src/engine/res \
    -I$(top_srcdir)/src/engine/sphere \
    -I$(top_srcdir)/src/engine/text \
    -I$(top_srcdir)/src/engine/util \
    -I$(top_srcdir)/src/engine/widget \
    -I$(top_srcdir)/src/engine/win \
    -I$(top_srcdir)/src/game \
    -I$(top_srcdir)/src/game/softbody \
    -I$(top_srcdir)/src/game/teapot\
    -I$(top_srcdir)/lib/fast_obj \
    -I$(top_srcdir)/lib/freetype/include \
    -I$(top_srcdir)/lib/glfw/include\
    -I$/usr/include/fribidi.h
    
        
#Open MP 
AM_CFLAGS += $(OPENMP_CFLAGS)

AM_CXXFLAGS = $(OPENMP_CXXFLAGS)

noinst_LTLIBRARIES = libengine.la

libengine_la_SOURCES = \
	src/engine/engine.c \
	src/engine/res/res.c \
	src/engine/util/file.c \
	src/engine/util/ppm.c \
	src/engine/log/log.c \
	src/engine/event/event.c \
	src/engine/win/win.c \
	src/engine/handle/handle.c \
	src/engine/mem/mem.c \
	src/engine/mem/sysmem.c \
	src/engine/gfx/gfx.c \
	src/engine/gfx/vk_util.c \
	src/engine/gfx/vulkan_utils.c \
	src/engine/gfx/vk_instance.c \
	src/engine/gfx/vk_device.c \
	src/engine/gfx/vk_swapchain.c \
	src/engine/gfx/vma.cpp \
	src/engine/widget/widget_renderer.c \
	src/engine/sphere/icosphere.c \
	src/engine/sphere/icosahedron.c \
	src/engine/sphere/sphere_renderer.c \
	src/engine/text/text_block.c \
	src/engine/text/text_engine.c \
	src/engine/text/text_geometry.c \
	src/engine/text/text_renderer.c\
	src/engine/gfx/teapot/teapot.c\
	src/engine/gfx/softbody/phash.c\
	src/engine/gfx/softbody/sbm.c\
	src/engine/gfx/softbody/softbody.c\
	src/engine/gfx/softbody/softbody_renderer.c\
	src/engine/gfx/softbody/wireframe_renderer.c
	
libengine_la_CFLAGS = -Wno-implicit-function-declaration


libengine_la_CPPFLAGS = \
    -I$(top_srcdir)/src \
    -I$(top_srcdir)/src/engine \
    -I$(top_srcdir)/src/engine/event \
    -I$(top_srcdir)/src/engine/gfx \
    -I$(top_srcdir)/src/engine/gfx/softbody \
    -I$(top_srcdir)/src/engine/gfx/teapot \
    -I$(top_srcdir)/src/engine/gfx/voxel \
    -I$(top_srcdir)/src/engine/handle \
    -I$(top_srcdir)/src/engine/log \
    -I$(top_srcdir)/src/engine/mem \
    -I$(top_srcdir)/src/engine/res \
    -I$(top_srcdir)/src/engine/sphere \
    -I$(top_srcdir)/src/engine/text \
    -I$(top_srcdir)/src/engine/util \
    -I$(top_srcdir)/src/engine/widget \
    -I$(top_srcdir)/src/engine/win\
    -I$(top_srcdir)/lib/fast_obj \
    -I$(top_srcdir)/lib/freetype/include \
    -I$(top_srcdir)/lib/glfw/include\
    -I$(top_srcdir)/lib/stb\
    -I$(top_srcdir)/lib/cglm\
    -I$(top_srcdir)/lib/include/cglm\
    -I/usr/include/fribidi
    

    

libengine_la_LIBADD = \
	$(OPENMP_LIBS) \
	$(FRIBIDI_LIBS) \
    $(top_builddir)/lib/libfast_obj_lib.a \
    $(top_builddir)/lib/libfreetyped.a \
    $(top_builddir)/lib/cglm/libcglm.la \
    $(top_builddir)/lib/libglfw3.a
	$(HARFBUZZ_LIBS) \
	-lvulkan \
	-lfreetype \
	-lharfbuzz\
	-lm
	
	

libengine_la_LDFLAGS = \
	-no-undefined


check_PROGRAMS = test_vulkan_resources test_widget_engine
 

TESTS = test_vulkan_resources

test_vulkan_resources_SOURCES = src/tests/test_vulkan_structs.c\
								src/engine/win/win.c\
								src/engine/event/event.c\
								src/engine/log/log.c
								
								
								
								
									


test_vulkan_resources_CPPFLAGS = $(AM_CPPFLAGS)\
    -I$(top_srcdir)/src \
    -I$(top_srcdir)/src/engine \
    -I$(top_srcdir)/src/engine/event \
    -I$(top_srcdir)/src/engine/gfx \
    -I$(top_srcdir)/src/engine/gfx/softbody \
    -I$(top_srcdir)/src/engine/gfx/teapot \
    -I$(top_srcdir)/src/engine/gfx/voxel \
    -I$(top_srcdir)/src/engine/handle \
    -I$(top_srcdir)/src/engine/log \
    -I$(top_srcdir)/src/engine/mem \
    -I$(top_srcdir)/src/engine/res \
    -I$(top_srcdir)/src/engine/sphere \
    -I$(top_srcdir)/src/engine/text \
    -I$(top_srcdir)/src/engine/util \
    -I$(top_srcdir)/src/engine/widget \
    -I$(top_srcdir)/src/engine/win\
    -I$(top_srcdir)/lib/fast_obj \
    -I$(top_srcdir)/lib/freetype/include \
    -I$(top_srcdir)/lib/glfw/include\
    -I$(top_srcdir)/lib/stb\
    -I$(top_srcdir)/lib/cglm\
    -I$(top_srcdir)/lib/include/cglm\
    -I/usr/include/fribidi


test_vulkan_resources_CFLAGS = $(AM_CFLAGS)



test_vulkan_resources_LDADD =$(OPENMP_LIBS) \
							$(FRIBIDI_LIBS) \
							-lm \
							-lpthread \
							$(VULKAN_SDK)/lib/libvulkan.so \
							$(top_builddir)/lib/fast_obj/libfast_obj_lib.a \
							$(top_builddir)/lib/freetype/objs/.libs/libfreetype.la \
							$(top_builddir)/lib/cglm/libcglm.la \
							$(top_builddir)/lib/glfw/src/libglfw3.a \
							$(HARFBUZZ_LIBS)
										


test_vulkan_resources_LDFLAGS = $(AM_LDFLAGS)


# Widget engine

test_widget_engine_SOURCES = \
    src/game/main.c

test_widget_engine_CPPFLAGS = $(AM_CPPFLAGS) \
    -I$(top_srcdir)/src \
    -I$(top_srcdir)/src/engine \
    -I$(top_srcdir)/src/engine/event \
    -I$(top_srcdir)/src/engine/gfx \
    -I$(top_srcdir)/src/engine/gfx/softbody \
    -I$(top_srcdir)/src/engine/gfx/teapot \
    -I$(top_srcdir)/src/engine/gfx/voxel \
    -I$(top_srcdir)/src/engine/handle \
    -I$(top_srcdir)/src/engine/log \
    -I$(top_srcdir)/src/engine/mem \
    -I$(top_srcdir)/src/engine/res \
    -I$(top_srcdir)/src/engine/sphere \
    -I$(top_srcdir)/src/engine/text \
    -I$(top_srcdir)/src/engine/util \
    -I$(top_srcdir)/src/engine/widget \
    -I$(top_srcdir)/src/engine/win \
    -I$(top_srcdir)/lib/fast_obj \
    -I$(top_srcdir)/lib/freetype/include \
    -I$(top_srcdir)/lib/glfw/include \
    -I$(top_srcdir)/lib/stb \
    -I$(top_srcdir)/lib/cglm \
    -I$(top_srcdir)/lib/include/cglm \
    -I/usr/include/fribidi

test_widget_engine_CFLAGS = $(AM_CFLAGS)

test_widget_engine_LDADD = \
    libengine.la \
    -lm \
    -lpthread \
    -lomp5 \
    $(VULKAN_SDK)/lib/libvulkan.so \
    $(top_builddir)/lib/fast_obj/libfast_obj_lib.a \
    $(top_builddir)/lib/freetype/objs/.libs/libfreetype.la \
    $(top_builddir)/lib/cglm/libcglm.la \
    $(top_builddir)/lib/glfw/src/libglfw3.a
    
#        $(HARFBUZZ_LIBS)
    


test_widget_engine_LDFLAGS = $(AM_LDFLAGS)

			

							
.PHONY: shaders

shaders:
	@for shader in $(glsl_sources); do \
		output="$$shader.spv"; \
		echo "Compiling $$shader -> $$output"; \
		glslc "$$shader" -o "$$output" || exit 1; \
	done						
							
							




# --------------------------------------------------------------------
# GLSL shaders
# --------------------------------------------------------------------

glsl_sources = \
	src/glsl/nuklear.frag \
	src/glsl/nuklear.vert \
	src/glsl/softbody.frag \
	src/glsl/softbody.shadow.vert \
	src/glsl/softbody.vert \
	src/glsl/sphere.frag \
	src/glsl/sphere.vert \
	src/glsl/text.frag \
	src/glsl/text.vert \
	src/glsl/tri.frag \
	src/glsl/tri.vert \
	src/glsl/voxel_raymarch.frag \
	src/glsl/voxel_raymarch.vert \
	src/glsl/voxel.shadow.frag \
	src/glsl/voxel.shadow.frag.glsl \
	src/glsl/voxel.shadow.vert \
	src/glsl/widget.frag \
	src/glsl/widget.vert \
	src/glsl/wireframe.frag \
	src/glsl/wireframe.vert
	
# --------------------------------------------------------------------
# Compiled SPIR-V shaders
# --------------------------------------------------------------------

shader_spv = \
	src/glsl/nuklear.frag.spv \
	src/glsl/nuklear.vert.spv \
	src/glsl/softbody.frag.spv \
	src/glsl/softbody.shadow.vert.spv \
	src/glsl/softbody.vert.spv \
	src/glsl/sphere.frag.spv \
	src/glsl/sphere.vert.spv \
	src/glsl/text.frag.spv \
	src/glsl/text.vert.spv \
	src/glsl/tri.frag.spv \
	src/glsl/tri.vert.spv \
	src/glsl/voxel_raymarch.frag.spv \
	src/glsl/voxel_raymarch.vert.spv \
	src/glsl/voxel.shadow.frag.spv \
	src/glsl/voxel.shadow.frag.glsl.spv \
	src/glsl/voxel.shadow.vert.spv \
	src/glsl/widget.frag.spv \
	src/glsl/widget.vert.spv \
	src/glsl/wireframe.frag.spv \
	src/glsl/wireframe.vert.spv	

glsl_spv = $(glsl_sources:%=%.spv)

BUILT_SOURCES = $(glsl_spv)
CLEANFILES = $(glsl_spv)
EXTRA_DIST = $(glsl_sources)

# Ensure res.c is rebuilt after shader binaries change.
engine/res/res.lo: $(glsl_spv)

# Also make the library depend explicitly on the generated shader files.
libengine_la_DEPENDENCIES = $(glsl_spv)


%.vert.spv: %.vert.glsl
	glslc -fshader-stage=vert $< -o $@

%.frag.spv: %.frag.glsl
	glslc -fshader-stage=frag $< -o $@

%.comp.spv: %.comp.glsl
	glslc -fshader-stage=comp $< -o $@

# Compile, for example:
# glsl/sphere.vert -> glsl/sphere.vert.spv
%.spv: %
	$(AM_V_GEN)$(GLSLC) -o "$@" "$<"

# --------------------------------------------------------------------
# Copy compiled shaders to the build-tree resources directory
# --------------------------------------------------------------------

resourcesdir = $(builddir)/resources

shader_resources = $(glsl_spv:%=$(resourcesdir)/%)

all-local: $(shader_resources)

$(resourcesdir)/%.spv: %.spv
	$(AM_V_GEN)$(MKDIR_P) "$(dir $@)"
	$(AM_V_GEN)cp "$<" "$@"


#demoshaders/triangle.frag.h: demoshaders/triangle.frag.spv
#	/usr/bin/xxd -i demoshaders/triangle.frag.spv /home/dave/src/nuklear-glfw-vulkan/demoshaders/triangle.frag.h
#
#demoshaders/triangle.frag.spv: demoshaders/triangle.frag
#	/home/dave/src/vulkansdk-linux-x86_64-1.3.261.1/1.3.261.1/x86_64/bin/glslangValidator -V /home/dave/src/nuklear-glfw-vulkan/demoshaders/triangle.frag -o /home/dave/src/nuklear-glfw-vulkan/demoshaders/triangle.frag.spv


# DRE 2022 - target recipe makes doxygen outputs, after updating config format file
dox:
	doxygen
#
create-dox:
	doxygen -g 



