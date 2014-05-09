#include <stdio.h>
#include <config.h>

#include <GL/gl3w.h>
#include <GL/glfw3.h>

void run_game(int);

/* debug mode print */
int noprint(const char *f, ...) { return 0; }
int (*dprint)(const char *f, ...) = noprint;

int main(int argc, char **argv)
{
	int i;
	int debug = 0;

	#define ARG_CHECK(item, cmp) if (strcmp(item, cmp) == 0)
	for (i = 0; i < argc; i++)
	{
		ARG_CHECK(argv[i], "--debug")
		{
			dprint = printf;
			debug = 1;
		}

		/* --version exits early. */
		ARG_CHECK(argv[i], "--version")
		{
			printf("%s\n", PACKAGE_STRING);
			return 0;
		}
	}
	/* don't need this anymore */
	#undef ARG_CHECK

	run_game(debug);

	return 0;
}

/* note: in real programs you don't use many globals, they're ugly as fuck */
GLuint g_vbo;
GLuint g_shader;

void setup()
{
	GLuint vs, fs;

	/* vertex/fragment shader sources */
	const char *vss =
		"attribute vec3 input;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = input;\n"
		"}\n";
	const char *fss =
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(1.0);\n"
		"}\n";

	glGenBuffers(1, &g_vbo);

	/* create shader objects to compile & link */
	/* these are basically just objects for source files */
	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, &vss, NULL);
	glShaderSource(fs, 1, &fss, NULL);

	/* this is the final program object, things get attached and linked
	 * to this and you bind these prior to rendering anything */

	/* note: you'll usually have way more than one of these. */
	g_shader = glCreateProgram();
}

void cleanup()
{

}

void run_game(int debug)
{
	glfwInit();
	
	// w, h, windowed, name, sharing
	glfwWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
	GLFWwindow window = glfwCreateWindow(960, 540, GLFW_WINDOWED, "sup", NULL);

	glfwMakeContextCurrent(window);

	// vsync
	glfwSwapInterval(1);

	// gather function pointers up to a given level
	gl3wInit();
	if (!gl3wIsSupported(3, 2))
	{
		printf("kaboom!\n");
		glfwTerminate();

		return;
	}

	setup();

	//glfwShowWindow(window);

	while(glfwGetKey(window, GLFW_KEY_ESC) != GLFW_PRESS)
	{	
		if (glfwGetWindowParam(window, GLFW_CLOSE_REQUESTED))
			break;

		glClearColor(0.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* now shit gets real */

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cleanup();

	glfwDestroyWindow(window);
	glfwTerminate();
}
