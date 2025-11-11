# Documentación - Escenario Desierto

## Hábitat: Desierto (-X, +Z)

El desierto es un escenario árido ubicado en el cuadrante **(-X, +Z)** del mapa. Este hábitat alberga tres animales únicos: el Camello, la Tortuga y el Cóndor, cada uno con animaciones complejas y jerárquicas.

---

## Tabla de Contenidos

1. [Descripción General](#descripción-general)
2. [Carga de Modelos](#carga-de-modelos)
3. [Carga de Texturas](#carga-de-texturas)
4. [Estructura del Escenario](#estructura-del-escenario)
5. [Animales del Desierto](#animales-del-desierto)
6. [Variables de Animación](#variables-de-animación)
7. [Sistema de Controles](#sistema-de-controles)
8. [Detalles Técnicos](#detalles-técnicos)

---

## Descripción General

**Coordenadas de Piso:**
- Posición: `glm::vec3(-7.25f, -0.49f, 7.25f)`
- Escala: `glm::vec3(10.5f, 0.1f, 10.5f)`
- Textura: Arena (`sand.jpg`)

---

## Carga de Modelos

### Estructura de Carpetas
```
Models/
├── oasis/
│   └── oasis.obj              // Oasis (estructura del escenario)
├── huesos/
│   └── huesos.obj             // Huesos (elemento decorativo)
├── tronco/
│   └── tronco.obj             // Tronco (elemento decorativo)
├── cactus/
│   └── Cactus.obj             // Cactus (elemento decorativo)
├── camello/
│   ├── CamelBody.obj          // Cuerpo principal del camello
│   ├── CamelCabeza.obj        // Cabeza del camello
│   ├── CamelPataizqEnfr.obj   // Pata delantera izquierda
│   ├── CamelPataEnfreDer.obj  // Pata delantera derecha
│   ├── CamelPataizqAtras.obj  // Pata trasera izquierda
│   └── CamelPataAtrasDer.obj  // Pata trasera derecha
├── tortuga/
│   ├── tortuga_cuerpo.obj     // Cuerpo de la tortuga
│   ├── tortuga_pata_izq.obj   // Pata izquierda
│   └── tortuga_pata_der.obj   // Pata derecha
└── condor/
    ├── condor_cuerpo.obj      // Cuerpo del cóndor
    ├── condor_cabeza.obj      // Cabeza del cóndor
    ├── condor_ala_der.obj     // Ala derecha
    └── condor_ala_izq.obj     // Ala izquierda
```

### Código de Carga
```cpp
// ====== ESCENARIO ======
Model Oasis((char*)"Models/oasis/oasis.obj");
Model Huesos((char*)"Models/huesos/huesos.obj");
Model Tronco((char*)"Models/tronco/tronco.obj");
Model Cactus((char*)"Models/cactus/Cactus.obj");

// ====== CAMELLO ======
Model CamelBody((char*)"Models/camello/CamelBody.obj");
Model CamelHead((char*)"Models/camello/CamelCabeza.obj");
Model CamelLeg_FL((char*)"Models/camello/CamelPataizqEnfr.obj");
Model CamelLeg_FR((char*)"Models/camello/CamelPataEnfreDer.obj");
Model CamelLeg_BL((char*)"Models/camello/CamelPataizqAtras.obj");
Model CamelLeg_BR((char*)"Models/camello/CamelPataAtrasDer.obj");

// ====== TORTUGA ======
Model TortugaBody((char*)"Models/tortuga/tortuga_cuerpo.obj");
Model TortugaLeg_FL((char*)"Models/tortuga/tortuga_pata_izq.obj");
Model TortugaLeg_FR((char*)"Models/tortuga/tortuga_pata_der.obj");

// ====== CÓNDOR ======
Model CondorBody((char*)"Models/condor/condor_cuerpo.obj");
Model CondorHead((char*)"Models/condor/condor_cabeza.obj");
Model CondorAla_Der((char*)"Models/condor/condor_ala_der.obj");
Model CondorAla_Izq((char*)"Models/condor/condor_ala_izq.obj");
```

---

## Carga de Texturas

La carpeta `images/` contiene las texturas utilizadas en el desierto:

```
images/
├── sand.jpg                   // Textura de arena para el piso
├── muro.jpg                   // Textura para las paredes
└── (texturas compartidas con otros hábitats)
```

### Código de Carga
```cpp
// *** TEXTURA PARA EL PISO DESIERTO ***
GLuint pisoArenaTextureID = TextureFromFile("images/sand.jpg", ".");
ConfigurarTexturaRepetible(pisoArenaTextureID);

// *** TEXTURA PARA LAS PAREDES ***
GLuint paredTextureID = TextureFromFile("images/muro.jpg", ".");
ConfigurarTexturaRepetible(paredTextureID);
```

---

## Estructura del Escenario

### Elementos Decorativos

#### Oasis
```cpp
glm::vec3 oasisPos(-9.5f, -0.64f, 9.5f);
glm::vec3 oasisScale(20.0f, 20.0f, 20.0f);
float oasisRot = 270.0f;
```

**Función:**
- Centro del escenario del desierto
- Proporciona agua y vegetación

#### Huesos
```cpp
glm::vec3 huesosPos(-8.5f, -0.6f, 4.0f);
glm::vec3 huesosScale(0.3f, 0.25f, 0.25f);
float huesosRot = 90.0f;
```

**Función:** Elemento decorativo que añade ambiente árido

#### Tronco
```cpp
glm::vec3 troncoPos(-6.8f, -0.5f, 6.0f);
glm::vec3 troncoScale(0.7f, 0.7f, 0.7f);
float troncoRot = 0.0f;
```

**Función:** Elemento decorativo de madera

#### Cactus
```cpp
glm::vec3 cactusPos(-6.0f, -0.5f, 3.7f);
glm::vec3 cactusScale(0.04f, 0.04f, 0.04f);
float cactusRot = 0.0f;
```

**Función:** Vegetación típica del desierto

---

## Animales del Desierto

### 1. Camello (Camel)

**Posición Base:**
```cpp
glm::vec3 camelPos = glm::vec3(-6.0f, -0.5f, 10.0f);
float rotCamel = 180.0f;
float camelScale = 0.65f;
```

**Descripción:**
El camello realiza una secuencia de movimiento donde camina hacia el cactus y simula estar comiendo.

**Fases de Animación:**

#### Fase 1: Caminata (0-8 segundos)
```cpp
// Movimiento: Z = 10.0 → Z = 5.0
float totalDist = 10.0f - 5.0f; // 5 unidades
camelPos.z = 10.0f - (t * (totalDist / 8.0f));

// Movimiento de patas alternadas
camelLegFL = sin(t * 2.0f) * 15.0f;   // Pata frontal izq
camelLegBR = sin(t * 2.0f) * 15.0f;   // Pata trasera der
camelLegFR = -sin(t * 2.0f) * 15.0f;  // Pata frontal der (opuesta)
camelLegBL = -sin(t * 2.0f) * 15.0f;  // Pata trasera izq (opuesta)

// Movimiento de cabeza
camelHead = sin(t * 0.5f) * 1.3f;
```

#### Fase 2: Comiendo (8-14 segundos)
```cpp
float t2 = t - 8.0f;
camelPos.z = 5.0f; // En el cactus

// Patas se detienen lentamente
camelLegFL = sin(t2 * 1.0f) * 5.0f;
camelLegFR = -camelLegFL;
camelLegBL = -camelLegFR;
camelLegBR = camelLegFR;

// Movimiento de cabeza: bajada y subida lenta
camelHead = abs(sin(t2 * 1.5f)) * 2.9f;
```

#### Fase 3: Reposo (14+ segundos)
```cpp
camelPos.z = 5.0f;
camelHead = 0.0f;
camelLegFL = camelLegFR = camelLegBL = camelLegBR = 0.0f;
```

**Jerarquía de Transformaciones:**
- **Cuerpo** (Padre) → Cabeza (Hijo)
- **Cuerpo** → Pata Delantera Izquierda
- **Cuerpo** → Pata Delantera Derecha
- **Cuerpo** → Pata Trasera Izquierda
- **Cuerpo** → Pata Trasera Derecha

**Pivotes de Rotación:**
```cpp
glm::vec3 camelPivotFL(0.3f, 1.2f, 0.5f);   // Pata frontal izq
glm::vec3 camelPivotFR(-0.3f, 1.2f, 0.5f);  // Pata frontal der
glm::vec3 camelPivotBL(0.3f, 1.2f, -0.5f);  // Pata trasera izq
glm::vec3 camelPivotBR(-0.3f, 1.2f, -0.5f); // Pata trasera der
```

---

### 2. Tortuga (Tortoise)

**Posición Base:**
```cpp
glm::vec3 tortugaPos = glm::vec3(-7.8f, -0.18f, 9.5f);
float rotTortuga = 0.0f;
float tortugaScale = 0.20f;
```

**Descripción:**
La tortuga simula caminar desde arena hacia el agua (oasis), sumergirse gradualmente y salir del otro lado.

**Fases de Animación:**

#### Fase 1: Caminata hacia el agua (0-2.5 segundos)
```cpp
tortugaPos.x = -7.8f - (t * 0.08f);
tortugaPos.y = -0.18f;
rotTortuga = 0.0f;
tortugaScale = 0.20f;
```

#### Fase 2: Entrada al agua (2.5-6.0 segundos)
```cpp
float t2 = t - 2.5f;
tortugaPos.x = -8.0f - (t2 * 0.4f);      // Avanza en el agua
tortugaPos.y = -0.18f - (t2 * 0.07f);    // Baja suavemente
tortugaScale = 0.20f - (t2 * 0.012f);    // Se achica
rotTortuga = sin(t2 * 0.5f) * 5.0f;      // Leve inclinación
```

#### Fase 3: Salida del agua (6.0-9.0 segundos)
```cpp
float t3 = t - 6.0f;
tortugaPos.x = -9.4f - (t3 * 0.7f);       // Sale del agua
tortugaPos.y = -0.425f + (t3 * 0.0483f);  // Sube gradualmente
tortugaScale = 0.19f + (t3 * 0.0033f);    // Crece
rotTortuga = t3 * 60.0f;                  // Giro progresivo
```

#### Fase 4: Reposo (9.0+ segundos)
```cpp
tortugaPos.x = -11.5f;
tortugaPos.y = -0.28f;
tortugaScale = 0.20f;
rotTortuga = 180.0f;
```

**Jerarquía de Transformaciones:**
- **Cuerpo** (Padre) → Pata Izquierda (Hijo)
- **Cuerpo** → Pata Derecha (Hijo)

**Pivotes de Rotación:**
```cpp
glm::vec3 tortugaPivotFL(0.2f, 0.3f, 0.3f);   // Pata frontal izq
glm::vec3 tortugaPivotFR(-0.2f, 0.3f, 0.3f);  // Pata frontal der
```

---

### 3. Cóndor (Condor)

**Posición Base:**
```cpp
glm::vec3 condorPos = glm::vec3(-6.7f, 0.5f, 6.0f);
float rotCondor = 90.0f;
float condorScale = 0.70f;
```

**Descripción:**
El cóndor vuela en círculos sobre el desierto, agitando sus alas y moviendo la cabeza.

**Animación Continua:**
```cpp
float t = glfwGetTime();

// Movimiento de alas (rápido y alternado)
condorAlaIzq = sin(t * 10.0f) * 1.5f;    // Frecuencia: 10 Hz
condorAlaDer = -condorAlaIzq;            // Opuesta

// Movimiento de cabeza (leve)
condorHead = sin(t * 8.0f) * 1.0f;       // Frecuencia: 8 Hz

// Movimiento vertical (flotación)
condorPos.y = 0.7f + sin(t * 0.8f) * 0.15f;  // Sube y baja suavemente
```

**Jerarquía de Transformaciones:**
- **Cuerpo** (Padre) → Cabeza (Hijo)
- **Cuerpo** → Ala Izquierda (Hijo)
- **Cuerpo** → Ala Derecha (Hijo)

**Pivotes de Rotación:**
```cpp
glm::vec3 condorPivotAlaIzq(0.5f, 0.5f, 0.0f);   // Ala izquierda
glm::vec3 condorPivotAlaDer(-0.5f, 0.5f, 0.0f);  // Ala derecha
```

---

## Variables de Animación

### Camello
```cpp
float rotCamel = 180.0f;           // Rotación en Y
float camelLegFL = 0.0f;           // Pata frontal izq
float camelLegFR = 0.0f;           // Pata frontal der
float camelLegBL = 0.0f;           // Pata trasera izq
float camelLegBR = 0.0f;           // Pata trasera der
float camelHead = 0.0f;            // Cabeza
float camelTail = 0.0f;            // Cola (reservado)
float camelScale = 0.65f;          // Escala
glm::vec3 camelPos = glm::vec3(-6.0f, -0.5f, 10.0f);

bool animarCamello = false;        // Control de animación
float startTimeCamello = 0.0f;     // Tiempo de inicio
bool teclaC_presionada = false;    // Control de teclado
```

### Tortuga
```cpp
float rotTortuga = 0.0f;           // Rotación en Y
float tortugaLegFL = 0.0f;         // Pata frontal izq
float tortugaLegFR = 0.0f;         // Pata frontal der
float tortugaScale = 0.20f;        // Escala
glm::vec3 tortugaPos = glm::vec3(-7.8f, -0.18f, 9.5f);

bool animarTortuga = false;        // Control de animación
float startTimeTortuga = 0.0f;     // Tiempo de inicio
bool teclaX_presionada = false;    // Control de teclado
```

### Cóndor
```cpp
float rotCondor = 90.0f;           // Rotación en Y
float condorHead = 0.0f;           // Cabeza
float condorAlaIzq = 0.0f;         // Ala izquierda
float condorAlaDer = 0.0f;         // Ala derecha
float condorScale = 0.70f;         // Escala
glm::vec3 condorPos = glm::vec3(-6.7f, 0.5f, 6.0f);

bool animarCondor = false;         // Control de animación
bool teclaZ_presionada = false;    // Control de teclado
```

---

## Sistema de Controles

### Activación de Animaciones

| Tecla | Animal | Acción |
|-------|--------|--------|
| **C** | Camello | Toggle animación (caminata y comida) |
| **X** | Tortuga | Toggle animación (caminata en agua) |
| **Z** | Cóndor | Toggle animación (vuelo) |

### Código de Controles
```cpp
// CAMELLO
if (keys[GLFW_KEY_C])
{
    if (!teclaC_presionada)
    {
        animarCamello = !animarCamello;
        startTimeCamello = glfwGetTime();
        teclaC_presionada = true;
    }
}
else
{
    teclaC_presionada = false;
}

// CÓNDOR
if (keys[GLFW_KEY_Z])
{
    if (!teclaZ_presionada)
    {
        animarCondor = !animarCondor;
        teclaZ_presionada = true;
    }
}
else
{
    teclaZ_presionada = false;
}

// TORTUGA
if (keys[GLFW_KEY_X])
{
    if (!teclaX_presionada)
    {
        animarTortuga = !animarTortuga;
        startTimeTortuga = glfwGetTime();
        teclaX_presionada = true;
    }
}
else
{
    teclaX_presionada = false;
}
```

---

## Detalles Técnicos

### Dibujo Jerárquico

#### Camello
```cpp
// 1. Cuerpo (base)
model = glm::mat4(1);
model = glm::translate(model, camelPos);
model = glm::rotate(model, glm::radians(rotCamel), glm::vec3(0.0f, 1.0f, 0.0f));
model = glm::scale(model, glm::vec3(camelScale));
modelTemp = model;
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
CamelBody.Draw(lightingShader);

// 2. Cabeza (rotación en X desde el cuerpo)
model = modelTemp;
model = glm::rotate(model, glm::radians(camelHead), glm::vec3(1.0f, 0.0f, 0.0f));
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
CamelHead.Draw(lightingShader);

// 3-6. Patas (rotación articulada desde pivotes)
glm::vec3 camelPivotFL(0.3f, 1.2f, 0.5f);
model = modelTemp;
model = glm::translate(model, camelPivotFL);
model = glm::rotate(model, glm::radians(camelLegFL), glm::vec3(1.0f, 0.0f, 0.0f));
model = glm::translate(model, -camelPivotFL);
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
CamelLeg_FL.Draw(lightingShader);
// ... (Similar para FR, BL, BR)
```

#### Tortuga
```cpp
// 1. Cuerpo (base)
model = glm::mat4(1);
model = glm::translate(model, tortugaPos);
model = glm::rotate(model, glm::radians(rotTortuga), glm::vec3(0.0f, 1.0f, 0.0f));
model = glm::scale(model, glm::vec3(tortugaScale));
modelTemp = model;
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
TortugaBody.Draw(lightingShader);

// 2-3. Patas (rotación desde pivotes)
glm::vec3 tortugaPivotFL(0.2f, 0.3f, 0.3f);
model = modelTemp;
model = glm::translate(model, tortugaPivotFL);
model = glm::rotate(model, glm::radians(tortugaLegFL), glm::vec3(1.0f, 0.0f, 0.0f));
model = glm::translate(model, -tortugaPivotFL);
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
TortugaLeg_FL.Draw(lightingShader);
// ... (Similar para FR)
```

#### Cóndor
```cpp
// 1. Cuerpo (base)
model = glm::mat4(1);
model = glm::translate(model, condorPos);
model = glm::rotate(model, glm::radians(rotCondor), glm::vec3(0.0f, 1.0f, 0.0f));
model = glm::scale(model, glm::vec3(condorScale));
modelTemp = model;
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
CondorBody.Draw(lightingShader);

// 2. Cabeza (rotación en X)
model = modelTemp;
model = glm::rotate(model, glm::radians(condorHead), glm::vec3(1.0f, 0.0f, 0.0f));
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
CondorHead.Draw(lightingShader);

// 3-4. Alas (rotación en Z desde pivotes)
glm::vec3 condorPivotAlaIzq(0.5f, 0.5f, 0.0f);
model = modelTemp;
model = glm::translate(model, condorPivotAlaIzq);
model = glm::rotate(model, glm::radians(condorAlaIzq), glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, -condorPivotAlaIzq);
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
CondorAla_Izq.Draw(lightingShader);
// ... (Similar para Ala Der)
```

### Función de Configuración VAO/VBO

```cpp
void ConfigurarVAO(GLuint& VAO, GLuint& VBO, float* vertices, size_t size)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    // Atributo de Posición (Location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atributo de Normal (Location 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Atributo de Coordenadas de Textura (Location 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}
```

---

## Resumen de Características

| Aspecto | Detalles |
|--------|----------|
| **Ubicación** | Cuadrante (-X, +Z) |
| **Animales** | Camello, Tortuga, Cóndor |
| **Elementos Decorativos** | Oasis, Huesos, Tronco, Cactus |
| **Textura de Piso** | Arena (sand.jpg) |
| **Textura de Paredes** | Muro (muro.jpg) |
| **Total de Modelos** | 14 archivos OBJ |
| **Tipos de Animación** | Caminata, Comida, Inmersión, Vuelo |
| **Técnica de Control** | Toggle (Teclas C, X, Z) |

---

**Última Actualización:** 2024  
**Versión:** 1.0  
**Parte del Proyecto:** Proyecto Final de Computación Gráfica
