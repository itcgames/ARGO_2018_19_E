#ifndef SDL_OPENGL_EXT
#define SDL_OPENGL_EXT

#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>

static PFNGLCREATESHADERPROC glCreateShader;
static PFNGLSHADERSOURCEPROC glShaderSource;
static PFNGLCOMPILESHADERPROC glCompileShader;
static PFNGLGETSHADERIVPROC glGetShaderiv;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
static PFNGLDELETESHADERPROC glDeleteShader;
static PFNGLATTACHSHADERPROC glAttachShader;
static PFNGLCREATEPROGRAMPROC glCreateProgram;
static PFNGLLINKPROGRAMPROC glLinkProgram;
static PFNGLVALIDATEPROGRAMPROC glValidateProgram;
static PFNGLGETPROGRAMIVPROC glGetProgramiv;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
static PFNGLUSEPROGRAMPROC glUseProgram;
static PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
static PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
static PFNGLUNIFORM1FPROC glUniform1f;

static int SDL_OpenGL_Ext_Init() {
	int result = 0;



	glCreateShader = (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)SDL_GL_GetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)SDL_GL_GetProcAddress("glCompileShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)SDL_GL_GetProcAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)SDL_GL_GetProcAddress("glGetShaderInfoLog");
	glDeleteShader = (PFNGLDELETESHADERPROC)SDL_GL_GetProcAddress("glDeleteShader");
	glAttachShader = (PFNGLATTACHSHADERPROC)SDL_GL_GetProcAddress("glAttachShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)SDL_GL_GetProcAddress("glCreateProgram");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)SDL_GL_GetProcAddress("glLinkProgram");
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)SDL_GL_GetProcAddress("glValidateProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)SDL_GL_GetProcAddress("glGetProgramiv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)SDL_GL_GetProcAddress("glGetProgramInfoLog");
	glUseProgram = (PFNGLUSEPROGRAMPROC)SDL_GL_GetProcAddress("glUseProgram");
	glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)SDL_GL_GetProcAddress("glGenFramebuffers");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)SDL_GL_GetProcAddress("glGetAttribLocation");
	glUniform1f = (PFNGLUNIFORM1FPROC)SDL_GL_GetProcAddress("glGetAttribLocation");

	result = result && glCreateShader;
	result = result && glShaderSource;
	result = result && glCompileShader;
	result = result && glGetShaderiv;
	result = result && glGetShaderInfoLog;
	result = result && glDeleteShader;
	result = result && glAttachShader;
	result = result && glCreateProgram;
	result = result && glLinkProgram;
	result = result && glValidateProgram;
	result = result && glGetProgramiv;
	result = result && glGetProgramInfoLog;
	result = result && glUseProgram;
	result = result && glGenFramebuffers;
	result = result && glGetAttribLocation;
	result = result && glUniform1f;

	return result;
}

#endif