//#include <glew.h>
//#include <glfw3.h>
//#include <iostream>

//#include "ShaderLoader.h"

// Textures
#define STB_IMAGE_IMPLEMENTATION
//#include "CTextureLoader.h"

// Math includes
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>

//#include "CCamera.h"

// My class includes
//#include "CQuad.h"
//#include "CTESTQUADSHAPE.h"
//#include "CShapeHex.h"
//#include "CShapeQuad.h"
#include "CGameManager.h"

//// Window Pointer
//GLFWwindow* pWindow = nullptr;
//
//// Window Dimensions
//int iWindowWidth = 800;
//int iWindowHeight = 800;
//
//// Function Prototypes
//void InitialSetup();
//void Update();
//void Render();
//
//// Programs
//GLuint Program_ClipSpace;
//GLuint Program_AnimationSpriteSheet;
//
//// Time
//float fCurrentTime;
//float fPreviousTimeStep;
////float fDeltaTime;
//
//// Textures
//GLuint Texture_Rayman;
//GLuint Texture_AwesomeFace;
//GLuint Texture_Animation;
//GLuint Texture_VinesSpriteSheet;
//GLuint Texture_Squid;
//GLuint Texture_Sprinkler;
//
//// Camera
//CCamera camera;
//
//// Create Quad using class to test;
//CShapeHex* pShapeHex;
//CShapeQuad* pShapeQuad;


int main()
{
	// Window Pointer
	GLFWwindow* pWindow = nullptr;

	// Window Dimensions
	int iWindowWidth = 800;
	int iWindowHeight = 800;

	// Initializing GLFW and setting the version to 4.6 with only Core functionality avaliable
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Create a GLFW controlled context window
	pWindow = glfwCreateWindow(iWindowWidth, iWindowHeight, "The Two Hexagons which are One and the Miracle Regrowing Vine", NULL, NULL);
	if (pWindow == NULL)
	{
		std::cout << "GLFW failed to initialize properly. Terminating program" << std::endl;
		system("pause");

		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(pWindow);

	// Initializing GLEW to populate OpenGL function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW failed to initialize properly. Terminating program" << std::endl;

		glfwTerminate();
		return (-1);
	}

	// Setup the Initial elements of the program
	//InitialSetup(); // GAME MANAGER TO BE CREATED HERE
	CGameManager gameManager(pWindow, iWindowWidth, iWindowHeight);

	// Main loop
	while (glfwWindowShouldClose(pWindow) == false)
	{
		// Update all objects and run the processes
		//Update();
		gameManager.Update();

		// Render all the objects
		//Render();
		gameManager.Render();
	}

	// Ensure correct shutdown of GLFW
	glfwTerminate();
	return (0);
}

// ------------------------------------- Function Definitions -------------------------------------

//// Setup the Initial elements of the program
//void InitialSetup()
//{
//	// Set the color of the window for when the buffer is cleared
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//	// Maps the range of the window size to NDC (-1 -> 1)
//	glViewport(0, 0, iWindowWidth, iWindowHeight);
//
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//	// Create the programs
//	
//	Program_ClipSpace = ShaderLoader::CreateProgram(			"Resources/Shaders/ClipSpace.vs",
//																"Resources/Shaders/TextureMix.fs");
//
//	Program_AnimationSpriteSheet = ShaderLoader::CreateProgram(	"Resources/Shaders/ClipSpace.vs",
//																"Resources/Shaders/TextureAnimation.fs");
//
//	pShapeHex = new CShapeHex;
//	pShapeQuad = new CShapeQuad;
//
//	// Face Culling
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
//
//	// enabled so textures dont apply upsidedown
//	stbi_set_flip_vertically_on_load(true);
//	// ---------------------------------------------------Load the Image Data
//	CTextureLoader::LoadTexture(Texture_Rayman, "Resources/Textures/Rayman.jpg", true);
//	CTextureLoader::LoadTexture(Texture_Squid, "Resources/Textures/Kalimari.png", true);
//
//	// ----------------------------------------------------- Load the Second Image Data
//	CTextureLoader::LoadTexture(Texture_AwesomeFace, "Resources/Textures/AwesomeFace.png", true);
//	CTextureLoader::LoadTexture(Texture_Sprinkler, "Resources/Textures/Sprinkler.PNG", true);
//
//	// Load the spritesheet for the animation
//	CTextureLoader::LoadTexture(Texture_Animation, "Resources/Textures/Capguy_Walk.png", true);
//	CTextureLoader::LoadTexture(Texture_VinesSpriteSheet, "Resources/Textures/GrowingVinesSpriteSheet.png", true);
//
//
//	// Initialize the first value of the "previous" time step
//	fPreviousTimeStep = (float)glfwGetTime();
//	return;
//}
//
//// Render all the objects
//void Render()
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	pShapeHex->Draw(fCurrentTime, Program_ClipSpace, Texture_Squid, Texture_Sprinkler);
//	pShapeQuad->Draw(Program_AnimationSpriteSheet, Texture_VinesSpriteSheet);
//
//	glfwSwapBuffers(pWindow);
//
//	return;
//}
//
//// Update
//void Update()
//{
//	// Calculate the current DeltaTime and update the PreviousTimeStep for the next frame
//	fCurrentTime = (float)glfwGetTime();
//	float fDeltaTime = fCurrentTime - fPreviousTimeStep;
//	fPreviousTimeStep = fCurrentTime;
//
//	glfwPollEvents();
//
//	// Update the Orthographic Projection Matrix and the View Matrix
//	camera.Update(fDeltaTime, iWindowWidth, iWindowHeight);
//
//	// Update the Hex and generate its PVMs
//	pShapeHex->Update(camera.GetProjectionMat(), camera.GetViewMat());
//
//	// Update the Quad and generate its PVM
//	pShapeQuad->Update(camera.GetProjectionMat(), camera.GetViewMat(), fDeltaTime);
//
//	return;
//}

