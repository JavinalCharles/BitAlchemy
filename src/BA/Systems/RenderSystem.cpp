#include <BA/Systems/RenderSystem.hpp>
#include <BA/Systems/EntityManager.hpp>

#include <iostream>

namespace ba {

RenderSystem::RenderSystem(EntityManager* entities) :
	m_entities(entities)
{

}

void RenderSystem::add(std::vector<std::shared_ptr<Entity>> entities) {
	for(auto& e : entities) {
		this->add(e);
	}
}

void RenderSystem::add(std::shared_ptr<Entity> entity) {
	auto drawable = entity->getDrawable();
	if (drawable == nullptr)
		return;
	DrawLayer layer = drawable->getDrawLayer();
	if(m_drawables.contains(layer)) {
		std::clog << "Adding Entity #" << entity->ID << " to drawable layer: " << layer << std::endl;
		m_drawables.at(layer).push_back(entity->ID);
	}
	else {
		std::clog << "Adding a new drawable layer: " << layer << std::endl;
		std::clog << "Adding Entity #" << entity->ID << " to drawable layer: " << layer << std::endl;
		m_drawables.insert_or_assign(layer, std::vector<IDtype>{entity->ID});
	}

}

void RenderSystem::remove(IDtype entityID) {
	for(auto& v: m_drawables) {
		std::erase(v.second, entityID);
	}
}

void RenderSystem::update(float) {
	sort();
}

void RenderSystem::draw(Window& window) {
	FloatRect viewSpace = window.getViewSpace();

	for(auto& v : m_drawables) {
		for(auto& id : v.second) {
			auto drawable = m_entities->at(id)->getDrawable();
			// std::clog << "Drawing: #" << id << std::endl;
			if(viewSpace.intersects(drawable->getGlobalBounds()).has_value()) {
				drawable->draw(window);
			}
		}
	}
}

void RenderSystem::sort() {
	EntityManager* entities = m_entities;
	auto layerSort = [entities](IDtype a, IDtype b) -> bool {
		return entities->at(a)->getDrawable()->getSortOrder() < entities->at(b)->getDrawable()->getSortOrder();
	};

	for(auto& layer : m_drawables) {
		if(!std::is_sorted(layer.second.begin(), layer.second.end(), layerSort)) {
			std::sort(layer.second.begin(), layer.second.end(), layerSort);
		}
	}
}


} // namespace ba