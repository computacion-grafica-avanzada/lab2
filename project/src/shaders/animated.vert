#version 130

const int MAX_JOINTS = 50;
const int MAX_WEIGHTS = 4;

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in ivec4 jointIds;
layout (location = 4) in vec4 jointWeights;

varying vec2 texCoord0;
varying vec3 normal0;

uniform mat4 transform;
uniform mat4 viewProjection;
uniform mat4 jointTransforms[MAX_JOINTS];

void main()
{
    vec4 totalLocalPos = vec4(0.0);
    vec4 totalNormal = vec4(0.0);

    for (int i = 0; i<MAX_WEIGHTS; i++) 
    {		
        mat4 jointTransform = jointTransforms[jointIds[i]];

        vec4 posePosition = jointTransform * position;
        totalLocalPos += posePosition * jointWeights[i];

        vec4 worldNormal = jointTransform * vec4(normal, 0.0);
        totalNormal += worldNormal * jointWeights[i];
    }

    //totalLocalPos = position;

	mat4 modelViewProjection = viewProjection * transform;

	gl_Position = modelViewProjection * totalLocalPos;

	texCoord0 = texCoord;
    normal0 = (totalLocalPos * vec4(normal, 0.0)).xyz;
}