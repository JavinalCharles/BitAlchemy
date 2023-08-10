#pragma once

#include <memory>
#include <map>
#include <set>
#include <BA/Components/Drawable.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Types.hpp>
#include <BA/Window/Window.hpp>

namespace ba {

class EntityManager;

using DrawLayer = unsigned;

class RenderSystem {
public:
	explicit RenderSystem(EntityManager* entities);

	void add(std::vector<std::shared_ptr<Entity>> entities);
	void add(std::shared_ptr<Entity> entity);

	void remove(IDtype entityID);

	void update(float deltaTime);
	void draw(Window& window);

private:
	void sort();

	std::map<DrawLayer, std::vector<IDtype>> m_drawables;

	EntityManager* m_entities;
}; // class RenderSystem


} // namespace ba
