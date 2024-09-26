#include <BA/Systems/RenderSystem.hpp>
#include <BA/Systems/EntityManager.hpp>

#include <iostream>

namespace ba {

RenderSystem::objectData::objectData(IDtype id, const std::weak_ptr<Drawable>& newPtr) :
	ID(id),
	ptr(newPtr)
{

}

RenderSystem::staticObjectData::staticObjectData(IDtype id, int32 newOrder, const std::weak_ptr<Drawable>& newPtr) :
	objectData(id, newPtr),
	order(newOrder)
{

}

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

	if (IS_STATIC) {
		auto result = m_statics.try_emplace(DRAW_LAYER);

		std::vector<staticObjectData>& v = result.first->second;
		const std::size_t N = v.size();

		if (N == 0 || ORDER <+ v[0].order) {
			v.emplace(v.begin() ,ENTITY_ID, ORDER, std::weak_ptr<Drawable>(drawable));
		}
		else if (v[N-1].order <= ORDER ) {
			v.emplace_back(ENTITY_ID, ORDER, std::weak_ptr<Drawable>(drawable));
		}
		else {
			// Using binary search to find the first index
			// where v[i].order >= ORDER.
			std::size_t lo = 0u;
			std::size_t hi = v.size() - 1;

			while (lo < hi) {
				std::size_t mi = lo + ((hi - lo) >> 1);
				if (v[mi].order < ORDER) {
					lo = mi + 1;
				}
				else {
					hi = mi;
				}
			}
			v.emplace(v.begin() + lo, ENTITY_ID, ORDER, std::weak_ptr<Drawable>(drawable));
		}
	}
	else {
		// Moveables are sorted every frame anyway.
		auto result = m_moveables.try_emplace(DRAW_LAYER);
		result.first->second.emplace_back(ENTITY_ID, std::weak_ptr<Drawable>(drawable));;
	}
}

void RenderSystem::remove(IDtype entityID) {
	auto entity = m_entities->at(entityID);
	if (entity == nullptr || entity->getDrawable() == nullptr) {
		for (auto& [LAYER_ID, v] : m_moveables) {
			for (auto iter = v.begin(); iter != v.end(); ++iter) {
				if (iter->ID == entityID) {
					v.erase(iter);
					return;
				}
			}
		}
		for (auto& [LAYER_ID, v] : m_statics) {
			for(auto iter = v.begin(); iter != v.end(); ++iter) {
				if (iter->ID == entityID) {
					v.erase(iter);
					return;
				}
			}
		}
		return;
	}
	std::shared_ptr<Drawable> drawable = entity->getDrawable();

	const bool IS_STATIC = entity->isStatic();
	const IDtype DRAW_LAYER = drawable->getDrawLayer();

	if (IS_STATIC && m_statics.contains(DRAW_LAYER)) {
		std::vector<staticObjectData>& v = m_statics.at(DRAW_LAYER);
		for (auto iter = v.begin(); iter != v.end(); ++iter) {
			if (iter->ID == entityID) {
				v.erase(iter);
				return;
			}
		}
	}
	else if (m_moveables.contains(DRAW_LAYER)) [[likely]] {
		std::vector<objectData>& v = m_moveables.at(DRAW_LAYER);
		for (auto iter = v.begin(); iter != v.end(); ++iter) {
			if (iter->ID == entityID) {
				v.erase(iter);
				return;
			}
		}
	}
	// Reaching this point means that while the entity does
	// exists, and does contain a drawable, that entity is
	// most like not added to this RenderSystem, or that
	// it was added but later on erased already.
}

void RenderSystem::update(float) {
	sort();
}

void RenderSystem::draw(Window& window) {
	// Assuming the entities are sorted at this point.
	auto kons = m_statics.begin();
	auto vars = m_moveables.begin();

	while (kons != m_statics.end() || vars != m_moveables.end()) {
		if (kons->first == vars->first) { // same keys exists.
			window.useViewFromLayer(kons->first);
			const FloatRect VIEWSPACE = window.getCurrentView().getViewSpace();

			std::queue<std::shared_ptr<Drawable>> konsQueue;
			std::queue<std::shared_ptr<Drawable>> varsQueue;

			for (const staticObjectData& data : kons->second) {
				if (!data.ptr.expired()) {
					std::shared_ptr<Drawable> d = data.ptr.lock();
					if (VIEWSPACE.intersects(d->getGlobalBounds())) {
						konsQueue.push(d);
					}
				}
			}
			for (const objectData& data : vars->second) {
				if (!data.ptr.expired()) {
					std::shared_ptr<Drawable> d = data.ptr.lock();
					if (VIEWSPACE.intersects(d->getGlobalBounds())) {
						varsQueue.push(d);
					}
				}
			}
			while (!konsQueue.empty() && !varsQueue.empty()) {
				if (konsQueue.front()->getSortOrder() <= varsQueue.front()->getSortOrder()) {
					konsQueue.front()->draw(window);
					konsQueue.pop();
				}
				else {
					varsQueue.front()->draw(window);
					varsQueue.pop();
				}
			}
			std::queue<std::shared_ptr<Drawable>>& remainingQ = konsQueue.empty() ? varsQueue : konsQueue;
			while (!remainingQ.empty()) {
				remainingQ.front()->draw(window);
				remainingQ.pop();
			}
			kons++;
			vars++;
		}
		else if (kons->first < vars->first) { // statics turn
			window.useViewFromLayer(kons->first);
			const FloatRect VIEWSPACE = window.getCurrentView().getViewSpace();
			for (const staticObjectData& data : kons->second) {
				if (!data.ptr.expired()) {
					std::shared_ptr<Drawable> d = data.ptr.lock();
					if (VIEWSPACE.intersects(d->getGlobalBounds())) {
						d->draw(window);
					}
				}
			}
			kons++;
		}
		else {
			window.useViewFromLayer(vars->first);
			const FloatRect VIEWSPACE = window.getCurrentView().getViewSpace();
			for (const objectData& data : vars->second) {
				if (!data.ptr.expired()) {
					std::shared_ptr<Drawable> d = data.ptr.lock();
					if (VIEWSPACE.intersects(d->getGlobalBounds())) {
						d->draw(window);
					}
				}
			}
			vars++;
		}
	}
}

void RenderSystem::sort() {
	
}


} // namespace ba