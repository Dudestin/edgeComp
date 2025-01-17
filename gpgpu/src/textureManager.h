#pragma once
#include "macro.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>

#include <array>
#include <mutex>

class textureManager
{
	const GLenum target;
	const GLenum internalFormat;
	const GLenum internalType;
	const GLenum textureUnit;
	GLuint id;
	GLsizei textureWidth;
	GLsizei textureHeight;

	inline GLint getUnitNum() {
		return this->textureUnit - GL_TEXTURE0;
	}
public:
	textureManager(GLsizei texWidth, GLsizei texHeight,
		const void* pixels,
		GLenum textureUnit,
		GLint location,
		GLenum target = GL_TEXTURE_2D,
		GLenum internalFmt = TEXTURE_FORMAT,
		GLenum type = TEXTURE_TYPE)
		: textureWidth{ texWidth },
		textureHeight{ texHeight },
		textureUnit{ textureUnit },
		target{ target },
		internalFormat{ internalFmt },
		internalType{ type }
	{
		glGenTextures(1, &(this->id));
		glActiveTexture(textureUnit);
		this->bind();
		this->setUniformLocation(location);
		this->setTexParameter();
		glTexImage2D(this->target, 0, this->internalFormat,
			this->textureWidth, this->textureHeight,
			0, this->internalFormat, this->internalType, pixels);
	}

	inline void setTexParameter() {
		this->bind();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	inline void setUniformLocation(GLint location) {
		this->bind();
		glUniform1i(location, this->getUnitNum());
	}

	inline void bind() const
	{
		glBindTexture(this->target, id);
	}

	inline void unbind() const
	{
		glBindTexture(this->target, 0);
	}
};
