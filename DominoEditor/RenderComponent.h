#pragma once
#define GLEW_STATIC
#include <gl\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\quaternion.hpp>

#include "IComponent.h"

#include <vector>

class RenderComponent : public IComponent
{
	
public:
	RenderComponent(unsigned int id)
	{
		m_id = id;
	}
	//Draws buffer
	void Draw(glm::mat4 vp);
	//Update vertex buffer
	void SetVertices(std::vector<glm::vec3> vertices);
	//Update color buffer
	void SetColor(std::vector<glm::vec3> color);
	//Set draw type
	void SetDrawPrimitive(GLuint type);
	//Set OpenGL program
	void SetProgram(GLuint program);
	void Update();
	void SetOwner(Object*);
	const char* GetName() override
	{
		return COMPONENT_NAME;
	}
private:
	const static char* COMPONENT_NAME;

	//Number of vertices to be drawn
	int m_numVertices;
	//Program ID
	GLuint m_program;
	//Buffer IDs
	GLuint m_vertexBufferObject = 0;
	GLuint m_colorBufferObject = 0;
	//Draw type
	GLuint m_drawPrimitive;
};
