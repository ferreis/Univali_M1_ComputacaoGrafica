#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/freeglut.h>
#include <vector>

struct Vertice {
    double x;
    double y;
    double z;
};

using lista_vertices = std::vector<Vertice>;
using aresta = std::pair<int, int>;
using lista_arestas = std::vector<aresta>;

struct Poligono {
    double tamanhoLado;
    Vertice posicao;
    Vertice escala;
    Vertice rotacao;
    lista_vertices vertices;
    lista_arestas arestas;
};

constexpr double PI = 3.14159265358979323846;
constexpr double PASSO_MOVIMENTO = 0.25;
constexpr double PASSO_ROTACAO = 5.0;
constexpr double FATOR_ESCALA = 1.10;

Poligono criar_cubo(double centro_x, double centro_y, double centro_z, double tamanho_lado);
void desenhar(const Poligono& poligono);
void movimentar(Poligono& poligono, double deslocamento_x, double deslocamento_y, double deslocamento_z);
void escalar(Poligono& poligono, double escala_x, double escala_y, double escala_z);
void rotacionar(Poligono& poligono, double angulo_x, double angulo_y, double angulo_z);
void display();
void reshape(int largura, int altura);
void keyboard(unsigned char key, int x, int y);
void keyboard_special(int key, int x, int y);
void imprimir_controles();

double graus_para_radianos(double graus);

Poligono cubo;

int main(int argc, char** argv) {
    cubo = criar_cubo(0.0, 0.0, -6.0, 2.0);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Trabalho M1 - Cubo 3D");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboard_special);

    imprimir_controles();
    glutMainLoop();

    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    desenhar(cubo);

    glutSwapBuffers();
}

void reshape(int largura, int altura) {
    if (altura == 0) {
        altura = 1;
    }

    const double proporcao = static_cast<double>(largura) / static_cast<double>(altura);
    const double plano_proximo = 1.0;
    const double plano_distante = 100.0;
    const double campo_visao = 60.0;
    const double topo = std::tan(graus_para_radianos(campo_visao / 2.0)) * plano_proximo;
    const double direita = topo * proporcao;

    glViewport(0, 0, largura, altura);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-direita, direita, -topo, topo, plano_proximo, plano_distante);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
    case 27: // Esc
        std::exit(0);
        break;

    // Rotacao no eixo X.
    case 'w':
    case 'W':
        rotacionar(cubo, PASSO_ROTACAO, 0.0, 0.0);
        break;
    case 's':
    case 'S':
        rotacionar(cubo, -PASSO_ROTACAO, 0.0, 0.0);
        break;

    // Rotacao no eixo Y.
    case 'a':
    case 'A':
        rotacionar(cubo, 0.0, -PASSO_ROTACAO, 0.0);
        break;
    case 'd':
    case 'D':
        rotacionar(cubo, 0.0, PASSO_ROTACAO, 0.0);
        break;

    // Rotacao no eixo Z.
    case 'q':
    case 'Q':
        rotacionar(cubo, 0.0, 0.0, PASSO_ROTACAO);
        break;
    case 'e':
    case 'E':
        rotacionar(cubo, 0.0, 0.0, -PASSO_ROTACAO);
        break;

    // Escala uniforme nos tres eixos.
    case '+':
    case '=':
        escalar(cubo, FATOR_ESCALA, FATOR_ESCALA, FATOR_ESCALA);
        break;
    case '-':
    case '_':
        escalar(cubo, 1.0 / FATOR_ESCALA, 1.0 / FATOR_ESCALA, 1.0 / FATOR_ESCALA);
        break;

    // Volta o cubo para o estado inicial.
    case 'r':
    case 'R':
        cubo = criar_cubo(0.0, 0.0, -6.0, 2.0);
        break;

    default:
        return;
    }

    glutPostRedisplay();
}

void keyboard_special(int key, int, int) {
    switch (key) {
    case GLUT_KEY_LEFT:
        movimentar(cubo, -PASSO_MOVIMENTO, 0.0, 0.0);
        break;
    case GLUT_KEY_RIGHT:
        movimentar(cubo, PASSO_MOVIMENTO, 0.0, 0.0);
        break;
    case GLUT_KEY_UP:
        movimentar(cubo, 0.0, PASSO_MOVIMENTO, 0.0);
        break;
    case GLUT_KEY_DOWN:
        movimentar(cubo, 0.0, -PASSO_MOVIMENTO, 0.0);
        break;
    case GLUT_KEY_PAGE_UP:
        movimentar(cubo, 0.0, 0.0, PASSO_MOVIMENTO);
        break;
    case GLUT_KEY_PAGE_DOWN:
        movimentar(cubo, 0.0, 0.0, -PASSO_MOVIMENTO);
        break;
    default:
        return;
    }

    glutPostRedisplay();
}

