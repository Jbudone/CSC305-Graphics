#version 150

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform int usePostMultiply;


uniform mat3 normalMatrix;
uniform vec3 lightPos;
uniform vec4 lightCol;

in vec3 vertex;
in vec4 color;
in vec3 normal;

varying vec3 fvVertex;
varying vec4 fvColor;
varying vec3 fvNormal;


void main()
{
	// (prof) vertex pos
	vec4 position = modelMatrix * vec4(vertex, 1.0);
	gl_Position = projectionMatrix * viewMatrix * position;

	fvVertex = vertex;
	fvColor = color;
	fvNormal = normal;
}
