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

GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath)
{
	// 쉐이더들 생성
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// 버텍스 쉐이더 코드를 파일에서 읽기
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
		//printf("파일 %s 를 읽을 수 없음.\n", vertexFilePath);
		getchar();
		return 0;
	}

	// 프래그먼트 쉐이더 코드를 파일에서 읽기
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

	// 버텍스 쉐이더를 컴파일
	printf("Compiling shader : %s\n", vertexFilePath);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// 버텍스 쉐이더를 검사
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// 프래그먼트 쉐이더를 컴파일
	printf("Compiling shader : %s\n", fragmentFilePath);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// 프래그먼트 쉐이더를 검사
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// 프로그램에 링크
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// 프로그램 검사
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

#define SOA

int main()
{
	initGLFW();
	initGLEW();

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// structure of array
#ifdef SOA
	static const GLfloat g_vertex_buffer_data[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
	};

	static const GLfloat g_color_data[] =
	{
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
	};

	GLuint programID = LoadShaders("vertex.glsl", "Image.glsl");
	glUseProgram(programID);

	// 버텍스 버퍼에 핸들
	GLuint vertexbuffer[2];
	// 버퍼를 생성
	glGenBuffers(2, vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
	// 버텍스들을 버퍼로 이동
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// 컬러 버퍼 생성
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);
	// 버텍스 컬러들을 버퍼로 이동
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_data), g_color_data, GL_STATIC_DRAW);
#else
	static const GLfloat g_vertex_buffer_data[] =
	{
		-0.5f, -0.5f, 0.0f, // v0
		1.0f, 1.0f, 1.0f, 1.0f,// c0
		0.5f, -0.5f, 0.0f, // v1
		1.0f, 0.0f, 0.0f, 1.0f,// c1
		-0.5f,  0.5f, 0.0f, // v2
		0.0f, 0.0f, 1.0f, 1.0f,// c2
		0.5f,  0.5f, 0.0f, // v3
		0.0f, 1.0f, 0.0f, 1.0f,// c3
	};

	GLuint programID = LoadShaders("vertex.glsl", "Image.glsl");
	glUseProgram(programID);
	GLuint vertexbuffer;
	// 버퍼를 생성
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// 버텍스들을 OpenGL로
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

#endif

	do
	{
		// drawing
		static const GLfloat blue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, blue);

#ifdef SOA
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);

		glVertexAttribPointer(
			0,                  // 0번째 속성(attribute).
			3,                  // 크기(size)
			GL_FLOAT,           // 타입(type)
			GL_FALSE,           // 정규화(normalized)?
			0,                  // 다음 요소 까지 간격(stride)
			(void*)0            // 배열 버퍼의 오프셋(offset; 옮기는 값)
		);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,                  // 0번째 속성(attribute).
			4,                  // 크기(size)
			GL_FLOAT,           // 타입(type)
			GL_FALSE,           // 정규화(normalized)?
			0,                  // 다음 요소 까지 간격(stride)
			(void*)0            // 배열 버퍼의 오프셋(offset; 옮기는 값)
		);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
#else
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		GLint offset = 0;

		glVertexAttribPointer(
			0,                  // 0번째 속성(attribute).
			3,                  // 크기(size)
			GL_FLOAT,           // 타입(type)
			GL_FALSE,           // 정규화(normalized)?
			sizeof(GLfloat) * 7,                  // 다음 요소 까지 간격(stride)
			(void*)offset            // 배열 버퍼의 오프셋(offset; 옮기는 값)
		);

		offset = sizeof(GLfloat) * 3;
		glVertexAttribPointer(
			1,                  // 0번째 속성(attribute).
			4,                  // 크기(size)
			GL_FLOAT,           // 타입(type)
			GL_FALSE,           // 정규화(normalized)?
			sizeof(GLfloat) * 7,                  // 다음 요소 까지 간격(stride)
			(void*)offset            // 배열 버퍼의 오프셋(offset; 옮기는 값)
		);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
#endif
		// swap buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glfwTerminate();
	return 0;
}