Poligono criar_cubo(double centro_x, double centro_y, double centro_z, double tamanho_lado) {
    Poligono novo_poligono;
    novo_poligono.tamanhoLado = tamanho_lado;
    novo_poligono.posicao = {centro_x, centro_y, centro_z};
    novo_poligono.escala = {1.0, 1.0, 1.0};
    novo_poligono.rotacao = {0.0, 0.0, 0.0};

    const double metade = tamanho_lado / 2.0;

    // Oito vertices do cubo descritos diretamente em torno do centro.
    novo_poligono.vertices = {
        {centro_x - metade, centro_y - metade, centro_z - metade}, // 0
        {centro_x + metade, centro_y - metade, centro_z - metade}, // 1
        {centro_x + metade, centro_y + metade, centro_z - metade}, // 2
        {centro_x - metade, centro_y + metade, centro_z - metade}, // 3
        {centro_x - metade, centro_y - metade, centro_z + metade}, // 4
        {centro_x + metade, centro_y - metade, centro_z + metade}, // 5
        {centro_x + metade, centro_y + metade, centro_z + metade}, // 6
        {centro_x - metade, centro_y + metade, centro_z + metade}  // 7
    };

    // Doze arestas: quatro de cada face paralela e quatro ligando as faces.
    novo_poligono.arestas = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    return novo_poligono;
}

void movimentar(Poligono& poligono, double deslocamento_x, double deslocamento_y, double deslocamento_z) {
    // A translacao e calculada diretamente, sem glTranslate.
    poligono.posicao.x += deslocamento_x;
    poligono.posicao.y += deslocamento_y;
    poligono.posicao.z += deslocamento_z;

    for (Vertice& vertice : poligono.vertices) {
        vertice.x += deslocamento_x;
        vertice.y += deslocamento_y;
        vertice.z += deslocamento_z;
    }
}

void escalar(Poligono& poligono, double escala_x, double escala_y, double escala_z) {
    // Cada vertice e convertido para coordenadas relativas ao centro, escalado
    // e colocado novamente no espaco. Assim o centro do cubo permanece fixo.
    for (Vertice& vertice : poligono.vertices) {
        vertice.x = poligono.posicao.x + (vertice.x - poligono.posicao.x) * escala_x;
        vertice.y = poligono.posicao.y + (vertice.y - poligono.posicao.y) * escala_y;
        vertice.z = poligono.posicao.z + (vertice.z - poligono.posicao.z) * escala_z;
    }

    poligono.escala.x *= escala_x;
    poligono.escala.y *= escala_y;
    poligono.escala.z *= escala_z;
}

void rotacionar(Poligono& poligono, double angulo_x, double angulo_y, double angulo_z) {
    const double radianos_x = graus_para_radianos(angulo_x);
    const double radianos_y = graus_para_radianos(angulo_y);
    const double radianos_z = graus_para_radianos(angulo_z);

    const double cos_x = std::cos(radianos_x);
    const double sin_x = std::sin(radianos_x);
    const double cos_y = std::cos(radianos_y);
    const double sin_y = std::sin(radianos_y);
    const double cos_z = std::cos(radianos_z);
    const double sin_z = std::sin(radianos_z);

    for (Vertice& vertice : poligono.vertices) {
        // Trabalha sempre em relacao ao centro do poligono.
        double x = vertice.x - poligono.posicao.x;
        double y = vertice.y - poligono.posicao.y;
        double z = vertice.z - poligono.posicao.z;

        // Rotacao no eixo X.
        double novo_y = y * cos_x - z * sin_x;
        double novo_z = y * sin_x + z * cos_x;
        y = novo_y;
        z = novo_z;

        // Rotacao no eixo Y.
        double novo_x = x * cos_y + z * sin_y;
        novo_z = -x * sin_y + z * cos_y;
        x = novo_x;
        z = novo_z;

        // Rotacao no eixo Z.
        novo_x = x * cos_z - y * sin_z;
        novo_y = x * sin_z + y * cos_z;
        x = novo_x;
        y = novo_y;

        vertice.x = poligono.posicao.x + x;
        vertice.y = poligono.posicao.y + y;
        vertice.z = poligono.posicao.z + z;
    }

    poligono.rotacao.x += angulo_x;
    poligono.rotacao.y += angulo_y;
    poligono.rotacao.z += angulo_z;
}

void desenhar(const Poligono& poligono) {
    glColor3f(0.0f, 0.0f, 0.0f);

    // O cubo e desenhado somente pelas arestas, conforme solicitado.
    glBegin(GL_LINES);
    for (const aresta& linha : poligono.arestas) {
        const Vertice& origem = poligono.vertices[linha.first];
        const Vertice& destino = poligono.vertices[linha.second];

        glVertex3d(origem.x, origem.y, origem.z);
        glVertex3d(destino.x, destino.y, destino.z);
    }
    glEnd();
}

double graus_para_radianos(double graus) {
    return graus * PI / 180.0;
}

void imprimir_controles() {
    std::cout
        << "Controles:\n"
        << "  Setas             : mover em X/Y\n"
        << "  Page Up/Page Down : mover em Z\n"
        << "  W/S                : rotacionar no eixo X\n"
        << "  A/D                : rotacionar no eixo Y\n"
        << "  Q/E                : rotacionar no eixo Z\n"
        << "  +/-                : aumentar/diminuir escala\n"
        << "  R                  : restaurar cubo\n"
        << "  Esc                : sair\n";
}
