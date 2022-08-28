//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name	: main.cpp
// Description	: Contains the main() function of the program and controls the flow of the program
// Author		: Oliver Webb-Speight
// Mail			: Oliver.WebbSpeight@mds.ac.nz
//

// Required for Textures
#define STB_IMAGE_IMPLEMENTATION

#include "CGameManager.h"

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
	CGameManager gameManager(pWindow, iWindowWidth, iWindowHeight);

	// Main loop
	while (glfwWindowShouldClose(pWindow) == false)
	{
		// Update all objects and run the processes
		gameManager.Update();

		// Render all the objects
		gameManager.Render();
	}

	// Ensure correct shutdown of GLFW
	glfwTerminate();
	return (0);
}