#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
// =================================================================================
// 	CONFIGURACIÓN INICIAL Y VARIABLES GLOBALES
// =================================================================================

// Funciones prototipo para callbacks
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();

// Propiedades de la ventana
const GLuint WIDTH = 1000, HEIGHT = 800;
int SCREEN_WIDTH, SCREEN_HEIGHT;


// Configuración de la cámara
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;

bool keys[1024];
bool firstMouse = true;
// Posiciones de las luces
glm::vec3 lightPos(1.5f, 2.0f, -2.5f);
glm::vec3 lightPos2(-1.5f, 2.0f, -2.5f);
bool active;

// Posiciones para luces puntuales 
glm::vec3 pointLightPositions[] = {
	glm::vec3(2.0f, 0.2f,  2.0f),  // Esquina 1 (Positivo X, Positivo Z)
	glm::vec3(-2.0f, 0.2f,  2.0f),  // Esquina 2 (Negativo X, Positivo Z)
	glm::vec3(2.0f, 0.2f, -2.0f),  // Esquina 3 (Positivo X, Negativo Z)
	glm::vec3(-2.0f, 0.2f, -2.0f)   // Esquina 4 (Negativo X, Negativo Z)
};

// ---------------------------------------------------------------------------------
//VARIABLES PARA ANIMACIÓN Y MOVIMIENTO DE OBJETOS
// ---------------------------------------------------------------------------------
float hombro_rot = 0.0f;
float codo_rot = 0.0f;
float tiempo_animacion = 0.0f; // Variable para animaciones automáticas

// Vértices del cubo CON COORDENADAS DE TEXTURA
float vertices[] = {
	// Posiciones           // Normales           // Coordenadas de Textura (U, V)
	// Cara Trasera (-Z)
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	// Cara Frontal (+Z)
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
	// Cara Izquierda (-X)
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	// Cara Derecha (+X)
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 // Cara Inferior (-Y)
	 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 // Cara Superior (+Y)
	 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

//glm::vec3 lampColors[] = {
//	glm::vec3(1.0f, 0.0f, 0.0f), // Rojo
//	glm::vec3(0.0f, 1.0f, 0.0f), // Verde
//	glm::vec3(0.0f, 0.0f, 1.0f), // Azul
//	glm::vec3(1.0f, 1.0f, 1.0f)  // Blanco
//};

glm::vec3 Light1 = glm::vec3(0);


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Función para dibujar una parte del brazo con textura
void pataDraw(glm::mat4 modelo, glm::vec3 escala, glm::vec3 traslado, GLint uniformModel, GLuint VAO, GLuint texturaID)
{
	// 1. Configurar la matriz del modelo para esta parte
	modelo = glm::mat4(1);
	modelo = glm::scale(modelo, escala); // tamaño
	modelo = glm::translate(modelo, traslado);// posición
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelo));

	// 2. Activar y enlazar la textura específica para esta parte
	//    Asumimos que el shader ya tiene los uniforms de sampler (material.diffuse = 0, material.specular = 1)
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturaID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturaID); // Usamos la misma textura para difuso y especular

	// 3. Enlazar el VAO del cubo
	glBindVertexArray(VAO);

	// 4. *** CRÍTICO *** Habilitar TODOS los atributos que usa lightingShader
	// (El lampShader los deshabilita, así que hay que volver a habilitarlos)
	glEnableVertexAttribArray(0); // Posición
	glEnableVertexAttribArray(1); // Normal
	glEnableVertexAttribArray(2); // TexCoords

	// 5. Dibujar el cubo
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// 6. Desvincular (buena práctica)
	glBindVertexArray(0);
}

void cuboDraw(glm::mat4 modelo, glm::vec3 escala, glm::vec3 traslado, GLint uniformModel, GLuint VAO, GLuint texturaID, float rotacion)
{
	// 1. Configurar la matriz del modelo para esta parte
	modelo = glm::mat4(1);
	modelo = glm::translate(modelo, traslado);// primero traslación
	modelo = glm::rotate(modelo, rotacion, glm::vec3(0.0f, 1.0f, 0.0f)); // luego rotación
	modelo = glm::scale(modelo, escala); // finalmente escala
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelo));

	// 2. Activar y enlazar la textura
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturaID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturaID);

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

