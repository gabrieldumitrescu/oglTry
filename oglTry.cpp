/* My OpenGL try aplication
 */


#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ShaderSourceFile.h"
#include <math.h>
#include <assert.h>

GLuint vbo;
GLuint gScaleLocation;


void RenderSceneCB(){
  glClear(GL_COLOR_BUFFER_BIT);
  
  static float Scale = 0.0f;

  Scale += 0.005f;

  glUniform1f(gScaleLocation, sinf(Scale));


  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,vbo);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
  glDrawArrays(GL_TRIANGLES,0,3);
  glDisableVertexAttribArray(0);
  //glutWireTorus(0.2f, 0.5f, 50,100);

  
  glutSwapBuffers();
}

void CompileShaders(){
  GLuint ShaderProgram = glCreateProgram();

  if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
  }
  ShaderSourceFile vs("vertex.glsl",GL_VERTEX_SHADER);
  ShaderSourceFile fs("fragment.glsl",GL_FRAGMENT_SHADER);

  vs.AttachToProgram(ShaderProgram);
  fs.AttachToProgram(ShaderProgram);
  
  GLint Success = 0;
  GLchar ErrorLog[1024] = { 0 };

  glLinkProgram(ShaderProgram);
  glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
  if (Success == 0) {
    glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
    exit(1);
  }
  glValidateProgram(ShaderProgram);
  glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
  if (!Success) {
    glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
    exit(1);
  }
  glUseProgram(ShaderProgram);
  gScaleLocation = glGetUniformLocation(ShaderProgram, "gScale");
  assert(gScaleLocation != 0xFFFFFFFF);
}

GLuint CreateVertexBuffer(){
  GLuint res;
  glGenBuffers(1,&res);
  glBindBuffer(GL_ARRAY_BUFFER,res);
  float vertices[9]={
    -0.5f,-0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    0.0f,0.5f,0.0f
  };
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);
  return res;
}

int main (int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(800,600);
  glutInitWindowPosition(100,100);

  
  
  if(!glutGet(GLUT_DISPLAY_MODE_POSSIBLE)) exit(1);

  int win_no=glutCreateWindow("My OpenGl Application");
  printf("Created window no:%d\n",win_no);

  glutDisplayFunc(RenderSceneCB);
  glutIdleFunc(RenderSceneCB);

  GLenum res=glewInit();
  if(res!=GLEW_OK){
    printf("Error: %s\n",glewGetErrorString(res));
    return 1;
  }
  
  glClearColor(0.0f,0.0f,0.25f,0.0f);
  
  vbo=CreateVertexBuffer();

  CompileShaders();

  glutMainLoop();

  return 0;


}
