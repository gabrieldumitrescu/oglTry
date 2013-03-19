/* My OpenGL try aplication
 */


#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

GLuint vbo;

void RenderSceneCB(){
  glClear(GL_COLOR_BUFFER_BIT);
  
  //glEnableVertexAttribArray(0);
  //glBindBuffer(GL_ARRAY_BUFFER,vbo);
  //glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
  //glDrawArrays(GL_TRIANGLES,0,3);
  //glDisableVertexAttribArray(0);
  glutWireTorus(0.2f, 0.5f, 50,100);

  
  glutSwapBuffers();
}

void AddShader(){
}

void CreateProgram(){
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

  glutMainLoop();

  return 0;


}
