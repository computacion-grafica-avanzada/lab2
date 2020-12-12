#include "AnimatedRenderable.h"

/**
 * This adds the current model-space transform of a joint (and all of its
 * descendants) into an array of transforms. The joint's transform is added
 * into the array at the position equal to the joint's index.
 *
 * @param headJoint
 *            - the current joint being added to the array. This method also
 *            adds the transforms of all the descendents of this joint too.
 * @param jointMatrices
 *            - the array of joint transforms that is being filled.
 */
void AnimatedRenderable::addJointsToArray(Joint* headJoint, std::vector<glm::mat4> jointMatrices) {
	jointMatrices[headJoint->index] = headJoint->getAnimatedTransform();
	for (Joint* childJoint : headJoint->children) {
		addJointsToArray(childJoint, jointMatrices);
	}
}

/**
 * Creates a new entity capable of animation. The inverse bind transform for
 * all joints is calculated in this constructor. The bind transform is
 * simply the original (no pose applied) transform of a joint in relation to
 * the model's origin (model-space). The inverse bind transform is simply
 * that but inverted.
 *
 * @param model
 *            - the VAO containing the mesh data for this entity. This
 *            includes vertex positions, normals, texture coords, IDs of
 *            joints that affect each vertex, and their corresponding
 *            weights.
 * @param texture
 *            - the diffuse texture for the entity.
 * @param rootJoint
 *            - the root joint of the joint hierarchy which makes up the
 *            "skeleton" of the entity.
 * @param jointCount
 *            - the number of joints in the joint hierarchy (skeleton) for
 *            this entity.
 *
 */
AnimatedRenderable::AnimatedRenderable(AnimatedMesh* mesh, Texture* texture, float textureTiling, Joint* rootJoint, int jointCount) {
	this->setMesh(mesh);
	this->setTexture(texture, textureTiling);
	this->rootJoint = rootJoint;
	this->jointCount = jointCount;
	this->animator = new Animator(this->rootJoint);
	rootJoint->calcInverseBindTransform(glm::identity<glm::mat4>());
}

/**
 * @return The root joint of the joint hierarchy. This joint has no parent,
 *         and every other joint in the skeleton is a descendant of this
 *         joint.
 */
Joint* AnimatedRenderable::getRootJoint() {
	return rootJoint;
}

/**
 * Instructs this entity to carry out a given animation. To do this it
 * basically sets the chosen animation as the current animation in the
 * {@link Animator} object.
 *
 * @param animation
 *            - the animation to be carried out.
 */
void AnimatedRenderable::doAnimation(Animation* animation) {
	animator->doAnimation(animation);
}

/**
 * Updates the animator for this entity, basically updating the animated
 * pose of the entity. Must be called every frame.
 */
void AnimatedRenderable::update() {
	animator->setRootJoint(this->rootJoint);
	animator->update();
}

/**
 * Gets an array of the all important model-space transforms of all the
 * joints (with the current animation pose applied) in the entity. The
 * joints are ordered in the array based on their joint index. The position
 * of each joint's transform in the array is equal to the joint's index.
 *
 * @return The array of model-space transforms of the joints in the current
 *         animation pose.
 */
std::vector<glm::mat4> AnimatedRenderable::getJointTransforms() {
	std::vector<glm::mat4> jointMatrices = std::vector<glm::mat4>(jointCount, glm::identity<glm::mat4>());
	addJointsToArray(rootJoint, jointMatrices);
	return jointMatrices;
}