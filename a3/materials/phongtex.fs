
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
in vec2 fvtexcoord0;

uniform sampler2D colormap;
uniform sampler2D bumpmap;


const float ambienceIntensity = 1.00;
const vec4  specularVec = vec4(1.0);
const float shininess = 86.0;


void main()
{

	// main texture
	vec4 texcolor = texture(colormap, fvtexcoord0.st);



	////////////////////////////////
	// Bump Mapping
	//
	//   ^ (0, N, Zn-Zs)
	//   |
	//   |   
	//   *---->
	//       (N, 0, Ze-Zw)
	// 
	// C = controller for bumpiness
	// dt = 1 texel unit
	// N = C*dt
	// norm = (N,0,Ze-Zw)x(0,N,Zn-Zs)
	//
	// using one channel (the red channel in this case), creates a Z coordinate
	// from given texture position. Create a tangent vector (x-direction) by
	// offsetting the current texcoord by 1 texel in the left and right direction
	// Z=Ze-Zw; the binormal is the same as the tangent vector, except in the
	// y-direction. 

	float x = fvtexcoord0.s;
	float y = fvtexcoord0.t;
	float dt = 1.0/1024.0;
	float N = texture(bumpmap, vec2(x, y + dt)).r;
	float S = texture(bumpmap, vec2(x, y - dt)).r;
	float E = texture(bumpmap, vec2(x + dt, y)).r;
	float W = texture(bumpmap, vec2(x - dt, y)).r;
	float C = 6.0;

	vec3 tangent = vec3(C * dt, 0, E - W);
	vec3 binormal = vec3(0, C * dt, N - S);
	vec3 norm = normalize(cross(tangent,binormal));



	////////////////////////////////
	// Positions
	//
	// lightDir = viewModel * (lightPos - vertex);  basically the negative direction 
	// 												between the light and the vertex
	// 												then projected by the view*model
	// vertPos = - (viewModel * vertex); the vertex projected by the view*model

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
	
	vec4 ambient = lightCol * texcolor * ambienceIntensity;
	vec4 diffuse = lightCol * texcolor * lDotN;
	vec4 spec = vec4(0.0);
	if (lDotN > 0.0) // only specular on areas facing towards us
		spec = texcolor * specularVec * pow(max(dot(reflect(lightDir,norm),vertPos), 0.0), shininess);
	fColor = ambient + diffuse + spec;
}
