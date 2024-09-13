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

	const bool IS_STATIC = entity->isStatic();
	const IDtype DRAW_LAYER = drawable->getDrawLayer();
	const IDtype ENTITY_ID = entity->ID;

	if (!m_drawables.contains(DRAW_LAYER)) {
		m_drawables.emplace(DRAW_LAYER,
			std::make_pair(std::vector<IDtype>(), std::vector<IDtype>())
		);
		m_drawables.try_emplace(DRAW_LAYER);
	}

	if (IS_STATIC) {
		m_drawables.at(DRAW_LAYER).first.push_back(ENTITY_ID);
		if (!m_staticEntitiesAdded) {
			m_staticEntitiesAdded = true;
		}
	}
	else {
		m_drawables.at(DRAW_LAYER).second.push_back((ENTITY_ID));
	}
}

void RenderSystem::remove(IDtype entityID) {
	auto entity = m_entities->at(entityID);
	if (entity == nullptr) {
		// Unlikely to happen.
		// Entity somehow already deleted.
		// Erase via brute-force approach.
		for (auto& [LAYER_ID, P] : m_drawables) {
			std::erase(P.first, entityID);
			std::erase(P.second, entityID);
		}
		return;
	}
	auto drawable = entity->getDrawable();
	if (drawable == nullptr) {
		// Entity not deleted, but has no drwable component.
		// Unlikely to be found here. Just return.
		return;
	}

	const IDtype DRAW_LAYER = drawable->getDrawLayer();
	if (entity->isStatic()) {
		std::erase(m_drawables.at(DRAW_LAYER).first, entityID);
	}
	else {
		std::erase(m_drawables.at(DRAW_LAYER).second, entityID);
	}
}

void RenderSystem::update(float) {
	sort();
}

void RenderSystem::draw(Window& window) {
	// debug << "RenderSystem::draw()" << std::endl;
	for(const auto& [DRAW_LAYER, P] : m_drawables) {
		// debug << '\t' << DRAW_LAYER << '\n';
		window.useViewFromLayer(DRAW_LAYER);

		auto i = P.first.begin();
		auto j = P.second.begin();
		auto i_drawable = i != P.first.end() ? m_entities->at(*i)->getDrawable() : nullptr;
		auto j_drawable = j != P.second.end() ? m_entities->at(*j)->getDrawable() : nullptr;

		while(i != P.first.end() && j != P.second.end()) {
			if (i_drawable->getSortOrder() <= j_drawable->getSortOrder()) {
				i_drawable->draw(window);
				++i;
				i_drawable = i != P.first.end() ? m_entities->at(*i)->getDrawable() : nullptr;
			}
			else {
				j_drawable->draw(window);
				++j;
				j_drawable = j != P.second.end() ? m_entities->at(*j)->getDrawable() : nullptr;
			}
		}
		while (i != P.first.end()) {
			i_drawable->draw(window);
			++i;
			i_drawable = i != P.first.end() ? m_entities->at(*i)->getDrawable() : nullptr;
		}
		while (j != P.second.end()) {
			j_drawable->draw(window);
				++j;
				j_drawable = j != P.second.end() ? m_entities->at(*j)->getDrawable() : nullptr;
		}
	}
}

void RenderSystem::sort() {
	EntityManager* entities = m_entities;
	auto layerSort = [entities](IDtype a, IDtype b) -> bool {
		return entities->at(a)->getDrawable()->getSortOrder() < entities->at(b)->getDrawable()->getSortOrder();
	};

	for (auto& [LAYER, P] : m_drawables) {
		if (m_staticEntitiesAdded && !std::is_sorted(P.first.begin(), P.second.end(), layerSort)) {
			std::sort(P.first.begin(), P.first.end(), layerSort);
		}

		if (!std::is_sorted(P.second.begin(), P.second.end(), layerSort)) {
			std::sort(P.second.begin(), P.second.end(), layerSort);
		}
	}
	if (m_staticEntitiesAdded) 
		m_staticEntitiesAdded = false;
}


} // namespace ba