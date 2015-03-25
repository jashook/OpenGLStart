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

   glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mode)
   {
      // When a user presses the escape key, we set the WindowShouldClose property to true, 
      // closing the application
      if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
         glfwSetWindowShouldClose(window, GL_TRUE);
   });

   while (!glfwWindowShouldClose(window))
   {
      glfwPollEvents();
      glfwSwapBuffers(window);
   }

   glfwTerminate();

   return 0;
}