////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: gl_helper.hpp
//
// Timeperiod: 25-March-15: Version 1.0: Created
// Timeperiod: 25-March-15: Version 1.0: Last Updated
//
// Notes:
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <cstdarg>
#include <exception>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glfw3.h>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __GL_HELPER_HPP__
#define __GL_HELPER_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void compile_shaders(int count, ...)
{
   va_list arg_ptr;

   va_start(arg_ptr, count);

   GLuint shader_program;
   shader_program = glCreateProgram();

   for (int index = 0; index < count; ++index)
   {
      glAttachShader(shader_program, va_arg(arg_ptr, GLuint));
   }

   va_end(arg_ptr);

   glLinkProgram(shader_program);

   GLint success;
   GLchar info_log[512];
   glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
   if (!success) {
      glGetProgramInfoLog(shader_program, 512, NULL, info_log);
      
      throw std::runtime_error(std::string("[gl_helper.hpp::set_up_shader()::58] - Linking of shader failed: ") + info_log);
   }

   glUseProgram(shader_program);

}

void delete_shader(GLuint shader)
{
   glDeleteShader(shader);
}

template<typename __Type> void set_up_and_send_buffer_data(__Type& data, size_t size, GLenum usage)
{
   GLuint VBO;

   glGenBuffers(1, &VBO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

GLuint set_up_shader(const char* vertex_shader_source, GLenum shader_type)
{
   GLuint shader;
   shader = glCreateShader(shader_type);

   glShaderSource(shader, 1, (const char**)&vertex_shader_source, NULL);
   glCompileShader(shader);

   GLint success;
   GLchar info_log[512];
   glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

   if (!success)
   {
      glGetShaderInfoLog(shader, 512, NULL, info_log);
      
      throw std::runtime_error(std::string("[gl_helper.hpp::set_up_shader()::89] - Compilation of shader failed: ") + info_log);
   }

   return shader;
}

GLuint set_up_shader_from_file(const char* filename, GLenum shader_type)
{
   std::ifstream input_file(filename);

   std::stringstream buffer;
   buffer << input_file.rdbuf();

   std::string contents = buffer.str();

   const char* string = contents.c_str();

   return set_up_shader(string, shader_type);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif // __GL_HELPER_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////