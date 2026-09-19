#ifndef COMPOSITE_OBJECT_CLASS_H
#define COMPOSITE_OBJECT_CLASS_H

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Primitive.h"

// A complex object made of several primitives (and/or other composite objects).
//
// Every part has its own transform *relative to this object*, and the object itself has a transform
// that moves/rotates/scales all of its parts together (hierarchical modelling):
//
//     world matrix of a part = parent's world matrix * this object's matrix * part's own matrix
//
// Example: a Pillar is built from a base, a shaft and a capital in local space around (0,0,0);
// placing the whole pillar in the cave is then just setting the Pillar's position.
class CompositeObject {
public:
	std::string name;
	glm::vec3 position;
	glm::vec3 rotation; // degrees
	glm::vec3 scale;

	explicit CompositeObject(std::string name = "");
	virtual ~CompositeObject() = default;

	// Adds a primitive; position / rotation / scale are relative to this object.
	// Returns the primitive so the caller can adjust it further (e.g. set its alpha).
	Primitive& AddPart(std::unique_ptr<Primitive> part,
		const glm::vec3& position,
		const glm::vec3& rotation = glm::vec3(0.0f),
		const glm::vec3& scale = glm::vec3(1.0f));

	// Adds a nested object (its transform is relative to this object).
	CompositeObject& AddChild(std::unique_ptr<CompositeObject> child);

	glm::mat4 GetModelMatrix() const;

	// Two passes, so translucent parts are drawn after everything opaque:
	// call DrawOpaque for the whole scene first, then DrawTransparent.
	void DrawOpaque(Shader& shader);
	void DrawTransparent(Shader& shader);

	int CountPrimitives() const; // including all nested children
	void Delete();               // frees the GPU meshes of all parts and children

private:
	std::vector<std::unique_ptr<Primitive>> parts;
	std::vector<std::unique_ptr<CompositeObject>> children;

	void DrawPass(Shader& shader, const glm::mat4& parentMatrix, bool transparentPass);
};

#endif
