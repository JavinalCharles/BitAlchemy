#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>
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

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

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

using TileSet = std::unordered_map<IDtype, TileData>;

std::vector<std::shared_ptr<Entity>> parseMap(const std::string& tmxFileName, const Vector2f& SCALE, SharedContext* context);

TileSet generateTileSet(int firstgid, const std::string& tsxFile, ResourceManager* resources);

std::string getXMLdata(const std::string& fileName);

} // namespace generator

} // namespace ba