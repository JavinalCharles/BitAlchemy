#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>

#include "BA/Components/Sprite.hpp"
#include "BA/Components/Colliders/BoxCollider.hpp"
#include "BA/Entities/Entity.hpp"
#include "BA/ResourceManager.hpp"
#include "BA/Utilities/Vector2.hpp"
#include "BA/Utilities/Rect.hpp"
#include "BA/Types.hpp"

namespace ba {

namespace generator {

struct TileData {
	IDtype 		gid;
	IDtype 		textureID;
	IntRect 	textureRect;
}; // struct TileData

struct TileInfo {
	IDtype		gid;
	Vector2i	pos;
}; // struct TileInfo

// using TileSet = std::unordered_map<IDtype, TileData>;

class TileMapGenerator {
public:
	TileMapGenerator();
	TileMapGenerator(SharedContext* context);
	TileMapGenerator(TileMapGenerator&) = delete;

	TileMapGenerator& operator=(TileMapGenerator&) = delete;

public: // METHODS
	void setContext(SharedContext* res);

	std::vector<std::shared_ptr<Entity>> generate(const std::string& tmxFile, const Vector2f& textureScale = {1.f, 1.f}, SharedContext* context = nullptr);

private: // HELPERS
	void generateTilesets(long firstgid, const std::string& source);
	const tinyxml2::XMLDocument* getXML(const std::string& source);
	IDtype loadXML(const std::string& source);

	std::vector<TileInfo> getLayerInfo(tinyxml2::XMLElement* dataNode, const Vector2i& LAYER_AREA) const;

	// void freeUsedTextures(); TODO:
private:
	std::unordered_map<IDtype, TileData> m_tilesets;
	// Vector2f m_scale{0.f, 0.f};
	// const std::string& tmxFile;

	std::vector<std::shared_ptr<Entity>> m_createdTileMaps;

	std::set<IDtype> m_textureIDs;
	std::set<IDtype> m_xmlIDs;
	std::unordered_map<std::string, IDtype> m_sourceIdMap;
	std::unordered_map<std::string, IDtype> m_texSrcIdMap;
	ba::SharedContext* mp_context = nullptr;
	ba::ResourceManager* mp_resources = nullptr;
};



// std::vector<std::shared_ptr<Entity>> parseMap(const std::string& tmxFileName, const Vector2f& SCALE, SharedContext* const context);

// std::vector<std::pair<int, Vector2f>> getObjects(const std::string& tmxFileName, ResourceManager* const resources);

// TileSet generateTileSet(int firstgid, const std::string& tsxFile, ResourceManager* const resources);

} // namespace generator

} // namespace ba
