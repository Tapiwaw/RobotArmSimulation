#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

#include "Renderer.h"

#include "Texture.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "RawModel.h"
#include "FileLoader.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
bool Wpressed = false;
bool Spressed = false;
bool Apressed = false;
bool Dpressed = false;

bool Qpressed = false;
bool Epressed = false;

bool Rpressed = false;

int main(void)
{

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
*/
	/* Create a windowed mode window and its OpenGL context */
	unsigned int width = 1080;
	unsigned int height = 720;
	window = glfwCreateWindow(width, height, "Simulator", NULL, NULL);

	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1); //Makes sure every keypress is handled

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		std::cout << "Error!" << std::endl;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;

	{
	/*
		float squarePositions[] = {
			-0.5, -0.5, 0.0f, //0
			0.5, -0.5, 0.0f,  //1
			0.5, 0.5, 0.0f,   //2
			-0.5, 0.5, 0.0f   //3
		};
		float squareTextures[] = {
			0.0f, 0.0f, //0
			1.0f, 0.0f, //1
			1.0f, 1.0f, //2
			0.0f, 1.0f  //3
		};

		unsigned int indices[] = { // draw a square with two triangles
			0,1,2,
			2,3,0
		};
		*/
		float cubePositions[] = {
			-0.5,0.5,0.5,  //0
			-0.5,-0.5,0.5,  //1
			 0.5, 0.5, 0.5, //2
			 0.5, -0.5, 0.5, //3
			 0.5, 0.5, -0.5,  //4 
			 0.5, -0.5, -0.5,  //5
			-0.5, 0.5, -0.5,  //6
			-0.5, -0.5, -0.5   //7
		};
		float cubeTextures[] = {
			0.0f, 1.0f, //0
			0.0f, 0.0f, //1
			1.0f, 1.0f, //2
			1.0f, 0.0f,  //3
			0.0f, 1.0f,  //4
			0.0f, 1.0f,  //5
			0.0f, 1.0f,  //6
			0.0f, 1.0f  //7
		};

		unsigned int cubeIndices[] = { // draw a square with two triangles
			0,1,2,
			1,3,2,
			3,4,2,
			3,5,4,
			0,4,6,
			0,2,4,
			7,4,6,
			7,5,4,
			0,1,6,
			1,7,6,
			1,3,5,
			1,5,7
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		RawModel basicCube;
		basicCube.addVertexPositions(cubePositions, 8*3* sizeof(float));
		basicCube.addTextureCoord(cubeTextures, 8 *2* sizeof(float));
		basicCube.addIndices(cubeIndices, 12 * 3);

		FileLoader objFile;
		float* Positions = new float[objFile.GetVertexBufferSize("res/Models/stall.obj")];
		float* TextureCoord = new float[objFile.GetTextureBufferSize("res/Models/stall.obj")];
		float* Normals = new float[objFile.GetNormalsBufferSize("res/Models/stall.obj")];
		unsigned int* Indices = new unsigned int[objFile.GetIndexBufferSize("res/Models/stall.obj")];

		objFile.load("res/Models/stall.obj", Positions, TextureCoord, Normals, Indices);

		RawModel Stall;
		Stall.addVertexPositions(Positions, objFile.GetVertexBufferSize("res/Models/stall.obj") * sizeof(float));
		Stall.addTextureCoord(TextureCoord, objFile.GetTextureBufferSize("res/Models/stall.obj") * sizeof(float));	
		Stall.addIndices(Indices, objFile.GetIndexBufferSize("res/Models/stall.obj"));

	/*	for (int i = 0; i < objFile.GetVertexBufferSize("res/Models/cube.obj"); i++) {
			std::cout << "vertex[" << i << "] = " << Positions[i] << std::endl;
		} */

		Shader basicVertexShader("res/Shaders/basicVertexShader.vs", GL_VERTEX_SHADER);
		Shader basicFragmentShader("res/Shaders/basicFragmentShader.fs", GL_FRAGMENT_SHADER);
		
		ShaderProgram basicShaderProgram;

		basicShaderProgram.AttachShader(basicVertexShader);
		basicShaderProgram.AttachShader(basicFragmentShader);
		basicShaderProgram.CompileAndLink();
		basicShaderProgram.Bind();

		//glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		
		// note that we're translating the scene in the reverse direction of where we want to move

		//glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -13.0f));
		glm::mat4 view;
		view = glm::lookAt(glm::vec3(0.0f, 0.0f, 13.0f), //Camera postition 
			   glm::vec3(0.0f, 0.0f, 0.0f),//Target position
			   glm::vec3(0.0f, 1.0f, 0.0f)); //up direction


		Texture basicTexture("res/Textures/stallTexture.png");
		basicTexture.Bind();

		float r = 0.0f;
		basicShaderProgram.SetUniform1i("u_Texture", 0);
		basicShaderProgram.SetUniformMat4f("u_Projection",projection);
		basicShaderProgram.SetUniformMat4f("u_View", view);
		basicShaderProgram.SetUniformMat4f("u_Model", model);
		basicShaderProgram.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
		basicShaderProgram.Unbind();


		Renderer render;
		
		float increment = 0.05f;
		float Model_Xpos = 0.0f;
		float Model_Ypos = 0.0f;
		float Model_Zpos = 0.0f;
		float Model_RotateY = 0.0f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			render.Clear();

			basicShaderProgram.Bind();

			if (Wpressed) {
				Model_Ypos = increment;
				std::cout << "W Pressed" << std::endl;
				Wpressed = false;
			}
			if (Spressed) {
				Model_Ypos = -1*increment;
				std::cout << "S Pressed" << std::endl;
				Spressed = false;
			}
			if (Apressed) {
				Model_Xpos =  -1*increment;
				std::cout << "A Pressed" << std::endl;
				Apressed = false;
			}
			if (Dpressed) {
				Model_Xpos = increment;
				std::cout << "D Pressed" << std::endl;
				Dpressed = false;
			}
			if (Qpressed) {
				Model_Zpos = -1 * increment;
				std::cout << "Q Pressed" << std::endl;
				Qpressed = false;
			}
			if (Epressed) {
				Model_Zpos = increment;
				std::cout << "E Pressed" << std::endl;
				Epressed = false;
			}
			if (Rpressed) {
				Model_RotateY = 1.0f;
				std::cout << "R Pressed" << std::endl;
				Rpressed = false;
			}

			model = glm::translate(model, glm::vec3(Model_Xpos, Model_Ypos, Model_Zpos));
			model = glm::rotate(model, glm::radians(Model_RotateY), glm::vec3(0.0f, 1.0f, 0.0f));
			basicShaderProgram.SetUniformMat4f("u_Model", model);
			Model_Xpos = 0.0f;
			Model_Ypos = 0.0f;
			Model_Zpos = 0.0f;
			Model_RotateY = 0.0f;


			//render.DrawRawModel(basicSquare, basicShaderProgram);
			//render.DrawRawModel(Cube, basicShaderProgram);
			render.DrawRawModel(Stall, basicShaderProgram);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
		
		/*Delete ShaderProgram and Shaders before program terminates*/

	}

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W )
	{
		Wpressed = true;
	}
	if (key == GLFW_KEY_S) {
		Spressed = true;
	}
	if (key == GLFW_KEY_A) {
		Apressed = true;
	}
	if (key == GLFW_KEY_D) {
		Dpressed = true;
	}
	if (key == GLFW_KEY_Q) {
		Qpressed = true;
	}
	if (key == GLFW_KEY_E) {
		Epressed = true;
	}
	if (key == GLFW_KEY_R) {
		Rpressed = true;
	}

	//if (key == GLFW_KEY_E && action == GLFW_PRESS)

}