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
	// GLFW 초기화
	if (!glfwInit())
	{
		cerr << "ERROR : init GLFW\n";
		return exit(-1);
	}

	// GLFW 설정
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// window 생성
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
	// GLEW 초기화
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
	// 버텍스 쉐이더를 컴파일
	printf("Compiling shader\n");
	for (int i = 0; i < shaderCodies.size(); ++i)
	{
		GLuint shaderID = glCreateShader(shaderCodies[i].second);

		shaderIdVec.push_back(shaderID);

		char const * shaderPointer = shaderCodies[i].first.c_str();
		glShaderSource(shaderID, 1, &shaderPointer, NULL);
		glCompileShader(shaderID);

		// 버텍스 쉐이더를 검사
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

	// 링크
	glLinkProgram(ProgramID);


	// 프로그램 검사
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
		printf("파일 %s 를 읽을 수 없음.\n", filePath);
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

	// 버텍스 버퍼에 핸들
	GLuint vertexbuffer;
	// 버퍼를 생성
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// 버텍스들을 OpenGL로
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// 셰이더를 조금 범용적으로 만들자.
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
			0,                  // 0번째 속성(attribute).
			3,                  // 크기(size)
			GL_FLOAT,           // 타입(type)
			GL_FALSE,           // 정규화(normalized)?
			0,                  // 다음 요소 까지 간격(stride)
			(void*)0            // 배열 버퍼의 오프셋(offset; 옮기는 값)
		);

		// vertex를 이동시킨다. vertex.glsl에 in 지시어를 추가해야함.
		GLfloat attr[] = { sin(time) * 0.5, cos(time) * 0.5, 0.0, 0.0 };
		glVertexAttrib4fv(1, attr);

		// 색상을 변경 시킨다.
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