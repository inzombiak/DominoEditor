#include "BTDebugDrawer.h"

void BTDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	m_vertices.push_back(glm::vec3(from.getX(), from.getY(), from.getZ()));
	m_vertices.push_back(glm::vec3(to.getX(), to.getY(), to.getZ()));

	m_colors.push_back(glm::vec3(0.f,0.f,0.f));// glm::vec3(color.getX(), color.getY(), color.getZ()));
}

void BTDebugDrawer::Draw(glm::mat4& mvp)
{
	if (m_vertices.size() == 0)
		return;
	//Set program
	glUseProgram(m_program);
	mvp = mvp * glm::mat4(1.0f);

	GLuint vertexBufferObject =0;

	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);

	GLuint colorBufferObject = 0;
	glGenBuffers(1, &colorBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferObject);
	glBufferData(GL_ARRAY_BUFFER, m_colors.size() * sizeof(glm::vec3), &m_colors[0], GL_STATIC_DRAW);

	//Enable attributes for use
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferObject);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);

	//Set draw mode
	//glPolygonMode(GL_FRONT, GL_LINE);

	//Pass in MVP
	GLuint MVPMatID = glGetUniformLocation(m_program, "MVP");
	glUniformMatrix4fv(MVPMatID, 1, GL_FALSE, &mvp[0][0]);

	//Draw
	glDrawArrays(GL_LINES, 0, m_vertices.size());

}