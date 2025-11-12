# ?? Hábitat Selva - Documentación Completa

## ?? Tabla de Contenidos
1. [Descripción General](#descripción-general)
2. [Ubicación en el Mapa](#ubicación-en-el-mapa)
3. [Modelos 3D Cargados](#modelos-3d-cargados)
4. [Texturas Utilizadas](#texturas-utilizadas)
5. [Variables Globales de Control](#variables-globales-de-control)
6. [Elementos Decorativos](#elementos-decorativos)
7. [Animales Animados](#animales-animados)
8. [Sistema de Controles](#sistema-de-controles)
9. [Lógica de Animación Detallada](#lógica-de-animación-detallada)
10. [Jerarquía de Transformaciones](#jerarquía-de-transformaciones)
11. [Estructura de Archivos](#estructura-de-archivos)

---

## Descripción General

El **Hábitat Selva** es el tercer escenario implementado en el proyecto. Está ubicado en el cuadrante (X, Z) y contiene:

- **3 animales animados** con comportamientos específicos
- **12 elementos decorativos** para ambientación realista
- **1 textura personalizada** para el piso de la selva
- **23 modelos 3D** en total

**Estado:** ? Completamente implementado y funcional

---

## Ubicación en el Mapa

### Coordenadas
```
Cuadrante: (X, Z) - Selva (Superior Derecha)
Posición Centro: (7.25, 7.25)
Dimensión: 10.5 × 10.5 unidades
```

### Mapa Visual
```
         (-X,+Z)          (+X,+Z)
         [SELVA] ?      [SELVA] ?
            |________________|
            |                |
            |                |
            |______ ________|
            |        |        |
         (-X,-Z)    (0,0)    (+X,-Z)
         [SABANA]  [ENTRADA] [ACUARIO] ?
         
Ubicación: Cuadrante Superior Derecha
Piso: Textura de selva/bosque tropical
```

---

## Modelos 3D Cargados

### Total: 23 Modelos OBJ

#### ?? Elementos Decorativos (12 modelos)

| Elemento | Ruta | Variables | Posición | Escala | Rotación |
|----------|------|-----------|----------|--------|----------|
| **Árbol Selva** | `Models/arbolSelva/arbolSelva.obj` | `ArbolSelva` | (11.0, -0.5, 3.1) | (0.2, 0.2, 0.2) | 0° |
| **Sandía** | `Models/sandia/sandia.obj` | `Sandia` | (3.0, -0.2, 8.0) | (1.0, 1.0, 1.0) | 180° |
| **Tronco Selva 1** | `Models/troncoSelva/troncoSelva.obj` | `TroncoSelva1` | (10.0, -0.2, 11.0) | (1.0, 0.7, 1.0) | 0° |
| **Tronco Selva 2** | `Models/troncoSelva/troncoSelva.obj` | `TroncoSelva2` | (5.5, -0.2, 11.0) | (1.0, 0.5, 1.0) | 0° |
| **Pelota** | `Models/pelota/pelota.obj` | `Pelota` | (5.5, -0.2, 11.0) | (0.5, 0.5, 0.5) | 0° |
| **Plátano 1** | `Models/platano/platano.obj` | `Platano1` | (11.0, -0.4, 11.8) | (5.0, 5.0, 5.0) | 0° |
| **Plátano 2** | `Models/platano/platano.obj` | `Platano2` | (7.6, -0.4, 9.8) | (5.0, 5.0, 5.0) | 0° |
| **Gato** | `Models/platano/gato.obj` | `Gato` | (3.2, 0.0, 11.9) | (0.5, 0.5, 0.5) | 90° |
| **Árbol Rama** | `Models/arbolRama/arbolRama.obj` | `ArbolRama` | (11.0, 0.6, 6.0) | (2.5, 2.5, 2.5) | 0° |
| **Rama Selva** | `Models/ramaSelva/ramaSelva.obj` | `RamaSelva` | (3.0, 0.15, 6.0) | (2.5, 2.5, 4.0) | 0° |
| **Planta Selva 1** | `Models/plantaSelva/planta_selva.obj` | `PlantaSelva1` | (8.5, -0.3, 3.1) | (0.4, 0.4, 0.4) | 0° |
| **Planta Selva 2** | `Models/plantaSelva/planta_selva.obj` | `PlantaSelva2` | (11.0, -0.3, 9.5) | (0.4, 0.4, 0.4) | 0° |

#### ?? Flores (Lotos) - 3 modelos

| Loto | Ruta | Variables | Posición | Escala |
|------|------|-----------|----------|--------|
| **Loto 1** | `Models/loto/loto.obj` | `Loto1` | (6.5, -0.21, 3.1) | (1.0, 1.0, 1.0) |
| **Loto 2** | `Models/loto/loto.obj` | `Loto2` | (5.0, -0.21, 3.1) | (1.0, 1.0, 1.0) |
| **Loto 3** | `Models/loto/loto.obj` | `Loto3` | (3.5, -0.21, 3.1) | (1.0, 1.0, 1.0) |

#### ?? Animales Animados (8 componentes)

**CAPIBARA (7 componentes)**
```cpp
Model Capibara_Cabeza        ("Models/capibara/cabezaCapi.obj")
Model Capibara_Cuerpo        ("Models/capibara/cuerpoCapi.obj")
Model Capibara_Naranja       ("Models/capibara/naranjaCapi.obj")
Model Capibara_PataDelDer    ("Models/capibara/pataDelDerCapi.obj")
Model Capibara_PataDelIzq    ("Models/capibara/pataDelIzqCapi.obj")
Model Capibara_PataTrasDer   ("Models/capibara/pataTrasDerCapi.obj")
Model Capibara_PataTrasIzq   ("Models/capibara/pataTrasIzqCapi.obj")
```

**MONO (6 componentes)**
```cpp
Model Mono_Cuerpo            ("Models/mono/cuerpoMono.obj")
Model Mono_Cola              ("Models/mono/colaMono.obj")
Model Mono_PataDelDer        ("Models/mono/pataDelDerMono.obj")
Model Mono_PataDelIzq        ("Models/mono/pataDelIzqMono.obj")
Model Mono_PataTrasDer       ("Models/mono/pataTasDerMono.obj")
Model Mono_PataTrasIzq       ("Models/mono/pataTrasIzqMono.obj")
```

**GUACAMAYA (3 componentes)**
```cpp
Model Ave_Cuerpo             ("Models/aveSelva/cuerpoAve.obj")
Model Ave_AlaDer             ("Models/aveSelva/alaDerAve.obj")
Model Ave_AlaIzq             ("Models/aveSelva/alaIzqAve.obj")
```

---

## Texturas Utilizadas

### Textura del Piso Selva

```cpp
GLuint pisoSelvaTextureID = TextureFromFile("images/selva.png", ".");
ConfigurarTexturaRepetible(pisoSelvaTextureID);
```

| Aspecto | Valor |
|---------|-------|
| **Archivo** | `images/selva.png` |
| **Formato** | PNG (preferido por transparencia) |
| **Wrapping** | GL_REPEAT |
| **Filtrado** | GL_LINEAR_MIPMAP_LINEAR (MIN) |
| **Filtrado** | GL_LINEAR (MAG) |
| **Posición** | (7.25, -0.49, 7.25) |
| **Escala** | (10.5, 0.1, 10.5) |

---

## Variables Globales de Control

### CAPIBARA

```cpp
// Posición y rotación
float capibaraScale = 0.7f;              // Escala del modelo
float rotCapibara = 180.0f;              // Rotación en eje Y
glm::vec3 capibaraPos = glm::vec3(11.0f, 0.0f, 8.0f);  // Posición inicial

// Articulaciones
float capibaraCabezaRot = 0.0f;          // Rotación de cabeza
float capibaraNaranjaRot = 0.0f;         // Rotación de naranja/fruta
float capibaraPataDelDer = 0.0f;         // Pata delantera derecha
float capibaraPataDelIzq = 0.0f;         // Pata delantera izquierda
float capibaraPataTrasDer = 0.0f;        // Pata trasera derecha
float capibaraPataTrasIzq = 0.0f;        // Pata trasera izquierda

// Control de animación
bool animarCapibara = false;             // Flag de animación
float startTimeCapibara = 0.0f;          // Tiempo de inicio
bool teclaP_presionada = false;          // Flag para evitar repetición
```

### MONO

```cpp
// Posición y rotación
float monoScale = 0.8f;                  // Escala del modelo
float rotMono = 180.0f;                  // Rotación en eje Y
glm::vec3 monoPos = glm::vec3(11.0f, 0.0f, 11.0f);  // Posición inicial

// Articulaciones
float monoColaRot = 0.0f;                // Rotación de cola
float monoPataDelDer = 0.0f;             // Pata delantera derecha
float monoPataDelIzq = 0.0f;             // Pata delantera izquierda
float monoPataTrasDer = 0.0f;            // Pata trasera derecha
float monoPataTrasIzq = 0.0f;            // Pata trasera izquierda

// Control de animación
bool animarMono = false;                 // Flag de animación
float startTimeMono = 0.0f;              // Tiempo de inicio
bool teclaM_presionada = false;          // Flag para evitar repetición
```

### GUACAMAYA

```cpp
// Posición y rotación
float guacamayaScale = 1.0f;             // Escala del modelo
float rotGuacamaya = 270.0f;             // Rotación inicial en eje Y
glm::vec3 guacamayaPos = glm::vec3(11.1f, 1.55f, 6.5f);  // Posición inicial

// Articulaciones
float guacamayaAlaDer = 0.0f;            // Ala derecha
float guacamayaAlaIzq = 0.0f;            // Ala izquierda

// Control de animación
bool animarGuacamaya = false;            // Flag de animación
float startTimeGuacamaya = 0.0f;         // Tiempo de inicio
bool teclaO_presionada = false;          // Flag para evitar repetición
```

---

## Elementos Decorativos

### Distribución en el Escenario

```
ÁRBOL SELVA (11.0, -0.5, 3.1)
    ?? Pequeño y alejado
    ?? Primera línea de decoración

SANDÍA (3.0, -0.2, 8.0)
    ?? Centro-izquierda
    ?? Elemento de color

TRONCOS SELVA (10.0, -0.2, 11.0) y (5.5, -0.2, 11.0)
    ?? Segundo elemento de escenario
    ?? Madera caída

PELOTA (5.5, -0.2, 11.0)
    ?? Elemento jugable (para mono)
    ?? Interacción visual

PLÁTANOS (11.0, -0.4, 11.8) y (7.6, -0.4, 9.8)
    ?? Recursos para animales
    ?? Elementos de comida

GATO (3.2, 0.0, 11.9)
    ?? Elemento sorpresa
    ?? Propósito decorativo

ÁRBOL RAMA (11.0, 0.6, 6.0)
    ?? Percha para guacamaya
    ?? Elemento de altura

RAMA SELVA (3.0, 0.15, 6.0)
    ?? Fondo de escena
    ?? Elemento natural

PLANTAS SELVA (8.5, -0.3, 3.1) y (11.0, -0.3, 9.5)
    ?? Vegetación baja
    ?? Densidad del bosque

LOTOS (6.5, -0.21, 3.1), (5.0, -0.21, 3.1), (3.5, -0.21, 3.1)
    ?? Flores acuáticas
    ?? Detalles de agua
```

---

## Animales Animados

### 1. ?? CAPIBARA - "El Roedor Gigante"

**Información Base:**
- **Posición Inicial:** (11.0, 0.0, 8.0)
- **Escala:** 0.7
- **Rotación Y:** 180°
- **Tecla:** P (solo caminata)
- **Duración Total:** 16 segundos

**Componentes:**
1. Cuerpo (padre principal)
2. Cabeza (articulación Y)
3. Naranja/Fruta (rotación Y)
4. Pata Delantera Derecha (rotación Z)
5. Pata Delantera Izquierda (rotación Z)
6. Pata Trasera Derecha (rotación Z)
7. Pata Trasera Izquierda (rotación Z)

### 2. ?? MONO - "El Acróbata Saltarín"

**Información Base:**
- **Posición Inicial:** (11.0, 0.0, 11.0)
- **Escala:** 0.8
- **Rotación Y:** 180°
- **Tecla:** M
- **Duración Total:** 5.9 segundos

**Componentes:**
1. Cuerpo (padre principal)
2. Cola (articulación X - frontal/trasero)
3. Pata Delantera Derecha (rotación Z)
4. Pata Delantera Izquierda (rotación Z)
5. Pata Trasera Derecha (rotación Z)
6. Pata Trasera Izquierda (rotación Z)

### 3. ?? GUACAMAYA - "El Loro Volador"

**Información Base:**
- **Posición Inicial:** (11.1, 1.55, 6.5)
- **Escala:** 1.0
- **Rotación Y:** 270°
- **Tecla:** O
- **Duración Total:** 12 segundos

**Componentes:**
1. Cuerpo (padre principal)
2. Ala Derecha (rotación Z)
3. Ala Izquierda (rotación Z)

---

## Sistema de Controles

### Tabla de Teclas

| Tecla | Animal | Acción | Duración | Estado |
|-------|--------|--------|----------|--------|
| **P** | Capibara | Toggle Caminata/Comida | 16s | ? Implementado |
| **M** | Mono | Toggle Saltos/Caminata | 5.9s | ? Implementado |
| **O** | Guacamaya | Toggle Vuelo/Percha | 12s | ? Implementado |

### Código de Control en KeyCallback()

```cpp
// CAPIBARA - Tecla P
if (keys[GLFW_KEY_B])  // Nota: Usa GLFW_KEY_B (conflicto con Foca)
{
    if (!teclaP_presionada)
    {
        animarCapibara = !animarCapibara;
        startTimeCapibara = glfwGetTime();
        teclaP_presionada = true;
    }
}
else
{
    teclaP_presionada = false;
}

// MONO - Tecla M
if (keys[GLFW_KEY_M])
{
    if (!teclaM_presionada)
    {
        animarMono = !animarMono;
        startTimeMono = glfwGetTime();
        teclaM_presionada = true;
    }
}
else
{
    teclaM_presionada = false;
}

// GUACAMAYA - Tecla O
if (keys[GLFW_KEY_O])
{
    if (!teclaO_presionada)
    {
        animarGuacamaya = !animarGuacamaya;
        startTimeGuacamaya = glfwGetTime();
        teclaO_presionada = true;
    }
}
else
{
    teclaO_presionada = false;
}
```

---

## Lógica de Animación Detallada

### ?? CAPIBARA (16 segundos totales)

#### Fase 1: CAMINATA (0-10 segundos)
```
Movimiento X: 11.0 ? 4.0 (7 unidades de recorrido)
Velocidad: 0.7 unidades/segundo
Patas: Ciclo de caminar sincronizado
  - Pata FL: sin(t*6) * 1.5°
  - Pata FR: -sin(t*6) * 1.5°
  - Pata TR: sin(t*6) * 1.5°
  - Pata TL: -sin(t*6) * 1.5°
Naranja: Rotación continua t*180°/segundo
```

**Pseudocódigo:**
```cpp
if (t < 10.0f)
{
    float totalDist = 7.0f;
    capibaraPos.x = 11.0f - (t * (totalDist / 10.0f));
    
    float paso = sin(t * 6.0f);
    capibaraPataDelDer = paso * 1.5f;
    capibaraPataTrasDer = paso * 1.5f;
    capibaraPataDelIzq = -paso * 1.5f;
    capibaraPataTrasIzq = -paso * 1.5f;
    
    capibaraNaranjaRot = t * 180.0f;
    rotCapibara = 180.0f;
}
```

#### Fase 2: DETENIDO, COMIENDO (10-16 segundos)
```
Posición fija: X = 4.0
Patas: Movimiento pequeño y lento (0.5 Hz)
  - Amplitud: ±2.0°
Naranja: Regresa a posición inicial (0°)
  - Desaceleración suave
```

**Pseudocódigo:**
```cpp
else if (t < 16.0f)
{
    float t2 = t - 10.0f;
    capibaraPos.x = 4.0f;
    
    capibaraPataDelDer = sin(t2 * 0.5f) * 2.0f;
    capibaraPataDelIzq = -capibaraPataDelDer;
    capibaraPataTrasDer = -capibaraPataDelDer;
    capibaraPataTrasIzq = capibaraPataDelDer;
    
    capibaraNaranjaRot = 1800.0f - (t2 * 300.0f);
    rotCapibara = 180.0f;
}
```

---

### ?? MONO (5.9 segundos totales)

#### Fase 1: PRIMER BRINCO (0-1.5s)
```
Movimiento X: 11.0 ? 8.75
Altura Y: 0.0 ? 1.0 (arco de salto)
Patas: Recogidas durante salto (±8°)
Cola: Levantada (2.0° + salto*1.5°)
```

#### Fase 2: ATERRIZAJE 1 (1.5-1.7s)
```
Posición: X=8.75, Y=0.0
Patas: Relajadas (0°)
Cola: Baja (0.5°)
```

#### Fase 3: SEGUNDO BRINCO (1.7-3.2s)
```
Movimiento X: 8.75 ? 6.5
Altura: Repetir arco
Patas: Recogidas (±8°)
Cola: Levantada
```

#### Fase 4: ATERRIZAJE 2 (3.2-3.4s)
```
Posición: X=6.5, Y=0.0
Patas: Relajadas (0°)
Cola: Baja (0.5°)
```

#### Fase 5: TERCER BRINCO (3.4-4.9s)
```
Movimiento X: 6.5 ? 4.25
Altura: Arco de salto
Patas: Recogidas (±8°)
Cola: Levantada
```

#### Fase 6: CAMINATA (4.9-5.9s)
```
Movimiento X: 4.25 ? 3.0 (1 segundo de caminata)
Patas: Ciclo normal de caminata (±2°)
Cola: Movimiento suave sin(t2*2)*2°
```

---

### ?? GUACAMAYA (12 segundos totales)

#### Fase 1: VUELO HORIZONTAL (0-8s)
```
Trayectoria: X: 11.1 ? 3.1 (8 unidades)
             Y: 1.55 (altura constante)
             Z: 6.5 (sin cambio)
Velocidad: 1.0 unidades/segundo
Aleteo: sin(t*2.5) * 5°
  - Ala Derecha: +aleteo
  - Ala Izquierda: -aleteo
Rotación Y: 270° (mirando hacia el frente)
```

#### Fase 2: DESCENSO A LA RAMA (8-12s)
```
Movimiento X: 3.1 ? 3.0 (casi nada)
Altura Y: 1.55 ? 0.5 (descenso gradual)
Aleteo: 3.0° (planeando)
Rotación Y: 270°
```

**Fórmula de Descenso:**
```
Y(t) = 1.55 - (t2 * 0.2625)
donde t2 = t - 8.0
```

---

## Jerarquía de Transformaciones

### CAPIBARA - Estructura Jerárquica

```
CUERPO (Padre Principal)
?? Transformación Global: Traslación + Rotación Y + Escala
?
?? CABEZA (Hijo)
?  ?? Pivote: (0.0, 0.5, 0.4)
?     ?? Rotación Y: capibaraCabezaRot
?
?? NARANJA (Hijo)
?  ?? Pivote: (0.0, 0.0, 0.0)
?     ?? Rotación Y: capibaraNaranjaRot
?
?? PATA DELANTERA DERECHA (Hijo)
?  ?? Pivote: (0.2, 0.3, 0.3)
?     ?? Rotación Z: capibaraPataDelDer
?
?? PATA DELANTERA IZQUIERDA (Hijo)
?  ?? Pivote: (-0.2, 0.3, 0.3)
?     ?? Rotación Z: capibaraPataDelIzq
?
?? PATA TRASERA DERECHA (Hijo)
?  ?? Pivote: (0.2, 0.3, -0.3)
?     ?? Rotación Z: capibaraPataTrasDer
?
?? PATA TRASERA IZQUIERDA (Hijo)
   ?? Pivote: (-0.2, 0.3, -0.3)
      ?? Rotación Z: capibaraPataTrasIzq
```

### MONO - Estructura Jerárquica

```
CUERPO (Padre Principal)
?? Transformación Global: Traslación + Rotación Y + Escala
?
?? COLA (Hijo)
?  ?? Pivote: (0.0, 0.5, -0.4)
?     ?? Rotación X: monoColaRot
?
?? PATA DELANTERA DERECHA (Hijo)
?  ?? Pivote: (0.2, 0.3, 0.3)
?     ?? Rotación Z: monoPataDelDer
?
?? PATA DELANTERA IZQUIERDA (Hijo)
?  ?? Pivote: (-0.2, 0.3, 0.3)
?     ?? Rotación Z: monoPataDelIzq
?
?? PATA TRASERA DERECHA (Hijo)
?  ?? Pivote: (0.2, 0.3, -0.3)
?     ?? Rotación Z: monoPataTrasDer
?
?? PATA TRASERA IZQUIERDA (Hijo)
   ?? Pivote: (-0.2, 0.3, -0.3)
      ?? Rotación Z: monoPataTrasIzq
```

### GUACAMAYA - Estructura Jerárquica

```
CUERPO (Padre Principal)
?? Transformación Global: Traslación + Rotación Y + Escala
?
?? ALA DERECHA (Hijo)
?  ?? Pivote: (0.3, 0.0, 0.0)
?     ?? Rotación Z: guacamayaAlaDer
?
?? ALA IZQUIERDA (Hijo)
   ?? Pivote: (-0.3, 0.0, 0.0)
      ?? Rotación Z: guacamayaAlaIzq
```

### Código de Dibujo Jerárquico - CAPIBARA

```cpp
// 1. CUERPO (Padre Principal)
model = glm::mat4(1);
model = glm::translate(model, capibaraPos);
model = glm::rotate(model, glm::radians(rotCapibara), glm::vec3(0, 1, 0));
model = glm::scale(model, glm::vec3(capibaraScale));
modelTemp = model;
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
Capibara_Cuerpo.Draw(lightingShader);

// 2. CABEZA (Hijo del Cuerpo)
glm::vec3 capibaraPivotCabeza(0.0f, 0.5f, 0.4f);
model = modelTemp;
model = glm::translate(model, capibaraPivotCabeza);
model = glm::rotate(model, glm::radians(capibaraCabezaRot), glm::vec3(0, 1, 0));
model = glm::translate(model, -capibaraPivotCabeza);
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
Capibara_Cabeza.Draw(lightingShader);

// 3. PATA DELANTERA DERECHA
glm::vec3 capibaraPivotPataDelDer(0.2f, 0.3f, 0.3f);
model = modelTemp;
model = glm::translate(model, capibaraPivotPataDelDer);
model = glm::rotate(model, glm::radians(capibaraPataDelDer), glm::vec3(0, 0, 1));
model = glm::translate(model, -capibaraPivotPataDelDer);
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
Capibara_PataDelDer.Draw(lightingShader);

// ... (Repetir para otras patas y naranja)
```

---

## Estructura de Archivos

### Directorios Completos

```
?? Models/
??? ?? arbolSelva/
?   ??? arbolSelva.obj
??? ?? sandia/
?   ??? sandia.obj
??? ?? troncoSelva/
?   ??? troncoSelva.obj
??? ?? pelota/
?   ??? pelota.obj
??? ?? platano/
?   ??? platano.obj
?   ??? gato.obj
??? ?? arbolRama/
?   ??? arbolRama.obj
??? ?? ramaSelva/
?   ??? ramaSelva.obj
??? ?? plantaSelva/
?   ??? planta_selva.obj
??? ?? loto/
?   ??? loto.obj
??? ?? capibara/
?   ??? cabezaCapi.obj
?   ??? cuerpoCapi.obj
?   ??? naranjaCapi.obj
?   ??? pataDelDerCapi.obj
?   ??? pataDelIzqCapi.obj
?   ??? pataTrasDerCapi.obj
?   ??? pataTrasIzqCapi.obj
??? ?? mono/
?   ??? cuerpoMono.obj
?   ??? colaMono.obj
?   ??? pataDelDerMono.obj
?   ??? pataDelIzqMono.obj
?   ??? pataTasDerMono.obj
?   ??? pataTrasIzqMono.obj
??? ?? aveSelva/
    ??? cuerpoAve.obj
    ??? alaDerAve.obj
    ??? alaIzqAve.obj

?? images/
??? selva.png
```

### Resumen de Archivos

| Tipo | Cantidad | Estado |
|------|----------|--------|
| Directorios | 15 | ? Completo |
| Modelos OBJ | 23 | ? Completo |
| Texturas | 1 | ? Completo |

---

## ?? Estadísticas

### Contenido del Hábitat

| Métrica | Cantidad |
|---------|----------|
| **Modelos 3D** | 23 |
| **Animales** | 3 |
| **Decorativos** | 12 |
| **Flores (Lotos)** | 3 |
| **Componentes Jerárquicos** | 16 |
| **Texturas** | 1 |
| **Variables de Control** | 22 |
| **Fase de Animación** | 12 (total) |

### Cobertura del Proyecto

| Hábitat | Estado | Animales | Modelos |
|---------|--------|----------|---------|
| Acuario | ? 100% | 3 | 14 |
| Desierto | ? 100% | 3 | 14 |
| Selva | ? 100% | 3 | 23 |
| Sabana | ? 0% | 0 | 0 |
| **Total** | **75%** | **9** | **51** |

---

## ?? Controles Rápidos

```
Navegación:
?? W/?: Adelante
?? S/?: Atrás
?? A/?: Izquierda
?? D/?: Derecha
?? ESC: Salir

Animales Selva:
?? P: Capibara (Caminata/Comida)
?? M: Mono (Saltos/Caminata)
?? O: Guacamaya (Vuelo/Percha)

Animales Otros:
?? V: Pingüino (Acuario)
?? B: Foca (Acuario)
?? N: Delfín (Acuario)
?? C: Camello (Desierto)
?? X: Tortuga (Desierto)
?? Z: Cóndor (Desierto)

Iluminación:
?? ESPACIO: Toggle luz puntual
?? H: Bajar luz
?? U: Mover luz -Z
?? J: Mover luz +Z
```

---

## ? Estado de Implementación

| Aspecto | Estado | Notas |
|---------|--------|-------|
| **Modelos Cargados** | ? 100% | 23 modelos OBJ |
| **Texturas** | ? 100% | 1 textura PNG |
| **Animaciones** | ? 100% | 3 animales |
| **Controles** | ? 100% | 3 teclas |
| **Jerarquía** | ? 100% | 16 componentes |
| **Documentación** | ? 100% | Completa |
| **Compilación** | ? C++14 | Sin errores |

---

**Autor:** Uriel Benjamín De La Merced Soriano  
**Rama:** Develop  
**Fecha:** 2024  
**Estado:** ? COMPLETADO
