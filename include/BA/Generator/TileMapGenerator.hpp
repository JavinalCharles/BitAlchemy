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
#include "BA/Entities/Entity.hpp"
#include "BA/ResourceManager.hpp"
#include "BA/Utilities/Rect.hpp"

#include <rapidxml/rapidxml.hpp>

namespace ba {

namespace generator {

struct TileData {
	IDtype 		gid;
	IDtype 		textureID;
	IntRect 	textureRect;
}; // TileData

using TileSet = std::unordered_map<IDtype, TileData>;

std::vector<std::shared_ptr<Entity>> parseMap(const std::string& tmxFileName, SharedContext* context);

TileSet generateTileSet(int firstgid, const std::string& tsxFile, ResourceManager* resources);

std::string getXMLdata(const std::string& fileName);

} // namespace generator

} // namespace ba