#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>	
#include <GLFW/glfw3.h>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct GLModel
{
	GLuint vaoID;
	GLuint vboID;
	GLuint iboID;
	GLuint indexCnt;
	
	GLuint textureID;
	int width;
	int height;
	int bitDepth;
};

struct Point3D
{
	GLfloat x,y,z;
};

struct Point2D
{
	GLfloat x,y;
};

class ObjModel
{
public:
	ObjModel();
	~ObjModel();

	void LoadModel(const std::string& fileName);
	void RenderModel(GLint loc, glm::mat4 mvp);
	void LoadMtl(const std::string& fileName);
	void LoadTexture(const std::string& fileName);
	void UseTexture();

	GLModel model;
};
