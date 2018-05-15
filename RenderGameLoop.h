#pragma once
#include "Init.h"

	void BeginRenderingLoop();

	void RenderVertex(GLuint vertexBuffer, glm::mat4 model, GLuint programID /*shader program*/);
	void RenderQuad(GLuint vertexBuffer, glm::mat4 model, GLuint programID /*shader program*/);
	void RenderTriangle(GLuint vertexBuffer, glm::mat4 model, GLuint programID /*shader program*/);
	void RenderCube(GLuint vertexBuffer, glm::mat4 model, GLuint programID /*shader*/);