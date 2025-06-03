// main.cpp
// Lista 4 - Cena com sprites texturizados usando OpenGL moderna

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../include/stb_image.h"

#include <iostream>
#include <vector>
#include "../include/Sprite.h"

const int LARGURA = 800;
const int ALTURA = 600;

GLuint criarShader(const char* vsSrc, const char* fsSrc);

const char* vertexShaderSrc = R"(
#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 texCoord;

uniform mat4 model;
uniform mat4 projection;

out vec2 TexCoord;

void main() {
    gl_Position = projection * model * vec4(pos, 0.0, 1.0);
    TexCoord = texCoord;
})";

const char* fragmentShaderSrc = R"(
#version 330 core
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D textura;
void main() {
    FragColor = texture(textura, TexCoord);
})";

int main() {
    glfwInit();
    GLFWwindow* janela = glfwCreateWindow(LARGURA, ALTURA, "Cena com Sprites", NULL, NULL);
    glfwMakeContextCurrent(janela);
    glewExperimental = GL_TRUE;
    glewInit();

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint shader = criarShader(vertexShaderSrc, fragmentShaderSrc);
    glm::mat4 proj = glm::ortho(0.0f, float(LARGURA), 0.0f, float(ALTURA), -1.0f, 1.0f);

    Sprite fundo("imagens/background.png", shader);
    fundo.setPosicao(glm::vec2(400, 300));
    fundo.setEscala(glm::vec2(800, 600));

    Sprite player("imagens/player.png", shader);
    player.setPosicao(glm::vec2(400, 100));
    player.setEscala(glm::vec2(100, 100));

    Sprite enemy("imagens/enemy.png", shader);
    enemy.setPosicao(glm::vec2(600, 300));
    enemy.setEscala(glm::vec2(100, 100));

    Sprite arvore("imagens/tree.png", shader);
    arvore.setPosicao(glm::vec2(200, 300));
    arvore.setEscala(glm::vec2(120, 200));

    while (!glfwWindowShouldClose(janela)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(proj));

        fundo.draw();
        arvore.draw();
        enemy.draw();
        player.draw();

        glfwSwapBuffers(janela);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

GLuint criarShader(const char* vsSrc, const char* fsSrc) {
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSrc, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSrc, NULL);
    glCompileShader(fs);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}
