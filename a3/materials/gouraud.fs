#version 150

out vec4 fColor;

in vec4 vColor;
in vec4 vDiffuse;
in vec4 vSpec;
in float specI;
in float diffI;

void main()
{
   fColor = vColor + vDiffuse * diffI + vSpec * specI;
}
