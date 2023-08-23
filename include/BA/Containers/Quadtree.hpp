#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include <BA/Components/Component.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Utilities/Rect.hpp>
#include <BA/Types.hpp>

namespace ba {

template <typename T>
class Quadtree {
public:
	Quadtree();
	Quadtree(std::size_t maxObjects, int maxLevels, int level = 0, FloatRect bounds = {0, 0, 3200, 3200}, Quadtree* parent = nullptr);

	void insert(std::shared_ptr<T> object);
	void remove(std::shared_ptr<T> object);
	// bool remove(IDtype ID);

	void clear();

	std::vector<std::shared_ptr<T>> search(const FloatRect& area) const;

	const FloatRect& getBounds() const;

	void drawBounds(Window& window);
private:
	void split();
	int getChildIndexForObject(const FloatRect& objectBounds);
	void search(const FloatRect& area, std::vector<std::shared_ptr<T>>& returnList) const;

	static const int thisTree = -1;
	static const int childNE = 0;
	static const int childNW = 1;
	static const int childSW = 2;
	static const int childSE = 3;

	std::size_t m_maxObjects;
	int m_maxLevels;
	int m_level;

	FloatRect m_bounds;

	Quadtree<T>* m_parent;

	std::unique_ptr<Quadtree<T>> m_children[4];

	std::unordered_map<IDtype, std::shared_ptr<T>> m_objects;
}; // class Quadtree

template <typename T>
void Quadtree<T>::drawBounds(Window& window) {
	window.drawRect(m_bounds, Color::Red);

	if (m_children[0] == nullptr) {
		return;
	}

	for (std::size_t i = 0; i < 4; ++i) {
		m_children[i]->drawBounds(window);
	}
}

template <typename T>
Quadtree<T>::Quadtree() :
	Quadtree(5, 5)
{
	static_assert(std::is_base_of<Component, T>::value, "Assertion Error: T must be a sub-type of Component.");
}

template <typename T>
Quadtree<T>::Quadtree(std::size_t maxObjects, int maxLevels, int level, FloatRect bounds, Quadtree* parent) :
	m_maxObjects(maxObjects),
	m_maxLevels(maxLevels),
	m_level(level),
	m_bounds(bounds),
	m_parent(parent)
{
	static_assert(std::is_base_of<Component, T>::value, "Assertion Error: T must be a sub-type of Component.");
}


template <typename T>
void Quadtree<T>::insert(std::shared_ptr<T> object) {
	FloatRect bounds = object->getGlobalBounds();
	std::optional<FloatRect> intersection = m_bounds.intersects(bounds);


	// Terminate function if the given object does not intersect with the bounds of this quadtree
	if (!intersection.has_value()) {
		return;
	}

	if (m_children[0] != nullptr) {
		int index = getChildIndexForObject(bounds);
		if (index != thisTree) {
			m_children[index]->insert(object);
			return;
		}
		else {
			m_objects.insert_or_assign(object->getOwner()->ID, object);
		}
	}
	else {
		m_objects.insert_or_assign(object->getOwner()->ID, object);

		if(m_objects.size() > m_maxObjects && m_level < m_maxLevels && m_children[0] == nullptr) {
			this->split();
			auto objIterator = m_objects.begin();
			while(objIterator != m_objects.end()) {
				auto obj = *objIterator;
				int index = this->getChildIndexForObject(obj.second->getGlobalBounds());

				if (index != thisTree) {
					m_children[index]->insert(obj.second);
					objIterator = m_objects.erase(objIterator);
				}
				else {
					// no need to insert since the object is already in this tree.
					++objIterator;
				}
			}
		}
	}
}

template <typename T>
void Quadtree<T>::remove(std::shared_ptr<T> object) {
	unsigned ID = object->getOwner()->ID;
	if(m_objects.contains(ID)) {
		m_objects.erase(ID);
	}
	else {
		FloatRect bounds = object->getGlobalBounds();
		int i = this->getChildIndexForObject(bounds);
		if(m_children[i] != nullptr) {
			m_children[i]->remove(object);
		}
	}
}

template <typename T>
void Quadtree<T>::clear() {
	for (int i = 0; i < 4; ++i) {
		if (m_children[i] != nullptr) {
			m_children[i]->clear();
			m_children[i] = nullptr;
		}
	}

	m_objects.clear();
}

template <typename T>
std::vector<std::shared_ptr<T>> Quadtree<T>::search(const FloatRect& area) const {
	std::vector<std::shared_ptr<T>> res;

	search(area, res);

	return res;
}

template <typename T>
void Quadtree<T>::search(const FloatRect& area, std::vector<std::shared_ptr<T>>& returnList) const{
	for (auto& [key, object] : m_objects) {
		std::optional<FloatRect> intersection(object->getGlobalBounds().intersects(area));
		if (intersection.has_value()) {
			returnList.emplace_back(object);
		}
	}

	if(m_children[0] == nullptr)
		return;

	for(int i = 0; i < 4; ++i) {
		std::optional<FloatRect> intersection = m_children[i]->getBounds().intersects(area);
		if (intersection.has_value()) {
			m_children[i]->search(area, returnList);
		}
	}
}

template <typename T>
const FloatRect& Quadtree<T>::getBounds() const {
	return m_bounds;
}

template <typename T>
int Quadtree<T>::getChildIndexForObject(const FloatRect& objectBounds) {
	int index = thisTree;

	double verticalDividingLine = m_bounds.l + m_bounds.w * 0.5f;
	double horizontalDividingLine = m_bounds.t + m_bounds.h * 0.5f;

	bool north = objectBounds.t < horizontalDividingLine && (objectBounds.h + objectBounds.t < horizontalDividingLine);
    bool south = objectBounds.t > horizontalDividingLine;
    bool west = objectBounds.l < verticalDividingLine && (objectBounds.l + objectBounds.w < verticalDividingLine);
    bool east = objectBounds.l > verticalDividingLine;

	if(east)
    {
        if(north)
        {
            index = childNE;
        }
        else if(south)
        {
            index = childSE;
        }
    }
    else if(west)
    {
        if(north)
        {
            index = childNW;
        }
        else if(south)
        {
            index = childSW;
        }
    }

    return index;
}

template <typename T>
void Quadtree<T>::split() {
	const Vector2f size{
		m_bounds.w / 2,
		m_bounds.h / 2
	};

	m_children[childNE] = std::make_unique<Quadtree<T>>(m_maxObjects, m_maxLevels, m_level + 1, FloatRect({m_bounds.l + size.x, m_bounds.t}, size), this);
	m_children[childNW] = std::make_unique<Quadtree<T>>(m_maxObjects, m_maxLevels, m_level + 1, FloatRect({m_bounds.l, m_bounds.t}, size), this);
	m_children[childSW] = std::make_unique<Quadtree<T>>(m_maxObjects, m_maxLevels, m_level + 1, FloatRect({m_bounds.l, m_bounds.t + size.y}, size), this);
	m_children[childSE] = std::make_unique<Quadtree<T>>(m_maxObjects, m_maxLevels, m_level + 1, FloatRect({m_bounds.l + size.x, m_bounds.t + size.y}, size), this);
}

} // namespace ba
