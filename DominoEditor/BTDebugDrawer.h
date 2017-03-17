#pragma once
#define GLEW_STATICW
#include "GL\glew.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <vector>

#include "LinearMath\btIDebugDraw.h"
#include "btBulletDynamicsCommon.h"

class BTDebugDrawer : public btIDebugDraw
{
public:
	void SetProgram(GLuint program)
	{
		m_program = program;


	}
	void Clear()
	{

		m_vertices.clear();
		m_colors.clear();
	}
	void Draw(glm::mat4& mvp);
	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
	virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color){};

	virtual void reportErrorWarning(const char* warningString){};

	virtual void draw3dText(const btVector3& location, const char* textString){};

	virtual void setDebugMode(int debugMode)
	{
		m_debugMode = debugMode;
	};

	virtual int getDebugMode() const
	{
		return m_debugMode;
	};

private:
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_colors;

	int m_debugMode = DBG_DrawWireframe | DBG_DrawConstraints | DBG_DrawConstraintLimits;

	GLuint m_program;

};

