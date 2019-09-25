#pragma warning(disable:4996)
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")

#include <GL/glew.h>	
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
using namespace std;

GLFWwindow* window;

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

	// window ����
	window = glfwCreateWindow(1024, 768, "OpenGL", NULL, NULL);

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

GLuint BuildShader(std::vector<pair<std::string, int> >& shaderCodies)
{
	GLuint ProgramID = glCreateProgram();
	GLint Result = GL_FALSE;
	int InfoLogLength;

	vector<int> shaderIdVec;
	// ���ؽ� ���̴��� ������
	printf("Compiling shader\n");
	for (int i = 0; i < shaderCodies.size(); ++i)
	{
		GLuint shaderID = glCreateShader(shaderCodies[i].second);

		shaderIdVec.push_back(shaderID);

		char const * shaderPointer = shaderCodies[i].first.c_str();
		glShaderSource(shaderID, 1, &shaderPointer, NULL);
		glCompileShader(shaderID);

		// ���ؽ� ���̴��� �˻�
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0)
		{
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			printf("%s\n", &VertexShaderErrorMessage[0]);
		}

		glAttachShader(ProgramID, shaderID);
	}

	// ��ũ
	glLinkProgram(ProgramID);


	// ���α׷� �˻�
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	
	if (InfoLogLength > 0)
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	for (int i = 0; i < shaderIdVec.size(); ++i)
	{
		glDetachShader(ProgramID, shaderIdVec[i]);
		glDeleteShader(shaderIdVec[i]);
	}

	return ProgramID;
}

std::string ReadShaderFile(const char* filePath)
{
	std::string shaderCode;
	std::ifstream shaderStream(filePath, std::ios::in);
	if (shaderStream.is_open()) {
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	}
	else
	{
		printf("���� %s �� ���� �� ����.\n", filePath);
	}

	return shaderCode;
}

int main()
{
	initGLFW();
	initGLEW();

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
	};

	// ���ؽ� ���ۿ� �ڵ�
	GLuint vertexbuffer;
	// ���۸� ����
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// ���ؽ����� OpenGL��
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// ���̴��� ���� ���������� ������.
	std::vector<pair<std::string, int> > shaderCodies;
	shaderCodies.push_back(make_pair(ReadShaderFile("vertex.glsl"), GL_VERTEX_SHADER));
	shaderCodies.push_back(make_pair(ReadShaderFile("fragment.glsl"), GL_FRAGMENT_SHADER));
	shaderCodies.push_back(make_pair(ReadShaderFile("tcs.glsl"), GL_TESS_CONTROL_SHADER));
	shaderCodies.push_back(make_pair(ReadShaderFile("tes.glsl"), GL_TESS_EVALUATION_SHADER));
	// shaderCodies.push_back(make_pair(ReadShaderFile("gs.glsl"), GL_GEOMETRY_SHADER));

	GLuint programID = BuildShader(shaderCodies);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(programID);

	do
	{
		double time = glfwGetTime();

		// drawing
		static const GLfloat blue[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, blue);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		glVertexAttribPointer(
			0,                  // 0��° �Ӽ�(attribute).
			3,                  // ũ��(size)
			GL_FLOAT,           // Ÿ��(type)
			GL_FALSE,           // ����ȭ(normalized)?
			0,                  // ���� ��� ���� ����(stride)
			(void*)0            // �迭 ������ ������(offset; �ű�� ��)
		);

		// vertex�� �̵���Ų��. vertex.glsl�� in ���þ �߰��ؾ���.
		GLfloat attr[] = { sin(time) * 0.5, cos(time) * 0.5, 0.0, 0.0 };
		glVertexAttrib4fv(1, attr);

		// ������ ���� ��Ų��.
		GLfloat color[] = { sin(time) * 0.5 + 0.5f, cos(time) * 0.5 + 0.5f, 0.0, 1.0 };
		glVertexAttrib4fv(2, color);
		glPointSize(5.0f);
		glDrawArrays(GL_PATCHES, 0, 3);
		glDisableVertexAttribArray(0);

		// swap buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glfwTerminate();
	return 0;
}