#ifndef SDL_OPENGL_IMPL
#define SDL_OPENGL_IMPL

#include <fstream>
#include "SDL_OpenGL_Ext.h"

static GLuint SDL_OpenGL_CompileShader(const char* src, GLuint type) {

	glLoadIdentity();

	GLint isCompiled = GL_FALSE;	// Shader Compiled
	GLuint result = glCreateShader(type);

	glShaderSource(result, 1, &src, NULL);
	glCompileShader(result);

	//Check is Shader Compiled
#if defined DEBUG
	DEBUG_MSG("Checking Shader Status");
#endif

	glGetShaderiv(result, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {

#if defined DEBUG
		DEBUG_MSG("Fragment Shader Compiled");
#endif

		isCompiled = GL_FALSE;
	}
	else
	{
#if defined DEBUG
		DEBUG_MSG("ERROR: Shader Compilation Error");
#endif
		GLint logLength;
		glGetShaderiv(result, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			GLchar *log = (GLchar*)malloc(logLength);
			glGetShaderInfoLog(result, logLength, &logLength, log);
#if defined DEBUG
			DEBUG_MSG("Shader Log");
			DEBUG_MSG(log);
#endif
			free(log);
		}
		glDeleteShader(result);
		result = 0;
	}
	return result;
}

static void SDL_OpenGL_RenderFrame(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* frame, GLuint progID) {

#if defined DEBUG
	//DEBUG_MSG("Rendering to Backbuffer and applying Shader");
#endif

	int w, h;
	SDL_QueryTexture(frame, NULL, NULL, &w, &h);

	SDL_Rect target;
	target.x = 0;
	target.y = 0;
	target.w = w;
	target.h = h;

	// ******************************************************************
	// Filling backbuffer and swapping
	// ******************************************************************

	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderClear(renderer);

	SDL_GL_BindTexture(frame, NULL, NULL);

	if (progID != 0) {
		glUseProgram(progID);
	}

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f((GLfloat)target.x, (GLfloat)target.y, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f((GLfloat)target.w, (GLfloat)target.y, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f((GLfloat)target.x, (GLfloat)target.h, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f((GLfloat)target.w, (GLfloat)target.h, 0.0f);
	glEnd();


	if (progID != 0) {
		glUseProgram(progID);
	}

	SDL_GL_SwapWindow(window);

}

static int SDL_OpenGL_Init_Orho(int screen_width, int screen_height)
{
	GLint result = GL_FALSE;

	GLdouble aspect;

	glViewport(0, 0, screen_width, screen_height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspect = (GLdouble)screen_width / screen_height;
	glOrtho(-3.0, 3.0, -3.0 / aspect, 3.0 / aspect, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);

	result = GL_TRUE;

	return result;
}

static GLuint SDL_OpenGL_CompileProgram(const char* vertex_shader, const char* fragment_shader) {
	GLint isLinked = 0;					// Shader Linked
	GLuint result = glCreateProgram();	//Create program in GPU
	GLuint vsid, fsid;

	std::ifstream f(vertex_shader);
	std::string source((std::istreambuf_iterator<char>(f)),
		std::istreambuf_iterator<char>());
	vsid = SDL_OpenGL_CompileShader(source.c_str(), GL_VERTEX_SHADER);

	f = std::ifstream(fragment_shader);
	source = std::string((std::istreambuf_iterator<char>(f)),
		std::istreambuf_iterator<char>());
	fsid = SDL_OpenGL_CompileShader(source.c_str(), GL_FRAGMENT_SHADER);

	if (vsid, fsid) {
		glAttachShader(result, vsid); //Attach Vertex Shader to Program
		glAttachShader(result, fsid); //Attach Fragment Shader to Program
		glLinkProgram(result);
		glValidateProgram(result);
	}

	//Check is Shader Linked
	glGetProgramiv(result, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
#if defined DEBUG
		DEBUG_MSG("Shader Linked");
#endif
	}
	else
	{
#if defined DEBUG
		DEBUG_MSG("ERROR: Shader Compilation Error");
#endif
		GLint logLength;
		glGetProgramiv(result, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			GLchar *log = (GLchar*)malloc(logLength);
			glGetShaderInfoLog(result, logLength, &logLength, log);
#if defined DEBUG
			DEBUG_MSG("Shader Log");
			DEBUG_MSG(log);
#endif
			free(log);
		}
		result = 0;
	}

#if defined DEBUG
	DEBUG_MSG("ProgID:" + std::to_string(result));
#endif
	if (vsid) {
		glDeleteShader(vsid);
	}
	if (fsid) {
		glDeleteShader(fsid);
	}
	return result;
}

static void QuitShaders(GLuint	progID) {
	//TODO: Cleanup
}

#endif