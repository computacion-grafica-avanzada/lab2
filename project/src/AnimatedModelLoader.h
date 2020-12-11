#pragma once

#include "Texture.h"
#include "JointData.h"
#include "AnimationRenderer.h"
#include "ColladaLoader.h"
#include "MeshData.h"
#include "AnimatedMesh.h"
#include "AnimatedRenderable.h"
#include "Joint.h"

class AnimatedModelLoader
{
	/* Loads up the diffuse texture for the model. */
	static Texture* loadTexture(const char* textureFile);

	/* Constructs the joint-hierarchy skeleton from the data extracted from the collada file. */
	static Joint* createJoints(JointData* data);

public:
	/* Creates an AnimatedEntity from the data in an entity file. It loads up
	the collada model data, stores the extracted data in a VAO, sets up the
	joint heirarchy, and loads up the entity's texture.*/
	static AnimatedRenderable* loadEntity(const char* modelFile, const char* textureFile);
};

