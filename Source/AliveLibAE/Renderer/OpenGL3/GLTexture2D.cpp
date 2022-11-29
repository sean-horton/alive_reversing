#include <GL/glew.h>

#include "../AliveLibCommon/FatalError.hpp"
#include "../AliveLibCommon/Types.hpp"
#include "../relive_lib/data_conversion/rgb_conversion.hpp"
#include "GLDebug.hpp"
#include "GLTexture2D.hpp"


GLTexture2D::GLTexture2D()
{
}

GLTexture2D::GLTexture2D(u32 width, u32 height, GLenum format)
    : mFormat(format),
    mHeight(height),
    mWidth(width),
    mIsOriginal(true)
{
    GL_VERIFY(glGenTextures(1, &mGLId));

    BindTo(GL_TEXTURE0);

    GL_VERIFY(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_VERIFY(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GL_VERIFY(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_VERIFY(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    GL_VERIFY(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, 0));
}

GLTexture2D::GLTexture2D(const GLTexture2D& src)
{
    *this = src;
}

GLTexture2D::GLTexture2D(GLTexture2D&& src)
    : mFormat(src.mFormat),
    mGLId(src.mGLId),
    mHeight(src.mHeight),
    mWidth(src.mWidth),
    mIsOriginal(src.mIsOriginal)
{
    src.mGLId = 0;
    src.mIsOriginal = false;
}

GLTexture2D::~GLTexture2D()
{
    if (mGLId && mIsOriginal)
    {
        GL_VERIFY(glDeleteTextures(1, &mGLId));
    }
}


GLTexture2D& GLTexture2D::operator=(const GLTexture2D& src)
{
    if (this != &src)
    {
        if (mGLId && mIsOriginal)
        {
            GL_VERIFY(glDeleteTextures(1, &mGLId));
        }

        mFormat = src.mFormat;
        mGLId = src.mGLId;
        mWidth = src.mWidth;
        mHeight = src.mHeight;
        mIsOriginal = false;
    }

    return *this;
}

GLTexture2D& GLTexture2D::operator=(GLTexture2D&& src)
{
    if (this != &src)
    {
        if (mGLId && mIsOriginal)
        {
            GL_VERIFY(glDeleteTextures(1, &mGLId));
        }

        mFormat = src.mFormat;
        mGLId = src.mGLId;
        mWidth = src.mWidth;
        mHeight = src.mHeight;
        mIsOriginal = src.mIsOriginal;

        src.mGLId = 0;
        src.mIsOriginal = false;
    }

    return *this;
}


bool GLTexture2D::operator==(const GLTexture2D& other)
{
    return mGLId == other.mGLId;
}


void GLTexture2D::BindTo(GLenum texUnit)
{
    GL_VERIFY(glActiveTexture(texUnit));
    GL_VERIFY(glBindTexture(GL_TEXTURE_2D, mGLId));
}

u32 GLTexture2D::GetHeight()
{
    return mHeight;
}

u32 GLTexture2D::GetWidth()
{
    return mWidth;
}

bool GLTexture2D::IsValid()
{
    return mGLId > 0;
}

void GLTexture2D::LoadImage(const void* pixels, GLenum type)
{
    BindTo(GL_TEXTURE0);

    SetPixelUnpacking();
    GL_VERIFY(glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mFormat, type, pixels));
}

void GLTexture2D::LoadSubImage(GLint x, GLint y, GLsizei width, GLsizei height, const void* pixels, GLenum type)
{
    BindTo(GL_TEXTURE0);

    SetPixelUnpacking();
    GL_VERIFY(glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, mFormat, type, pixels));
}


void GLTexture2D::SetPixelUnpacking()
{
    switch (mFormat)
    {
        case GL_RED:
            GL_VERIFY(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
            break;

        default:
            GL_VERIFY(glPixelStorei(GL_UNPACK_ALIGNMENT, 4));
            break;
    }
}
