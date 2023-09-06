#include "BA/Generator/TileMapGenerator.hpp"

#include <iostream>

using std::filesystem::path;

using ba::generator::TileInfo;
using ba::generator::TileData;
using ba::IDtype;

namespace {
	std::vector<TileInfo> getLayerData(rapidxml::xml_node<>* layerNode);
} // anonymouse namespace

namespace ba {

namespace generator {

std::vector<std::shared_ptr<Entity>> parseMap(const std::string& tmxFileName, const Vector2f& SCALE, SharedContext* context) {
	std::string xml{getXMLdata(tmxFileName)};
	char c_data[xml.size()+1];
	strncpy(c_data, xml.c_str(), xml.size()+1);

	rapidxml::xml_document<> doc;
	doc.parse<0>(c_data);

	rapidxml::xml_node<>* tmxNode = doc.first_node("map");
	int tileWidth;
	int tileHeight;
	// int mapWidth;
	// int mapHeight;

	// GATHER MAP DATA
	if (tmxNode->first_attribute("tilewidth") == nullptr || tmxNode->first_attribute("tileheight") == nullptr || tmxNode->first_attribute("width") == nullptr || tmxNode->first_attribute("height") == nullptr) {
		throw std::invalid_argument("Error at file " + tmxFileName + " is missing some attributes.");
	}
	tileWidth = std::stoi(tmxNode->first_attribute("tilewidth")->value());
	tileHeight = std::stoi(tmxNode->first_attribute("tileheight")->value());
	// mapWidth = std::stoi(tmxNode->first_attribute("width")->value());
	// mapHeight = std::stoi(tmxNode->first_attribute("height")->value());

	// GENERATE TILESETS
	TileSet tilesets;
	rapidxml::xml_node<>* tilesetNode = tmxNode->first_node("tileset");
	// std::filesystem::path baseDir = context->resources->getBaseDirectory() / path("Textures");
	while(tilesetNode != nullptr) {
		if (tilesetNode->first_attribute("firstgid") == nullptr ||tilesetNode->first_attribute("source") == nullptr) {
			throw std::invalid_argument("Error at " + tmxFileName + ": Tileset is missing some attributes.");
		}
		int firstgid = std::stoi(tilesetNode->first_attribute("firstgid")->value());
		std::string tsx{tilesetNode->first_attribute("source")->value()};
		// path p = baseDir / path(tsx);
		TileSet ts = generator::generateTileSet(firstgid, tsx, context->resources);
		tilesets.merge(ts);

		tilesetNode = tilesetNode->next_sibling("tileset");
	}

	std::vector<std::shared_ptr<Entity>> r_entities;
	// GENERATE LAYERS
	rapidxml::xml_node<>* layerNode = tmxNode->first_node("layer");
	IDtype drawLayer = 1u;
	while(layerNode != nullptr) {
		if (layerNode->first_attribute("id") == nullptr || layerNode->first_attribute("width") == nullptr || layerNode->first_attribute("height") == nullptr || layerNode->first_attribute("name") == nullptr) {
			throw std::invalid_argument("Error at " + tmxFileName + "; A layer is missing some attributes.");
		}
		std::string layerName(layerNode->first_attribute("name")->value());

		std::vector<TileInfo> layerData = getLayerData(layerNode);

		const int LAYER = drawLayer++;

		for(std::size_t i = 0; i < layerData.size(); ++i) {
			const int GID = layerData.at(i).gid;
			const Vector2i POS = layerData.at(i).pos;
			if (GID == 0) {
				continue;
			}

			std::shared_ptr<Entity> e = std::make_shared<Entity>(context);
			e->setPosition({
				static_cast<float>(POS.x * tileWidth * SCALE.x),
				static_cast<float>(POS.y * tileHeight * SCALE.y)
			});
			e->setScale(SCALE);
			e->setStatic(true);

			auto e_sprite = e->addComponent<Sprite>();
			e_sprite->setTexture(tilesets.at(GID).textureID);
			e_sprite->setTextureRect(tilesets.at(GID).textureRect);
			e_sprite->setDrawLayer(LAYER);

			if (layerName.find("[COLLISION]") != std::string::npos) {
				auto collider = e->addComponent<BoxCollider>();
				collider->setSize({
					static_cast<float>(tilesets.at(GID).textureRect.w),
					static_cast<float>(tilesets.at(GID).textureRect.h)
				});
				collider->setLayer(1u);
			}

			r_entities.push_back(e);
		}
		// next layer
		layerNode = layerNode->next_sibling("layer");
	}
	return r_entities;
}

std::vector<std::pair<int, Vector2f>> getObjects(const std::string& tmxFileName) {
	std::vector<std::pair<int, Vector2f>> result;
	std::string xml{getXMLdata(tmxFileName)};
	char c_data[xml.size()+1];
	strncpy(c_data, xml.c_str(), xml.size()+1);

	rapidxml::xml_document<> doc;
	doc.parse<0>(c_data);
	rapidxml::xml_node<>* node = doc.first_node("map");
	if (node == nullptr) {
		return result;
	}
	rapidxml::xml_node<>* ogNode = node->first_node("objectgroup");
	while (ogNode != nullptr) {
		rapidxml::xml_node<>* objectNode = ogNode->first_node("object");
		while (objectNode != nullptr) {
			if (objectNode->first_attribute("id") == nullptr || objectNode->first_attribute("x") == nullptr || objectNode->first_attribute("y") == nullptr) {
				objectNode = objectNode->next_sibling("object");
				continue;
			}

			result.push_back(std::make_pair(
				std::atoi(objectNode->first_attribute("id")->value()),
				Vector2f {
					std::atof(objectNode->first_attribute("x")->value()),
					std::atof(objectNode->first_attribute("y")->value())
				}
			));

			objectNode = objectNode->next_sibling("object");
		}

		ogNode = ogNode->next_sibling("objectgroup");
	}

	return result;
}

TileSet generateTileSet(int firstgid, const std::string& tsxFile, ResourceManager* resources) {
	int gid = firstgid;
	int tilewidth;
	int tileheight;
	int tilecount;
	int columns;

	IDtype xmlID = resources->loadXML(tsxFile);

	// Open up the tsx file and get the data.
	std::string xml(resources->getString(xmlID));
	char data[xml.size()+1];
	strncpy(data, xml.c_str(), xml.size()+1);

	// Parse the data through rapidxml
	rapidxml::xml_document<> doc;
	doc.parse<0>(data);

	// Traverse the xml nodes and collect data
	rapidxml::xml_node<>* tsxNode = doc.first_node("tileset");

	if(tsxNode->first_attribute("tilewidth") == nullptr || tsxNode->first_attribute("tileheight") == nullptr || tsxNode->first_attribute("tilecount") == nullptr || tsxNode->first_attribute("columns") == nullptr) {
		// CHECK IF ALL ATTRIBUTES ARE ACCOUNTED FOR.
		// THROW ERROR IF NOT.
		throw std::invalid_argument("TSX file: " + tsxFile + " is missing some attributes.");
	}
	tilewidth = std::atoi(tsxNode->first_attribute("tilewidth")->value());
	tileheight = std::atoi(tsxNode->first_attribute("tileheight")->value());
	tilecount = std::atoi(tsxNode->first_attribute("tilecount")->value());
	columns = std::atoi(tsxNode->first_attribute("columns")->value());

	rapidxml::xml_node<>* imgNode = tsxNode->first_node("image");
	if (imgNode == nullptr) {
		throw std::invalid_argument("TSX file: " + tsxFile + " does not have an \"image\" node.");
	}

	if (imgNode->first_attribute("source") == 0) {
		// NO "source" ATTRIBUTE. THROW ANOTHER ERROR.
		throw std::invalid_argument("TSX file: " + tsxFile + " image node is missing it's \"source\" attribute");
	}

	IDtype textureID = resources->loadTexture(std::string(imgNode->first_attribute("source")->value()));


	TileSet r_tileset;

	int row = 0; // first row
	int col = 0; // first column
	// const int maxRow = tilecount / columns;



	while(gid - firstgid < tilecount) {
		TileData td;
		td.gid = gid;
		td.textureID = textureID;
		td.textureRect = {
			col * tilewidth,
			row * tileheight,
			tilewidth,
			tileheight
		};

		r_tileset.insert_or_assign(gid, td);

		++gid;
		++col;

		if (col == columns) {
			col = 0;
			++row;
		}
	}

	return r_tileset;
}

std::string getXMLdata(const std::string& filePath) {
	std::ifstream f(filePath);
	if(f.fail()) {
		throw std::invalid_argument("Error. Can't open file; \"" + filePath + "\" Either the file does not exist or is corrupted.");
	}
	std::stringstream stream;
	stream << f.rdbuf();
	f.close();

	return stream.str();
}

} // namespace generator

} // namespace ba

