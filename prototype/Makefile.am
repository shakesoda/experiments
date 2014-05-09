bin_PROGRAMS = prototype

prototype_SOURCES = src/main.c extern/gl3w/src/gl3w.c
prototype_CFLAGS = -Iextern/glm -Iextern/gl3w/include -Iextern/glfw3/include
prototype_LDADD = -Lextern/glfw3/src -lglfw3 -lX11 -lXrandr -lGL
#$(DEPS_LIBS)