#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>
#include "IDrawable.h"

class Window;

class Framebuffer : public IDrawable
{
private:
    Window *attachedWindow = nullptr;
    GLuint fbo, texture, rbo;

public:
    Framebuffer(unsigned int width, unsigned int height);
    Framebuffer(Window *window);
    ~Framebuffer();

    void AttachWindow(Window *window);
    void DetachWindow();
    void Draw() override;

    void Bind() override;

    GLuint GetFBO();
    Window *GetAttachedWindow();
};
#endif