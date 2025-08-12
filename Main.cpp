#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//Vertex Shader Source Code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader Source Code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor =vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";



int main() 
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using.
	//In this case , we are using OpenGL 3.3 Core Profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE Pryyofile
	//So that means we only have the morden functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Tell GLFW we are not using the old functions
	//Vertical coordinate
	GLfloat vertices[] = {
		// positions
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,// bottom left
		 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,// bottom right
		 0.0f,  0.5f * float(sqrt(3)) / 2/3, 0.0f,// top 
	};
	// create a GLFWwidow object of 800x800 pixels, naming it "OPenGL_New"
	GLFWwindow* window = glfwCreateWindow(800, 800, "OPenGL_New", NULL, NULL);

	// Check if the window was created successfully
	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window to the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL function pointers
	gladLoadGL();

	//specify the viewport of OpenGL in the window
	//In the case the viewport goes from x = 0, y = 0; to x = 800; y = 800
	glViewport(0, 0, 800, 800);


	// Create Vertex Shader Objecrt and get reference to it
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach the source code to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//Compile the vertex shader into machine code
	glCompileShader(vertexShader);

	//Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach the source code to the fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Complile the Vertex shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();

	//Attach the vertex shader and fragment shader to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Wrap-up/Link all the shaders together into the shader program
	glLinkProgram(shaderProgram);

	//Delete the now useless vertex and fragment shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	//Create Vertex Array Object (VAO) and Vertex Buffer Object (VBO)
	GLuint VAO, VBO;

	//Generate a Vertex Array Object and a Vertex Buffer Object with 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	//Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	//Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Introduce the data to the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the vertex attributes so that OpenGL knows how to interpret the data in the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Enable the vertex attribute at index 0
	glEnableVertexAttribArray(0);

	//Bind both the VBO and VAO to 0 to unbind them
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the VBO

	glBindVertexArray(0); // Unbind the VAO

	// Clear the color buffer






	//specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	
	// clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap the front and back buffers
	glfwSwapBuffers(window);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		//Bind the VAO so that OpenGL knows which VBO to use
		glBindVertexArray(VAO);
		//Draw the triangle using the vertices in the VBO
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		//Take care of all the GlFW events
		glfwPollEvents();
	}

	//Delete the VAO, VBO and Shader Program
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//Delelte windows before ending the program
	glfwDestroyWindow(window); 

	//Terminating GLFW before ending the program
	glfwTerminate();
	return 0;
}