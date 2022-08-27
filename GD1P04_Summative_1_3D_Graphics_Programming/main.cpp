#include <glew.h>
#include <glfw3.h>
#include <iostream>

#include "ShaderLoader.h"

// Textures
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// Math includes
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "CCamera.h"

// My class includes
#include "CQuad.h"
#include "CTESTQUADSHAPE.h"
#include "CShapeHex.h"
#include "CShapeQuad.h"

// Window Pointer
GLFWwindow* pWindow = nullptr;

// Window Dimensions
int iWindowWidth = 800;
int iWindowHeight = 800;

// Function Prototypes
void InitialSetup();
void Update();
void Render();

// Programs
GLuint Program_FixedTri;
GLuint Program_PositionOnly;
GLuint Program_VertexColor;
GLuint Program_ColorFade;
GLuint Program_Texture;
GLuint Program_TextureMix;
GLuint Program_WorldSpace;
GLuint Program_ClipSpace;

// Verticies / Indicies

// Week 4 EBO stuff
GLfloat fVertices_Quad[] = {
	// Index	// Position				// Color			// Texture Coords
	/* 1 */		-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,		// Top - Left
	/* 2 */		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		// Bot - Left
	/* 3 */		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 1.0f,	1.0f, 0.0f,		// Bot - Right
	/* 4 */		 0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f,		// Top - Left
};

GLuint Indices_Quad[] = {
	0, 1, 2,	// First Triangle	(TL -> BL -> BR)
	0, 2, 3,	// Second Triangle	(TL -> BR -> TR)
};

// Quad VAO, VBO, and EBO
GLuint VBO_Quad;
GLuint VAO_Quad;
GLuint EBO_Quad;

// Time
float fCurrentTime;
float fPreviousTimeStep;
//float fDeltaTime;

// Textures
GLuint Texture_Rayman;
GLuint Texture_AwesomeFace;

// Object Matrices and Components
glm::vec3 ObjPosition = glm::vec3(0.0f, 0.0f, 0.0f);
glm::mat4 TranslationMat;

float ObjRotationAngle = 0.0f;
glm::mat4 RotationMat;

glm::vec3 ObjScale = glm::vec3(400.0f, 400.0f, 1.0f);
glm::mat4 ScaleMat;

glm::mat4 ObjModelMat;

glm::mat4 PVMMat;

// Camera
CCamera camera;

// Create Quad using class to test
CShape* pQuad;
// Create PVMMat for this quad
glm::mat4 PVMMatQuad;
glm::mat4 PVMMatTestQuad;
//glm::mat4 PVMMatHex;
//glm::mat4 PVMMatHexTwo;

CTESTQUADSHAPE* pTestQuad;
CShapeHex* pShapeHex;
CShapeQuad* pShapeQuad;


int main()
{
	// Initializing GLFW and setting the version to 4.6 with only Core functionality avaliable
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Create a GLFW controlled context window
	pWindow = glfwCreateWindow(iWindowWidth, iWindowHeight, "First OpenGL Window", NULL, NULL);
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
	InitialSetup();

	// Main loop
	while (glfwWindowShouldClose(pWindow) == false)
	{
		// Update all objects and run the processes
		Update();

		// Render all the objects
		Render();
	}

	// Ensure correct shutdown of GLFW
	glfwTerminate();
	return (0);
}

// ------------------------------------- Function Definitions -------------------------------------

