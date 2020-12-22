#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <iostream>
#include <unistd.h>

int initializeEGL(Display *xdisp, Window &xwindow, EGLDisplay &display, EGLContext &context, EGLSurface &surface)
{
	display = eglGetDisplay(static_cast<EGLNativeDisplayType>(xdisp));
	if (display == EGL_NO_DISPLAY)
	{
		std::cerr << "Error eglGetDisplay." << std::endl;
		return -1;
	}
	if (!eglInitialize(display, nullptr, nullptr))
	{
		std::cerr << "Error eglInitialize." << std::endl;
		return -1;
	}
	
	EGLint attr[] = {EGL_BUFFER_SIZE, 16, EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_NONE};
	EGLConfig config = nullptr;
	EGLint numConfigs = 0;
	if (!eglChooseConfig(display, attr, &config, 1, &numConfigs))
	{
		std::cerr << "Error eglChooseConfig." << std::endl;
		return -1;
	}
	if (numConfigs != 1)
	{
		std::cerr << "Error numConfigs" << std::endl;
		return -1;
	}

	surface = eglCreateWindowSurface(display, config, xwindow, nullptr);
	if (surface == EGL_NO_SURFACE)
	{
		std::cerr << "Error eglCreateWindowSurface" << eglGetError() << std::endl;
		return -1;
	}

	EGLint ctxattr[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
	context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxattr);
	if (context == EGL_NO_CONTEXT)
        {
	        std::cerr << "Error eglCreateContext. " << eglGetError() << std::endl;
	        return -1;
	}
	eglMakeCurrent(display, surface, surface, context);
	 
	return 0;
}

void mainloop(Display *xdisplay, EGLDisplay display, EGLSurface surface)
{
	while(true)
	{
	        XPending(xdisplay);
       		glClearColor(0.25f, 0.25f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		eglSwapBuffers(display, surface);
		usleep(1000);
	}
}

void destroyEGL(EGLDisplay &display, EGLContext &context, EGLSurface &surface)
{
    eglDestroyContext(display, context);
    eglDestroySurface(display, surface);
    eglTerminate(display);
}
int main(void) {
	Display* xdisplay = XOpenDisplay(nullptr);
	if (xdisplay == nullptr)
	{
		std::cerr << "Error XOpenDisplay." << std::endl;
		exit(EXIT_FAILURE);
	}
	
	Window xwindow = XCreateSimpleWindow(xdisplay, DefaultRootWindow(xdisplay), 100, 100, 640, 480, 1, BlackPixel(xdisplay, 0), WhitePixel(xdisplay, 0));
	XMapWindow(xdisplay, xwindow);

	EGLDisplay display = nullptr;
	EGLContext context = nullptr;
	EGLSurface surface = nullptr;
	
	if (initializeEGL(xdisplay, xwindow, display, context, surface) < 0)
	{
		std::cerr << "Error initializeEGL." << std::endl;
		exit(EXIT_FAILURE);
	}
	
	mainloop(xdisplay, display, surface);
	XDestroyWindow(xdisplay, xwindow);
	XCloseDisplay(xdisplay);

	return 0;
}
