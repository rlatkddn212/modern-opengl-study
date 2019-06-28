#pragma warning(disable:4996)
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")

#include <GL/glew.h>	
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;

GLFWwindow* window;
GLuint width;
GLuint height;

void initGLFW()
{
	// GLFW �ʱ�ȭ
	if (!glfwInit())
	{
		cerr << "ERROR : init GLFW\n";
		return exit(-1);
	}

	// GLFW ����
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	width = 1024;
	height = 768;

	// window ����
	window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);

	if (window == NULL)
	{
		cerr << "Error : open GLFW\n";
		glfwTerminate();
		return exit(-1);
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void initGLEW()
{
	// GLEW �ʱ�ȭ
	glfwMakeContextCurrent(window);
	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		cerr << "ERROR : init GLEW\n";
		return exit(-1);
	}
}

GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath)
{
	// ���̴��� ����
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// ���ؽ� ���̴� �ڵ带 ���Ͽ��� �б�
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertexFilePath, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else
	{
		//printf("���� %s �� ���� �� ����.\n", vertexFilePath);
		getchar();
		return 0;
	}

	// �����׸�Ʈ ���̴� �ڵ带 ���Ͽ��� �б�
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragmentFilePath, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// ���ؽ� ���̴��� ������
	printf("Compiling shader : %s\n", vertexFilePath);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// ���ؽ� ���̴��� �˻�
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// �����׸�Ʈ ���̴��� ������
	printf("Compiling shader : %s\n", fragmentFilePath);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// �����׸�Ʈ ���̴��� �˻�
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// ���α׷��� ��ũ
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// ���α׷� �˻�
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

int main()
{
	initGLFW();
	initGLEW();

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,
	};
	static const GLfloat g_uv_buffer_data[] =
	{
		0.0, 1.0,
		1.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,
	};

	// ���ؽ� ���ۿ� �ڵ�
	GLuint vertexbuffer[2];
	// ���۸� ����
	glGenBuffers(2, &vertexbuffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
	// ���ؽ����� OpenGL��
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);
	// ���ؽ����� OpenGL��
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	GLuint programID = LoadShaders("vertex.glsl", "Image.glsl");
	glUseProgram(programID);
	
	GLuint textureID[2];
	glGenTextures(1, &textureID[0]);

	{
		int x, y, d;
		unsigned char* texData = stbi_load("kart.png", &x, &y, &d, 0);
		if (!texData)
		{
			return false;
		}
		glBindTexture(GL_TEXTURE_2D, textureID[0]);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(texData);
	}

	{
		int x, y, d;
		unsigned char* texData = stbi_load("matrix.png", &x, &y, &d, 0);
		if (!texData)
		{
			return false;
		}
		glBindTexture(GL_TEXTURE_2D, textureID[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(texData);
	}

	GLint loc = glGetUniformLocation(programID, "mvp_matrix");
	float aspect = (float)width / (float)height;
	glm::mat4 perspect = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 1000.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, -50.0f, -5.0f), glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0, 1.0, 0.0));

	do
	{
		glViewport(0, 0, width, height);

		// drawing
		static const GLfloat blue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		static const GLfloat one = 1.0f;
		glClearBufferfv(GL_COLOR, 0, blue);
		glClearBufferfv(GL_DEPTH, 0, &one);

		for (int i = 0; i < 100; ++i)
		{
			for (int j = 0; j < 100; ++j)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, textureID[0]);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, textureID[1]);

				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);

				glVertexAttribPointer(
					0,                  // 0��° �Ӽ�(attribute).
					3,                  // ũ��(size)
					GL_FLOAT,           // Ÿ��(type)
					GL_FALSE,           // ����ȭ(normalized)?
					0,                  // ���� ��� ���� ����(stride)
					(void*)0            // �迭 ������ ������(offset; �ű�� ��)
				);

				glEnableVertexAttribArray(1);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);

				glVertexAttribPointer(
					1,                  // 0��° �Ӽ�(attribute).
					2,                  // ũ��(size)
					GL_FLOAT,           // Ÿ��(type)
					GL_FALSE,           // ����ȭ(normalized)?
					0,                  // ���� ��� ���� ����(stride)
					(void*)0            // �迭 ������ ������(offset; �ű�� ��)
				);

				GLuint texloc = glGetUniformLocation(programID, "texID");
				glUniform1i(texloc, i+j);

				glm::mat4 mvpMat = glm::mat4(1.0f);
				mvpMat = glm::translate(mvpMat, glm::vec3(-50.0f + i, -50.0f + j, -10.0f));
				
				//mvpMat = glm::rotate(mvpMat, glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				mvpMat = glm::scale(mvpMat, glm::vec3(0.5f, 0.5f, 0.5f));
				mvpMat = perspect * view * mvpMat;
				glUniformMatrix4fv(loc, 1, GL_FALSE, &mvpMat[0][0]);

				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
				glDisableVertexAttribArray(1);
				glDisableVertexAttribArray(0);
			}
		}

		// swap buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glfwTerminate();
	return 0;
}