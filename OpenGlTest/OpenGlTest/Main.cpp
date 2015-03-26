////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: Main.cpp
//
// Timeperiod: 24-March-15: Version 1.0: Created
// Timeperiod: 25-March-15: Version 1.0: Last Updated
//
// Notes:
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>

#include "gl_helper.hpp"
#include "glew_helper.hpp"
#include "glfw_helper.hpp"
#include "vertex_data.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define WIDTH 800
#define HEIGHT 600

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void add_call_backs(glfw_helper& glfw, GLFWwindow* window)
{
   glfw.add_call_back(window, [] (GLFWwindow* window, int key, int scancode, int action, int mode)
   {
      // When a user presses the escape key, we set the WindowShouldClose property to true, 
      // closing the application
      if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
         glfwSetWindowShouldClose(window, GL_TRUE);
   });
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main()
{
   // Set up and tear down automatically done.
   glfw_helper glfw(GL_FALSE);

   GLFWwindow* window = glfw.create_window(WIDTH, HEIGHT, "OpenGl Example");
   glfw.set_window_context(window);

   add_call_backs(glfw, window);

   set_up_glew(WIDTH, HEIGHT);

   GLuint VAO = set_up_and_send_buffer_data(vertices, sizeof(vertices), GL_STATIC_DRAW);

   GLuint vertex_shader = set_up_shader_from_file("shader.txt", GL_VERTEX_SHADER);
   GLuint frag_shader = set_up_shader_from_file("example.frag", GL_FRAGMENT_SHADER);

   GLuint shader_program = compile_shaders(2, vertex_shader, frag_shader);

   delete_shader(vertex_shader);
   delete_shader(frag_shader);

   // Set up the Vertex Atribute pointer to skip every third data, because we are using
   // x y and z
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(0);

   while (!glfwWindowShouldClose(window))
   {
      glfwPollEvents();

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shader_program);
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glBindVertexArray(0);

      glfwSwapBuffers(window);
   }

   return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

