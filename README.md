# ProyectoFinal
## Proyecto Final de Laboratorio de Computación Gráfica e Interacción Humano - Computadora
## De La Merced Soriano Uriel Benjamín - 319074473

Este documento proporciona una guía completa de la estructura y organización del archivo `Main.cpp`, que es el núcleo de la aplicación gráfica basada en OpenGL. El proyecto utiliza una arquitectura modular para gestionar múltiples escenarios (Acuario, Selva, Sabana, Desierto) con animales y texturas.

---

## Tabla de Contenidos

1. [Librerías y Headers](#1-librerías-y-headers)
2. [Prototipos de Callbacks](#2-prototipos-de-callbacks)
3. [Configuración Inicial y Variables Globales](#3-configuración-inicial-y-variables-globales)
4. [Animaciones y Posiciones Base de Animales](#4-animaciones-y-posiciones-base-de-animales)
5. [Vértices del Cubo](#5-vértices-del-cubo)
6. [Función pataDraw()](#6-función-patadraw)
7. [Función cuboDraw()](#7-función-cubodraw)
8. [Función main() - Inicio](#8-función-main---inicio)
9. [Inicialización de GLFW, GLEW y Ventana](#9-inicialización-de-glfw-glew-y-ventana)
10. [Carga de Modelos y Texturas](#10-carga-de-modelos-y-texturas)
11. [Configuración de Vértices para Primitivas](#11-configuración-de-vértices-para-primitivas)
12. [Ciclo de Renderizado (Game Loop)](#12-ciclo-de-renderizado-game-loop)
13. [Iluminación](#13-iluminación)
14. [Dibujo de Escenarios](#14-dibujo-de-escenarios)
15. [Funciones Auxiliares](#15-funciones-auxiliares)
16. [Callbacks de Entrada](#16-callbacks-de-entrada)
17. [Estructura de Carpetas](#17-estructura-de-carpetas)

---

## 1. Librerías y Headers

### Librerías Estándar
```cpp
#include <iostream>     // Entrada/Salida estándar
#include <cmath>        // Funciones matemáticas
```

### GLEW (OpenGL Extension Wrangler)
```cpp
#include <GL/glew.h>    // Gestor de extensiones de OpenGL
```

### GLFW (Graphics Library Framework)
```cpp
#include <GLFW/glfw3.h> // Gestor de ventanas y eventos
```

### Librerías de Utilidad
```cpp
#include "stb_image.h"   // Carga de imágenes (texturas)
#include "SOIL2/SOIL2.h" // Gestor alternativo de texturas
```

### GLM (OpenGL Mathematics)
```cpp
#include <glm/glm.hpp>                    // Matemáticas vectoriales y matriciales
#include <glm/gtc/matrix_transform.hpp>   // Funciones de transformación
#include <glm/gtc/type_ptr.hpp>           // Conversión de tipos GLM a punteros
```

### Headers Personalizados
```cpp
#include "Shader.h"     // Clase para gestión de shaders
#include "Camera.h"     // Clase para gestión de cámara
#include "Model.h"      // Clase para carga de modelos 3D
```

---

## 2. Prototipos de Callbacks

Los prototipos de funciones utilizadas como callbacks para GLFW:

```cpp
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
// Maneja eventos de teclado

void MouseCallback(GLFWwindow* window, double xPos, double yPos);
// Maneja movimiento del ratón

void DoMovement();
// Procesa el movimiento de la cámara basado en teclas presionadas
```

### Prototipos de Funciones Auxiliares
```cpp
void ConfigurarTexturaRepetible(GLuint textureID);
// Configura parámetros de repetición de texturas

void DibujarPiso(GLuint textureID, glm::vec3 posicion, glm::vec3 escala, GLuint VAO_Cubo, GLint modelLoc);
// Dibuja pisos con texturas
```

---

## 3. Configuración Inicial y Variables Globales

### Propiedades de la Ventana
```cpp
const GLuint WIDTH = 1000, HEIGHT = 800;  // Resolución: 1000x800 píxeles
int SCREEN_WIDTH, SCREEN_HEIGHT;          // Variables para almacenar tamaño real
```

### Configuración de la Cámara
```cpp
Camera camera(glm::vec3(0.0f, 0.0f, 21.0f));  // Posición inicial de la cámara
GLfloat lastX = WIDTH / 2.0;                   // Posición X anterior del ratón
GLfloat lastY = HEIGHT / 2.0;                  // Posición Y anterior del ratón
bool keys[1024];                               // Array para rastrear teclas presionadas
bool firstMouse = true;                        // Bandera para primer movimiento de ratón
```

### Posiciones de Luces
```cpp
glm::vec3 lightPos(1.5f, 2.0f, -2.5f);   // Posición de luz principal
glm::vec3 lightPos2(-1.5f, 2.0f, -2.5f); // Posición de luz secundaria
bool active;                              // Bandera para activar/desactivar luz

// Posiciones para luces puntuales en las 4 esquinas del mapa
glm::vec3 pointLightPositions[] = {
    glm::vec3(2.0f, 0.2f,  2.0f),   // Esquina 1 (+X, +Z)
    glm::vec3(-2.0f, 0.2f,  2.0f),  // Esquina 2 (-X, +Z)
    glm::vec3(2.0f, 0.2f, -2.0f),   // Esquina 3 (+X, -Z)
    glm::vec3(-2.0f, 0.2f, -2.0f)   // Esquina 4 (-X, -Z)
};

glm::vec3 Light1 = glm::vec3(0);    // Color dinámico de luz
```

### Variables de Control de Tiempo
```cpp
GLfloat deltaTime = 0.0f;  // Tiempo transcurrido entre frames
GLfloat lastFrame = 0.0f;   // Tiempo del frame anterior
```

---

## 4. Animaciones y Posiciones Base de Animales

### Pingüino (Cuadrante X, -Z)
```cpp
float PinAlaIzq = 0.0f;                                // Rotación del ala izquierda
float PinAlaDer = 0.0f;                                // Rotación del ala derecha
float PinScale = 0.70f;                                // Escala del pingüino
glm::vec3 PinguinoPos = glm::vec3(10.0f, -0.1f, -4.0f); // Posición base

bool animarPinguino = false;                           // Estado de animación
float startTimePinguino = 0.0f;                        // Tiempo de inicio
bool teclaC_presionada = false;                        // Control de teclado

// Activación: Tecla 'C' para animar, Tecla 'V' para detener
```

**Descripción:** El pingüino aletea sus alas de manera alternada. La animación es cíclica y se controla mediante rotaciones en el eje X de las alas.

### Foca (Cuadrante X, -Z)
```cpp
float rotFocaMedio = 0.0f;                             // Rotación de la sección media
float rotFocaCola = 0.0f;                              // Rotación de la cola
float FocaScale = 1.6f;                                // Escala de la foca
glm::vec3 focaPosBase = glm::vec3(5.0f, -0.17f, -9.0f); // Posición inicial
glm::vec3 focaPosActual = focaPosBase;                 // Posición animada actual
float focaRotY = -90.0f;                               // Rotación en el eje Y (orientación)

float rotFocaPataDer = 0.0f;                           // Rotación aleta derecha
float rotFocaPataIzq = 0.0f;                           // Rotación aleta izquierda

bool animarFoca = false;                               // Estado de animación
float startTimeFoca = 0.0f;                            // Tiempo de inicio
bool teclaB_presionada = false;                        // Control de teclado

// Activación: Tecla 'B' para animar, Tecla 'N' para detener
```

**Descripción:** La foca nada en línea recta, alternando entre desplazarse en una dirección, girar 180° y regresar. Sus aletas se mueven continuamente durante el movimiento.

**Jerarquía de Transformaciones:**
- Cuerpo (Padre) → Medio (Hijo) → Cola (Hijo del Medio)
- Cuerpo → Aleta Derecha
- Cuerpo → Aleta Izquierda

### Delfín (Cuadrante X, -Z)
```cpp
glm::vec3 delfinPosBase = glm::vec3(2.8f, -0.9f, -10.7f); // Posición inicial
glm::vec3 delfinPosActual = delfinPosBase;             // Posición animada
float delfinRotY = -90.0f;                             // Rotación en Y (dirección)
float delfinRotX = 0.0f;                               // Cabeceo (pitch)
float DelfinScale = 0.8f;                              // Escala del delfín

bool animarDelfin = false;                             // Estado de animación
float startTimeDelfin = 0.0f;                          // Tiempo de inicio
bool teclaD_presionada = false;                        // Control de teclado

// Activación: Tecla 'X' para animar, Tecla 'Z' para detener
```

**Descripción:** El delfín realiza saltos en arco. Se desplaza en el eje X mientras salta hacia arriba en el eje Y, crea un efecto de salto parabólico, gira 180° y repite.

---

## 5. Vértices del Cubo

Los vértices del cubo se definen con información de **posición**, **normal** y **coordenadas de textura**. Cada vértice contiene 8 floats:

```
[X, Y, Z] | [NX, NY, NZ] | [U, V]
```

### Estructura del Arreglo
```cpp
float vertices[] = {
    // Cara Trasera (-Z)
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
    // ... (6 caras = 36 vértices en total)
    
    // Caras Superior e Inferior - MODIFICADAS PARA REPETIR TEXTURA
    // Usan coordenadas UV de 0.0 a 10.0 para repetir 10 veces
};
```

### Especificación de Caras
- **Cara Trasera (-Z):** Normal = [0, 0, -1]
- **Cara Frontal (+Z):** Normal = [0, 0, 1]
- **Cara Izquierda (-X):** Normal = [-1, 0, 0]
- **Cara Derecha (+X):** Normal = [1, 0, 0]
- **Cara Inferior (-Y):** Normal = [0, -1, 0] | Coordenadas UV: 0.0 a 10.0 (repetida)
- **Cara Superior (+Y):** Normal = [0, 1, 0] | Coordenadas UV: 0.0 a 10.0 (repetida)

**Total de vértices:** 36 (6 caras × 6 vértices por cara)

---

## 6. Función pataDraw()

Dibuja un cubo escalable con textura, utilizado para crear estructuras como patas, paredes, etc.

```cpp
void pataDraw(glm::mat4 modelo, glm::vec3 escala, glm::vec3 traslado, 
              GLint uniformModel, GLuint VAO, GLuint texturaID)
```

### Parámetros
- `modelo`: Matriz de transformación base
- `escala`: Vector de escala [X, Y, Z]
- `traslado`: Vector de posición [X, Y, Z]
- `uniformModel`: Ubicación del uniform "model" en el shader
- `VAO`: Vertex Array Object del cubo
- `texturaID`: ID de la textura a aplicar

### Proceso
1. Crear matriz identidad
2. Aplicar escala
3. Aplicar traslación
4. Activar texturas (difuso y especular)
5. Enlazar VAO
6. Habilitar atributos (posición, normal, textura)
7. Dibujar 36 vértices (cubo completo)

---

## 7. Función cuboDraw()

Similar a `pataDraw()`, pero con la diferencia de que aplica una **rotación adicional** en el eje Y.

```cpp
void cuboDraw(glm::mat4 modelo, glm::vec3 escala, glm::vec3 traslado, 
              GLint uniformModel, GLuint VAO, GLuint texturaID, float rotacion)
```

### Diferencia Principal
El orden de transformaciones es:
1. Traslación (primero)
2. Rotación en eje Y (segundo)
3. Escala (tercero)

### Orden de Matriz
```
modelo = Escala(Rotación(Traslación(modelo)))
```

---

## 8. Función main() - Inicio

### Estructura General

```cpp
int main()
{
    // Sección 1: Inicialización de GLFW, GLEW y Ventana
    // Sección 2: Carga de Shaders
    // Sección 3: Carga de Modelos
    // Sección 4: Carga de Texturas
    // Sección 5: Configuración de Vértices
    // Sección 6: Game Loop
    // Sección 7: Limpieza y Terminar
}
```

---

## 9. Inicialización de GLFW, GLEW y Ventana

### Paso 1: Inicializar GLFW
```cpp
glfwInit();
```

### Paso 2: Configurar Hints de GLFW
```cpp
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);      // OpenGL 3.3
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Para macOS
glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);            // Ventana no redimensionable
```

### Paso 3: Crear Ventana
```cpp
GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr);

if (nullptr == window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return EXIT_FAILURE;
}
```

### Paso 4: Establecer Contexto Actual
```cpp
glfwMakeContextCurrent(window);
glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
```

### Paso 5: Configurar Callbacks
```cpp
glfwSetKeyCallback(window, KeyCallback);          // Eventos de teclado
glfwSetCursorPosCallback(window, MouseCallback);  // Movimiento de ratón
glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Ratón oculto
```

### Paso 6: Inicializar GLEW
```cpp
glewExperimental = GL_TRUE;
if (GLEW_OK != glewInit()) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return EXIT_FAILURE;
}
```

### Paso 7: Configurar Viewport
```cpp
glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
```

---

## 10. Carga de Modelos y Texturas

### Carga de Shaders
```cpp
Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
```

### Estructura de Carpetas para Modelos

La carpeta `Models/` contiene todos los modelos 3D en formato OBJ:

```
Models/
├── piso.obj                    // Piso general
├── delfin.obj                  // Modelo del delfín
├── agua/
│   └── agua.obj               // Agua del acuario
├── pinguino/
│   ├── cuerpo.obj             // Cuerpo del pingüino
│   ├── arm1.obj               // Ala derecha
│   ├── aletIzq.obj            // Ala izquierda
│   ├── medio.obj              // Sección media
│   └── cola.obj               // Cola
├── foca/
│   ├── cuerpoFoca.obj         // Cuerpo principal
│   ├── medio.obj              // Sección media
│   ├── cola.obj               // Parte de cola
│   ├── FocaDer.obj            // Aleta derecha
│   └── FocaIzq.obj            // Aleta izquierda
├── iglu/
│   └── iglu3d.obj             // Estructura del iglú
├── huevo/
│   └── huevo.obj              // Huevo (decorativo)
└── pino/
    └── nievepino.obj          // Pino con nieve
```

### Carga de Modelos en Código
```cpp
Model Piso((char*)"Models/piso.obj");
Model Delfin((char*)"Models/delfin.obj");
Model cuerpoPin((char*)"Models/pinguino/cuerpo.obj");
Model arm1((char*)"Models/pinguino/arm1.obj");
Model arm2((char*)"Models/pinguino/aletIzq.obj");
Model Foca1((char*)"Models/foca/cuerpoFoca.obj");
Model FocaCo((char*)"Models/foca/medio.obj");
Model FocaMe((char*)"Models/foca/cola.obj");
// ... más modelos
```

### Estructura de Carpetas para Texturas

La carpeta `images/` contiene todas las texturas utilizadas en la aplicación:

```
images/
├── ladrillo.png               // Textura de piso general
├── pasto.jpg                  // Textura de entrada
├── textnieve.jpg              // Textura del piso del acuario
├── selva.jpg                  // Textura del piso de selva
├── sabana.jpg                 // Textura del piso de sabana
├── sand.jpg                   // Textura de arena/desierto
├── madera.jpg                 // Textura de madera (objetos decorativos)
├── textverde.jpg              // Textura verde
├── textamarillo.jpg           // Textura amarilla
└── cafe.jpg                   // Textura café
```

### Carga de Texturas en Código
```cpp
GLuint armTextureID = TextureFromFile("images/madera.jpg", ".");
GLuint greenTextureID = TextureFromFile("images/textverde.jpg", ".");
GLuint amarilloTextureID = TextureFromFile("images/textamarillo.jpg", ".");
GLuint cafeTextureID = TextureFromFile("images/cafe.jpg", ".");

// Texturas de pisos
GLuint pisoTextureID = TextureFromFile("images/ladrillo.png", ".");
ConfigurarTexturaRepetible(pisoTextureID);

GLuint pisoEntradaID = TextureFromFile("images/pasto.jpg", ".");
ConfigurarTexturaRepetible(pisoEntradaID);

GLuint pisoAcuarioTextureID = TextureFromFile("images/textnieve.jpg", ".");
ConfigurarTexturaRepetible(pisoAcuarioTextureID);

GLuint pisoSelvaTextureID = TextureFromFile("images/selva.jpg", ".");
ConfigurarTexturaRepetible(pisoSelvaTextureID);

GLuint pisoSabanaTextureID = TextureFromFile("images/sabana.jpg", ".");
ConfigurarTexturaRepetible(pisoSabanaTextureID);

GLuint pisoArenaTextureID = TextureFromFile("images/sand.jpg", ".");
ConfigurarTexturaRepetible(pisoArenaTextureID);
```

---

## 11. Configuración de Vértices para Primitivas

### VAO y VBO Generales
```cpp
GLuint VBO, VAO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// Atributo de Posición (Location 0)
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
glEnableVertexAttribArray(0);

// Atributo de Normal (Location 1)
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 
                      (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
```

### VAO para Cubos (con Coordenadas de Textura)
```cpp
GLuint VBO_Cubo, VAO_Cubo;
glGenVertexArrays(1, &VAO_Cubo);
glGenBuffers(1, &VBO_Cubo);
glBindVertexArray(VAO_Cubo);

glBindBuffer(GL_ARRAY_BUFFER, VBO_Cubo);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// Stride = 8 floats (3 pos + 3 norm + 2 tex)

// Atributo de Posición
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

// Atributo de Normal
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 
                      (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);

// Atributo de Coordenadas de Textura
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 
                      (void*)(6 * sizeof(float)));
glEnableVertexAttribArray(2);

glBindVertexArray(0);
```

### VAO para Entrada
```cpp
GLuint VBO_Entrada, VAO_Entrada;
glGenVertexArrays(1, &VAO_Entrada);
glGenBuffers(1, &VBO_Entrada);
// ... Configuración similar a VAO_Cubo
```

### Configuración de Uniforms de Texturas
```cpp
lightingShader.Use();
glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);
```

---

## 12. Ciclo de Renderizado (Game Loop)

### Estructura del Loop
```cpp
while (!glfwWindowShouldClose(window))
{
    // 1. Calcular deltaTime
    // 2. Procesar Eventos (Polling y Callbacks)
    // 3. Limpiar Buffers
    // 4. Configurar Iluminación
    // 5. Dibujar Escenarios y Animales
    // 6. Intercambiar Buffers
}
```

### Cálculo de DeltaTime
```cpp
GLfloat currentFrame = glfwGetTime();
deltaTime = currentFrame - lastFrame;
lastFrame = currentFrame;
```

### Limpieza de Buffers
```cpp
glClearColor(0.6f, 0.7f, 0.9f, 1.0f);  // Color azul claro
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glEnable(GL_DEPTH_TEST);  // Habilitar prueba de profundidad
```

### Procesamiento de Eventos
```cpp
glfwPollEvents();
DoMovement();
```

---

## 13. Iluminación

### Luz Direccional (Directional Light)
```cpp
glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), 
            -0.2f, -1.0f, -0.3f);
glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 
            0.05f, 0.05f, 0.05f);
glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 
            0.6f, 0.6f, 0.6f);
glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 
            0.6f, 0.6f, 0.6f);
```

**Propósito:** Iluminación general que simula la luz del sol desde una dirección constante.

### Luces Puntuales (Point Lights)
Se configuran 4 luces puntuales en las esquinas del mapa:

```cpp
// Point Light 0 - Dinámica (colores que cambian)
glm::vec3 lightColor;
lightColor.x = abs(sin(glfwGetTime() * Light1.x));
lightColor.y = abs(sin(glfwGetTime() * Light1.y));
lightColor.z = sin(glfwGetTime() * Light1.z);

glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), 
            pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 
            lightColor.x, lightColor.y, lightColor.z);
glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 
            lightColor.x, lightColor.y, lightColor.z);
glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 
            1.0f, 1.0f, 0.0f);
glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);
```

**Point Lights 1-3:** Se configuran con valores de atenuación variables pero sin luz activa inicialmente.

### Luz Tipo Spotlight (Linterna)
```cpp
glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), 
            camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), 
            camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 
            0.8f, 0.8f, 0.8f);
glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 
            0.8f, 0.8f, 0.8f);
glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 
            1.0f, 1.0f, 1.0f);
glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), 
            glm::cos(glm::radians(6.0f)));
glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), 
            glm::cos(glm::radians(10.0f)));
```

**Propósito:** Simula una linterna que sigue la cámara, proporcionando iluminación local.

### Propiedades de Material
```cpp
glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 2.0f);
```

---

## 14. Dibujo de Escenarios

### Distribución del Mapa

El mapa se divide en 4 cuadrantes principales:

```
           (-X,+Z)          (+X,+Z)
           [SELVA]          [ACUARIO]
              |________________|
              |                |
              |                |
              |______ ________|
              |        |        |
           (-X,-Z)    (0,0)    (+X,-Z)
           [SABANA]  [ENTRADA] [ACUARIO]
```

### Piso General
```cpp
DibujarPiso(pisoTextureID, glm::vec3(0.0f, -0.5f, 0.0f), 
            glm::vec3(25.0f, 0.1f, 25.0f), VAO_Cubo, modelLoc);
```

**Posición:** Centro del mapa  
**Escala:** 25 × 0.1 × 25 (muy extendido horizontalmente, delgado verticalmente)

### Piso de Entrada (Pasto)
```cpp
DibujarPiso(pisoEntradaID, glm::vec3(0.0f, -0.5f, 17.5f), 
            glm::vec3(25.0f, 0.1f, 10.0f), VAO_Cubo, modelLoc);
```

**Posición:** Frente al mapa (Z positivo)

---

## 15. Funciones Auxiliares

### ConfigurarTexturaRepetible()
```cpp
void ConfigurarTexturaRepetible(GLuint textureID)
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}
```

**Propósito:** Configura una textura para que se repita cuando las coordenadas UV superan 1.0.

### DibujarPiso()
```cpp
void DibujarPiso(GLuint textureID, glm::vec3 posicion, glm::vec3 escala, 
                 GLuint VAO_Cubo, GLint modelLoc)
{
    // Activar texturas
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Enlazar VAO
    glBindVertexArray(VAO_Cubo);
    
    // Habilitar atributos
    glEnableVertexAttribArray(0); // Posición
    glEnableVertexAttribArray(1); // Normal
    glEnableVertexAttribArray(2); // TexCoords
    
    // Matriz de transformación
    glm::mat4 model_piso = glm::mat4(1.0f);
    model_piso = glm::translate(model_piso, posicion);
    model_piso = glm::scale(model_piso, escala);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_piso));
    
    // Dibujar
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
```

**Propósito:** Dibuja un cubo escalable y texturizado que actúa como piso.

---

## 16. Callbacks de Entrada

### DoMovement()
```cpp
void DoMovement()
{
    // Movimiento de cámara
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
        camera.ProcessKeyboard(RIGHT, deltaTime);
    
    // Control de luces
    if (keys[GLFW_KEY_H])
        pointLightPositions[0].y -= 0.01f;
    if (keys[GLFW_KEY_U])
        pointLightPositions[0].z -= 0.1f;
    if (keys[GLFW_KEY_J])
        pointLightPositions[0].z += 0.01f;
}
```

### KeyCallback()

**Controles Principales:**
- **ESC:** Cerrar aplicación
- **Teclas WASD / Flechas:** Mover cámara
- **Espacio:** Activar/desactivar luz dinámica
- **C:** Animar pingüino
- **V:** Detener animación del pingüino
- **B:** Animar foca
- **N:** Detener animación de foca
- **X:** Animar delfín
- **Z:** Detener animación de delfín

### MouseCallback()
```cpp
void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement(xOffset, yOffset);
}
```

**Propósito:** Permite rotar la cámara con el movimiento del ratón.

---

## 17. Estructura de Carpetas

### Estructura Recomendada del Proyecto

```
ProyectoFinal/
│
├── Project1/
│   ├── Main.cpp                  # Archivo principal (este documento)
│   ├── Shader.h                  # Clase para gestión de shaders
│   ├── Camera.h                  # Clase para gestión de cámara
│   ├── Model.h                   # Clase para carga de modelos
│   │
│   ├── Shader/
│   │   ├── lighting.vs           # Vertex shader de iluminación
│   │   ├── lighting.frag         # Fragment shader de iluminación
│   │   ├── lamp.vs               # Vertex shader de lámparas
│   │   └── lamp.frag             # Fragment shader de lámparas
│   │
│   ├── Models/
│   │   ├── piso.obj              # Modelo del piso base
│   │   ├── delfin.obj            # Modelo del delfín
│   │   ├── agua/
│   │   │   └── agua.obj          # Agua (acuario)
│   │   ├── pinguino/
│   │   │   ├── cuerpo.obj
│   │   │   ├── arm1.obj
│   │   │   ├── aletIzq.obj
│   │   │   ├── medio.obj
│   │   │   └── cola.obj
│   │   ├── foca/
│   │   │   ├── cuerpoFoca.obj
│   │   │   ├── medio.obj
│   │   │   ├── cola.obj
│   │   │   ├── FocaDer.obj
│   │   │   └── FocaIzq.obj
│   │   ├── iglu/
│   │   │   └── iglu3d.obj
│   │   ├── huevo/
│   │   │   └── huevo.obj
│   │   └── pino/
│   │       └── nievepino.obj
│   │
│   └── images/
│       ├── ladrillo.png          # Textura piso general
│       ├── pasto.jpg             # Textura entrada
│       ├── textnieve.jpg         # Textura acuario
│       ├── selva.jpg             # Textura selva
│       ├── sabana.jpg            # Textura sabana
│       ├── sand.jpg              # Textura desierto
│       ├── madera.jpg            # Textura decorativa
│       ├── textverde.jpg         # Textura decorativa
│       ├── textamarillo.jpg      # Textura decorativa
│       └── cafe.jpg              # Textura decorativa
│
├── README.md                     # Este archivo
├── README_Acuario.md             # Documentación del acuario
├── Project1.sln                  # Solución de Visual Studio
└── .gitignore

```

### Convenciones de Nombres

- **Modelos OBJ:** Nombres en minúsculas, sin espacios
  - Ejemplo: `cuerpoFoca.obj`, `nievepino.obj`
  
- **Texturas:** Nombres descriptivos en minúsculas
  - Ejemplo: `textnieve.jpg`, `ladrillo.png`
  
- **Shaders:** Extensiones `.vs` (vertex) y `.frag` (fragment)
  - Ejemplo: `lighting.vs`, `lighting.frag`

---

## Notas Importantes

### Optimización de Memoria
- Las texturas se cargan una sola vez en memoria
- Los modelos se reutilizan en varias jerarquías de animales
- Se usa blending para transparencias

### Jerarquía de Transformaciones
Las transformaciones se aplican en orden de **escala → rotación → traslación** en el código, pero matemáticamente se multiplican en orden inverso (traslación · rotación · escala · vértice).

### Animación
- Las animaciones utilizan `glfwGetTime()` para obtener tiempo global
- El deltaTime se usa para movimiento suave independiente de FPS
- Las funciones seno y coseno generan movimientos cíclicos

### Iluminación
- Se utiliza un modelo Phong completo con 3 tipos de luces
- Las texturas especulares se aplican en la ubicación 1
- El brillo del material se controla con `material.shininess`

---

## Referencias

- **OpenGL:** https://learnopengl.com/
- **GLFW:** https://www.glfw.org/
- **GLM:** https://glm.g-truc.net/
- **Assimp:** https://www.assimp.org/

---

**Autor:** Uriel Benjamín De La Merced Soriano
