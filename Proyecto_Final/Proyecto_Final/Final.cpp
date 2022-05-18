/*---------------------------------------------------------*/
/* ----------------  Proyecto Final             -----------*/
/*-----------------    2022-2   ---------------------------*/
/*------------- No. Cuenta: 316054416       ---------------*/
/*------------- No. Cuenta: 316184979       ---------------*/
/*------------- No. Cuenta: 419049300       ---------------*/
/*------------- No. Cuenta: 316073934       ---------------*/

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
float	movAuto_x = 0.0f,
		movAuto_z = 0.0f,

		orienta = 180.0f,
		girollantas = 0.0f,
		estadoAuto = 1.0f;

//para mov de deportista
float movShan = 0.0f, //con esto se movera el deportista
	IdaRegresoShan = 1.0f; //para que avance y regrese
int estadoShan = 1.0f;
float orienShan = 0.0f; // para que gire a diferentes posiciones

#define SPEED_MOV 0.2f
float	rotDogPerson = 180.0f,
		movPersonX = 0.0f,
		movPersonZ = 0.0f,
		movDogX = 0.0f,
		movDogZ = 0.0f;

//para el movimiento del constructor
float movConstX = 0.0f,
	movConstZ = 0.0f,
	OrientaConst = 180.0f,
	estadoConst = 1.0f;

bool	animacion = false,//para el carro
		animacionConst = false,//para el constructor
		recorrido1 = true,
		recorrido2 = false,
		recorrido3 = false,
		recorrido4 = false;

int estado_trici = 0,
	estado_dogPerson = 0,
	estado_bici = 0;

float movBici_z = -5.0f, // posición inicial en z
	  movBici_x = -500.0f,	// posición inicial en x
	  orientaBici = 0.0f;	// orientación incial

float movTrici_z = -500.0f,	// posición inicial en Z
	  movTrici_x = -175.0f,	// posición inicial en x
	  orientaTrici = 0.0f;	// orinetación inical

float giroPedales = 0.0f;


