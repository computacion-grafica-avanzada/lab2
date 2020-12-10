#include "ColladaLoader.h"

AnimatedModelData* ColladaLoader::loadColladaModel(const char* colladaFile, int maxWeights) {
	tinyxml2::XMLDocument doc;
	doc.LoadFile(colladaFile);

	SkinLoader* skinLoader = new SkinLoader(doc.FirstChildElement("library_controllers"), maxWeights);
	SkinningData* skinningData = skinLoader->extractSkinData();

	SkeletonLoader* jointsLoader = new SkeletonLoader(doc.FirstChildElement("library_visual_scenes"), skinningData->jointOrder);
	SkeletonData* jointsData = jointsLoader->extractBoneData();

	GeometryLoader* g = new GeometryLoader(doc.FirstChildElement("library_geometries"), skinningData->verticesSkinData);
	MeshData* meshData = g->extractModelData();

	return new AnimatedModelData(meshData, jointsData);
}

AnimationData* ColladaLoader::loadColladaAnimation(const char* colladaFile) {
	tinyxml2::XMLDocument doc;
	doc.LoadFile(colladaFile);

	tinyxml2::XMLElement* animNode = doc.FirstChildElement("library_animations");
	tinyxml2::XMLElement* jointsNode = doc.FirstChildElement("library_visual_scenes");
	AnimationDataLoader* loader = new AnimationDataLoader(animNode, jointsNode);
	AnimationData* animData = loader->extractAnimation();
	return animData;
}