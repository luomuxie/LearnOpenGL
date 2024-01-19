#include "InputUtil.h"

void InputUtility::mouseCallback(GLFWwindow* window, double xposIn, double yposIn, bool& firstMouse, float& lastX, float& lastY, Camera& camera)
{
	if (firstMouse)
	{
		lastX = xposIn;
		lastY = yposIn;
		firstMouse = false;
	}

	float xoffset = xposIn - lastX;
	float yoffset = lastY - yposIn; // reversed since y-coordinates go from bottom to top

	lastX = xposIn;
	lastY = yposIn;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void InputUtility::processInput(GLFWwindow* window, Camera& camera, float deltaTime)
{
    //check if the escape ,a ,s ,d ,w is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        //close the window
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}