// Setup the Initial elements of the program
void InitialSetup()
{
	// Set the color of the window for when the buffer is cleared
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Maps the range of the window size to NDC (-1 -> 1)
	glViewport(0, 0, iWindowWidth, iWindowHeight);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Create the programs

	// Week 4
	Program_Texture = ShaderLoader::CreateProgram(		"Resources/Shaders/NDC_Texture.vs",
														"Resources/Shaders/Texture.fs");

	Program_TextureMix = ShaderLoader::CreateProgram(	"Resources/Shaders/NDC_Texture.vs",
														"Resources/Shaders/TextureMix.fs");

	Program_WorldSpace = ShaderLoader::CreateProgram(	"Resources/Shaders/WorldSpace.vs",
														"Resources/Shaders/TextureMix.fs");
	
	Program_ClipSpace = ShaderLoader::CreateProgram(	"Resources/Shaders/ClipSpace.vs",
														"Resources/Shaders/TextureMix.fs");


	// Week 4 Quad using EBO
	// 
	// Generate the VAO for a Quad
	glGenVertexArrays(1, &VAO_Quad);
	glBindVertexArray(VAO_Quad);

	// Generate the EBO for a Quad
	glGenBuffers(1, &EBO_Quad);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Quad);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices_Quad), Indices_Quad, GL_STATIC_DRAW);

	// Generate the VBO for a Quad
	glGenBuffers(1, &VBO_Quad);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Quad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fVertices_Quad), fVertices_Quad, GL_STATIC_DRAW);

	// Set the Vertex Attribute information (how to interpret the vertex data)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// Quad via class

	pQuad = new CQuad;
	pTestQuad = new CTESTQUADSHAPE;
	pShapeHex = new CShapeHex;
	pShapeQuad = new CShapeQuad;

	// Face Culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// ---------------------------------------------------Load the Image Data
	stbi_set_flip_vertically_on_load(true);
	int ImageWidth;
	int ImageHeight;
	int ImageComponents;
	unsigned char* ImageData = stbi_load(	"Resources/Textures/Rayman.jpg",
											&ImageWidth, &ImageHeight, &ImageComponents, 0);

	// Create and bind a new texture template
	glGenTextures(1, &Texture_Rayman);
	glBindTexture(GL_TEXTURE_2D, Texture_Rayman);

	// Check how many components the loaded image has (RGB or RGBA?)
	GLint LoadedComponents = (ImageComponents == 4) ? GL_RGBA : GL_RGB;

	// Populate the texture with the image data
	glTexImage2D(	GL_TEXTURE_2D, 0, LoadedComponents, ImageWidth, ImageHeight, 0,
					LoadedComponents, GL_UNSIGNED_BYTE, ImageData);

	// Generate the mipmaps, free the memory and unbind the texture
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(ImageData);

	// Setting the filtering and mipmap parameters for this texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Setting the address mode for this texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Clamp to border - would replace above two lines
	//GLfloat BorderColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, BorderColor);

	glBindTexture(GL_TEXTURE_2D, 0);

	// ----------------------------------------------------- Load the Second Image Data
	//stbi_set_flip_vertically_on_load(true);
	unsigned char* ImageData1 = stbi_load("Resources/Textures/AwesomeFace.png",
		&ImageWidth, &ImageHeight, &ImageComponents, 0);

	// Create and bind a new texture template
	glGenTextures(1, &Texture_AwesomeFace);
	glBindTexture(GL_TEXTURE_2D, Texture_AwesomeFace);

	// Check how many components the loaded image has (RGB or RGBA?)
	GLint LoadedComponents1 = (ImageComponents == 4) ? GL_RGBA : GL_RGB;

	// Populate the texture with the image data
	glTexImage2D(GL_TEXTURE_2D, 0, LoadedComponents1, ImageWidth, ImageHeight, 0,
		LoadedComponents1, GL_UNSIGNED_BYTE, ImageData1);

	// Generate the mipmaps, free the memory and unbind the texture
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(ImageData1);

	// Setting the filtering and mipmap parameters for this texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Setting the address mode for this texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Clamp to border - would replace above two lines
	//GLfloat BorderColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, BorderColor);

	glBindTexture(GL_TEXTURE_2D, 0);


	// Initialize the first value of the "previous" time step
	fPreviousTimeStep = (float)glfwGetTime();
	return;
}

