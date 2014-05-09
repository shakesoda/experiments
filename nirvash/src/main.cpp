#define GLM_SWIZZLE
#include <cstring>
#include <string>
#include <GL/glcorearb.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "configuration.h"
#include "screen.h"
#include "state.h"
#include "window.h"
#include "utils/logger.h"
#include "utils/thread.h"

// Calculate FXAA alpha for a given color
float calc_fxaa_alpha(glm::vec3 in)
{
	return glm::dot(in, glm::vec3(0.299, 0.587, 0.114));
}

void start_video(void *data)
{
	Nepgear::State *ng = (Nepgear::State*)data;
	Nepgear::Window *w;
	Nepgear::Logger log(NULL);
	log.print_header();

	// wait for the window to be created.
	while(ng->windows.empty());

	w = ng->windows[0];

	// Bind the OpenGL context to this thread
	const Nepgear::WindowFlags f = w->GetFlags();
	w->MakeCurrent();
	w->VSync(true);
	if (!w->Prepare(f.gl_major, f.gl_minor))
	{
		/* We shouldn't ever get here if window creation succeeded, unless
		 * the driver lied to us when we created the window. */
		log.warn(
			"OpenGL %d.%d is not supported. Please check your drivers "
			"or hardware for support.", f.gl_major, f.gl_minor
		);
		w->ClearCurrent();
		return;
	}

	// HACK: NVIDIA 295.20 drivers specifically doesn't wait properly.
	if (strcmp((const char*)glGetString(GL_VERSION), "3.2.0 NVIDIA 295.20")==0)
		ng->configuration["enable_wait_hack"] = true;
	ng->start = true;

	std::vector<Nepgear::Screen> screen_stack;

	Nepgear::Screen scr("Base");
	scr.load(ng);

	screen_stack.push_back(scr);

	glm::vec4 clear = glm::vec4(0.1, 0.4, 0.8, 1.0);

	glClearColor(clear.r, clear.g, clear.b, clear.a);
	glEnable(GL_DEPTH_TEST);

	double now = glfwGetTime();
	double then = now;
	double delta = 0.0;

	while(ng->running)
	{
		now = glfwGetTime();
		delta = now - then;
		then = now;

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		for (size_t i = 0; i < screen_stack.size(); i++)
			screen_stack[i].update(delta);

		for (size_t i = 0; i < screen_stack.size(); i++)
			screen_stack[i].draw();

		w->SwapBuffers();

		// This only needs to happen for the first update!
		if (ng->configuration["enable_wait_hack"])
		{
			glfwPollEvents();
			ng->configuration["enable_wait_hack"] = false;
		}
	}

	screen_stack.clear();

	w->ClearCurrent();
}

void start_audio(void *data)
{
	Nepgear::State *ng = (Nepgear::State*)data;

	UNUSED(ng);
}

static void open_libs(lua_State *L)
{
	luaL_Reg libs[] =
	{
		{ "base",	luaopen_base },
		{ "table",	luaopen_table },
		{ "string",	luaopen_string },
		{ "math",	luaopen_math },
		{ "debug",	luaopen_debug },
		{ NULL, NULL }
	};

	for (const luaL_reg *lib = libs; lib->func; lib++)
	{
		lib->func(L);
		lua_settop(L, 0);
	}
}

void init_game(Nepgear::State *ng)
{
	Nepgear::Configuration conf("config.lua");
	Nepgear::Logger log(NULL);

	ng->lua = lua_open();

	open_libs(ng->lua);

	Nepgear::Window w;
	Nepgear::WindowFlags f;
	{
		std::string renderer = conf.get_string("Renderer", "OpenGL");
		int major = 2;
		int minor = 1;	

		/* Parse OpenGL major/minor version out of the preference.
		 * Format: OpenGL_X.Y */
		size_t pos = renderer.find_first_of("_");
		if (pos != std::string::npos)
		{
			std::string version = renderer.substr(pos+1);
			std::string upper, lower;
			log.debug("Requested OpenGL version " + version);

			pos = version.find_first_of(".");

			upper = version.substr(0, pos);
			lower = version.substr(pos+1);

			major = atoi(upper.c_str());
			minor = atoi(lower.c_str());
		}
		
		f.width = conf.get_integer("DisplayWidth", 1280);
		f.height = conf.get_integer("DisplayHeight", 720);

		f.gl_major = major;
		f.gl_minor = minor;

		f.strict = major >= 3;
		f.mode = Nepgear::WindowFlags::Windowed;
		f.homie = NULL;
	}
	w.Create(f);

	ng->windows.push_back(&w);

	// wait a moment for configuration to be worked out in the GL thread
	while (!ng->start)
		tthread::this_thread::sleep_for(tthread::chrono::milliseconds(2));

	while (ng->running)
	{
		/* HACK: glfwWaitEvents misbehaves for me using nvidia's 295.20 drivers
		 * and a GT 330. Workaround: force poll on first update in other thread
		 */
		if (!ng->configuration["enable_wait_hack"])
			glfwWaitEvents();
		else
			tthread::this_thread::sleep_for(tthread::chrono::milliseconds(16));

		if (glfwGetKey(w.GetHandle(), GLFW_KEY_ESC) == GLFW_PRESS ||
			glfwGetWindowParam(w.GetHandle(), GLFW_CLOSE_REQUESTED))
		{
			Nepgear::LockGuard<Nepgear::Mutex>::type hold(ng->lock);
			ng->running = false;
		}
	}

	w.Destroy();
}

int main()
{
	Nepgear::State ng;

	glfwInit();

	ng.threads["video"] = new Nepgear::Thread(start_video, (void*)&ng);
	ng.threads["audio"] = new Nepgear::Thread(start_audio, (void*)&ng);

	init_game(&ng);

	auto it = ng.threads.begin();
	for ( ; it != ng.threads.end(); ++it)
	{
		if (!it->second)
			continue;
		it->second->join();
		delete it->second;
	}

	glfwTerminate();

	return 0;
}
