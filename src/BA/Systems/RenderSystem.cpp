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
	// const IDtype ENTITY_ID = entity->ID;
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

				if (array[mid]->getSortOrder() < ORDER) {
					left = mid + 1;
				}
				else {
					right = mid;
				}
			}

			array.insert(array.begin() + left, drawable);
		}
		// std::cout << "Added 1 static entity." << std::endl;
	}
	else { // NOT IS_STATIC
		containerPair.second.push_back(drawable);
		// std::cout << "Added one moveable entity." << std::endl;
	}
}

void RenderSystem::remove(IDtype entityID) {
	std::shared_ptr<Entity> entity;
	try {
		entity = m_entities->at(entityID);
	}
	catch (const std::out_of_range& e) {
		return;
	}
	

	std::shared_ptr<Drawable> drawable = entity->getDrawable();
	if (drawable == nullptr) {
		// Nothing to do here.
		return;
	}

	const bool IS_STATIC = entity->isStatic();
	const DrawLayer LAYER = drawable->getDrawLayer();
	if (m_drawables.contains(LAYER)) {
		std::vector<std::shared_ptr<Drawable>>& vec = IS_STATIC ? m_drawables.at(LAYER).first : m_drawables.at(LAYER).second;

		auto iter = std::find(vec.begin(), vec.end(), drawable);

		if (iter != vec.end()) {
			vec.erase(iter);
		}
	}
}

void RenderSystem::update(float) {
	sort();
}

using tuple = std::tuple<const std::vector<std::shared_ptr<Drawable>>&, std::size_t&, const std::size_t&>;

void RenderSystem::draw(Window& window) {
	// Assuming the entities are sorted at this point.
	for (auto& [DRAW_LAYER, containers] : m_drawables) {
		window.useViewFromLayer(DRAW_LAYER);

		if (containers.first.empty()) {
			if (containers.second.empty()) {
				continue;
			}
			for (std::shared_ptr<Drawable>& drawable : containers.second) {
				drawable->draw(window);
			}
		}
		else if (containers.second.empty()) { 
			for (std::shared_ptr<Drawable>& drawable : containers.first) {
				drawable->draw(window);
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
	for (auto& v : m_drawables) {
		sort(v.second.second);;
	}
}

void RenderSystem::sort(std::vector<std::shared_ptr<Drawable>>& drawables) {
	const std::size_t N = drawables.size();
	if (N < 2) {
		return;
	}
	constexpr auto compare = [](const std::shared_ptr<Drawable>& A, const std::shared_ptr<Drawable>& B) -> bool {
		return A->getSortOrder() < B->getSortOrder();
	};

	auto begin = drawables.begin();
	auto end = drawables.end();

	auto unsorted_start = std::is_sorted_until(begin, end, compare);

	if (unsorted_start == end) {
		// vector is properly sorted. No need to do anything.
		return;
	}
	// else
	// unsorted_start's proper order is most definitely going to be
	// found at some index left of it [begin, unsorted_start), which
	// is the sorted part of the vector.
	// Use binary search to find the proper place for the object w/in
	// unsorted_start, then start sorting from there.
	auto left = begin;
	auto right = unsorted_start - 1;

	// a const value to reduce number of pointer dereferences.
	const ba::int32 ORDER = (*unsorted_start)->getSortOrder();
	while (left < right) {
		auto mid = left + (right - left) / 2;

		if ((*mid)->getSortOrder() < ORDER) {
			left = mid + 1;
		}
		else {
			right = mid;
		}
	}

	std::sort(left, end, compare);
}


} // namespace ba