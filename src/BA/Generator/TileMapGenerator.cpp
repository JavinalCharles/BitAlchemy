#include "BA/Generator/TileMapGenerator.hpp"

namespace ba {


TileSet generateTileSet(int firstgid, const std::string& tsxFile, ResourceManager* resources) {
	int gid = firstgid;
	int tilewidth;
	int tileheight;
	int tilecount;
	int columns;

	// Open up the tsx file and get the data.
	std::string xml(getXMLdata(tsxFile));
	char data[xml.size()+1];
	strncpy(data, xml.c_str(), xml.size()+1);

	// Parse the data through rapidxml
	rapidxml::xml_document<> doc;
	doc.parse<0>(data);

	// Traverse the xml nodes and collect data
	rapidxml::xml_node<>* tsxNode = doc.first_node("tileset");
	if(tsxNode->first_attribute("tilewidth") == 0 || tsxNode->first_attribute("tileheight") == 0 || tsxNode->first_attribute("tilecount") == 0 || tsxNode->first_attribute("columns") == 0) {
		// CHECK IF ALL ATTRIBUTES ARE ACCOUNTED FOR.
		// THROW ERROR IF NOT.
		throw std::invalid_argument("TSX file: " + tsxFile + " is missing some attributes.");
	}

	tilewidth = std::atoi(tsxNode->first_attribute("tilewidth")->value());
	tileheight = std::atoi(tsxNode->first_attribute("tileheight")->value());
	tilecount = std::atoi(tsxNode->first_attribute("tilecount")->value());
	columns = std::atoi(tsxNode->first_attribute("columns")->value());

	rapidxml::xml_node<>* imgNode = tsxNode->first_node("image");
	if (imgNode == 0) {
		throw std::invalid_argument("TSX file: " + tsxFile + " does not have an \"image\" node.");
	}

	
}

std::string getXMLdata(const std::string& filePath) {
	std::ifstream f(filePath);
	std::stringstream stream;
	stream << f.rdbuf();
	f.close();

	return stream.str();
}

} // namespace ba