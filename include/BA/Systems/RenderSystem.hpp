#pragma once

#include <memory>
#include <map>
#include <queue>
#include <BA/Components/Drawable.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Types.hpp>
#include <BA/Window/Window.hpp>

namespace ba {

class EntityManager;

using DrawLayer = IDtype;

// const IDtype DEFAULT_RENDER_LAYER = 0;

class RenderSystem {
private:
	struct objectData {
		IDtype ID;
		std::weak_ptr<Drawable> ptr;

		objectData() = delete;
		objectData(IDtype id, const std::weak_ptr<Drawable>& newPtr = std::weak_ptr<Drawable>());
	};
	struct staticObjectData : public objectData {
		int32 order;

		staticObjectData() = delete;
		staticObjectData(IDtype id, int32 newOrder, const std::weak_ptr<Drawable>& newPtr = std::weak_ptr<Drawable>());
	};
public:
	explicit RenderSystem(EntityManager* entities);

	void add(std::vector<std::shared_ptr<Entity>> entities);
	void add(std::shared_ptr<Entity> entity);

	void remove(IDtype entityID);

	void update(float deltaTime);
	void draw(Window& window);

private:
	void sort();
private:
	// bool m_staticEntitiesAdded = false;
	// std::map<IDtype, ba::View> m_viewMap;

	std::map<DrawLayer, std::vector<staticObjectData>> m_statics;
	std::map<DrawLayer, std::vector<objectData>> m_moveables;

	// std::queue<std::shared_ptr<Drawable>> m_renderingQ;

	EntityManager* m_entities;
}; // class RenderSystem


} // namespace ba
