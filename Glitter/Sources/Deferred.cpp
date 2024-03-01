#include "Deferred.h"
#include "model.h"



void Deferred::RenderModel(Shader &shader, Model& modelObj)
{
	//render the model by the objPos
	shader.use();
	//set the view and projection matrix
	shader.setMat4("projection", GetProjectionMatrix());
	shader.setMat4("view", GetViewMatrix());
	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, objectPositions[i]);
		model = glm::scale(model, glm::vec3(0.25f));
		shader.setMat4("model", model);
		modelObj.Draw(shader);
	}
}

void Deferred::Run()
{
	scale = 1;
	screenWidth = 800 * scale;
	screenHeight = 600 * scale;
	InitWindow();

	//load a model
	//create a model object
	Model ourModel("resources/objects/nanosuit/nanosuit.obj");
	Shader defferedGSahder = CreateShader("", "");


	//main loop
	//check the window is not closed
	while (!glfwWindowShouldClose(window))
	{
		//input
		//process the input
		InputProcess(window);

		//render
		//set the clear color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//clear the color buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//render the model
		RenderModel(defferedGSahder, ourModel);


		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}
	


}
