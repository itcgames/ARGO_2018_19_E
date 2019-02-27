#ifndef SDL_OPENGL_IMPL
#define SDL_OPENGL_IMPL

#include <fstream>
#include "SDL_OpenGL_Ext.h"

static GLuint SDL_OpenGL_CompileShader(const char* src, GLuint type) {

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


static SDL_Texture* screen_frame;

static void SDL_OpenGL_Apply_Frame_FX(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* level_frame, SDL_Texture* screen_frame, SDL_Rect* camera, GLuint progID) {

#if defined DEBUG
	//DEBUG_MSG("Rendering to Backbuffer and applying Shader");
#endif

	// ******************************************************************
	// Filling backbuffer and swapping
	// ******************************************************************

	// Copy the Level Frame enclosed by camera into screen frame
	SDL_SetRenderTarget(renderer, screen_frame);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, level_frame, camera, NULL);


	// Apply the Shader

	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderClear(renderer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SDL_RenderCopy(renderer, screen_frame, camera, camera);

	if (progID != 0) {
		glUseProgram(progID);
	}

	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
	glEnd();

	if (progID != 0) {
		glUseProgram(progID);
	}

}

static void SDL_OpenGL_Init_Ortho(int screen_width, int screen_height)
{
	GLdouble aspect;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0); 
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspect = (GLdouble)screen_width / screen_height;
	glOrtho(-3.0, 3.0, -3.0 / aspect, 3.0 / aspect, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
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
