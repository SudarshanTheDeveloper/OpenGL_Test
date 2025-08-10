#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   g1_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 g1_Color;\n"
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





	//specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	
	// clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap the front and back buffers
	glfwSwapBuffers(window);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Take care of all the GlFW events
		glfwPollEvents();
	}

	//Delelte windows before ending the program
	glfwDestroyWindow(window); 

	//Terminating GLFW before ending the program
	glfwTerminate();
	return 0;
}