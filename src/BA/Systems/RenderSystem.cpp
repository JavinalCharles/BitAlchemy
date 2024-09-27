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
	const int32 ORDER = drawable->getSortOrder();

	auto& containerPair = m_drawables.try_emplace(DRAW_LAYER).first->second; // Get the pair of vectors

	if (IS_STATIC) {
		std::vector<std::shared_ptr<Drawable>>& array = containerPair.first;
		const std::size_t N = containerPair.first.size();

		if (N == 0 || ORDER <= array.front()->getSortOrder()) {
			array.insert(array.begin(), drawable);
		}
		else if (array.back()->getSortOrder() <= ORDER) {
			array.push_back(drawable);
		}
		else {
			std::size_t left = 0;
			std::size_t right = N - 1;

			while (left < right) {
				std::size_t mid = left + ((right - left) >> 1);

				if (array[left]->getSortOrder() < ORDER) {
					left = mid + 1;
				}
				else {
					right = mid;
				}
			}

			array.insert(array.begin() + left, drawable);
		}
	}
	else { // NOT IS_STATIC
		containerPair.second.push_back(drawable);
	}
}

void RenderSystem::remove(IDtype entityID) {
	// auto entity = m_entities->at(entityID);

}

void RenderSystem::update(float) {
	sort();
}

using tuple = std::tuple<const std::vector<std::shared_ptr<Drawable>>&, std::size_t&, const std::size_t&>;

void RenderSystem::draw(Window& window) {
	// Assuming the entities are sorted at this point.
	for (auto& [DRAW_LAYER, containers] : m_drawables) {
		window.useViewFromLayer(DRAW_LAYER);
		const FloatRect VIEWSPACE = window.getCurrentView().getViewSpace();

		if (containers.first.empty()) {
			if (containers.second.empty()) {
				// both containers are empty, proceed to next layer.
				continue;
			}
			// Second container is not empty, first is
			for (std::shared_ptr<Drawable>& drawable : containers.second) {
				if (VIEWSPACE.intersects(drawable->getGlobalBounds())) {
					drawable->draw(window);
				}
			}
		}
		else if (containers.second.empty()) { 
			// first is not empty
			debug << "Drawing first container." << std::endl;
			for (std::shared_ptr<Drawable>& drawable : containers.second) {
				if (VIEWSPACE.intersects(drawable->getGlobalBounds())) {
					drawable->draw(window);
				}
			}
		}
		else {
			const std::vector<std::shared_ptr<Drawable>>& KONS = containers.first;
			const std::vector<std::shared_ptr<Drawable>>& VARS = containers.second;

			const std::size_t N = KONS.size();
			const std::size_t O = VARS.size();

			std::size_t i = 0;
			std::size_t j = 0;
			while (i < N && j < O) {
				if (KONS.at(i)->getSortOrder() <= VARS.at(j)->getSortOrder()) {
					KONS.at(i++)->draw(window);
				}
				else {
					VARS.at(j++)->draw(window);
				}
			}
			auto [REM, k, SIZE] = (i < N) ? tuple(KONS, i, N) : tuple(VARS, j, O);
			for (; k < SIZE; ++k) {
				REM.at(k)->draw(window);
			}
		}
	}
}

void RenderSystem::sort() {

}


} // namespace ba