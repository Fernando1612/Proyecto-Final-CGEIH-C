/*---------------------------------------------------------*/
/* ----------------  Proyecto Final             -----------*/
/*-----------------    2022-2   ---------------------------*/
/*------------- Alumno: Maceda Patricio Fernando  ---------*/
/*------------- No. Cuenta: 316054416       ---------------*/
/*------------- Alumno:  Reyes Avila David  ---------------*/
/*------------- No. Cuenta:   316184979     ---------------*/
/*------------- Alumno: Salinas Romero Daniel -------------*/
/*------------- No. Cuenta: 419049300       ---------------*/
/*------------- Alumno: Vaquero Barajas Alexis-------------*/
/*------------- No. Cuenta:  316073934      ---------------*/

//ejemplo de cambio para mi rama Daniel
#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

#include <mmsystem.h>

// Pragma para musica
#pragma comment(lib, "winmm.lib")
bool sound = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor *monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 50.0f, 200.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

// posiciones
//float x = 0.0f;
//float y = 0.0f;
//para el movimiento del automovil
float	movAuto_x = 0.0f,
		movAuto_z = 0.0f,

		orienta = 90.0f,
		girollantas = 0.0f,
		estadoAuto = 1.0f;

//para mov de deportista
float movShan = 0.0f, //con esto se movera el deportista
	IdaRegresoShan = 1.0f; //para que avance y regrese
int estadoShan = 1.0f;
float orienShan = 0.0f; // para que llegue a diferentes posiciones

float movPersonaZ = 0.0f;

bool	animacion = false,
		recorrido1 = true,
		recorrido2 = false,
		recorrido3 = false,
		recorrido4 = false;



float movBici_z = 0.0f,
	  movBici_x = 0.0f;

float movTrici_z = 170.0f;

//Keyframes (Manipulación y dibujo)
float	posX = 0.0f,
		posY = 0.0f,
		posZ = 0.0f,
		rotRodIzq = 0.0f,
		giroMonito = 0.0f;
float	incX = 0.0f,
		incY = 0.0f,
		incZ = 0.0f,
		rotInc = 0.0f,
		giroMonitoInc = 0.0f;

float giroPedales = 0.0f;

#define MAX_FRAMES 9
int i_max_steps = 60;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotRodIzq;
	float giroMonito;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	std::cout << "Frame Index = " << FrameIndex << std::endl;

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].giroMonito = giroMonito;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	giroMonito = KeyFrame[0].giroMonito;
}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

}


