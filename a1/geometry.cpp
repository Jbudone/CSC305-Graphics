#include "geometry.h"
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <iostream>
#include <algorithm>
#include "stream.h"
#include "tokenizer.h"
#include "openglerror.h"

Geometry::Geometry() : mFileName(),
    mFilePath(),
    mColorBuffer(0),
    mNormalBuffer(0),
    mTexCoordBuffer(0),
    mVertexBuffer(0),
    mVertexArray(0),
    mPrimitiveType(POINTS),
    mVertices(),
    mNormals(),
    mTexCoords(),
    mColors(),
    mScaleFactor(1.0f)

{   
	initOpenGLBuffers();

	initDefaultShader();
}

Geometry::Geometry(std::string m_FilePath) : mFileName(),
    mFilePath(m_FilePath),
    mColorBuffer(0),
    mNormalBuffer(0),
    mTexCoordBuffer(0),
    mVertexBuffer(0),
    mVertexArray(0),
    mPrimitiveType(POINTS),
    mVertices(),
    mNormals(),
    mTexCoords(),
    mColors(),
    mScaleFactor(1.0f)

{
	initOpenGLBuffers();
	
	initDefaultShader();

    this->parseFile();
}

Geometry::~Geometry()
{
    mVertices.clear();
    mNormals.clear();
    mTexCoords.clear();
    mColors.clear();

    glDeleteVertexArrays(1, & mVertexArray);

    glDeleteBuffers(1, & mColorBuffer);
    glDeleteBuffers(1, & mNormalBuffer);
    glDeleteBuffers(1, & mTexCoordBuffer);
    glDeleteBuffers(1, & mVertexBuffer);

}

