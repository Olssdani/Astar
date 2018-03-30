#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "shader.h"
#include "grid.h"
#include "Astar.h"
#include <iostream>
#include <vld.h>


//Funktion Def
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, float vertices[], grid &temp, Astar &_astar);

// settings
const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 720;

int main()
{
	//Number of squares per row
	const static int size = 50;
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Sets the minimum opengl version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//GIves us a subset of opengl tools

	

	// glfw window creation
	// --------------------
	//GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "A* pathfinding", glfwGetPrimaryMonitor(), NULL); //fullscreen
	//Creates a pointer to a window object 
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "A* pathfinding", NULL, NULL);  
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader zprogram
	// ------------------------------------
	Shader ourShader("C:/Users/Daniel olsson/Documents/Programmering/AI/Project/Astar_g/GameEngine/Shaders/Vertex.glsl", "C:/Users/Daniel olsson/Documents/Programmering/AI/Project/Astar_g/GameEngine/Shaders/Fragment.glsl");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	//
	//Creates a grid of squares
	grid current(size);
	
	//Size of the vertices and indices arrays
	float vertices[size*size*16] = {0};
	unsigned int indices[size*size*6] = { 0 };

	//Creates the vertices and indices and set their position
	current.update(vertices, indices);

	//Creates buffers
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4* sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Astar _astar;

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window, vertices, current, _astar);

		// Rebind the Vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render the triangle
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, size*size*6, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, float vertices[], grid &temp, Astar &_astar)
{
	//Get the mouse postion
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	//Get the window size
	GLint m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	//Calculate from pixel cordinate to opengl postion
	float glXpos = (xpos / m_viewport[2] - 0.5) / 0.5;
	float glYpos = (ypos / m_viewport[3] - 0.5) / -0.5;

	// Press escape to close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	
	// Set start postion with left button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		temp.check_square(glXpos, glYpos, "start");
		temp.update(vertices);
	}

	// Set end postion with right button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		temp.check_square(glXpos, glYpos, "end");
		temp.update(vertices);
	}

	// Set walls with middle button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)  {
		temp.check_square(glXpos, glYpos, "wall");
		temp.update(vertices);
	}

	// If both start and end nodes are placed out it start to calculate the quickest route
	if (temp.redo()) {
		//Update the start and end node
		_astar.update(temp.pos_start, temp.pos_end);	
		// Reset the colours of the grid.
		temp.reset();
		//Runs the A* code
		_astar.run(temp);
		//Update the vertices colour
		temp.update(vertices);
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