void animate(void)
{
	giroPedales += 5.5f;//PARA QUE GIREN LOS PEDALES
	
	if (animacion)//ANIMACÓN DEL CARRO
	{
		if (estadoAuto == 1) {
			movAuto_z -= 3.0f;
			girollantas += 3.0f;
			if (movAuto_z <= -260) {
				orienta = 90.0f;
				estadoAuto = 2.0f;
			}
		}
		if (estadoAuto == 2) {
			movAuto_x += 3.0f;
			girollantas += 3.0f;
			if (movAuto_x >= 360) {
				orienta = 0.0f;
				estadoAuto = 3.0f;
			}
		}
		if (estadoAuto == 3) {
			movAuto_z += 3.0f;
			girollantas += 3.0f;
			if (movAuto_z >= -30) {
				orienta = 90.0f;
				estadoAuto = 4.0f;
			}
		}
		if (estadoAuto == 4) {
			movAuto_x += 3.0f;
			girollantas += 3.0f;
			if (movAuto_x >= 580) {
				orienta = 180.0f;
				estadoAuto = 5.0f;
			}
		}
		if (estadoAuto == 5) {
			movAuto_z -= 3.0f;
			girollantas += 3.0f;
			if (movAuto_z <= -330) {
				orienta = 270.0f;
				estadoAuto = 6.0f;
			}
		}
		if (estadoAuto == 6) {
			movAuto_x -= 3.0f;
			girollantas += 3.0f;
			if (movAuto_x <= 450) {
				orienta = 180.0f;
				estadoAuto = 7.0f;
			}
		}
		if (estadoAuto == 7) {
			movAuto_z -= 3.0f;
			girollantas += 3.0f;
			if (movAuto_z <= -750) {
				orienta = 90.0f;
				estadoAuto = 8.0f;
			}
		}
		if (estadoAuto == 8) {
			movAuto_x += 3.0f;
			girollantas += 3.0f;
			if (movAuto_x >= 650) {
				orienta = 180.0f;
				estadoAuto = 9.0f;
			}
		}
		if (estadoAuto == 9) {
			movAuto_z -= 3.0f;
			girollantas += 3.0f;
			if (movAuto_z <= -800) {
				estadoAuto = 10.0f;
				animacion = FALSE;
			}
		}
	}

	if (animacionConst) {//ANIMACIÓN DEL CONSTRUCTOR
		if (estadoConst == 1) {
			movConstX -= 0.6f;
			if (movConstX <= -90) {
				OrientaConst = 90.0f;
				estadoConst = 2.0f;
			}
		}
		if (estadoConst == 2) {
			movConstZ -= 0.6f;
			if (movConstZ <= -85) {
				OrientaConst = 180.0f;
				estadoConst = 3.0f;
			}
		}
		if (estadoConst == 3) {
			movConstX -= 0.6f;
			if (movConstX <= -290) {
				OrientaConst = 90.0f;
				estadoConst = 4.0f;
			}
		}
		if (estadoConst == 4) {
			movConstZ -= 0.6f;
			if (movConstZ <= -200) {
				OrientaConst = 180.0f;
				estadoConst = 5.0f;
			}
		}
		if (estadoConst == 5 && estadoAuto != 2) {//solo cruza si es que el carro no esta pasando por ahi
			movConstX -= 0.6f;
			if (movConstX <= -370) {
				OrientaConst = 90.0f;
				estadoConst = 6.0f;
			}
		}
		if (estadoConst == 6) {
			movConstZ -= 0.6f;
			if (movConstZ <= -275) {
				OrientaConst = 180.0f;
				estadoConst = 7.0f;

			}
		}
		if (estadoConst == 7) {
			movConstX -= 0.6f;
			if (movConstX <= -440) {
				OrientaConst = -90.0f;
				estadoConst = 8.0f;
			}
		}
		if (estadoConst == 8) {
			movConstZ += 0.6f;
			if (movConstZ >= -260) {
				animacionConst = FALSE;
				estadoConst = 9.0f;//Para que ya no se mueva
			}
		}
	}

	switch (estadoShan){//ANIMACIÓN DEL DEPORTISTA
	case 1://lega a 20
		if (IdaRegresoShan == 1)
		{
			movShan += 0.5f;
			if (movShan >= 20) {
				IdaRegresoShan = 0;
				orienShan = 180.0f;
			}
		}
		else {
			movShan -= 0.5f;
			if (movShan <= 0) {
				orienShan = 0.0f;
				IdaRegresoShan = 1;
				estadoShan = 2;
			}
		}
		break;
	case 2://llega a 80
		if (IdaRegresoShan == 1 && estadoShan == 2)
		{
			movShan += 0.5f;
			if (movShan >= 80) {
				IdaRegresoShan = 0;
				orienShan = 180.0f;
			}
		}
		else {
			movShan -= 0.5f;
			if (movShan <= 0) {
				orienShan = 0.0f;
				IdaRegresoShan = 1;
				estadoShan = 3;
			}
		}
		break;
	case 3://llega a 120
		if (IdaRegresoShan == 1)
		{
			movShan += 0.5f;
			if (movShan >= 120) {
				IdaRegresoShan = 0;
				orienShan = 180.0f;
			}
		}
		else {
			movShan -= 0.5f;
			if (movShan <= 0) {
				orienShan = 0.0f;
				IdaRegresoShan = 1;
				estadoShan = 4;
			}
		}
		break;
	case 4://llega a 160
		if (IdaRegresoShan == 1)
		{
			movShan += 0.5f;
			if (movShan >= 160) {
				IdaRegresoShan = 0;
				orienShan = 180.0f;
			}
		}
		else {
			movShan -= 0.5f;
			if (movShan <= 0) {
				orienShan = 0.0f;
				IdaRegresoShan = 1;
				estadoShan = 1;
			}
		}
		break;
	default:
		break;

	}
	
	switch (estado_trici)//ANIMACIÓN DEL TAMALERO
	{
	case 0:
		if (movTrici_z <= -250.0f){
			orientaTrici = 0.0f;
			movTrici_z += 0.5f;
		}else {
			estado_trici = 1;
		}
		break;
	case 1:
		if (movTrici_x <= 150.0f) {
			orientaTrici = 90.0f;
			movTrici_x += 0.5f;
		}
		else {
			estado_trici = 2;
		}
		break;
	case 2:
		if (movTrici_z >= -385.0f) {
			movTrici_z -= 0.5f;
			orientaTrici = 180.0f;
		}
		else {
			estado_trici = 3;
		}
		break;
	case 3:
		if (movTrici_x <= 490) {
			movTrici_x += 0.5f;
			orientaTrici = 90.0f;
		}
		else {
			estado_trici = 4;
		}
		break;
	case 4:
		if (movTrici_z <= -110.0f) {
			movTrici_z += 0.5f;
			orientaTrici = 0.0f;
		}
		else {
			estado_trici = 5;
		}
		break;
	case 5:
		if (movTrici_x >= 270.0f) {
			movTrici_x -= 0.5f;
			orientaTrici = 270.0f;
		}
		else {
			estado_trici = 6;
		}
		break;
	case 6:
		if (movTrici_z <= 190.0f) {
			movTrici_z += 0.5f;
			orientaTrici = 0.0f;
		}
		else {
			estado_trici = 7;
		}
		break;
	case 7:
		if (movTrici_x <= 500.0f) {
			orientaTrici = 90.0f;
			movTrici_x += 0.5f;
		}
		else {
			estado_trici = 8;
		}
		break;
	case 8:
		if (movTrici_x >= 270.0f) {
			orientaTrici = 270.0f;
			movTrici_x -= 0.5f;
		}
		else {
			estado_trici = 9;
		}
		break;
	case 9:
		if (movTrici_z >= -110.0f) {
			orientaTrici = 180.0f;
			movTrici_z -= 0.5f;
		}
		else {
			estado_trici = 10;
		}
		break;
	case 10:
		if (movTrici_x <= 490.0f) {
			orientaTrici = 90.0f;
			movTrici_x += 0.5f;
		}
		else {
			estado_trici = 11;
		}
		break;
	case 11:
		if (movTrici_z >= -385.0f) {
			orientaTrici = 180.0f;
			movTrici_z -= 0.5f;
		}
		else {
			estado_trici = 12;
		}
		break;
	case 12:
		if (movTrici_x >= 150.0f) {
			orientaTrici = 270.0f;
			movTrici_x -= 0.5f;
		}
		else {
			estado_trici = 13;
		}
		break;
	case 13:
		if (movTrici_z <= -250.0f) {
			movTrici_z += 0.5f;
			orientaTrici = 0.0f;
		}else {
			estado_trici = 14;
		}
		break;
	case 14:
		if (movTrici_x >= -175.0f) {
			orientaTrici = 270.0f;
			movTrici_x -= 0.5f;
		}
		else {
			estado_trici = 15;
		}
		break;
	case 15:
		if (movTrici_z >= -500.0f) {
			movTrici_z -= 0.5f;
			orientaTrici = 180.0f;
		}
		else {
			estado_trici = 0;
		}
		break;
	default:
		break;
	}

	switch (estado_bici)//ANIMACIÓN DE LA BICI
	{
	case 0:
		if (movBici_z <= 255.0f) {
			movBici_z += 2.0f;
			orientaBici = 0.0;
		}
		else {
			estado_bici = 1;
		}
		break;
	case 1:
		
		if (movBici_x <= 55.0f) {
			orientaBici = 90.0f;
			movBici_x += 2.0;
		}
		else {
			estado_bici = 2;
		}
		break;
	case 2:
		if (movBici_z >= 50.0f)
		{
			orientaBici = 180.0f;
			movBici_z -= 2.0f;
		}
		else {
			estado_bici = 3;
		}
		break;
	case 3:
		if (movBici_x >= -250.0f) {
			orientaBici = 270.0f;
			movBici_x -= 2.0f;
		}
		else {
			estado_bici = 4;
		}
		break;
	case 4:
		if (movBici_z >= -5.0f) {
			orientaBici = 180.0f;
			movBici_z -= 2.0f;
		}
		else {
			estado_bici = 5;
		}
		break;
	case 5:
		if (movBici_x >= -500.0f) {
			orientaBici = 270.0f;
			movBici_x -= 2.0f;
		}
		else
		{
			estado_bici = 0;
		}
		break;
	default:
		break;
	}

	switch (estado_dogPerson) {//ANIMACIÓN DEL PERRO
		case 0:
			if (movPersonZ <= 170.0f) {
				rotDogPerson = 0.0f;
				movDogZ += SPEED_MOV;
				movPersonZ += SPEED_MOV;
			} else {
				movDogZ = movPersonZ - 5.0f;
				estado_dogPerson = 1;
			}
			break;
		case 1:
			if (movPersonX <= 220.0f) {
				rotDogPerson = 90.0f;
				movDogX += SPEED_MOV;
				movPersonX += SPEED_MOV;
			} else {
				movDogX = movPersonX + 5.0f;
				estado_dogPerson = 2;
			}
			break;
		case 2:
			if (movPersonZ <= 250.0f) {
				rotDogPerson = 0.0f;
				movDogZ += SPEED_MOV;
				movPersonZ += SPEED_MOV;
			}
			else {
				movDogZ = movPersonZ + 10.0f;
				estado_dogPerson = 3;
			}
			break;
		case 3:
			if (movPersonX >= -80.0f) {
				rotDogPerson = 270.0f;
				movDogX -= SPEED_MOV;
				movPersonX -= SPEED_MOV;
			}
			else {
				movDogX = movPersonX - 10.0f;
				estado_dogPerson = 4;
			}
			break;
		case 4:
			if (movPersonZ >= 0.0f) {
				rotDogPerson = 180.0f;
				movDogZ -= SPEED_MOV;
				movPersonZ -= SPEED_MOV;
			}
			else {
				movDogZ = movPersonZ - 5.0f;
				estado_dogPerson = 5;
			}
			break;
		
		case 5:
			if (movPersonX <= 5.0f) {
				rotDogPerson = 90.0f;
				movDogX += SPEED_MOV;
				movPersonX += SPEED_MOV;
			}
			else {
				movDogZ = movPersonX + 5.0f;
				estado_dogPerson = 0;
				movPersonZ = movDogZ = 0.0f;
				movPersonX = movDogX = 0.0f;
			}
			break;
	}
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

	// Carga de Modelos
	// ----------------
	//EDIFICIOS
	Model oxxo("resources/objects/oxxo/oxxo.obj");
	Model entrada("resources/objects/Entrada/Entrada.obj");//Entrada a la unidad
	Model plano("resources/objects/Plano/planoVilla.obj");//Plano de la unidad
	Model edificiosVilla("resources/objects/EdificioVilla/EdificioVilla.obj");//Edificios de la unidad
	Model iglesia("resources/objects/Iglesia/iglesia.obj");//Iglesia
	Model arbusto("resources/objects/arbusto/arbusto.obj");//Arbusto
	Model courtBasket("resources/objects/CanchaBasquet/cancha.obj");//Cancha
	//OBJETOS A ANIMAR
	Model Carro("resources/objects/Bocho/Bocho.obj");//Carroceria del bocho
	Model llanta("resources/objects/Bocho/Rueda.obj");//Ruedas del bocho
	Model pedales("resources/objects/bicicleta/pedales.obj");//Pedales de la bicileta
	Model cuadro("resources/objects/bicicleta/cuadro.obj");//Cuadro de la bicilceta
	Model rueda("resources/objects/bicicleta/rueda.obj");//Reuedas de la bicileta
	Model pedalesTriciclo("resources/objects/triciclo/pedalesTriciclo.obj");//Pedales del tiriclo
	Model triciclo("resources/objects/triciclo/triciclo2F.obj");//cuerpo del triciclo
	Model ruedaTriciclo("resources/objects/triciclo/ruedaTriciclo.obj");//Ruedas del triciclo
	//MUEBLES
	Model Librero1("resources/objects/Cuarto1/Librero/Librero.obj");//Librero1
	//Model Mesa("resources/objects/Cuarto1/Mesa/Mesa.obj");//Mesa (No corrio)
	 

	// Modelos dinamicos
	//------------------
	
	// Perro
	ModelAnim dog("resources/objects/Dog/doggo.dae");
	dog.initShaders(animShader.ID);

	// Persona Paseando
	ModelAnim womanWalk("resources/objects/PersonaCaminando/woman.dae");
	womanWalk.initShaders(animShader.ID);

	// Persona Caminando
	ModelAnim manWalk("resources/objects/PersonaCaminando2/man.dae");
	manWalk.initShaders(animShader.ID);
	
	//Persona en Bicicleta
	ModelAnim manBici("resources/objects/bicicleta/man.dae");
	manBici.initShaders(animShader.ID);
	
	//Tamalero
	ModelAnim manTricycle("resources/objects/triciclo/manTricycle.dae");
	manTricycle.initShaders(animShader.ID);
	
	//persona corriendo
	ModelAnim shannon("resources/objects/Deportista/Running.dae");
	shannon.initShaders(animShader.ID);
	

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


		//-------------------Triciclo---------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movTrici_x, 1.0f, movTrici_z));
		model = glm::scale(model, glm::vec3(0.09));
		tmp = model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::rotate(tmp, glm::radians(orientaTrici), glm::vec3(0.0f, 0.0f, 1.0f));
		animShader.setMat4("model", model);
		manTricycle.Draw(animShader);

		//-------------------Bicicleta--------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movBici_x, 0.0f, movBici_z));
		model  = glm::rotate(model, glm::radians(orientaBici), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09));
		animShader.setMat4("model", model);
		manBici.Draw(animShader);

		
		//-------------------Perro--------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(290.0f + movDogX, 0.0f, 0.0f + movDogZ)); 
		model = glm::scale(model, glm::vec3(0.3f));	
		model = glm::rotate(model, glm::radians(rotDogPerson), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		dog.Draw(animShader);

		//-------------------Paseando--------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(285.0 + movPersonX, 0.0f, 0.0f + movPersonZ));
		model = glm::scale(model, glm::vec3(0.09f));
		model = glm::rotate(model, glm::radians(rotDogPerson), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		womanWalk.Draw(animShader);

		//-------------------Caminando--------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(580.0f + movConstX, 0.0f, 120.0f + movConstZ));
		model = glm::scale(model, glm::vec3(0.09f));
		model = glm::rotate(model, glm::radians(OrientaConst), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		manWalk.Draw(animShader);

		//-------------------Corriendo--------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 70.0f + movShan));
		model = glm::rotate(model, glm::radians(orienShan), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f));
		animShader.setMat4("model", model);
		shannon.Draw(animShader);
		

		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario 
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -70.0f));//proporciones de todo con un plano
		model = glm::scale(model, glm::vec3(12.0f));
		staticShader.setMat4("model", model);
		plano.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-170.0f, 0.1f, -140.0f));//iglesia
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(22.0f));
		staticShader.setMat4("model", model);
		iglesia.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-200.0f, 5.0f, 0.0f));//arbusto 1
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		arbusto.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(320.0f, 5.0f, 5.0f));//arbusto 2
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		arbusto.Draw(staticShader);
		
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, -75.0f));//edificio 1 de villa
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f));
		staticShader.setMat4("model", model);
		edificiosVilla.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(140.0f, 0.0f, 155.0f));//edificio 2 de villa
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f));
		staticShader.setMat4("model", model);
		edificiosVilla.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-160.0f, 0.0f, 155.0f));//edificio 3 de villa
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f));
		staticShader.setMat4("model", model);
		edificiosVilla.Draw(staticShader);
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(389.0f, 0.0f, 100.0f));//edificio 4 de villa
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f));
		staticShader.setMat4("model", model);
		edificiosVilla.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(320.0f, 0.0f, -245.0f));//edificio 5 de villa
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f));
		staticShader.setMat4("model", model);
		edificiosVilla.Draw(staticShader);
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(398.0f, 0.0f, -510.0f));//edificio 6 de villa
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f));
		staticShader.setMat4("model", model);
		edificiosVilla.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(195.0f, 0.0f, -510.0f));//edificio 7 de villa
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f));
		staticShader.setMat4("model", model);
		edificiosVilla.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-368.0f, 0.0f, 190.0f));//edificio 8 de villa
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f));
		staticShader.setMat4("model", model);
		edificiosVilla.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-368.0f, 0.0f, -70.0f));//edificio 9 de villa
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f));
		staticShader.setMat4("model", model);
		edificiosVilla.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 0.0f, -280.0f));//edificio 10 de villa
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f));
		staticShader.setMat4("model", model);
		edificiosVilla.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 0.0f, -490.0f));//edificio 11 de villa
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f));
		staticShader.setMat4("model", model);
		edificiosVilla.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(125.0f, 0.0f, -110.0f));//Oxxo
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f));
		staticShader.setMat4("model", model);
		oxxo.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(550.0f, 0.0f, 100.0f));//Entrada
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		entrada.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, 150.0f));//Cancha
		model = glm::scale(model, glm::vec3(9.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		courtBasket.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Muebles para los cuartos
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, 150.0f));//Librero1
		model = glm::scale(model, glm::vec3(0.15f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		Librero1.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Persona en Triciclo
		// -------------------------------------------------------------------------------------------------------------------------
		tmp = model = glm::translate(glm::mat4(1.0f), glm::vec3(movTrici_x, 1.0f, movTrici_z));
		tmp = model = glm::rotate(model, glm::radians(orientaTrici), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f));
		staticShader.setMat4("model", model);
		triciclo.Draw(staticShader);
		
		model = glm::translate(tmp, glm::vec3(0.0f, 3.25f, -3.0f));
		model = model = glm::rotate(model, glm::radians(giroPedales), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f));
		staticShader.setMat4("model", model);
		pedalesTriciclo.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(-0.45f, 4.0f, -8.5f));
		model = model = glm::rotate(model, glm::radians(giroPedales), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f));
		staticShader.setMat4("model", model);
		ruedaTriciclo.Draw(staticShader); // rueda trasera

		model = glm::translate(tmp, glm::vec3(-5.0f, 4.0f, 8.0f));
		model = model = glm::rotate(model, glm::radians(giroPedales), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f));
		staticShader.setMat4("model", model);
		ruedaTriciclo.Draw(staticShader); // rueda delantera der

		model = glm::translate(tmp, glm::vec3(5.0f, 4.0f, 8.0f));
		model = model = glm::rotate(model, glm::radians(giroPedales), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f));
		staticShader.setMat4("model", model);
		ruedaTriciclo.Draw(staticShader); // rueda delantera izq
		
		// -------------------------------------------------------------------------------------------------------------------------
		// Persona en bici
		// -------------------------------------------------------------------------------------------------------------------------
		tmp = model = glm::translate(glm::mat4(1.0f), glm::vec3(movBici_x, -0.5f, movBici_z));
		tmp = model = glm::rotate(model, glm::radians(orientaBici), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f));
		staticShader.setMat4("model", model);
		cuadro.Draw(staticShader);
		
		model = glm::translate(tmp, glm::vec3(0.0f, 2.75f, 0.5f));
		model = model = glm::rotate(model, glm::radians(giroPedales), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f));
		staticShader.setMat4("model", model);
		pedales.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(-0.2f, 2.85f, 5.85f));
		model = model = glm::rotate(model, glm::radians(giroPedales), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f));
		staticShader.setMat4("model", model);
		rueda.Draw(staticShader); // Adelante

		model = glm::translate(tmp, glm::vec3(-0.2f, 2.85f, -3.25f));
		model = model = glm::rotate(model, glm::radians(giroPedales), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f));
		staticShader.setMat4("model", model);
		rueda.Draw(staticShader); // Atras
		
		// -------------------------------------------------------------------------------------------------------------------------
		// Carro
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-225.0f + movAuto_x, 1.5f, 500.0f + movAuto_z));
		tmp = model = glm::rotate(model, glm::radians(orienta), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));
		staticShader.setMat4("model", model);
		Carro.Draw(staticShader);
		
		model = glm::translate(tmp, glm::vec3(6.7f, 1.0f, 15.0f));
		model = glm::rotate(model, glm::radians(girollantas), glm::vec3(1.0f, 0.0f, 0.0f));//giro de las llantas
		model = glm::scale(model, glm::vec3(0.0044f, 0.0044f, 0.0044f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Izq delantera

		model = glm::translate(tmp, glm::vec3(-6.7f, 1.0f, 15.0f));
		model = glm::rotate(model, glm::radians(girollantas), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0044f, 0.0044f, 0.0044f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Der delantera

		model = glm::translate(tmp, glm::vec3(-6.7f, 1.0f, -10.0f));
		model = glm::rotate(model, glm::radians(girollantas), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0044f, 0.0044f, 0.0044f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Der trasera

		model = glm::translate(tmp, glm::vec3(6.7f, 1.0f, -10.0f));
		model = glm::rotate(model, glm::radians(girollantas), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0044f, 0.0044f, 0.0044f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Izq trase   

		
		// -------------------------------------------------------------------------------------------------------------------------
		// Termina colocación de modelos
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
	
	//Musica
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		music();
	}

	//Carro animation
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		animacion ^= true;

	//Constructor animation
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		animacionConst ^= true;

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
