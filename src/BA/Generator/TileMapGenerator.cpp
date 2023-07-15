#include "BA/Generator/TileMapGenerator.hpp"

#include <iostream>

namespace ba {


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
	std::stringstream stream;
	stream << f.rdbuf();
	f.close();

	return stream.str();
}

} // namespace ba