namespace {

std::vector<TileInfo> getLayerData(rapidxml::xml_node<>* layerNode) {
	rapidxml::xml_node<>* dataNode = layerNode->first_node("data");
	if (dataNode == nullptr) {
		throw std::invalid_argument("Error: Layer has no data");
	}
	const int W = std::stoi(layerNode->first_attribute("width")->value());
	// const int H = std::stoi(layerNode->first_attribute("height")->value());

	std::vector<TileInfo> r_tiles;

	if(dataNode->first_node("chunk") != nullptr) {
		for (rapidxml::xml_node<>* chunkNode = dataNode->first_node("chunk"); chunkNode != nullptr; chunkNode = chunkNode->next_sibling("chunk")) {

			const int X = std::atoi(chunkNode->first_attribute("x")->value());
			const int Y = std::atoi(chunkNode->first_attribute("y")->value());
			const int WIDTH = std::atoi(chunkNode->first_attribute("width")->value());
			// const int HEIGHT = std::atoi(chunkNode->first_attribute("height")->value());

			std::string csvGIDs(chunkNode->value());
			std::stringstream ss(csvGIDs);
			std::string token;
			int row = 0;
			int col = 0;

			while (std::getline(ss, token, ',')) {
				TileInfo tile;
				ba::IDtype gid = static_cast<IDtype>(std::atoi(token.c_str()));
				if (gid != 0) {
					r_tiles.push_back({TileInfo{
						gid,
						{col+X, row+Y}
					}});
				}
				++col;
				if (col == WIDTH) {
					col = 0;
					++row;
				}
			}
		}
	}
	else {
		std::string csvGIDs(dataNode->value());
		std::stringstream ss(csvGIDs);
		std::string token;
		int row = 0;
		int col = 0;
		while(std::getline(ss, token, ',')) {
			IDtype gid = static_cast<IDtype>(std::atoi(token.c_str()));
			if (gid != 0) {
				r_tiles.push_back(TileInfo{
					gid,
					{col, row}
				});
			}
			++col;
			if (col == W) {
				col = 0;
				++row;
			}
		}
	}

	return r_tiles;
}

} // anonymous namespace
