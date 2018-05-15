#include "RenderGameLoop.h"
#include "OBJLoader.h"
static int myVertexArraySize = 36;

namespace {
	auto objPos = glm::vec3(1, 0, 0);

	double lastTime = glfwGetTime();
	float deltaTime = 0.016;

	float orbitAngle = 0.0f;
	float angle = 0.0f;

	auto quadRot = glm::vec3(0, 0, 0);
	float speed = 0.5;

	glm::mat4 TransformObject() {
		//Keyboard Input handled here
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			objPos.x += deltaTime * speed;
			//quadPos += glm::vec3(1 * speed, 0, 0);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			objPos.x -= deltaTime * speed;
			//quadPos -= glm::vec3(1 * speed, 0, 0);
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			objPos.y += deltaTime * speed;
			//quadPos += glm::vec3(0, 1 * speed, 0);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			objPos.y -= deltaTime * speed;
			//quadPos -= glm::vec3(0, 1 * speed, 0);
		}
		//if (glfwGetKey(window, GLFW_KEY_Q) || glfwGetKey(window, GLFW_KEY_E)) 
		//{
		if (glfwGetKey(window, GLFW_KEY_Q)) {
			//angle += deltaTime * 100.0f;
			angle += deltaTime * 100.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_E)) {
			//angle -= deltaTime * 100.0f;
			angle -= deltaTime * 200.0f;
		} 		

		glm::mat4 model;							// represents object, starts in world space & identity matrix | render quad
		
		model = glm::rotate(model, angle /*orbitAngle*/, vec3(1,1,0));
		/*																								//orbit
		model = glm::translate(model, objPos);		//moves quad
		model = glm::rotate(model, angle, vec3(0, 0, 1));
		*/

		//orbitAngle += deltaTime * 100.0f;

		return model;
	}

	//TASK ONE
	//rotate around orbit
	//spin independent of orbit

	//TASK TWO
	//create cubes

	//if (state == GLFW_PRESS)
	//	activate_airship();
}

//anonymous namespace - makes static

void BeginRenderingLoop() {

	GLuint vertexArrayID = 0;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	//Create and compile glsl program from shaders...
	GLuint programID = LoadShaders("BasicVertexShader.vertexshader", "BasicFragmentShader.fragmentshader");

	GLuint triangleID = LoadTriangle();
	GLuint quadID = LoadQuad(); //LoadCustomQuad();
	GLuint cubeID = LoadCube();

	//ObjLoader
	ObjLoader::ObjData data;
	ObjLoader::Load("cube.obj",data);

	do {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glm::mat4 model; // represents object, starts in world space & identity matrix | render quad
		//model = glm::translate(model, glm::vec3(1, 0, 0));

		//RenderTriangle(triangleID);
		//RenderQuad(quadID, TransformQuad(), programID);
		RenderCube(cubeID, TransformObject(),programID);
		
		//Update();
		//Render();
		glfwSwapBuffers(window);
		glfwPollEvents();

		//SET DELTATIME
		deltaTime = glfwGetTime() - lastTime;
		//lastTime = glfwGetTime() - deltaTime*glfwGetTime();

		//Update deltatime
		lastTime = glfwGetTime();
		//deltaTime = glfwGetTime();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

}

void RenderVertex(GLuint vertexBuffer, glm::mat4 model, GLuint programID/*shader program*/) {
	glUseProgram(programID);

	GLuint uniformModel = glGetUniformLocation(programID, "model");
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	//previous: only position, stride = 0 instead of 6*sizeof(float)
	/* ~ ~ ~ ~ ~ POSITION ATTRIBUTE ~ ~ ~ ~ ~*/
	glVertexAttribPointer(
		0,			//attribute layout
		3,			//Elements in array
		GL_FLOAT,	//Each element is of type float
		GL_FALSE,	//Normalized?
		0,			//Stride...
		(void*)0	//Array buffer offset...
	);

}

void RenderQuad(GLuint vertexBuffer, glm::mat4 model, GLuint programID/*shader program*/) {
	//glLoadIdentity();
	//glPushMatrix();
	//glTranslatef(2,0,0);

	RenderVertex(vertexBuffer, model, programID);

	//glPopMatrix();

	glDrawArrays(GL_TRIANGLES, 0, myVertexArraySize);
	glDisableVertexAttribArray(0);
}

void RenderTriangle(GLuint vertexBuffer, glm::mat4 model, GLuint programID/*shader program*/) {
	RenderVertex(vertexBuffer, model, programID); //ADDED programID

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}

void RenderCube(GLuint vertexBuffer, glm::mat4 model, GLuint programID/*shader program*/) {
	//glLoadIdentity();
	//glPushMatrix();
	//glTranslatef(2,0,0);

	RenderVertex(vertexBuffer, model, programID);

	//glPopMatrix();

	glDrawArrays(GL_TRIANGLES, 0, myVertexArraySize);
	glDisableVertexAttribArray(0);
}