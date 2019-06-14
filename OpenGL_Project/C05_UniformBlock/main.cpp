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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

GLFWwindow* window;
GLint width;
GLint height;

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
	width = 1024;
	height = 768;
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

int main()
{
	initGLFW();
	initGLEW();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// 책 소스코드에서 가져온 데이터
	static const GLushort vertex_indices[] =
	{
		0, 1, 2,
		2, 1, 3,
		2, 3, 4,
		4, 3, 5,
		4, 5, 6,
		6, 5, 7,
		6, 7, 0,
		0, 7, 1,
		6, 0, 2,
		2, 4, 6,
		7, 5, 3,
		7, 3, 1
	};

	static const GLfloat vertex_positions[] =
	{
		-0.25f, -0.25f, -0.25f,
		-0.25f,  0.25f, -0.25f,
		 0.25f, -0.25f, -0.25f,
		 0.25f,  0.25f, -0.25f,
		 0.25f, -0.25f,  0.25f,
		 0.25f,  0.25f,  0.25f,
		-0.25f, -0.25f,  0.25f,
		-0.25f,  0.25f,  0.25f,
	};

	// 버텍스 버퍼에 핸들
	GLuint vertexbuffer[2];
	// 버퍼를 생성
	glGenBuffers(2, vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
	// 버텍스들을 OpenGL로
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexbuffer[1]);
	// 버텍스들을 OpenGL로
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

	GLuint programID = LoadShaders("vertex.glsl", "Image.glsl");
	glUseProgram(programID);

	// 블록과 쉐이더 블록간에 binding 을 한다.
	GLuint matrices = glGetUniformBlockIndex(programID, "Matrices");
	glUniformBlockBinding(programID, matrices, 0);

	unsigned int uboMatrices;
	glGenBuffers(1, &uboMatrices);

	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

	float aspect = (float)width / (float)height;

	glm::mat4 perspectMat = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 1000.0f);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &perspectMat[0][0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	do
	{
		double t = glfwGetTime();
		glViewport(0, 0, width, height);

		// drawing
		static const GLfloat blue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		static const GLfloat one = 1.0f;
		glClearBufferfv(GL_COLOR, 0, blue);
		glClearBufferfv(GL_DEPTH, 0, &one);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexbuffer[1]);

		glVertexAttribPointer(
			0,                  // 0번째 속성(attribute).
			3,                  // 크기(size)
			GL_FLOAT,           // 타입(type)
			GL_FALSE,           // 정규화(normalized)?
			0,                  // 다음 요소 까지 간격(stride)
			(void*)0            // 배열 버퍼의 오프셋(offset; 옮기는 값)
		);

		float f = (float)t * 0.3f;
		glm::mat4 transformMat = glm::rotate(glm::mat4(1.f), (float)t * 0.3f, glm::vec3(1.0f, 0.0f, 0.0f));
		transformMat = glm::rotate(glm::mat4(1.f), (float)t * 0.8f, glm::vec3(0.0f, 1.0f, 0.0f)) * transformMat;
		transformMat = glm::translate(glm::mat4(1.f), glm::vec3(sinf(2.1f * f) * 0.5f, cosf(1.7f * f) * 0.5f, sinf(1.3f * f) * cosf(1.5f * f) * 2.0f)) *transformMat;
		transformMat = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, -4.0f)) * transformMat;
		
		glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &transformMat[0][0]);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
		glDisableVertexAttribArray(0);

		// swap buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glfwTerminate();
	return 0;
}