void animate(void)
{
	giroPedales += 5.5f;
	movBici_z += 0.1f;
	movTrici_z += 0.1f;

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;

			rotRodIzq += rotInc;
			giroMonito += giroMonitoInc;

			i_curr_steps++;
		}
	}


	//Vehículo (se estaciona)
	if (animacion)
	{
		if (estadoAuto == 1) {
			movAuto_x += 3.0f;
			girollantas += 3.0f;
			if (movAuto_x >= 200) {
				orienta = 0.0f;
				estadoAuto = 2.0f;
				//animacion = FALSE;//no debe pararse
			}
		}
		if (estadoAuto == 2) {
			movAuto_z += 3.0f;
			girollantas += 3.0f;
			if (movAuto_z >= 300) {
				orienta = 90.0f;
				estadoAuto = 3.0f;
				//animacion = FALSE;//no debe pararse
			}
		}
		if (estadoAuto == 3) {
			movAuto_x += 3.0f;
			girollantas += 3.0f;
			if (movAuto_x >= 500) {
				orienta = 0.0f;
				estadoAuto = 4.0f;
				//animacion = FALSE;//no debe pararse
			}
		}
		if (estadoAuto == 4) {
			movAuto_z += 3.0f;
			girollantas += 3.0f;
			if (movAuto_z >= 500) {
				orienta = -90.0f;
				estadoAuto = 5.0f;
				//animacion = FALSE;//no debe pararse
			}
		}
		if (estadoAuto == 5) {
			movAuto_x -= 3.0f;
			girollantas += 3.0f;
			if (movAuto_x <= 450) {
				animacion = FALSE;
			}
		}
	}

	//deportista: va a hacer Suicidios
	switch (estadoShan){
	case 1://lega a 50
		if (IdaRegresoShan == 1)
		{
			movShan += 0.5f;//con esto el deportista sale hacia adelante
			if (movShan >= 50) {
				IdaRegresoShan = 0;//cambio de estado
				orienShan = 180.0f;//giro para el regreso
			}
		}
		else {
			movShan -= 0.5f;//con esto el deportista sale hacia atras
			if (movShan <= 0) {
				orienShan = 0.0f;//giro hacia enfrente
				IdaRegresoShan = 1;//cambio de estado
				estadoShan = 2;//cambio de estado del case
			}
		}
		break;
	case 2://llega a 100
		if (IdaRegresoShan == 1 && estadoShan == 2)
		{
			movShan += 0.5f;//con esto el deportista sale hacia adelante
			if (movShan >= 100) {
				IdaRegresoShan = 0;//cambio de estado
				orienShan = 180.0f;//giro para el regreso
			}
		}
		else {
			movShan -= 0.5f;//con esto el deportista sale hacia atras
			if (movShan <= 0) {
				orienShan = 0.0f;//giro hacia enfrente
				IdaRegresoShan = 1;//cambio de estado
				estadoShan = 3;//cambio de estado del case
			}
		}
		break;
	case 3://llega a 150
		if (IdaRegresoShan == 1)
		{
			movShan += 0.5f;//con esto el deportista sale hacia adelante
			if (movShan >= 150) {
				IdaRegresoShan = 0;//cambio de estado
				orienShan = 180.0f;//giro para el regreso
			}
		}
		else {
			movShan -= 0.5f;//con esto el deportista sale hacia atras
			if (movShan <= 0) {
				orienShan = 0.0f;//giro hacia enfrente
				IdaRegresoShan = 1;//cambio de estado
				estadoShan = 4;//cambio de estado del case
			}
		}
		break;
	case 4://llega a 200
		if (IdaRegresoShan == 1)
		{
			movShan += 0.5f;//con esto el deportista sale hacia adelante
			if (movShan >= 200) {
				IdaRegresoShan = 0;//cambio de estado
				orienShan = 180.0f;//giro para el regreso
			}
		}
		else {
			movShan -= 0.5f;//con esto el deportista sale hacia atras
			if (movShan <= 0) {
				orienShan = 0.0f;//giro hacia enfrente
				IdaRegresoShan = 1;//cambio de estado
				estadoShan = 1;//cambio de estado del case (regreso)
			}
		}
		break;
	default:
		break;

	}
	movPersonaZ += 0.1f;
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void music() {
	if (sound) {
		bool played = PlaySound(L"TamalesOaxaquenos.wav", NULL, SND_LOOP | SND_ASYNC);
		sound = false;
	}
}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	// -----------
	Model piso("resources/objects/piso/piso.obj");
	Model botaDer("resources/objects/Personaje/bota.obj");
	Model piernaDer("resources/objects/Personaje/piernader.obj");
	Model piernaIzq("resources/objects/Personaje/piernader.obj");
	Model torso("resources/objects/Personaje/torso.obj");
	Model brazoDer("resources/objects/Personaje/brazoder.obj");
	Model brazoIzq("resources/objects/Personaje/brazoizq.obj");
	Model cabeza("resources/objects/Personaje/cabeza.obj");
	//Model carro("resources/objects/lambo/carroceria.obj");//en caso de ocuparlo tambien
	//Model llanta("resources/objects/lambo/Wheel.obj");//llantas del lambo
	Model casaVieja("resources/objects/casa/OldHouse.obj");
	Model edificio("resources/objects/edificio/edificio.obj");
	Model oxxo("resources/objects/oxxo/oxxo.obj");
	Model entrada("resources/objects/Entrada/Entrada.obj");//entrada a la unidad
	Model Carro("resources/objects/Bocho/Bocho.obj");//Carroceria del bocho
	Model llanta("resources/objects/Bocho/Rueda.obj");//ruedas 


	

	Model pedales("resources/objects/bicicleta/pedales.obj");
	Model cuadro("resources/objects/bicicleta/cuadro.obj");
	Model rueda("resources/objects/bicicleta/rueda.obj");

	Model pedalesTriciclo("resources/objects/triciclo/pedalesTriciclo.obj");
	Model triciclo("resources/objects/triciclo/triciclo2F.obj");
	Model ruedaTriciclo("resources/objects/triciclo/ruedaTriciclo.obj");

	Model courtBasket("resources/objects/CanchaBasquet/cancha.obj");

	// Modelos dinamicos
	//------------------
	
	// Dog
	ModelAnim dog("resources/objects/Dog/doggo.dae");
	dog.initShaders(animShader.ID);


	// Persona Paseando
	ModelAnim womanWalk("resources/objects/PersonaCaminando/woman.dae");
	womanWalk.initShaders(animShader.ID);

	// Persona Caminando
	ModelAnim manWalk("resources/objects/PersonaCaminando2/man.dae");
	manWalk.initShaders(animShader.ID);

	ModelAnim manBici("resources/objects/bicicleta/man.dae");
	manBici.initShaders(animShader.ID);
	

	ModelAnim manTricycle("resources/objects/triciclo/manTricycle.dae");
	manTricycle.initShaders(animShader.ID);

	ModelAnim shannon("resources/objects/Deportista/Running.dae");//cargando a SHANNON (deportista)
	shannon.initShaders(animShader.ID);

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].giroMonito = 0;
	}

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);
		
		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.08f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(-80.0, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(0.6f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(1.0f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(1.0f);
		

		// -------------------------------------------------------------------------------------------------------------------------
		// Animaciones
		// -------------------------------------------------------------------------------------------------------------------------
		//Remember to activate the shader with the animation
		animShader.use();
		animShader.setMat4("projection", projection);
		animShader.setMat4("view", view);
	
		animShader.setVec3("material.specular", glm::vec3(0.5f));
		animShader.setFloat("material.shininess", 32.0f);
		animShader.setVec3("light.ambient", ambientColor);
		animShader.setVec3("light.diffuse", diffuseColor);
		animShader.setVec3("light.specular", 0.0f, 0.0f, 0.0f);
		animShader.setVec3("light.direction", lightDirection);
		animShader.setVec3("viewPos", camera.Position);


		//model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.3f, 1.75f, 0.3f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(1.2f));	// it's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//animShader.setMat4("model", model);
		//animacionPersonaje.Draw(animShader);

		//dibujar a Shannon (deportista)
		model = glm::translate(glm::mat4(1.0f), glm::vec3(80.0f, 0.0f, movShan));//ubicar mi personaje //la var de mov debe colocarse bien
		model = glm::rotate(model, glm::radians(orienShan), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f));//escala
		animShader.setMat4("model", model);
		shannon.Draw(animShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Segundo Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------

		//model = glm::translate(glm::mat4(1.0f), glm::vec3(40.3f, 1.75f, 0.3f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.5f));	// it's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//animShader.setMat4("model", model);
		//ninja.Draw(animShader);

		//-------------------Triciclo---------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, movTrici_z));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2));
		animShader.setMat4("model", model);
		manTricycle.Draw(animShader);

		//-------------------Bicicleta--------------------------------
		//
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-150.0f, 0.0f, movBici_z));
		model = glm::scale(model, glm::vec3(0.2f));
		animShader.setMat4("model", model);
		manBici.Draw(animShader);


		// DOG
		model = glm::translate(glm::mat4(1.0f), glm::vec3(310.0f, 0.0f, movPersonaZ)); 
		model = glm::scale(model, glm::vec3(0.3f));	
		animShader.setMat4("model", model);
		dog.Draw(animShader);

		// Persona Paseando
		model = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 0.0f, movPersonaZ));
		model = glm::scale(model, glm::vec3(0.1f));
		animShader.setMat4("model", model);
		womanWalk.Draw(animShader);

		// Persona Caminando
		model = glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 0.0f, -40.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		manWalk.Draw(animShader);
		

		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2));
		staticShader.setMat4("model", model);
		piso.Draw(staticShader);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		casaVieja.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(70.0f, 0.0f, 70.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		//edificio.Draw(staticShader);

		// OXXO
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-70.0f, 0.0f, 70.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		//oxxo.Draw(staticShader);

		// ENTRADA
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 400.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		entrada.Draw(staticShader);

		// Cancha
		model = glm::translate(glm::mat4(1.0f), glm::vec3(70.0f, 0.0f, -105.0f));
		model = glm::scale(model, glm::vec3(9.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		courtBasket.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Persona en Triciclo
		// -------------------------------------------------------------------------------------------------------------------------
		tmp = model = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, movTrici_z));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		triciclo.Draw(staticShader);
		
		model = glm::translate(tmp, glm::vec3(0.0f, 7.2f, -6.5f));
		model = model = glm::rotate(model, glm::radians(giroPedales), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		pedalesTriciclo.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(-0.95f, 8.2f, -18.5f));
		model = model = glm::rotate(model, glm::radians(giroPedales), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		ruedaTriciclo.Draw(staticShader); // rueda trasera

		model = glm::translate(tmp, glm::vec3(-11.5f, 8.2f, 17.5f));
		model = model = glm::rotate(model, glm::radians(giroPedales), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		ruedaTriciclo.Draw(staticShader); // rueda delantera der

		model = glm::translate(tmp, glm::vec3(11.0f, 8.2f, 17.5f));
		model = model = glm::rotate(model, glm::radians(giroPedales), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		ruedaTriciclo.Draw(staticShader); // rueda delantera izq
		
		

		// -------------------------------------------------------------------------------------------------------------------------
		// Persona en bici
		// -------------------------------------------------------------------------------------------------------------------------
		tmp = model = glm::translate(glm::mat4(1.0f), glm::vec3(-150.0f, 0.0f, movBici_z));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		cuadro.Draw(staticShader);
		
		model = glm::translate(tmp, glm::vec3(0.0f,6.0f, 1.0f));
		model = model = glm::rotate(model, glm::radians(giroPedales), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		pedales.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(-0.5f, 6.5f, 13.25f));
		model = model = glm::rotate(model, glm::radians(giroPedales), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		rueda.Draw(staticShader); // Adelante

		model = glm::translate(tmp, glm::vec3(-0.5f, 6.5f, -7.5f));
		model = model = glm::rotate(model, glm::radians(giroPedales), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		rueda.Draw(staticShader); // Atras
		

		// -------------------------------------------------------------------------------------------------------------------------
		// Carro
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-450.0f + movAuto_x, 4.5f, -100.0f + movAuto_z));
		tmp = model = glm::rotate(model, glm::radians(orienta), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		staticShader.setMat4("model", model);
		Carro.Draw(staticShader);
		
		model = glm::translate(tmp, glm::vec3(13.0f, 2.0f, 30.0f));
		model = glm::rotate(model, glm::radians(girollantas), glm::vec3(1.0f, 0.0f, 0.0f));//giro de las llantas
		model = glm::scale(model, glm::vec3(0.009f, 0.009f, 0.009f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Izq delantera

		model = glm::translate(tmp, glm::vec3(-13.0f, 2.0f, 30.0f));
		model = glm::rotate(model, glm::radians(girollantas), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.009f, 0.009f, 0.009f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Der delantera

		model = glm::translate(tmp, glm::vec3(-13.0f, 2.0f, -20.0f));
		model = glm::rotate(model, glm::radians(girollantas), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.009f, 0.009f, 0.009f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Der trasera

		model = glm::translate(tmp, glm::vec3(13.0f, 2.0f, -20.0f));
		model = glm::rotate(model, glm::radians(girollantas), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.009f, 0.009f, 0.009f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Izq trase      
		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		tmp = model = glm::rotate(model, glm::radians(giroMonito), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		torso.Draw(staticShader);

		//Pierna Der
		model = glm::translate(tmp, glm::vec3(-0.5f, 0.0f, -0.1f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		piernaDer.Draw(staticShader);

		//Pie Der
		model = glm::translate(model, glm::vec3(0, -0.9f, -0.2f));
		staticShader.setMat4("model", model);
		botaDer.Draw(staticShader);

		//Pierna Izq
		model = glm::translate(tmp, glm::vec3(0.5f, 0.0f, -0.1f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		piernaIzq.Draw(staticShader);

		//Pie Iz
		model = glm::translate(model, glm::vec3(0, -0.9f, -0.2f));
		staticShader.setMat4("model", model);
		botaDer.Draw(staticShader);	//Izq trase

		//Brazo derecho
		model = glm::translate(tmp, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.75f, 2.5f, 0));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		brazoDer.Draw(staticShader);

		//Brazo izquierdo
		model = glm::translate(tmp, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.75f, 2.5f, 0));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		brazoIzq.Draw(staticShader);

		//Cabeza
		model = glm::translate(tmp, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0));
		staticShader.setMat4("model", model);
		cabeza.Draw(staticShader);
		// -------------------------------------------------------------------------------------------------------------------------
		// Caja Transparente --- Siguiente Práctica
		// -------------------------------------------------------------------------------------------------------------------------
		/*glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		cubo.Draw(staticShader);
		glEnable(GL_BLEND);*/
		// -------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	//To Configure Model
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		posZ++;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		posZ--;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		posX--;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		posX++;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		rotRodIzq--;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		rotRodIzq++;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		giroMonito--;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		giroMonito++;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		lightPosition.x++;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		lightPosition.x--;

	//Musica
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		music();
	}

	//Car animation
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		animacion ^= true;

	//To play KeyFrame animation 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	//To Save a KeyFrame
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
