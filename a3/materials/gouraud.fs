
#version 150

out vec4 fColor;

varying vec4 vColor;
varying vec4 vDiffuse;
varying vec4 vSpec;
varying float specI;
varying float diffI;

void main()
{
   fColor = vColor + vDiffuse * diffI + vSpec * specI;
}
