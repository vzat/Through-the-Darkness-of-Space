// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

#define GLSL(src) "#version 150 core\n" #src

class Triangle
{
	private:
		float vertices[6];
		GLuint vertexShader, fragmentShader, unicolor;
	public:
		Triangle(float v1, float v2, float v3, float v4, float v5, float v6)
		{
			vertices[0] = v1;
			vertices[1] = v2;
			vertices[2] = v3;
			vertices[3] = v4;
			vertices[4] = v5;
			vertices[5] = v6;
		}
		Triangle()
		{
			vertices[0] =  0.0f;
			vertices[1] =  0.5f;
			vertices[2] =  0.5f;
			vertices[3] = -0.5f;
			vertices[4] = -0.5f;
			vertices[5] = -0.5f;
		}
		void update()
		{
			// Put the vertices in the buffer
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			// Vertex Shader
			const char* vertexSource = GLSL(
				in vec2 position;

				void main()
				{
					gl_Position = vec4(position, 0.0, 1.0);
				}
			);

			// Compile Vertex Shader
			//GLuint 
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertexSource, NULL);
			glCompileShader(vertexShader);

			// Fragment Shader
			const char* fragmentSource = GLSL(
				uniform vec3 triangleColor;

				out vec4 outColor;

				void main()
				{
					outColor = vec4(triangleColor, 1.0);
				}
			);

			// Compile Fragment Source
			//GLuint 
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
			glCompileShader(fragmentShader);

			// Combining the Vertex and Fragment Shader
			GLuint shaderProgram = glCreateProgram();
			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram, fragmentShader);
			glBindFragDataLocation(shaderProgram, 0, "outColor");
			glLinkProgram(shaderProgram);
			glUseProgram(shaderProgram);

			// Link Vertex Data and Attributes
			GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
			glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(posAttrib);

			// Get the color location
			//GLint 
			unicolor = glGetUniformLocation(shaderProgram, "triangleColor");
		}
		void render()
		{
			glUniform3f(unicolor, 0.0f, 0.0f, 1.0f);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		void render2()
		{
			glUniform3f(unicolor, 1.0f, 0.0f, 0.0f);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
};

int main(int argc, char * argv[]) {

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr); // Add glfwGetPrimaryMonitor() to the 4th parameter for fullscreen

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
	fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

	// Create Vertex Array Object(VBO)
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object(VBO)
	GLuint vbo;
	glGenBuffers(1, &vbo);

	// Make the data active
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Triangle Test
	/*
	float vertices[] = {
		0.0f,  0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};*/

	// Copy the data
	/*
	GL_STATIC_DRAW - The vertex data will be uploaded once and drawn many times (e.g. the world).
	GL_DYNAMIC_DRAW - The vertex data will be changed from time to time, but drawn many times more than that.
	GL_STREAM_DRAW - The vertex data will change almost every time it's drawn (e.g. user interface).
	*/
	/*
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertex Shader
	const char* vertexSource = GLSL(
		in vec2 position;
		
		void main()
		{
			gl_Position = vec4(position, 0.0, 1.0);
		}	
	);

	// Compile Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Fragment Shader
	const char* fragmentSource = GLSL(
		uniform vec3 triangleColor;
		
		out vec4 outColor;
		
		void main()
		{
			outColor = vec4(triangleColor, 1.0);
		}
	);

	// Compile Fragment Source
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	*/


	// Check if it works
	/*
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
		printf("%s", "Works?");
	else
		printf("%s", "NO?");
	*/

	// Print error message
	/*
	char buffer[512];
	glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
	printf("%s", buffer);
	*/


	/*
	// Combining the Vertex and Fragment Shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Link Vertex Data and Attributes
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	// Get the color location
	GLint unicolor = glGetUniformLocation(shaderProgram, "triangleColor");
	*/

	Triangle tri;
	Triangle tri1(-1.0f, -0.5f, -0.5f, -0.5f, -0.75f, 0.5f);
	
	//tri.render();

    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
		// Close if the ESC key is pressed
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        // Background Fill Color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Change the colour
		//glUniform3f(unicolor, 0, 0, 1.0f);

		// Draw triangle
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		tri.update();
		tri.render();
		tri1.update();
		tri.render2();

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
		glfwPollEvents();
    }

	glfwTerminate();
    return EXIT_SUCCESS;
}