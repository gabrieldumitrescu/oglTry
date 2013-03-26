/* My OpenGL try aplication
 */


#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ShaderSourceFile.h"
#include "math_3d.h"
#include <math.h>
#include <assert.h>

GLuint vbo,ibo;
GLuint gWorldLocation;


void RenderSceneCB(){
  glClear(GL_COLOR_BUFFER_BIT);
  
  static float Step = 0.0f;

   Step+= 0.001f;

   Matrix4f scale,rotation,world;
   rotation.InitRotationMatrix(sinf(Step)*30.0f,sinf(Step)*30.0f,sinf(Step)*30.0f);
   scale.InitScaleMatrix(sinf(Step*0.1f),sinf(Step*0.1f),sinf(Step*0.1f));
   world=scale * rotation;

   glUniformMatrix4fv(gWorldLocation,1,GL_TRUE, &world.mat[0][0]);


  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,vbo);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);

  glDrawElements(GL_TRIANGLES,12,GL_UNSIGNED_INT,0);
  glDisableVertexAttribArray(0);
    
  glutSwapBuffers();
}

void CompileShaders(){
  GLuint ShaderProgram = glCreateProgram();

  if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
  }
  ShaderSourceFile vs("vertex.glsl",GL_VERTEX_SHADER);//load vertex shader from file vertex.glsl
  ShaderSourceFile fs("fragment.glsl",GL_FRAGMENT_SHADER);//load fragment shader from file fragment.glsl

  vs.AttachToProgram(ShaderProgram);//attach shaders to our program
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
  //glEnable(GL_FRAMEBUFFER_SRGB);
  glValidateProgram(ShaderProgram);
  glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
  
  if (!Success) {
    glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
    exit(1);
  }
  
  glUseProgram(ShaderProgram);
  gWorldLocation = glGetUniformLocation(ShaderProgram, "World");
  assert(gWorldLocation != 0xFFFFFFFF);
}

GLuint CreateIndexBuffer(){
  GLuint res;
  unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               0, 2, 1 };

  glGenBuffers(1,&res);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,res);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Indices),Indices,GL_STATIC_DRAW);
  return res;
  
}

GLuint CreateVertexBuffer(){
  GLuint res;
  glGenBuffers(1,&res);
  glBindBuffer(GL_ARRAY_BUFFER,res);
  float vertices[]={
    -1.0f,-1.0f,0.0f,
    0.0f,-1.0f,1.0f,
    1.0f,-1.0f,0.0f,
    0.0f,1.0f,0.0f
  };
  //printf("Sizeof(vertices)=%d",sizeof(vertices));
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
  //printf("Created window no:%d\n",win_no);

  glutDisplayFunc(RenderSceneCB);
  glutIdleFunc(RenderSceneCB);

  GLenum res=glewInit();
  if(res!=GLEW_OK){
    printf("Error: %s\n",glewGetErrorString(res));
    return 1;
  }
  
  glClearColor(0.0f,0.0f,0.55f,0.0f);

  ibo=CreateIndexBuffer();
  
  vbo=CreateVertexBuffer();

  CompileShaders();

  glutMainLoop();

  return 0;


}
