#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <vector>
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// One vertex as it is stored in the VBO: position (location 0) + color (location 1)
struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
};

// CPU-side geometry. Every primitive builds one of these; Mesh uploads it to the GPU.
struct MeshData {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices; // 3 per triangle, counter-clockwise when seen from outside
};

// GPU-side geometry: owns a VAO, a VBO and an EBO.
class Mesh {
public:
	Mesh(const MeshData& data);

	void Draw();
	void Delete();

private:
	VAO vao;
	std::unique_ptr<VBO> vbo;
	std::unique_ptr<EBO> ebo;
	GLsizei indexCount;
};

#endif
