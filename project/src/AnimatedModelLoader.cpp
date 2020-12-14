#include "AnimatedModelLoader.h"

/* Loads up the diffuse texture for the model. */
Texture* AnimatedModelLoader::loadTexture(const char* textureFile)
{
	Texture* diffuseTexture = new Texture(textureFile);
	return diffuseTexture;
}

/* Constructs the joint-hierarchy skeleton from the data extracted from the collada file. */
Joint* AnimatedModelLoader::createJoints(JointData* data)
{
	Joint* joint = new Joint(data->index, data->nameId, data->bindLocalTransform, data->inverseBindTransform);
	for (JointData* child : data->children)
	{
		joint->addChild(createJoints(child));
	}
	return joint;
}

/* Creates an AnimatedEntity from the data in an entity file. It loads up
the collada model data, stores the extracted data in a VAO, sets up the
joint heirarchy, and loads up the entity's texture.*/
AnimatedRenderable* AnimatedModelLoader::loadEntity(const char* modelFile, const char* textureFile)
{
	AnimatedModelData* entityData = ColladaLoader::loadColladaModel(modelFile, 3);
	MeshData* data = entityData->getMeshData();
	AnimatedMesh* model = new AnimatedMesh(data->vertices, data->textureCoords, data->normals, data->jointIds, data->vertexWeights, data->indices);
	Texture* texture = loadTexture(textureFile);
	SkeletonData* skeletonData = entityData->getJointsData();
	Joint* headJoint = createJoints(skeletonData->headJoint);
	return new AnimatedRenderable(model, texture, 1, headJoint, skeletonData->jointCount);
}