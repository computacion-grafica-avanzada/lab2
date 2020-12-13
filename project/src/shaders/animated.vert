#version 400

const int MAX_JOINTS = 50;
const int MAX_WEIGHTS = 3;

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in ivec3 jointIds;
layout (location = 4) in vec3 jointWeights;

// varying vec2 texCoord0;
// varying vec3 normal0;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 jointTransforms[MAX_JOINTS];

out DATA {
	vec3 worldPosition;
	vec2 textureCoord;
	vec3 normal;
	float alpha;
    vec4 test;
} Out;

void main()
{
    vec4 totalLocalPos = vec4(0.0);
    vec4 totalNormal = vec4(0.0);

    for (int i = 0; i < MAX_WEIGHTS; i++) 
    {		
        mat4 jointTransform = jointTransforms[jointIds[i]];
        vec4 posePosition = jointTransform * position;
        totalLocalPos = totalLocalPos + posePosition * jointWeights[i];

        vec4 worldNormal = jointTransform * vec4(normal, 0.0);
        totalNormal = totalNormal + worldNormal * jointWeights[i];
    }

    //totalLocalPos = position;

    vec4 worldPosition = model * totalLocalPos;
	// vec4 positionRelativeToCamera = view * worldPosition;

	mat4 modelViewProjection = projection * view * model;

	gl_Position = modelViewProjection * totalLocalPos;

	// texCoord0 = texCoord;
    // normal0 = (totalLocalPos * vec4(normal, 0.0)).xyz;
	
	Out.alpha = 1;
	Out.worldPosition = worldPosition.xyz;
	Out.textureCoord = texCoord;
	Out.normal = totalNormal.xyz;
    Out.test = jointTransforms[0] * position;
}