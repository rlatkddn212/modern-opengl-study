#include "ObjModel.h"
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;

ObjModel::ObjModel()
{
}


ObjModel::~ObjModel()
{
}

void ObjModel::LoadModel(const std::string& fileName)
{
	std::ifstream input(fileName.c_str());
	std::string lineStr;

	vector<Point3D> v;
	vector<Point2D> vt;
	vector<Point3D> vn;

	vector<GLfloat> vertices;
	vector<int> index;
	GLuint cnt = 0;
	if (input.bad())
	{
		return;
	}

	while (! input.eof())
	{
		getline(input, lineStr);
		stringstream ss(lineStr);

		string s;
		ss >> s;

		if (s == "mtllib")
		{
			// mtl ������ ã�´�.
			// �̹����� ã�´�.
			string mtlfileName;
			ss >> mtlfileName;
			LoadMtl(mtlfileName);
		}
		else if (s == "usemtl")
		{
			// mtl ���Ͽ��� � mtl�� ����� ������
		}
		else if (s == "g")
		{
			// �׷�
		}
		else if (s == "o")
		{
			// ������Ʈ
		}
		else if (s == "v")
		{
			// ���ؽ� x,y,z ��ǥ
			GLfloat x,y,z;
			ss >> x >> y >> z;
			v.push_back({ x,y,z });
		}
		else if (s == "vt")
		{
			// �ؽ��� ��ǥ
			GLfloat s, t;
			ss >> s >> t;
			vt.push_back({ s,t });
		}
		else if (s == "vn")
		{
			// ���ؽ� ���
			GLfloat x, y, z;
			ss >> x >> y >> z;
			vn.push_back({ x,y,z });
		}
		else if (s == "f")
		{

			for (int i = 0; i < 3 ; ++i)
			{
				string face;
				ss >> face;
				stringstream faceStream(face);
				GLuint vface;
				GLuint vtface;
				GLuint vnface;
				char temp;
				faceStream >> vface;
				faceStream >> temp;
				faceStream >> vtface;

				// ���Ͽ� ����� ���� �ּ� ó���ߴ�.
				//faceStream >> temp;
				//faceStream >> vnface;

				vertices.insert(vertices.end(), { v[vface - 1].x, v[vface - 1].y, v[vface - 1].z });
				vertices.insert(vertices.end(), { vt[vtface - 1].x, 1- vt[vtface - 1].y});
				
				//vertices.insert(vertices.end(), { vn[vnface - 1].x, vn[vnface - 1].y, vn[vnface - 1].z });
				vertices.insert(vertices.end(), { 0.0f,0.0f,0.0f });
				index.push_back(cnt++);
			}
		}
	}

	model.indexCnt = cnt;
	glGenVertexArrays(1, &model.vaoID);
	glBindVertexArray(model.vaoID);

	// IBO�� ����Ͽ� �������ϰԵȴ�.
	glGenBuffers(1, &model.iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index[0]) * cnt, &index[0], GL_STATIC_DRAW);

	glGenBuffers(1, &model.vboID);
	glBindBuffer(GL_ARRAY_BUFFER, model.vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void ObjModel::RenderModel(GLint loc, glm::mat4 mvp)
{
	glUniformMatrix4fv(loc, 1, GL_FALSE, &mvp[0][0]);
	glBindVertexArray(model.vaoID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.iboID);

	// IBO�� ����� ��� glDrawElements�� ȣ���ؾ��Ѵ�.
	glDrawElements(GL_TRIANGLES, model.indexCnt, GL_UNSIGNED_INT, 0);
	
	// ������ ���ڸ� �����Ͽ� BaseVertex�� ������ �� �ִ�. glDrawElements�� �ּ� ó���ϰ�
	// �Ʒ� �ڵ带 �����ϸ� ������ Ȯ���� �� �ִ�.
	//glDrawElementsBaseVertex(GL_TRIANGLES, model.indexCnt, GL_UNSIGNED_INT, 0, 3);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// �ؽ��� ��ġ�� �˾Ƴ���.                  
void ObjModel::LoadMtl(const std::string & fileName)
{
	std::ifstream input(fileName.c_str());
	std::string lineStr;
	std::string mtlMapStr;
	if (input.bad())
	{
		return;
	}

	while (!input.eof())
	{
		getline(input, lineStr);
		stringstream ss(lineStr);

		string s;
		ss >> s;
		if (s == "newmtl")
		{
			ss >> mtlMapStr;
		}
		if (s == "map_Kd")
		{
			ss >> s;
			LoadTexture(s);
		}
	}
}

void ObjModel::LoadTexture(const std::string & fileName)
{

	unsigned char* texData = stbi_load(fileName.c_str(), &model.width, &model.height, &model.bitDepth, 0);
	if (!texData)
	{
		return;
	}

	glGenTextures(1, &model.textureID);
	glBindTexture(GL_TEXTURE_2D, model.textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, model.width, model.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);
}

void ObjModel::UseTexture()
{
	glBindTexture(GL_TEXTURE_2D, model.textureID);
}
