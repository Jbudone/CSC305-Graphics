
Assignment 3
--------------

Assignment 3 implements basic shader techniques in illuminating objects in 
space. This includes Ambience, Diffuse and Specular (ADS) illumination; 
texture and bump mapping; and gouraud vs. phong models.


Marking
========

1 pt for code comments & README.txt file
1 pt for loading textures and uploading them to OpenGL
2 pt for Gouraud shading of vertex colours
2 pt for Phong shading of vertex colours
2 pt for Phong shading with textures
2 pt for Bump mapping
2* pt for additional surface shading technique (Alpha texture)

Running
========

./build/Release/BasicOpenGL.app/Contents/MacOS/BasicOpenGL


Gouraud
========

Gouraud shading is the simplest and lightest ADS (Ambience/Diffuse/Specular)
shading technique, which works per-vertex. The trick here is to pass the 
diffuse and specular calculate values off as varying variables to the fragment
(per-pixel) shade; which adds the diffuse and specular values to the output
colour for that pixel. The issue is apparent in the specular level which shows
a line/block rather than a circular area of specular activity.

Phong
========

Phong shading is more accurate than Gouraud by working per-pixel (in the
fragment shader). It calculates the standard ADS (Ambience/Diffuse/Specular)
but because its calculated per-pixel, its more accurate and is able to get
rid of the line/block problem thats apparent in the Gouraud technique. This
technique gives a proper circular-like specular illumination.

Bump Mapping
========

Bump mapping is accomplished via. a heightmap associated with the texture.
The fragment shader takes the current texel coordinate, as well as 4 offset
coordinates (up, down, left, right). These coordinates let us create a 
tangent vector (N, 0, Zr-Zl) where Zr is the red-channel of the right texel
coordinate, and Zl is the red-channel of the left texel coord; along with
a binormal vector (0, N, Zn-Zs). N = C*dt where dt is 1 texel-unit length, 
and C is the controller for the bumpiness; N basically controls our amount
of bump, where 1 is chaotically bumpy, and 50 is smooth. The cross product
of the tangent and binormal vectors gives us a new normal vector for the
given pixel, which is used in all the lighting calculations. This new normal
makes the mesh appear bumpy, due to the angled lighting calculations.

Alpha Texture
========

For an additional shading technique, I've implemented an alpha texture
which takes a second texture and mixes it with the base texture based off
of the alpha texture's alpha value. This gives a great effect for things 
like vines or moss growing ontop of the brick wall.
