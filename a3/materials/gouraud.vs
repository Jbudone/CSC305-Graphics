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

out vec4 vColor;
out vec4 vDiffuse;
out vec4 vSpec;
out float specI;
out float diffI;

const vec4  specularVec = vec4(1.0);
const float ambienceIntensity = 0.45;
const float shininess = 6.0;

void main()
{

	// (prof) vertex pos
	vec4 position = modelMatrix * vec4(vertex, 1.0);
	gl_Position = projectionMatrix * viewMatrix * position;


	////////////////////////////////
	// Positions
	//
	// norm = normMat * norm;  the normal vec projected into normal space
	// lightDir = viewModel * (lightPos - vertex);  basically the negative direction 
	// 												between the light and the vertex
	// 												then projected by the view*model
	// vertPos = - (viewModel * vertex); the vertex projected by the view*model

	vec3 norm = normalize(normalMatrix * normal);
	vec3 lightDir = normalize(vec3(vec4(viewMatrix * modelMatrix * (vec4(lightPos,1.0)-vec4(vertex,1.0))))); // light direction
	vec3 vertPos = normalize(vec3(-vec4(viewMatrix * modelMatrix * vec4(vertex, 1.0)))); // vertex position
	float lDotN = max(dot(lightDir,norm), 0.0);


	// ADS Shading (Ambience, Diffuse, Specular)
	/////////////////////////////////
	// ADS Shading
	//
	// NOTE
	// 	ambience, diffuse and specular are calculated here (per vertex),
	// 	but diffuse and specular are set to varying components which are
	// 	loaded in the fragment shader (per pixel) and added to the pixel
	// 	colour accordingly
	//
	// Ambience: the base colour * intensity
	// Diffuse: light * colour * lDotN (angle between lightvec and normal)
	// Specular: angle between reflected light direction and vertex; put to the power of shininess level
	
	vec4 ambient = lightCol * color * ambienceIntensity; // Ambience
	diffI = lDotN; // Diffuse Intensity
	vDiffuse = lightCol * color; // Diffuse Vec
	specI = 0.0;
	vSpec = lightCol * specularVec; // Specular Vec (white spec)
	if (lDotN > 0.0)
		specI = pow(max(dot(reflect(lightDir,norm),vertPos), 0.0), shininess); // Specular Intesity
	
	vColor = ambient; // only ambience given here; the rest are done in the frag-shader
}
