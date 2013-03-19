/* Header file for the ShaderSourceFile object */

#ifndef SHADER_SOURCE_FILE_H
#define SHADER_SOURCE_FILE_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>


class ShaderSourceFile{
 public:
  ShaderSourceFile(const char* filename, GLenum shader_type);
  ~ShaderSourceFile();
  void AttachToProgram(GLuint ShaderProgram);
 private:
  void CompileShader();

  std::string* m_source_file;
  std::string* m_source_code;
  GLenum m_shader_type;
  GLuint m_shader_obj;

};
 
#endif // SHADER_SOURCE_FILE_H
