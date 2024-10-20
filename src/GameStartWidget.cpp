#include "GameStartWidget.hpp"

#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
namespace ui
{

  void GameStartWidget::paintGL()
  {
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor\n"
    "void main()\n"
    "{\n"
    "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float vertices[] = {
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.0f,  0.5f, 0.0f
    };
    unsigned int VBO;
    f->glGenBuffers(1, &VBO);
    f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    unsigned int vertexShader;
    vertexShader = f->glCreateShader(GL_VERTEX_SHADER);
    f->glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    f->glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = f->glCreateShader(GL_FRAGMENT_SHADER);
    f->glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    f->glCompileShader(fragmentShader);


    unsigned int shaderProgram;
    shaderProgram = f->glCreateProgram();

    f->glAttachShader(shaderProgram, vertexShader);
    f->glAttachShader(shaderProgram, fragmentShader);
    f->glLinkProgram(shaderProgram);



    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);

    auto vao = QOpenGLVertexArrayObject();
    vao.bind();

    // 2. copy our vertices array in a buffer for OpenGL to use
    f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);
    f->glUseProgram(shaderProgram);
    f->glDrawArrays(GL_TRIANGLES, 0, 3);


    f->glDeleteShader(vertexShader);
    f->glDeleteShader(fragmentShader);
    vao.release();
  }

}