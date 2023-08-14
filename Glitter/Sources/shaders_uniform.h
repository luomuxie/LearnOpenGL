//create a class name shaders_uniform
#include <GLFW/glfw3.h>
class shaders_uniform {
	public:
		void shaders_uniformOpenGL();
	void initOpenGL();

	void setVertexData();

	void initShader();

	//create private variables
	GLFWwindow* window;
	unsigned int shaderProgram;
	unsigned int VBO, VAO, EBO;
};