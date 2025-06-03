// Sprite.h
#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Sprite {
public:
    Sprite(const std::string& caminhoTextura, GLuint shaderProgram);
    void setPosicao(glm::vec2 pos);
    void setEscala(glm::vec2 escala);
    void setRotacao(float angulo);
    void draw();

private:
    GLuint textura;
    GLuint VAO;
    GLuint shader;
    glm::vec2 posicao;
    glm::vec2 escala;
    float rotacao;

    void carregarTextura(const std::string& caminho);
    void inicializarQuad();
};
