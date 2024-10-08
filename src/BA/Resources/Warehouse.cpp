#include <BA/Resources/Warehouse.hpp>

using ba::Resources::Warehouse;

Warehouse::Warehouse() = default;

Warehouse::~Warehouse() {
	clear();
}

void Warehouse::clear() {
	for (auto& [type, manager] : m_managers) {
		manager.reset();
	}
	m_managers.clear();
}