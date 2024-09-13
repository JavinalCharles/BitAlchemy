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

using DrawLayer = IDtype;

// const IDtype DEFAULT_RENDER_LAYER = 0;

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

	void sortStaticEntities();
private:
	bool m_staticEntitiesAdded = false;
	std::map<IDtype, ba::View> m_viewMap;

	// For each layer in m_drawables:
	// .first = static entities
	// .second = non-static entities
	std::map<DrawLayer, std::pair<std::vector<IDtype>,std::vector<IDtype>>> m_drawables;

	EntityManager* m_entities;
}; // class RenderSystem


} // namespace ba
