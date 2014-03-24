#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <SOIL.h>

namespace RectGraphTest{
GLuint vertexShader;
GLuint fragmentShader;
GLuint shaderProgram;
GLuint vao; //Vertex Array Object
GLuint vbo; //Vertex Buffer Object
GLuint ebo; //Element Buffer Object
GLuint tex;
}


void setupGLEW() // Should be called after setting up OpenGL context
{
 glewExperimental= GL_TRUE;
 GLenum err = glewInit();
 //Check if glew Initialization was OK
 if(err != GLEW_OK)
 {
  std::cout<<"GLEW Initialization failed\n";
 }

}

void setupShaders()
{
    using namespace RectGraphTest;
    //Setup Vertex Shader
    vertexShader= glCreateShader(GL_VERTEX_SHADER);
    std::ifstream f("../GraphicsExperiments/SampleVertexShader.glsl", std::ios::in);
    if(f.is_open())
    {
        std::string vertexShaderCode;
        std::string line = "";
        while(getline(f,line))
        { vertexShaderCode+="\n"+ line;
        }
        f.close();
        const char * cvertexSource = vertexShaderCode.c_str();
        //const GLchar* vertexSource =cvertexSource;
        glShaderSource(vertexShader, 1, &cvertexSource, NULL);
        glCompileShader(vertexShader);
        GLint Status;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Status);
        if(Status!=GL_TRUE)
        { std::cout<< "Vertex Shader Compilation failed\n";
          char buffer[512];
          glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
          std::cout<<buffer;
        }
    }
    else
    {
        std::cout<<"Vertex Shader file could not be opened\n";
    }

    fragmentShader= glCreateShader(GL_FRAGMENT_SHADER);
    f.open("../GraphicsExperiments/SampleFragmentShader.glsl", std::ios::in);

    if(f.is_open())
    {
        std::string fragmentShaderCode;
        std::string line="";
        while(getline(f,line))
        { fragmentShaderCode+= "\n"+line;
        }
        f.close();

        const char * cfragmentSource= fragmentShaderCode.c_str();
        //std::cout<<cfragmentSource;
        glShaderSource(fragmentShader, 1, &cfragmentSource, NULL);
        glCompileShader(fragmentShader);
        GLint Status;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Status);
        if(Status!=GL_TRUE)
        { std::cout<< "Fragment Shader Compilation failed\n";
          char buffer[512];
          glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
          std::cout<<buffer;
        }
    }
    else
    {
        std::cout<<"Fragment Shader file could not be opened\n";
    }

    //Combine the shaders into a program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outcolor");

    glLinkProgram(shaderProgram);
    GLint Status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &Status);
    if(Status!=GL_TRUE)
    {
        std::cout<<"Program Not Linked\n";
    }
    glGetProgramiv(shaderProgram, GL_ATTACHED_SHADERS, &Status);
    //std::cout<<Status<<"Shaders Attached to Program\n";
    glUseProgram(shaderProgram);

}
void initRect()
{
    float vertices[] = {
    //  Position      Color             Texcoords
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
    };
   GLuint elements[] = {
       0, 1, 2,
       2, 3, 0
   };

   using namespace RectGraphTest;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float bordercolor[]={0.0f, 1.0f, 0.0f, 0.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, bordercolor);

    //Specify Texture Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height;
    unsigned char* image = SOIL_load_image("../GraphicsExperiments/img_test.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);


    GLint posAttrib=glGetAttribLocation(shaderProgram,"position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float),0);
    glEnableVertexAttribArray(posAttrib);
    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
                           7*sizeof(float), (void*)(5*sizeof(float)));

}
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glutSwapBuffers();
}
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);                 // Initialize GLUT
   //glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
   glutInitWindowSize(520, 520);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow("OpenGL Testing"); // Create a window with the given title
   setupGLEW();
   setupShaders();
   initRect();
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutMainLoop();           // Enter the infinitely event-processing loop
   glDeleteProgram(RectGraphTest::shaderProgram);
   glDeleteShader(RectGraphTest::fragmentShader);
   glDeleteShader(RectGraphTest::vertexShader);
   glDeleteBuffers(1, &RectGraphTest::vbo);
   glDeleteVertexArrays(1, &RectGraphTest::vao);
   return 0;
}
