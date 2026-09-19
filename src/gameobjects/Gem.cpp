#include "Gem.h"

#include "primitives/Cone.h"
#include "primitives/Cylinder.h"

namespace {
glm::vec3 ColorOf(GemType type) {
	switch (type) {
	case GemType::Ruby:     return glm::vec3(0.92f, 0.10f, 0.20f);
	case GemType::Emerald:  return glm::vec3(0.10f, 0.82f, 0.36f);
	case GemType::Sapphire: return glm::vec3(0.16f, 0.38f, 0.98f);
	case GemType::Amethyst: return glm::vec3(0.68f, 0.26f, 0.92f);
	}
	return glm::vec3(1.0f);
}

const char* NameOf(GemType type) {
	switch (type) {
	case GemType::Ruby:     return "Ruby";
	case GemType::Emerald:  return "Emerald";
	case GemType::Sapphire: return "Sapphire";
	case GemType::Amethyst: return "Amethyst";
	}
	return "Gem";
}

const float HOVER = 0.25f;    // height of the lowest tip above the floor
const float WIDTH = 0.70f;
const float PAVILION = 0.50f; // height of the lower cone
const float GIRDLE = 0.10f;   // height of the middle band
const float CROWN = 0.30f;    // height of the upper cone
}

Gem::Gem(GemType type) : GameObject(NameOf(type)), type(type) {
	const glm::vec3 color = ColorOf(type);

	// Pavilion: a cone turned upside down, its tip is the lowest point of the gem
	AddPart(std::make_unique<Cone>(0.5f, 1.0f, 6, color),
		glm::vec3(0.0f, HOVER + PAVILION / 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 180.0f), glm::vec3(WIDTH, PAVILION, WIDTH));

	// Girdle: a thin, slightly brighter band where the two cones meet
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 6, color * 1.2f),
		glm::vec3(0.0f, HOVER + PAVILION + GIRDLE / 2.0f, 0.0f), glm::vec3(0.0f), glm::vec3(WIDTH, GIRDLE, WIDTH));

	// Crown: a short cone on top, tip up
	AddPart(std::make_unique<Cone>(0.5f, 1.0f, 6, color * 1.1f),
		glm::vec3(0.0f, HOVER + PAVILION + GIRDLE + CROWN / 2.0f, 0.0f), glm::vec3(0.0f), glm::vec3(WIDTH, CROWN, WIDTH));
}