void Geometry::draw(Program * m_Program/* = NULL*/)
{
    // in case no shader is provided we use the default one created in the constructor
    if(!m_Program)
    {
        m_Program = mProgram;
    }

    m_Program->activate();

    AbstractParameter * colorParam = m_Program->getAttribute("color");
    AbstractParameter * normalParam = m_Program->getAttribute("normal");
    AbstractParameter * texCoordParam = m_Program->getAttribute("texcoord0");
    AbstractParameter * vertexParam = m_Program->getAttribute("vertex");

    /**
     *  @todo   assignment 1
     *  activate our vertex array objects. upload the geometry, if present to the corresponding buffers.
     *  if a corresponding parameter to the shader is present, then attach the buffer to the parameter.
     *  render the geometry and then deactivate our vertex array objects again.
     *  in order to access the shader parameter handle variable, use the AbstractParameter::getHandle()
     *  function.
     */

	// Activate VAO
	glBindVertexArray(mVertexArray);

	// vertices
	if (vertexParam != NULL) {
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(mVertices[0]), &mVertices.front(), GL_STATIC_DRAW);
		glEnableVertexAttribArray((GLuint)vertexParam->getHandle());
		glVertexAttribPointer((GLuint)vertexParam->getHandle(), 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	// colours
	if (colorParam != NULL) {
		glBindBuffer(GL_ARRAY_BUFFER, mColorBuffer);
		glBufferData(GL_ARRAY_BUFFER, mColors.size() * sizeof(mColors[0]), &mColors.front(), GL_STATIC_DRAW);
		glEnableVertexAttribArray((GLuint)colorParam->getHandle());
		glVertexAttribPointer((GLuint)colorParam->getHandle(), 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	// normals 
	if (normalParam != NULL) {
		glBindBuffer(GL_ARRAY_BUFFER, mNormalBuffer);
		glBufferData(GL_ARRAY_BUFFER, mNormals.size() * sizeof(mNormals[0]), &mNormals.front(), GL_STATIC_DRAW);
		glEnableVertexAttribArray((GLuint)normalParam->getHandle());
		glVertexAttribPointer((GLuint)normalParam->getHandle(), 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	// texcoords 
	if (texCoordParam != NULL) {
		glBindBuffer(GL_ARRAY_BUFFER, mTexCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, mTexCoords.size() * sizeof(mTexCoords[0]), &mTexCoords.front(), GL_STATIC_DRAW);
		glEnableVertexAttribArray((GLuint)texCoordParam->getHandle());
		glVertexAttribPointer((GLuint)texCoordParam->getHandle(), 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


    m_Program->deactivate();
}

void Geometry::translate(Vector3 m_Translation)
{
    /**
     *  @todo   assignment 1
     *  translate every vertex by the given translation
     */
	for (std::vector<Vector3>::iterator it = mVertices.begin(); it != mVertices.end(); ++it) {
		it->x-=m_Translation.x;
		it->y+=m_Translation.y;
	}
}

void Geometry::scale(float m_ScaleFactor)
{
    /**
     *  @todo   assignment 1
     *  scale the vertices based on the scalefactor
     *  hint: you have to scale using both mScaleFactor (the scale factor the mesh is currently in)
     *  and m_ScaleFactor (the new scale factor to be)
     */

	// printf("scaling: %f / %f = %f\n",m_ScaleFactor, mScaleFactor, (m_ScaleFactor / mScaleFactor));
	for (std::vector<Vector3>::iterator it = mVertices.begin(); it != mVertices.end(); ++it) {
		// scaling explanation,
		// let x=a, a0 is the initial x value, c=mScaleFactor, c'=m_ScaleFactor
		// a = a0 * c'   -->  a0 = (a / c')    NOTE: c=c' after this operation
		// a' = a0 * c'  -->  a' = (a / c) * c'  -->  a' = a * (c' / c)
		it->x *= (m_ScaleFactor / mScaleFactor);
		it->y *= (m_ScaleFactor / mScaleFactor);
	}

    mScaleFactor = m_ScaleFactor;
}

std::string Geometry::getFileName() const
{
    return mFileName;
}

std::string Geometry::getFilePath() const
{
    return mFilePath;
}

void Geometry::parseFile()
{
    // open our given file path in read mode ("r").
    // and text mode ("t")
    Stream input(mFilePath, "rt");

    mFileName = input.getFileName();
	
	std::vector<Vector3>	tempVertices;
	std::vector<Vector3>	tempNormals;
	std::vector<Vector3>	tempTexCoords;
	std::vector<Vector4>	tempColors;

    // we read the file line by line until we are at the end
    while(!input.eof())
    {
        std::string curLine = input.readLine();
        // we have an empty line or a comment (starts with #)
        if(curLine.compare("") == 0 || curLine[0] == '#')
        {
            continue;
        }
        Tokenizer tokenizer(curLine);
        tokenizer.tokenize();

        if(tokenizer.getNumTokens() == 0)
        {
            continue;
        }

        std::vector<std::string> tokens = tokenizer.getTokens();

        // vertices
        if(tokens[0].compare("v") == 0)
        {
            Vector3 curVertex;
			for(size_t i = 1; i < tokens.size(); ++i)
			{
				curVertex.elements[i - 1] = atof(tokens[i].c_str());
			}

            tempVertices.push_back(curVertex);
        }
        // normals
        else if(tokens[0].compare("vn") == 0)
        {
            Vector3 curNormal;
			for(size_t i = 1; i < tokens.size(); ++i)
			{
				curNormal.elements[i - 1] = atof(tokens[i].c_str());
			}

            tempNormals.push_back(curNormal);
        }
        // texture coordinates
        else if(tokens[0].compare("vt") == 0)
        {
            Vector3 curTexCoord;
			for(size_t i = 1; i < tokens.size(); ++i)
			{
				curTexCoord.elements[i - 1] = atof(tokens[i].c_str());
			}
            tempTexCoords.push_back(curTexCoord);
        }
        // colors. this is an extension needed only for the assignments. the standard
        // obj file format does not have vertex colors
        else if(tokens[0].compare("vc") == 0)
        {
			Vector4 curColor;
			for(size_t i = 1; i < tokens.size(); ++i)
			{
				curColor.elements[i - 1] = atof(tokens[i].c_str());
			}
            tempColors.push_back(curColor);
        }
        // faces. in case of quads we convert to two triangles
        else if(tokens[0].compare("f") == 0)
        {
			if(tokens.size() == 4)
			{
				mPrimitiveType = TRIANGLES;
			}
			else if(tokens.size() == 5)
			{
				mPrimitiveType = QUADS;
			}
			// no supported primitive type
			else
			{
				continue;
			}
			
			typedef enum
			{
				vertex = 0,
				texcoord = 1,
				normal = 2,
				color = 3
			}
			facePointParam;
			
			// we loop over every vertex in the face
			for(size_t i = 1; i < tokens.size(); ++i)
			{
				facePointParam curParam = vertex;
				size_t numParams = std::count(tokens[i].begin(), tokens[i].end(), '/');
				size_t lastDelimiterIndex = -1;
				
				std::string remainderString = tokens[i];
				
				// we loop over the v/t/n/c construct part by part by reading until the first
				// occurence of /, converting the string to the index of the component, and then removing this
				// part of the string
				for(size_t j = 0; j < (numParams + 1); ++j)
				{
					size_t firstDelimiter = remainderString.find_first_of("/");
					
					std::string curString = remainderString.substr(lastDelimiterIndex + 1, firstDelimiter);
					
					if(curString.compare("") != 0)
					{					
						size_t index = atoi(curString.c_str());
						switch (curParam) {
							case vertex:
								mVertices.push_back(tempVertices[index]);
								break;
							case texcoord:
								mTexCoords.push_back(tempTexCoords[index]);
								break;
							case normal:
								mNormals.push_back(tempNormals[index]);
								break;
							case color:
								mColors.push_back(tempColors[index]);
								break;
								
							default:
								break;
						}
					}
					
					remainderString = remainderString.substr(firstDelimiter + 1,
															 remainderString.size() - firstDelimiter - 1);
					
                    curParam = (facePointParam)(((uint32_t)curParam) + 1);
					
				}				
			}
        }
        // everything else, we are not interested
        else
        {
            // not handeled
        }
    }
	
	convertQuadsToTriangles();
}

void Geometry::convertQuadsToTriangles()
{
	if(mPrimitiveType == QUADS)
    {
        /**
         *	we need to change quads to triangles, since OpenGL3.2 Core
         *	does not support quads any more
         */
        std::vector<Vector3>	tempVertices;
        std::vector<Vector3>	tempNormals;
        std::vector<Vector3>	tempTexCoords;
        std::vector<Vector4>	tempColors;
		
        for(size_t i = 0; i < mVertices.size(); i += 4)
        {
            /**
             *	Triangle 1 from Quad.
             *	index 0-1-3
             */
            size_t index = i;
			
            tempVertices.push_back(mVertices[index]);
			if(index < mNormals.size())
				tempNormals.push_back(mNormals[index]);
            if(index < mTexCoords.size())
				tempTexCoords.push_back(mTexCoords[index]);
			if(index < mColors.size())
				tempColors.push_back(mColors[index]);
			
            index = i + 1;
			
            tempVertices.push_back(mVertices[index]);
			if(index < mNormals.size())
				tempNormals.push_back(mNormals[index]);
            if(index < mTexCoords.size())
				tempTexCoords.push_back(mTexCoords[index]);
            if(index < mColors.size())
				tempColors.push_back(mColors[index]);
			
            index = i + 3;
			
            tempVertices.push_back(mVertices[index]);
            if(index < mNormals.size())
				tempNormals.push_back(mNormals[index]);
            if(index < mTexCoords.size())
				tempTexCoords.push_back(mTexCoords[index]);
            if(index < mColors.size())
				tempColors.push_back(mColors[index]);
			
            /**
             *	triangle 2 from quad
             *	index 1-2-3
             */
			
            index = i + 1;
			
            tempVertices.push_back(mVertices[index]);
            if(index < mNormals.size())
				tempNormals.push_back(mNormals[index]);
            if(index < mTexCoords.size())
				tempTexCoords.push_back(mTexCoords[index]);
            if(index < mColors.size())
				tempColors.push_back(mColors[index]);
			
            index = i + 2;
			
            tempVertices.push_back(mVertices[index]);
            if(index < mNormals.size())
				tempNormals.push_back(mNormals[index]);
            if(index < mTexCoords.size())
				tempTexCoords.push_back(mTexCoords[index]);
            if(index < mColors.size())
				tempColors.push_back(mColors[index]);
			
            index = i + 3;
			
            tempVertices.push_back(mVertices[index]);
            if(index < mNormals.size())
				tempNormals.push_back(mNormals[index]);
            if(index < mTexCoords.size())
				tempTexCoords.push_back(mTexCoords[index]);
            if(index < mColors.size())
				tempColors.push_back(mColors[index]);
        }
		
        mVertices.swap(tempVertices);
        mNormals.swap(tempNormals);
        mTexCoords.swap(tempTexCoords);
        mColors.swap(tempColors);
		
        mPrimitiveType = TRIANGLES;
    }
    else if(mPrimitiveType == QUAD_STRIP)
    {
        /**
         *	luckily quad strips and triangle strips seem to require the same
         *	data
         */
        mPrimitiveType = TRIANGLE_STRIP;
    }
}

void Geometry::initOpenGLBuffers()
{
	glGenVertexArrays(1, & mVertexArray);
    glBindVertexArray(mVertexArray);
	
    glGenBuffers(1, & mColorBuffer);
    glGenBuffers(1, & mNormalBuffer);
    glGenBuffers(1, & mTexCoordBuffer);
    glGenBuffers(1, & mVertexBuffer);
	
    glBindVertexArray(0);

}

bool Geometry::initDefaultShader()
{
	const std::string vertexShader = "#version 150\n"
	"in vec4 vertex;\n"
	"in vec4 color;\n"
	"out vec4 vColor;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vertex;\n"
	"vColor = color;\n"
	"}";
	
    const std::string fragmentShader = "#version 150\n"
	"in vec4 vColor;\n"
	"out vec4 fColor;\n"
	"void main()\n"
	"{\n"
	"fColor = vColor;\n"
	"}";
	
	
    mProgram = new Program();
	
    Shader * vShader = new Shader(vertexShader, Shader::VERTEX);
    vShader->load();
    Shader * fShader = new Shader(fragmentShader, Shader::FRAGMENT);
    fShader->load();
	
    mProgram->push_back(vShader);
    mProgram->push_back(fShader);
	
    return mProgram->link();
}
