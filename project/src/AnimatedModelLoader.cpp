#include "AnimatedModelLoader.h"

/* Loads up the diffuse texture for the model. */
Texture AnimatedModelLoader::loadTexture(const char* textureFile)
{
	Texture diffuseTexture = Texture.newTexture(textureFile).anisotropic().create();
	return diffuseTexture;
}

/* Constructs the joint-hierarchy skeleton from the data extracted from the collada file. */
Joint AnimatedModelLoader::createJoints(JointData* data)
{
	Joint* joint = new Joint(data->index, data->nameId, data->bindLocalTransform);
	for (JointData* child : data->children)
	{
		joint->addChild(createJoints(child));
	}
	return joint;
}

/* Stores the mesh data in a VAO. */
Vao AnimatedModelLoader::createVao(MeshData* data)
{
	Vao vao = Vao.create();
	vao.bind();
	vao.createIndexBuffer(data->indices);
	vao.createAttribute(0, data->vertices, 3);
	vao.createAttribute(1, data->textureCoords, 2);
	vao.createAttribute(2, data->normals, 3);
	vao.createIntAttribute(3, data->jointIds, 3);
	vao.createAttribute(4, data->vertexWeights, 3);
	vao.unbind();
	return vao;
}

/* Creates an AnimatedEntity from the data in an entity file. It loads up
the collada model data, stores the extracted data in a VAO, sets up the
joint heirarchy, and loads up the entity's texture.*/
AnimationRenderer* AnimatedModelLoader::loadEntity(const char* modelFile, const char* textureFile)
{
	AnimatedModelData* entityData = ColladaLoader::loadColladaModel(modelFile, 3);
	Vao model = createVao(entityData->getMeshData());
	Texture texture = loadTexture(textureFile);
	SkeletonData* skeletonData = entityData->getJointsData();
	Joint headJoint = createJoints(skeletonData->headJoint);
	return new AnimationRenderer(model, texture, headJoint, skeletonData->jointCount);
}