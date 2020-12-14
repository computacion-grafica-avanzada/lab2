#include "ColladaLoader.h"

AnimatedModelData* ColladaLoader::loadColladaModel(const char* colladaFile, int maxWeights) {
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError error = doc.LoadFile(colladaFile);
	tinyxml2::XMLElement* firstElem = doc.FirstChildElement();

	SkinLoader* skinLoader = new SkinLoader(firstElem->FirstChildElement("library_controllers"), maxWeights);
	SkinningData* skinningData = skinLoader->extractSkinData();

	SkeletonLoader* jointsLoader = new SkeletonLoader(firstElem->FirstChildElement("library_visual_scenes"), skinningData->jointOrder, skinningData->inverseBindTransforms);
	SkeletonData* jointsData = jointsLoader->extractBoneData();

	GeometryLoader* g = new GeometryLoader(firstElem->FirstChildElement("library_geometries"), skinningData->verticesSkinData);
	MeshData* meshData = g->extractModelData();

	return new AnimatedModelData(meshData, jointsData);
}

AnimationData* ColladaLoader::loadColladaAnimation(const char* colladaFile) {
	tinyxml2::XMLDocument doc;
	doc.LoadFile(colladaFile);
	tinyxml2::XMLElement* firstElem = doc.FirstChildElement();

	tinyxml2::XMLElement* animNode = firstElem->FirstChildElement("library_animations");
	tinyxml2::XMLElement* jointsNode = firstElem->FirstChildElement("library_visual_scenes");
	AnimationDataLoader* loader = new AnimationDataLoader(animNode, jointsNode);
	AnimationData* animData = loader->extractAnimation();
	return animData;
}