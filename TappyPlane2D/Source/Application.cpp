#include "Common/Assertion.h"

#include "Vector/Vector.h"

#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>

int main(int argc, char* argv[])
{
	ASSERTION(glfwInit() == GLFW_TRUE, "failed to initialize GLFW...");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const std::string& title = "TappyPlane2D";
	const int32_t width = 1000;
	const int32_t height = 800;

	GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	ASSERTION(window != nullptr, "failed to create GLFW window...");

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, 
		[](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	);
	
	ASSERTION(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "failed to initialize OpenGL function loader...");

	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	window = nullptr;

	glfwTerminate();
	return 0;
}