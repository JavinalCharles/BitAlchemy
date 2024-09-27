#include "BA/Generator/TileMapGenerator.hpp"

using std::filesystem::path;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

using ba::generator::TileInfo;
using ba::generator::TileData;
using ba::IDtype;

using ba::Resources::TextureManager;
using ba::Resources::XMLManager;

// namespace {
// 	std::vector<TileInfo> getLayerData(rapidxml::xml_node<>* layerNode);
// } // anonymouse namespace

namespace ba {

namespace generator {

#define NULL_PTR_EXCEPTION std::runtime_error("TileMapGenerator requires a reference to a valid ResourceManager before operation.")
#define INVALID_TMX(tmxfile) std::invalid_argument((std::string(tmxfile) + " is invalid or corrupted").c_str())
#define INVALID_TSX(tsxfile) std::invalid_argument((std::string(tsxfile) + " is invalid or corrupted").c_str())


TileMapGenerator::TileMapGenerator() = default;

TileMapGenerator::TileMapGenerator(SharedContext* context) :
	mp_context(context)
{

}

void TileMapGenerator::setContext(SharedContext* context) {
	mp_context = context;
}



std::vector<std::shared_ptr<Entity>> TileMapGenerator::generate(const std::string& tmxFilename, const Vector2f& SCALE, SharedContext* context) {
	if (context != nullptr) {
		mp_context = context;
	}
	if (mp_context->warehouse == nullptr) {
		throw NULL_PTR_EXCEPTION;
	}

	XMLDocument& xmlDoc = getXML(tmxFilename);
	const XMLElement* node = xmlDoc.FirstChildElement("map");
	if (node == nullptr) {
		throw INVALID_TMX(tmxFilename);
	}
	const char* wAttr = node->Attribute("width");
	const char* hAttr = node->Attribute("height");
	const char* twAttr = node->Attribute("tilewidth");
	const char* thAttr = node->Attribute("tileheight");
	// Checks if any of above attributes are nullptr
	if ((wAttr && hAttr && twAttr && thAttr) == false) {
		throw INVALID_TMX(tmxFilename);
	}

	[[maybe_unused]] const Vector2i MAP_SIZE = {
		std::atoi(wAttr), std::atoi(hAttr)
	};
	const Vector2i TILE_SIZE = {
		std::atoi(twAttr), std::atoi(thAttr)
	};

	for(XMLElement* tilesetNode = const_cast<XMLElement*>(node->FirstChildElement("tileset")); tilesetNode != nullptr; tilesetNode = tilesetNode->NextSiblingElement("tileset")) {
		const char* firstgidAttr = tilesetNode->Attribute("firstgid");
		const char* sourceAttr = tilesetNode->Attribute("source");
		if ((firstgidAttr && sourceAttr) == false) {
			throw INVALID_TMX(tmxFilename);
		}
		generateTilesets(std::atol(firstgidAttr), sourceAttr);
	}

	std::vector<std::shared_ptr<Entity>> tileMapEntities;

	// IDtype drawLayer = 0;
	for(XMLElement* layerNode = const_cast<XMLElement*>(node->FirstChildElement("layer")); layerNode != nullptr; layerNode = layerNode->NextSiblingElement("layer")) {
		const char* W = layerNode->Attribute("width");
		const char* H = layerNode->Attribute("height");
		const char* LID = layerNode->Attribute("id");
		XMLElement* dataNode = layerNode->FirstChildElement("data");
		if ((W && H && LID && dataNode) == false) {
			throw INVALID_TMX(tmxFilename);
		}
		const Vector2i& LAYER_AREA{std::atoi(W), std::atoi(H)};
		const IDtype LAYER_ID = std::atoi(LID);

		std::vector<TileInfo> layerInfo = getLayerInfo(dataNode, LAYER_AREA);

		for (const TileInfo& INFO : layerInfo) {
			const TileData& TILEDATA = m_tilesets[INFO.gid];

			std::shared_ptr<Entity> tileEntity = std::make_shared<Entity>(mp_context);
			tileEntity->setPosition({
				static_cast<float>(INFO.pos.x * TILE_SIZE.x * SCALE.x),
				static_cast<float>(INFO.pos.y * TILE_SIZE.y * SCALE.y)
			});
			tileEntity->setScale(SCALE);
			tileEntity->setStatic(true);

			auto sprite = tileEntity->addComponent<Sprite>();

			sprite->setTexture(TILEDATA.textureID, TILEDATA.textureRect);
			sprite->setDrawLayer(LAYER_ID);
			// sprite->setSortOrder(tileEntity->getPosition().y);
			
			tileMapEntities.push_back(tileEntity);
		}
	}
	return tileMapEntities;
}

void TileMapGenerator::generateTilesets(long firstgid, const std::string& source) {
	XMLDocument& tsxDoc = getXML(source);
	const XMLElement* tsElement = tsxDoc.FirstChildElement("tileset");
	if (tsElement == nullptr) {
		throw INVALID_TSX(source);
	}
	const char* columnAttr = tsElement->Attribute("columns");
	const char* twAttr = tsElement->Attribute("tilewidth");
	const char* thAttr = tsElement->Attribute("tileheight");
	const char* tcAttr = tsElement->Attribute("tilecount");
	if ((columnAttr && twAttr && thAttr && tcAttr) == false) {
		throw INVALID_TSX(source);
	}

	const XMLElement* imgNode = tsElement->FirstChildElement("image");
	if (imgNode == nullptr) {
		throw INVALID_TSX(source);
	}
	const char* srcAttr = imgNode->Attribute("source");
	const char* imgWAttr = imgNode->Attribute("width");
	const char* imgHAttr = imgNode->Attribute("height");
	if ((srcAttr && imgHAttr && imgWAttr) == false) {
		debug << "Tileset file have some missing values." << std::endl;
		throw INVALID_TSX(source);
	}
	TextureManager& textures = mp_context->warehouse->getManager<TextureManager>();
		// debug << "TileMapGenerator querying PathFinder for: " << srcAttr << std::endl;
	std::optional<path> src = textures.findFile(path(srcAttr));

	if (!src.has_value()) {
		// debug << "TileMapGenerator is unable to find tileset image src: " << srcAttr << std::endl;
		throw INVALID_TSX(source);
	}
	// debug << "PathFinder returns: " << src.value().c_str() << std::endl;;

	const IDtype TEXTURE_ID = textures.create(src.value().string());

	m_textureIDs.insert(TEXTURE_ID);

	const int COLUMNS = std::atoi(columnAttr);
	const Vector2i TILE_AREA(std::atoi(twAttr), std::atoi(thAttr));
	const IDtype TILECOUNT = static_cast<IDtype>(std::atol(tcAttr));

	const Vector2i TEXTURE_AREA(std::atoi(imgHAttr), std::atoi(imgHAttr));

	IDtype currentGid = static_cast<IDtype>(firstgid);
	int row = 0;
	int col = 0;

	while((currentGid - firstgid) < TILECOUNT) {
		const TileData TD(
			currentGid, TEXTURE_ID, 
			IntRect(
				{col * TILE_AREA.x, row * TILE_AREA.y},
				TILE_AREA
			)
		);
		m_tilesets.insert_or_assign(currentGid++, TD);
		++col;
		if (col >= COLUMNS) {
			++row;
			col = 0;
		}
	}
}

XMLDocument& TileMapGenerator::getXML(const std::string& xmlFile) {
	const IDtype k_docID = m_sourceIdMap.contains(xmlFile) ? m_sourceIdMap.at(xmlFile) : loadXML(xmlFile);

	return mp_context->warehouse->getManager<XMLManager>().at(k_docID);
}

IDtype TileMapGenerator::loadXML(const std::string& xmlFile) {
	XMLManager& xmlManager = mp_context->warehouse->getManager<XMLManager>();

	std::optional<path> xmlpath = xmlManager.findFile(path(xmlFile));
	if (!xmlpath.has_value()) {
		debug << "Unable to load xml file: " << xmlFile.c_str() << std::endl;
		throw INVALID_TMX(xmlFile);
	}

	const IDtype id = xmlManager.create();
	xmlManager.at(id).LoadFile(xmlpath.value().c_str());

	m_sourceIdMap.insert_or_assign(xmlFile, id);
	m_xmlIDs.insert(id);
	return id;
}

std::vector<TileInfo> TileMapGenerator::getLayerInfo(XMLElement* dataNode, const Vector2i& LAYER_AREA) const {
	std::stringstream ss;
	ss << dataNode->GetText();

	std::string token;
	int row = 0;
	int col = 0;

	std::vector<TileInfo> tiles;

	while (std::getline(ss, token, ',')) {
		const IDtype GID = static_cast<IDtype>(std::stol(token));
		if (GID != 0) {
			tiles.push_back(TileInfo{
				GID,
				Vector2i{col, row}
			});
			// debug << "Tile Info created: GID " << tiles.back().gid << " {" << tiles.back().pos.x << ", " << tiles.back().pos.y << "}" << std::endl;
		}
		++col;
		if (col >= LAYER_AREA.y) {
			++row;
			col = 0;
		}
	}
	return tiles;
}

} // namespace generator

} // namespace ba