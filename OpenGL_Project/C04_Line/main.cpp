// OpenGL 빌드 템플릿 입니다.
// http://www.opengl-tutorial.org 을 참고 했습니다.


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

glm::vec3 bezier(glm::vec3 A, glm::vec3 B, glm::vec3 C, GLfloat t)
{
	glm::vec3 Q1 = glm::mix(A, B, t);
	glm::vec3 Q2 = glm::mix(B, C, t);

	return glm::mix(Q1, Q2, t);
}

void renderLine(glm::vec3* ptr, GLint lineCnt, GLfloat* color, GLuint buffer)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, lineCnt * 3 * sizeof(GLfloat), ptr, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		0,                  // 0번째 속성(attribute).
		3,                  // 크기(size)
		GL_FLOAT,           // 타입(type)
		GL_FALSE,           // 정규화(normalized)?
		0,                  // 다음 요소 까지 간격(stride)
		(void*)0            // 배열 버퍼의 오프셋(offset; 옮기는 값)
	);

	glVertexAttrib4fv(1, color);

	glDrawArrays(GL_LINE_STRIP, 0, lineCnt);
	glDisableVertexAttribArray(0);

}


int main()
{
	initGLFW();
	initGLEW();

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glm::vec3 A = glm::vec3(-0.5f, -0.5f, 0.0f);
	glm::vec3 B = glm::vec3(0.0f, 0.5f, 0.0f);
	glm::vec3 C = glm::vec3(0.5f, -0.5f, 0.0f);

	GLfloat color[] =
	{
		1.0f, 1.f, 1.0f, 1.0f
	};

	GLfloat color2[] =
	{
		1.0f, 0.f, 0.0f, 1.0f
	};

	GLfloat color3[] =
	{
		0.0f, 1.f, 0.0f, 1.0f
	};


	GLuint programID = LoadShaders("vertex.glsl", "Image.glsl");
	glm::vec3 line[2];
	line[0] = A; line[1] = B;
	GLuint bufferID01;
	glGenBuffers(1, &bufferID01);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID01);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), line, GL_STATIC_DRAW);
	
	GLuint bufferID02;
	glGenBuffers(1, &bufferID02);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID02);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), line, GL_STATIC_DRAW);

	GLuint bufferID03;
	glGenBuffers(1, &bufferID03);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID03);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), line, GL_STATIC_DRAW);

	GLuint bufferID04;
	glGenBuffers(1, &bufferID04);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID04);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), line, GL_STATIC_DRAW);
	
	glUseProgram(programID);
	
	glm::vec3 curvedLine[1000];
	curvedLine[0] = A;
	GLint curvedLineCnt = 1;
	GLfloat prevTT = 0;
	double prevT = 0;
	do
	{
		double t = glfwGetTime() / 2;
		float second = (float)((unsigned)(t * 100) % 100);
		float tt = (second) / 100.0;

		if (tt < prevTT)
		{
			curvedLine[0] = A;
			curvedLineCnt = 1;
		}

		// drawing
		static const GLfloat blue[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, blue);
		
		line[0] = A; line[1] = B;
		renderLine(line, 2, color, bufferID01);
		line[0] = B; line[1] = C;
		renderLine(line, 2, color, bufferID02);
		
		glm::vec3 Q1 = glm::mix(A, B, tt);
		glm::vec3 Q2 = glm::mix(B, C, tt);
		line[0] = Q1; line[1] = Q2;
		renderLine(line, 2, color2, bufferID03);

		if (prevT + 0.01 < t)
		{
			prevT = t;
			//cout << curvedLineCnt << '\n';
			glm::vec3 newPoint = bezier(A, B, C, tt);
			curvedLine[curvedLineCnt++] = newPoint;
		}

		renderLine(curvedLine, curvedLineCnt, color3, bufferID04);
		prevTT = tt;
		
		// swap buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glfwTerminate();
	return 0;
}