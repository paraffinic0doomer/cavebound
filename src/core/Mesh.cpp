#include "Mesh.h"

#include <cstddef>

Mesh::Mesh(const MeshData& data) {
	indexCount = static_cast<GLsizei>(data.indices.size());

	// The VAO must be bound before the EBO is created, because the EBO binding is stored inside the VAO.
	vao.Bind();

	vbo = std::make_unique<VBO>((GLfloat*)data.vertices.data(), data.vertices.size() * sizeof(Vertex));
	ebo = std::make_unique<EBO>((GLuint*)data.indices.data(), data.indices.size() * sizeof(GLuint));

	vao.LinkAttrib(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
	vao.LinkAttrib(*vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));

	vao.Unbind();
	vbo->Unbind();
	ebo->Unbind();
}

void Mesh::Draw() {
	vao.Bind();
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	vao.Unbind();
}

void Mesh::Delete() {
	vao.Delete();
	vbo->Delete();
	ebo->Delete();
}
