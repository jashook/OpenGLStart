#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glfw3.h>

int main()
{
   glfwInit();

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

   GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGl Example", nullptr, nullptr);

   glfwMakeContextCurrent(window);

   if (window == NULL)
   {
      std::cout << "Failed to create GLFW windows" << std::endl;

      glfwTerminate();

      return -1;
   }

   glewExperimental = GL_TRUE;
   GLenum err = glewInit();

   if (err != GLEW_OK)
   {
      std::cout << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
      return -1;
   }

   glViewport(0, 0, 800, 600);

   while (!glfwWindowShouldClose(window))
   {
      glfwPollEvents();
      glfwSwapBuffers(window);
   }

   glfwTerminate();

   return 0;
}