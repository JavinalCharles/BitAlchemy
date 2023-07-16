#include "BA/Generator/TileMapGenerator.hpp"

#include <iostream>

using std::filesystem::path;

namespace {
	std::vector<std::vector<int>> getLayerData(rapidxml::xml_node<>* layerNode);
} // anonymouse namespace

namespace ba {

namespace generator {

std::vector<std::shared_ptr<Entity>> parseMap(const std::string& tmxFileName, SharedContext* context) {
	std::string xml{getXMLdata(tmxFileName)};
	char c_data[xml.size()+1];
	strncpy(c_data, xml.c_str(), xml.size()+1);

	rapidxml::xml_document<> doc;
	doc.parse<0>(c_data);

	rapidxml::xml_node<>* tmxNode = doc.first_node("map");
	int tileWidth;
	int tileHeight;
	int mapWidth;
	int mapHeight;

	// GATHER MAP DATA
	if (tmxNode->first_attribute("tilewidth") == nullptr || tmxNode->first_attribute("tileheight") == nullptr || tmxNode->first_attribute("width") == nullptr || tmxNode->first_attribute("height") == nullptr) {
		throw std::invalid_argument("Error at file " + tmxFileName + " is missing some attributes.");
	}
	tileWidth = std::stoi(tmxNode->first_attribute("tilewidth")->value());
	tileHeight = std::stoi(tmxNode->first_attribute("tileheight")->value());
	mapWidth = std::stoi(tmxNode->first_attribute("width")->value());
	mapHeight = std::stoi(tmxNode->first_attribute("height")->value());

	// GENERATE TILESETS
	TileSet tilesets;
	rapidxml::xml_node<>* tilesetNode = tmxNode->first_node("tileset");
	std::filesystem::path baseDir = context->resources->getBaseDirectory() / path("Textures");
	while(tilesetNode != nullptr) {
		if (tilesetNode->first_attribute("firstgid") == nullptr ||tilesetNode->first_attribute("source") == nullptr) {
			throw std::invalid_argument("Error at " + tmxFileName + ": Tileset is missing some attributes.");
		}
		int firstgid = std::stoi(tilesetNode->first_attribute("firstgid")->value());
		std::string tsx{tilesetNode->first_attribute("source")->value()};
		path p = baseDir / path(tsx);
		TileSet ts = generator::generateTileSet(firstgid, p.string(), context->resources);
		tilesets.merge(ts);

		tilesetNode = tilesetNode->next_sibling("tileset");
	}
	std::clog << "Generated a total of " << tilesets.size() << " tiles." << std::endl;

	std::vector<std::shared_ptr<Entity>> r_entities;
	// GENERATE LAYERS
	rapidxml::xml_node<>* layerNode = tmxNode->first_node("layer");
	while(layerNode != nullptr) {
		if (layerNode->first_attribute("id") == nullptr || layerNode->first_attribute("width") == nullptr || layerNode->first_attribute("height") == nullptr || layerNode->first_attribute("name") == nullptr) {
			throw std::invalid_argument("Error at " + tmxFileName + "; A layer is missing some attributes.");
		}
		std::vector<std::vector<int>> layerData = getLayerData(layerNode);
		
		std::clog << "Translating data." << std::endl; 
		const int LAYER = std::stoi(layerNode->first_attribute("id")->value());

		for(std::size_t r = 0; r < layerData.size(); ++r) {
			for(std::size_t c = 0; c < layerData.at(r).size(); ++c) {
				const int GID = layerData.at(r).at(c);
				if (GID == 0) {
					continue;
				}
				std::shared_ptr<Entity> e = std::make_shared<Entity>(context);
				e->setPosition({c * tileWidth, r * tileHeight});
				auto e_sprite = e->addComponent<Sprite>();
				
				e_sprite->setTexture(tilesets.at(GID).textureID);
				e_sprite->setTextureRect(tilesets.at(GID).textureRect);
				e_sprite->setDrawLayer(LAYER);

				r_entities.push_back(e);
			}
		}
		// next layer
		layerNode = layerNode->next_sibling("layer");
	}
	return r_entities;
}


TileSet generateTileSet(int firstgid, const std::string& tsxFile, ResourceManager* resources) {
	int gid = firstgid;
	int tilewidth;
	int tileheight;
	int tilecount;
	int columns;

	// Open up the tsx file and get the data.
	std::string xml(getXMLdata(tsxFile));
	std::clog << "Recieved data: \n" << xml << std::endl;
	char data[xml.size()+1];
	strncpy(data, xml.c_str(), xml.size()+1);

	// Parse the data through rapidxml
	rapidxml::xml_document<> doc;
	doc.parse<0>(data);

	// Traverse the xml nodes and collect data
	std::clog << "Procuring tileset node." << std::endl;
	rapidxml::xml_node<>* tsxNode = doc.first_node("tileset");
	
	std::clog << "Checking tileset attributes." << std::endl;
	if(tsxNode->first_attribute("tilewidth") == nullptr || tsxNode->first_attribute("tileheight") == nullptr || tsxNode->first_attribute("tilecount") == nullptr || tsxNode->first_attribute("columns") == nullptr) {
		// CHECK IF ALL ATTRIBUTES ARE ACCOUNTED FOR.
		// THROW ERROR IF NOT.
		throw std::invalid_argument("TSX file: " + tsxFile + " is missing some attributes.");
	}
	std::clog << "Procuring tileset attributes." << std::endl;
	tilewidth = std::atoi(tsxNode->first_attribute("tilewidth")->value());
	tileheight = std::atoi(tsxNode->first_attribute("tileheight")->value());
	tilecount = std::atoi(tsxNode->first_attribute("tilecount")->value());
	columns = std::atoi(tsxNode->first_attribute("columns")->value());

	std::clog << "Procuring image node. " << std::endl;
	rapidxml::xml_node<>* imgNode = tsxNode->first_node("image");
	if (imgNode == 0) {
		throw std::invalid_argument("TSX file: " + tsxFile + " does not have an \"image\" node.");
	}

	std::clog << "Checking image attribute." << std::endl;
	if (imgNode->first_attribute("source") == 0) {
		// NO "source" ATTRIBUTE. THROW ANOTHER ERROR.
		throw std::invalid_argument("TSX file: " + tsxFile + " image node is missing it's \"source\" attribute");
	}
	
	std::clog << "Procuring image attribute." << std::endl;
	IDtype textureID = resources->loadTexture(std::string(imgNode->first_attribute("source")->value()));


	std::clog << "Generating tileset." << std::endl;
	TileSet r_tileset;

	int row = 0; // first row
	int col = 0; // first column
	const int maxRow = tilecount / columns;

	while (row < maxRow) {
		while(col < columns) {
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
		}
		col = 0;
		++row;
	}
	
	return r_tileset;
}

std::string getXMLdata(const std::string& filePath) {
	std::clog << "Reading tsx file: " << filePath << std::endl;
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

std::vector<std::vector<int>> getLayerData(rapidxml::xml_node<>* layerNode) {
	std::clog << "Generating layer data." << std::endl;
	rapidxml::xml_node<>* dataNode = layerNode->first_node("data");
	if (dataNode == nullptr) {
		throw std::invalid_argument("Error: Layer has no data");
	}
	const int W = std::stoi(layerNode->first_attribute("width")->value());
	const int H = std::stoi(layerNode->first_attribute("height")->value());

	std::vector<std::vector<int>> r;

	std::string data{dataNode->value()};
	std::replace(data.begin(), data.end(), ',', ' ');
	std::erase(data, '\n');
	std::erase(data, '\r');
	std::stringstream stream(data);
	int row = 0;
	int col = 0;

	while(stream.good()) {
		while(row < H) {
			std::vector<int> numCol;
			while(col < W) {
				int found;
				stream >> found;
				numCol.push_back(found);
				std::clog << found << ' ';
				++col;
			}
			r.push_back(numCol);
			col = 0;
			++row;
			std::clog << std::endl;
		}
	}
	std::clog << "Generated layer data." << std::endl;
	return r;
}

} // anonymous namespace