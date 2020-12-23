#pragma once
typedef unsigned short hfloat;

#define TEXTURE_TYPE GL_UNSIGNED_BYTE
#define TEXTURE_TYPE_TOKEN GLbyte
#define TEXTURE_INTERNAL_FMT GL_RGBA8_OES
#define TEXTURE_FORMAT GL_RGBA
#define TEXTURE_UNIT_NUM 32
/*
#define TEXTURE_TYPE GL_HALF_FLOAT_OES
#define TEXTURE_TYPE_TOKEN hfloat
#define TEXTURE_INTERNAL_FMT GL_RGBA16_EXT
#define TEXTURE_FORMAT GL_RGBA
*/

#define EGL_CHECK(x) \
    x; \
    { \
        EGLint eglError = eglGetError(); \
        if(eglError != EGL_SUCCESS) { \
            fprintf(stderr, "eglGetError() = %i (0x%.8x) at line %i\n", eglError, eglError, __LINE__); \
            exit(1); \
        } \
    }

#define GL_GET_ERROR \
	{ \
		GLenum code = glGetError(); \
		if (code != GL_NO_ERROR) { \
			std::cerr << "GL_GET_ERROR_OCCUR!!" << std::endl; \
			switch (code) { \
				case GL_INVALID_ENUM: \
					std::cerr << "GL_INVALID_ENUM" << std::endl; \
					break; \
				case GL_INVALID_VALUE: \
					std::cerr << "GL_INVALID_VALUE" << std::endl; \
					break; \
				case GL_INVALID_OPERATION: \
					std::cerr << "GL_INVALID_OPERATION" << std::endl; \
					break; \
				case GL_OUT_OF_MEMORY: \
					std::cerr << "GL_OUT_OF_MEMORY" << std::endl; \
					break; \
				default: \
					std::cerr << "GL_UNKNOWN_ERROR" << std::endl; \
			} \
			exit(1); \
		} \
	}