// Render all the objects
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Week 3
	// Render the Quad
	//glUseProgram(Program_ClipSpace);
	//glBindVertexArray(VAO_Quad);
	
	//// Activate and bind the textures then send them to the shader
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, Texture_Rayman);
	//glUniform1i(glGetUniformLocation(Program_ClipSpace, "ImageTexture"), 0);
	//
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, Texture_AwesomeFace);
	//glUniform1i(glGetUniformLocation(Program_ClipSpace, "ImageTexture1"), 1);

	//// Pass time
	//glUniform1f(glGetUniformLocation(Program_ClipSpace, "CurrentTime"), fCurrentTime);

	//// Send variables to the shaders via Uniform
	//GLint ModelMatLoc = glGetUniformLocation(Program_ClipSpace, "PVMMat");
	//glUniformMatrix4fv(ModelMatLoc, 1, GL_FALSE, glm::value_ptr(PVMMat));

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	/////////////////////////////////////////////////////////////// Render quad using class
	//glUseProgram(Program_ClipSpace);
	//glBindVertexArray(pTestQuad->GetVAO());

	//// Activate and bind the textures then send them to the shader
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, Texture_Rayman);
	//glUniform1i(glGetUniformLocation(Program_ClipSpace, "ImageTexture"), 0);

	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, Texture_AwesomeFace);
	//glUniform1i(glGetUniformLocation(Program_ClipSpace, "ImageTexture1"), 1);

	//// Pass time
	//glUniform1f(glGetUniformLocation(Program_ClipSpace, "CurrentTime"), fCurrentTime);

	//// Send variables to the shaders via Uniform
	//GLint ModelMatLoc = glGetUniformLocation(Program_ClipSpace, "PVMMat");
	//glUniformMatrix4fv(ModelMatLoc, 1, GL_FALSE, glm::value_ptr(PVMMatTestQuad));

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//// Unbind assests to prevent accidental use/modification
	//glBindVertexArray(0);
	//glUseProgram(0);

	pShapeHex->Draw(fCurrentTime, Program_ClipSpace, Texture_Rayman, Texture_AwesomeFace);
	pShapeQuad->Draw(fCurrentTime, Program_ClipSpace, Texture_Rayman, Texture_AwesomeFace);

	glfwSwapBuffers(pWindow);

	return;
}

// Update
void Update()
{
	// Calculate the current DeltaTime and update the PreviousTimeStep for the next frame
	fCurrentTime = (float)glfwGetTime();
	float fDeltaTime = fPreviousTimeStep - fCurrentTime;
	fPreviousTimeStep = fCurrentTime;

	glfwPollEvents();

	

	// Calculate the Translation matrix
	TranslationMat = glm::translate(glm::mat4(), ObjPosition);

	// Calculate the Rotation matrix
	RotationMat = glm::rotate(glm::mat4(), glm::radians(ObjRotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));

	// Calculate the Scale matrix
	ScaleMat = glm::scale(glm::mat4(), ObjScale);

	// Calculate the Model matrix
	ObjModelMat = TranslationMat * RotationMat * ScaleMat;

	// Update the Orthographic Projection Matrix and the View Matrix
	camera.Update(fDeltaTime, iWindowWidth, iWindowHeight);

	// Calculate the PVM matrix
	PVMMat = camera.GetProjectionMat() * camera.GetViewMat() * ObjModelMat;

	// Update Quad created using class
	pQuad->Update();
	pTestQuad->Update();

	// Calculate PVM matrix for Quad
	PVMMatQuad = camera.GetProjectionMat() * camera.GetViewMat() * pQuad->GetModelMatrix();
	PVMMatTestQuad = camera.GetProjectionMat() * camera.GetViewMat() * pTestQuad->GetModelMatrix();
	
	// Update the Hex and generate its PVMs
	pShapeHex->Update(camera.GetProjectionMat(), camera.GetViewMat());

	// Update the Quad and generate its PVM
	pShapeQuad->Update(camera.GetProjectionMat(), camera.GetViewMat());

	return;
}

