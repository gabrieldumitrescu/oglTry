/* Implementation of the ShaderSourceFile class */

#include "ShaderSourceFile.h"

ShaderSourceFile::ShaderSourceFile(const char* filename, GLenum shader_type):m_shader_type(shader_type){
  std::ifstream input;
  input.open(filename);
  if(input.fail()){
    fprintf(stderr,"Cannot open shader source file '%s'\n",filename);
    exit(1);
  }
  m_source_file=new std::string(filename);
  m_source_code=new std::string;
  std::string line;
  while(getline(input,line)){
    (*m_source_code)+=line;
    (*m_source_code)+="\n";
  }
  //fprintf(stderr,"Shader source from %s : %s \n",m_source_file->c_str(),m_source_code->c_str());
  input.close();
} 

ShaderSourceFile::~ShaderSourceFile(){
  delete m_source_file;
  delete m_source_code;
}

void ShaderSourceFile::CompileShader(){
  m_shader_obj=glCreateShader(m_shader_type);
  if (m_shader_obj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", m_shader_type);
        exit(0);
  }
  const GLchar* srcs[1];
  srcs[0]=m_source_code->c_str();
  GLint lengths[1];
  lengths[0]=m_source_code->length();
  glShaderSource(m_shader_obj,1,srcs,lengths);
  glCompileShader(m_shader_obj);
  GLint success;
  glGetShaderiv(m_shader_obj, GL_COMPILE_STATUS, &success);
  if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(m_shader_obj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", m_shader_type, InfoLog);
        exit(1);
  }
  
}

void ShaderSourceFile::AttachToProgram(GLuint ShaderProgram){
  CompileShader();
  glAttachShader(ShaderProgram,m_shader_obj);
}
