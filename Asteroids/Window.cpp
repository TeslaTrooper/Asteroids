#include "Window.h"
#include<stdio.h>

Window::Window() {
	initOpenGL();
	initWindow();
	initViewport();
	initProjectionMatrix();

	renderer = new Renderer();
}

Window::~Window() {
	glfwDestroyWindow(window);
	delete renderer;
}

void Window::initOpenGL() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void Window::initWindow() {
	window = glfwCreateWindow(500, 500, "Asteroids | OpenGL", nullptr, nullptr);

	glfwSetWindowPos(window, 500, 100);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	glGetString(GL_VERSION);

	glfwSetKeyCallback(window, Controller::key_callback);
}

void Window::initViewport() {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	windowSize = { width, height };

	glViewport(0, 0, width, height);
}

void Window::initProjectionMatrix() {
	projection = Mat4::ortho(0.0f, static_cast<GLfloat>(windowSize.width), 
		static_cast<GLfloat>(windowSize.height), 0.0f, -1.0f, 1.0f);
}

void Window::loop() {
	GLfloat start = 0;
	GLfloat dt = 0;

	renderer->setProjection(projection);

	while (!glfwWindowShouldClose(window)) {
		start = (GLfloat)glfwGetTime();

		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		renderer->render(dt);

		glfwSwapBuffers(window);

		dt = (GLfloat)glfwGetTime() - start;
	}

	glfwTerminate();
}