int main()
{
	// =================================================================================
	// INICIALIZACIÓN DE GLFW, GLEW Y VENTANA
	// =================================================================================

	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
	
	// =================================================================================
	// 						CARGA DE MODELOS 3D
	// =================================================================================

	Model Dog((char*)"Models/ball.obj");
	Model Piso((char*)"Models/piso.obj");
	Model Perro((char*)"Models/RedDog.obj");
	Model Pinguino((char*)"Models/pinguino.obj");
	Model Foca((char*)"Models/foca.obj");
	Model cuerpoPin((char*)"Models/pinguino/cuerpo.obj");
	Model arm1((char*)"Models/pinguino/arm1.obj");
	Model arm2((char*)"Models/pinguino/aletIzq.obj");


	// Carga textura
	GLuint armTextureID = TextureFromFile("images/madera.jpg", ".");
	GLuint greenTextureID = TextureFromFile("images/textverde.jpg", ".");
	GLuint amarilloTextureID = TextureFromFile("images/textamarillo.jpg", ".");
	GLuint cafeTextureID = TextureFromFile("images/cafe.jpg", ".");



	// =================================================================================
	// 					CONFIGURACIÓN DE VÉRTICES PARA PRIMITIVAS
	// =================================================================================

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

// =================================================================================
	// 					CONFIGURACIÓN DE VÉRTICES PARA PRIMITIVAS (CUBO)
	// =================================================================================
	GLuint VBO_Cubo, VAO_Cubo;
	glGenVertexArrays(1, &VAO_Cubo);
	glGenBuffers(1, &VBO_Cubo);
	glBindVertexArray(VAO_Cubo);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Cubo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO_Cubo); // Enlazar el VAO

	// Atributo de Posición (Location 0)
	// El Stride (paso) ahora es de 8 floats
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	// Atributo de Normal (Location 1)
	// El Stride es 8, el Offset (desplazamiento) es después de los 3 floats de posición
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// *** NUEVO: Atributo de Coordenadas de Textura (Location 2) ***
	// El Stride es 8, el Offset es después de 3 (pos) + 3 (norm) = 6 floats
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Desvincular el VAO
	// =================================================================================
	// 								CICLO DE RENDERIZADO (GAME LOOP)
	// =================================================================================

	while (!glfwWindowShouldClose(window))
	{

		// Delta time, Eventos, Limpieza
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		// Clear the colorbuffer
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);  // Aumentado de 0.1f para un fondo más claro
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
		// OpenGL options
		glEnable(GL_DEPTH_TEST);

		
		
		//Load Model
	

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

                  glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Luz Direccional (dirLight)
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.3f, 0.3f, 0.3f);    // Aumentado de 0.05f
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.7f, 0.7f, 0.7f);    // Aumentado de 0.2f
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);   // Aumentado de 0.2f

		// Luces Puntuales (pointLights) - Usando los colores de las lámparas
		// Point light 1
	    glm::vec3 lightColor;
		lightColor.x= abs(sin(glfwGetTime() *Light1.x));
		lightColor.y= abs(sin(glfwGetTime() *Light1.y));
		lightColor.z= sin(glfwGetTime() *Light1.z);

		//
		//// Point light 0 (Rojo)
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient")/*, lampColors[0].r * 0.1f, lampColors[0].g * 0.1f, lampColors[0].b * 0.1f*/); // Ambiente Rojo tenue
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse")/*, lampColors[0].r, lampColors[0].g, lampColors[0].b*/);       // Difuso Rojo
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular")/*, lampColors[0].r, lampColors[0].g, lampColors[0].b*/);      // Especular Rojo
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f); // Atenuación específica
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f); // Atenuación específica

		//// Point light 1 (Verde)
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), lampColors[1].r * 0.1f, lampColors[1].g * 0.1f, lampColors[1].b * 0.1f); // Ambiente Verde tenue
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), lampColors[1].r, lampColors[1].g, lampColors[1].b);       // Difuso Verde
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), lampColors[1].r, lampColors[1].g, lampColors[1].b);      // Especular Verde
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.09f); // Atenuación ejemplo
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.032f); // Atenuación ejemplo

		//// Point light 2 (Azul)
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), lampColors[2].r * 0.1f, lampColors[2].g * 0.1f, lampColors[2].b * 0.1f); // Ambiente Azul tenue
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), lampColors[2].r, lampColors[2].g, lampColors[2].b);       // Difuso Azul
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), lampColors[2].r, lampColors[2].g, lampColors[2].b);      // Especular Azul
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.09f); // Atenuación ejemplo
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.032f); // Atenuación ejemplo

		//// Point light 3 (Blanco)
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), lampColors[3].r * 0.1f, lampColors[3].g * 0.1f, lampColors[3].b * 0.1f); // Ambiente Blanco tenue
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), lampColors[3].r, lampColors[3].g, lampColors[3].b);       // Difuso Blanco
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), lampColors[3].r, lampColors[3].g, lampColors[3].b);      // Especular Blanco
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f); // Atenuación ejemplo
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f); // Atenuación ejemplo


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.0f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.0f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.0f);
		// SpotLight  //una luz tipo linterna en la cámara
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"),1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(6.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(10.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 2.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		GLint lampColorLoc = glGetUniformLocation(lampShader.Program, "lampColor");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// ---------------------------------------------------------------------------------
		// 							DIBUJO DE MODELOS CARGADOS
		// ---------------------------------------------------------------------------------
		// 
		
		//Carga de modelo 
		glm::mat4 model = glm::mat4(1.0f);
  //      view = camera.GetViewMatrix();	
		//model = glm::mat4(1);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Piso.Draw(lightingShader);

		////modelo perro
		//glm::mat4 perro = glm::mat4(1.0f);

		////glEnable(GL_BLEND);//Activa la funcionalidad para trabajar el canal alfa
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(perro));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
	 //   Perro.Draw(lightingShader);
		////glDisable(GL_BLEND);  //Desactiva el canal alfa 
		//glBindVertexArray(0);

		////modelo 
		//glm::mat4 pelota = glm::mat4(1.0f);
		////glEnable(GL_BLEND);//Activa la funcionalidad para trabajar el canal alfa
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pelota));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//Dog.Draw(lightingShader);
		////glDisable(GL_BLEND);  //Desactiva el canal alfa 
		//glBindVertexArray(0);

		//modelo pinguino
		glm::mat4 pinguino = glm::mat4(1.0f);
		pinguino = glm::translate(pinguino, glm::vec3(36.0f, 0.15f, -20.5f));
		pinguino = glm::rotate(pinguino, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glEnable(GL_BLEND);//Activa la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pinguino));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Pinguino.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);

		//modelo foca

		glm::mat4 foca = glm::mat4(1.0f);
		foca = glm::translate(foca, glm::vec3(28.0f, -0.2f, -20.5f));
		foca = glm::rotate(foca, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glEnable(GL_BLEND);//Activa la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(foca));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Foca.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);


		//modelo pin por partes

		glm::mat4 PinguinoCuerpo = glm::mat4(1.0f);
	/*	PinguinoCuerpo = glm::translate(PinguinoCuerpo, glm::vec3(28.0f, -0.2f, -20.5f));
		PinguinoCuerpo = glm::rotate(PinguinoCuerpo, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/
		//glEnable(GL_BLEND);//Activa la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(PinguinoCuerpo));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		cuerpoPin.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);

		glm::mat4 PinguinoDer = glm::mat4(1.0f);
		/*	PinguinoDer = glm::translate(PinguinoDer, glm::vec3(28.0f, -0.2f, -20.5f));
			PinguinoDer = glm::rotate(PinguinoDer, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/
			//glEnable(GL_BLEND);//Activa la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(PinguinoDer));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		arm1.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);

		glm::mat4 PinguinoIzq = glm::mat4(1.0f);
		/*	PinguinoDer = glm::translate(PinguinoDer, glm::vec3(28.0f, -0.2f, -20.5f));
			PinguinoDer = glm::rotate(PinguinoDer, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/
			//glEnable(GL_BLEND);//Activa la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(PinguinoIzq));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		arm2.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);







		/*lightingShader.Use();
		GLint objectColorLoc = glGetUniformLocation(lightingShader.Program, "objectColor");*/

		/*glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.0f);*/

		//mesa
		pataDraw(model, glm::vec3(0.1f, 0.8f, 0.1f), glm::vec3(9.5f, 0.5f, 5.5f), modelLoc, VAO_Cubo, armTextureID);//pata1
		pataDraw(model, glm::vec3(0.1f, 0.8f, 0.1f), glm::vec3(-9.5f, 0.5f, 5.5f), modelLoc, VAO_Cubo, armTextureID);//pata2
		pataDraw(model, glm::vec3(0.1f, 0.8f, 0.1f), glm::vec3(-9.5f, 0.5f, -5.5f), modelLoc, VAO_Cubo, armTextureID);//pata3
		pataDraw(model, glm::vec3(0.1f, 0.8f, 0.1f), glm::vec3(9.5f, 0.5f, -5.5f), modelLoc, VAO_Cubo, armTextureID);//pata4
		pataDraw(model, glm::vec3(2.0f, 0.05f, 1.2f), glm::vec3(0.0f, 16.5f, 0.0f), modelLoc, VAO_Cubo, armTextureID);//tabla superio

		//silla
		pataDraw(model, glm::vec3(0.4f, 0.05f, 0.4f), glm::vec3(0.0f, 8.5f, 2.19f),modelLoc, VAO_Cubo, armTextureID);// 1. Asiento
		pataDraw(model, glm::vec3(0.05f, 0.4f, 0.05f),glm::vec3(3.5f, 0.5f, 14.0f),modelLoc, VAO_Cubo, armTextureID);// 2. Patas
		pataDraw(model, glm::vec3(0.05f, 0.4f, 0.05f),glm::vec3(-3.5f, 0.5f, 14.0f),modelLoc, VAO_Cubo, armTextureID);// Pata delantera izquierda
		pataDraw(model, glm::vec3(0.05f, 0.4f, 0.05f),glm::vec3(-3.5f, 0.5f, 21.0f),modelLoc, VAO_Cubo, armTextureID);// Pata trasera izquierda
		pataDraw(model, glm::vec3(0.05f, 0.4f, 0.05f),glm::vec3(3.5f, 0.5f, 21.0f),modelLoc, VAO_Cubo, armTextureID);// Pata trasera derecha
		pataDraw(model, glm::vec3(0.4f, 0.4f, 0.05f),glm::vec3(0.0f, 1.63f, 21.0f),modelLoc, VAO_Cubo, armTextureID);// 3. Respaldo
	

		//pataDraw(model, glm::vec3(80.0f, 4.0f, 0.2f), glm::vec3(0.0f, 0.41f, -120.0f), modelLoc, VAO_Cubo, armTextureID);//pared uno
		//pataDraw(model, glm::vec3(0.2f, 4.0f, 48.0f), glm::vec3(200.0f, 0.41f, 0.0f), modelLoc, VAO_Cubo, armTextureID);//pared de enfrente
		//pataDraw(model, glm::vec3(0.2f, 4.0f, 10.0f), glm::vec3(160.0f, 0.41f, -1.9f), modelLoc, VAO_Cubo, armTextureID);//pared de pinguino derecha
		//pataDraw(model, glm::vec3(0.2f, 4.0f, 10.0f), glm::vec3(120.0f, 0.41f, -1.9f), modelLoc, VAO_Cubo, armTextureID);//pared de foca derecha
		//pataDraw(model, glm::vec3(0.2f, 4.0f, 10.0f), glm::vec3(77.0f, 0.41f, -1.9f), modelLoc, VAO_Cubo, armTextureID);//pared de delfín derecha
		
		// Maceta 
		cuboDraw(model, glm::vec3(0.3f, 0.05f, 0.3f), glm::vec3(0.0f, 0.5f, 0.0f), modelLoc, VAO_Cubo, armTextureID, 0.0f);

		// Maceta - Cuerpo
		cuboDraw(model, glm::vec3(0.25f, 0.3f, 0.25f), glm::vec3(0.0f, 0.7f, 0.0f), modelLoc, VAO_Cubo, armTextureID, 0.0f);

		// Flor
		// Tallo
		cuboDraw(model, glm::vec3(0.02f, 0.4f, 0.02f), glm::vec3(0.0f, 1.0f, 0.0f), modelLoc, VAO_Cubo, armTextureID, 0.0f);

		// Pétalos
		const int numPetalos = 8;
		const float radio = 0.15f;
		for (int i = 0; i < numPetalos; i++) {
			float angulo = (float)i * (2.0f * 3.14159f / numPetalos);
			float x = radio * cos(angulo);
			float z = radio * sin(angulo);

			// Cada pétalo
			cuboDraw(model,
				glm::vec3(0.05f, 0.15f, 0.02f),
				glm::vec3(x, 1.3f, z),  // Ajustado Y a 1.3f
				modelLoc,
				VAO_Cubo,
				armTextureID,
				angulo + glm::radians(30.0f));
		}

		// Centro de la flor
		cuboDraw(model, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.3f, 0.0f), modelLoc, VAO_Cubo, armTextureID, 0.0f);

		// Hojas del tallo
		cuboDraw(model, glm::vec3(0.1f, 0.02f, 0.05f), glm::vec3(0.1f, 1.1f, 0.0f), modelLoc, VAO_Cubo, armTextureID, glm::radians(45.0f));
		cuboDraw(model, glm::vec3(0.1f, 0.02f, 0.05f), glm::vec3(-0.1f, 1.0f, 0.0f), modelLoc, VAO_Cubo, armTextureID, glm::radians(-45.0f));

		//-------------------------------
		// maceta
		//------------------------------------
		cuboDraw(model, glm::vec3(0.5f, 0.1f, 0.5f), glm::vec3(1.0f, 0.5f, 2.0f),modelLoc, VAO_Cubo, cafeTextureID, 0.0f);// --- 1. Base de la Maceta
		cuboDraw(model, glm::vec3(0.5f, 0.4f, 0.05f),glm::vec3(1.0f, 0.75f, 1.775f),modelLoc, VAO_Cubo, cafeTextureID, 0.0f);//2. Paredes de la Maceta ---
		cuboDraw(model, glm::vec3(0.5f, 0.4f, 0.05f),glm::vec3(1.0f, 0.75f, 2.225f),modelLoc, VAO_Cubo, cafeTextureID, 0.0f);// Pared Delantera 
		cuboDraw(model, glm::vec3(0.05f, 0.4f, 0.4f),glm::vec3(0.775f, 0.75f, 2.0f),modelLoc, VAO_Cubo, cafeTextureID, 0.0f);// Pared Izquierda (-X)
		cuboDraw(model, glm::vec3(0.05f, 0.4f, 0.4f),glm::vec3(1.225f, 0.75f, 2.0f),modelLoc, VAO_Cubo, cafeTextureID, 0.0f);	// Pared Derecha (+X)
		cuboDraw(model, glm::vec3(0.4f, 0.05f, 0.4f), glm::vec3(1.0f, 0.875f, 2.0f),modelLoc, VAO_Cubo, cafeTextureID, 0.0f); //tieerra

		//-----------------------------------
		//flor
		//-----------------------------------
		cuboDraw(model, glm::vec3(0.05f, 0.5f, 0.05f),glm::vec3(1.0f, 1.15f, 2.0f),modelLoc, VAO_Cubo, greenTextureID, 0.0f);//flor color verde
		cuboDraw(model, glm::vec3(0.1f, 0.1f, 0.1f),glm::vec3(1.0f, 1.45f, 2.0f),modelLoc, VAO_Cubo, amarilloTextureID, 0.0f);//pistilos, amarillo

		// --- 3. Pétalos ---
		cuboDraw(model, glm::vec3(0.2f, 0.2f, 0.05f),glm::vec3(1.0f, 1.45f, 2.075f),modelLoc, VAO_Cubo, amarilloTextureID, 0.0f);
		cuboDraw(model, glm::vec3(0.2f, 0.2f, 0.05f),glm::vec3(1.0f, 1.45f, 1.925f),modelLoc, VAO_Cubo, amarilloTextureID, 0.0f);// Pétalo Trasero (-Z)
		cuboDraw(model, glm::vec3(0.05f, 0.2f, 0.2f),glm::vec3(1.075f, 1.45f, 2.0f),modelLoc, VAO_Cubo, amarilloTextureID, 0.0f);// Pétalo Derecho (+X)
		cuboDraw(model, glm::vec3(0.05f, 0.2f, 0.2f),glm::vec3(0.925f, 1.45f, 2.0f),modelLoc, VAO_Cubo, amarilloTextureID, 0.0f);// Pétalo Izquierdo (-X)


		//--------------------------------------------------
		lightingShader.Use(); // shader de iluminación 
		// -------------------------------------------------------------------------------- -
	// 							DIBUJO DE MODELO JERÁRQUICO (BRAZO)
	// ---------------------------------------------------------------------------------
		// Textura
		// (Asumimos que la textura difusa va en la unidad 0)
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, armTextureID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, armTextureID); 

		glBindVertexArray(VAO_Cubo); // Usa el VAO del cubo

		// Habilitar los atributos (Ubicación 0 y 1 ya están habilitadas por defecto)
		glEnableVertexAttribArray(0); // Posición
		glEnableVertexAttribArray(1); // Normal
		glEnableVertexAttribArray(2); //Habilitar Coordenadas de Textura

		// Hombro
		glm::mat4 model_brazo = glm::mat4(1.0f);
		glm::mat4 modelTemp = glm::mat4(1.0f);
		// ... (Transformaciones hombro) ...
		model_brazo = glm::translate(model_brazo, glm::vec3(2.0f, 1.0f, 0.0f));
		model_brazo = glm::rotate(model_brazo, glm::radians(hombro_rot), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model_brazo = glm::translate(model_brazo, glm::vec3(1.0f, 0.0f, 0.0f));
		model_brazo = glm::scale(model_brazo, glm::vec3(2.0f, 0.4f, 0.4f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model_brazo));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Antebrazo
		// ... (Transformaciones antebrazo) ...
		model_brazo = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f));
		model_brazo = glm::rotate(model_brazo, glm::radians(codo_rot), glm::vec3(0.0f, 0.0f, 1.0f));
		model_brazo = glm::translate(model_brazo, glm::vec3(0.75f, 0.0f, 0.0f));
		model_brazo = glm::scale(model_brazo, glm::vec3(1.5f, 0.4f, 0.4f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model_brazo));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0); // Desvincular VAO_Cubo


	

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//// Draw the light object (using light's vertex attributes)
		//for (GLuint i = 0; i < 4; i++)
		//{
		//	model = glm::mat4(1);
		//	model = glm::translate(model, pointLightPositions[i]);
		//	model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glUniform3fv(lampColorLoc, 1, glm::value_ptr(lampColors[i]));
		//	glBindVertexArray(VAO);
		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}
		//glBindVertexArray(0);



		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_Y])
	{
		pointLightPositions[0].y += 0.01f;
	}

	if (keys[GLFW_KEY_H])
	{
		pointLightPositions[0].y -= 0.01f;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z -= 0.1f;
	}
	if (keys[GLFW_KEY_J])
	{
		pointLightPositions[0].z += 0.01f;
	}
	
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(1.0f, 1.0f, 0.0f);
		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}