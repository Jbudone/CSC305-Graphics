#version 150

out vec4 fColor;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform int  usePostMultiply;

uniform mat3 normalMatrix;
uniform vec3 lightPos;
uniform vec4 lightCol;

in vec3 fvVertex;
in vec4 fvColor;
in vec3 fvNormal;

const vec4  specularVec = vec4(1.0);
const float ambienceIntensity = 0.45;
const float shininess = 6.0;

void main()
{



	////////////////////////////////
	// Positions
	//
	// norm = normMat * norm;  the normal vec projected into normal space
	// lightDir = viewModel * (lightPos - vertex);  basically the negative direction 
	// 												between the light and the vertex
	// 												then projected by the view*model
	// vertPos = - (viewModel * vertex); the vertex projected by the view*model

	vec3 norm = normalize(normalMatrix * fvNormal);
	vec3 lightDir = normalize(vec3(vec4(viewMatrix * modelMatrix * (vec4(lightPos,1.0)-vec4(fvVertex,1.0)))));
	vec3 vertPos = normalize(vec3(-vec4(viewMatrix * modelMatrix * vec4(fvVertex, 1.0))));
	float lDotN = max(dot(lightDir,norm), 0.0);


	// ADS Shading (Ambience, Diffuse, Specular)
	/////////////////////////////////
	// ADS Shading
	//
	// Ambience: the base colour * intensity
	// Diffuse: light * colour * lDotN (angle between lightvec and normal)
	// Specular: angle between reflected light direction and vertex; put to the power of shininess level
	
	vec4 ambient = lightCol * fvColor * ambienceIntensity;
	vec4 diffuse = lightCol * fvColor * lDotN;
	vec4 spec = vec4(0.0);
		spec = lightCol * specularVec * pow(max(dot(reflect(lightDir,norm),vertPos), 0.0), shininess);
	fColor = ambient + diffuse + spec;
}
