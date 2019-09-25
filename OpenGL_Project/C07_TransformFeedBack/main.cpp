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

enum BUFFER_TYPE_t
{
	POSITION_A,
	POSITION_B,
	VELOCITY_A,
	VELOCITY_B,
	CONNECTION
};

enum
{
	POINTS_X = 10,
	POINTS_Y = 10,
	POINTS_TOTAL = (POINTS_X * POINTS_Y),
	CONNECTIONS_TOTAL = (POINTS_X - 1) * POINTS_Y + (POINTS_Y - 1) * POINTS_X
};

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
	window = glfwCreateWindow(1024, 768, "ShaderToy Viewer", NULL, NULL);

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

	if (vertexFilePath == "update.glsl")
	{
		static const char * tf_varyings[] =
		{
			"tf_position_mass",
			"tf_velocity"
		};

		glTransformFeedbackVaryings(ProgramID, 2, tf_varyings, GL_SEPARATE_ATTRIBS);
	}

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

	// 초기 위치
	glm::vec4 * initial_positions = new glm::vec4[POINTS_TOTAL];
	// 초기 속도
	glm::vec3 * initial_velocities = new glm::vec3[POINTS_TOTAL];
	// 버텍스 연결(스프링)
	glm::ivec4 * connection_vectors = new glm::ivec4[POINTS_TOTAL];

	int n = 0;

	for (int j = 0; j < POINTS_Y; j++)
	{
		float fj = (float)j / (float)POINTS_Y;
		for (int i = 0; i < POINTS_X; i++)
		{
			float fi = (float)i / (float)POINTS_X;

			initial_positions[n] = glm::vec4((fi - 0.5f) * (float)POINTS_X,
				0.0, (fj - 0.5f) * (float)POINTS_Y, 1.0f);
			initial_velocities[n] = glm::vec3(0.0f);

			connection_vectors[n] = glm::ivec4(-1);

			// 스프링 연결
			if (j != (POINTS_Y - 1))
			{
				if (i != 0)
					connection_vectors[n][0] = n - 1;

				if (j != 0)
					connection_vectors[n][1] = n - POINTS_X;

				if (i != (POINTS_X - 1))
					connection_vectors[n][2] = n + 1;

				if (j != (POINTS_Y - 1))
					connection_vectors[n][3] = n + POINTS_X;
			}

			n++;
		}
	}
	GLuint vaoID[2];
	GLuint vboID[5];
	glGenVertexArrays(2, vaoID);
	glGenBuffers(5, vboID);

	for (int i = 0; i < 2; i++) {
		glBindVertexArray(vaoID[i]);

		glBindBuffer(GL_ARRAY_BUFFER, vboID[POSITION_A + i]);
		glBufferData(GL_ARRAY_BUFFER, POINTS_TOTAL * sizeof(glm::vec4), initial_positions, GL_DYNAMIC_COPY);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vboID[VELOCITY_A + i]);
		glBufferData(GL_ARRAY_BUFFER, POINTS_TOTAL * sizeof(glm::vec3), initial_velocities, GL_DYNAMIC_COPY);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, vboID[CONNECTION]);
		glBufferData(GL_ARRAY_BUFFER, POINTS_TOTAL * sizeof(glm::ivec4), connection_vectors, GL_STATIC_DRAW);
		glVertexAttribIPointer(2, 4, GL_INT, 0, NULL);
		glEnableVertexAttribArray(2);
	}

	delete[] connection_vectors;
	delete[] initial_velocities;
	delete[] initial_positions;

	GLuint tboID[2];
	glGenTextures(2, tboID);
	glBindTexture(GL_TEXTURE_BUFFER, tboID[0]);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, vboID[POSITION_A]);
	glBindTexture(GL_TEXTURE_BUFFER, tboID[1]);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, vboID[POSITION_B]);

	int lines = (POINTS_X - 1) * POINTS_Y + (POINTS_Y - 1) * POINTS_X;

	// 인덱스를 만든다.
	GLuint iboID;
	glGenBuffers(1, &iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, lines * 2 * sizeof(int), NULL, GL_STATIC_DRAW);

	int * e = (int *)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, lines * 2 * sizeof(int), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	for (int j = 0; j < POINTS_Y; j++)
	{
		for (int i = 0; i < POINTS_X - 1; i++)
		{
			*e++ = i + j * POINTS_X;
			*e++ = 1 + i + j * POINTS_X;
		}
	}

	for (int i = 0; i < POINTS_X; i++)
	{
		for (int j = 0; j < POINTS_Y - 1; j++)
		{
			*e++ = i + j * POINTS_X;
			*e++ = POINTS_X + i + j * POINTS_X;
		}
	}

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

	GLuint updateShaderID = LoadShaders("update.glsl", "Image.glsl");
	GLuint renderShaderID = LoadShaders("vertex.glsl", "Image.glsl");

	float diffTime = 0;
	GLuint idx = 0;
	do
	{
		glUseProgram(updateShaderID);

		glEnable(GL_RASTERIZER_DISCARD);

		for (int i = 2; i != 0; --i)
		{
			glBindVertexArray(vaoID[idx & 1]);
			glBindTexture(GL_TEXTURE_BUFFER, tboID[idx & 1]);
			idx++;
			glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vboID[POSITION_A + (idx & 1)]);
			glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, vboID[VELOCITY_A + (idx & 1)]);
			glBeginTransformFeedback(GL_POINTS);
			glDrawArrays(GL_POINTS, 0, POINTS_TOTAL);
			glEndTransformFeedback();
		}

		glDisable(GL_RASTERIZER_DISCARD);

		static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

		glViewport(0, 0, 1024, 786);
		glClearBufferfv(GL_COLOR, 0, black);

		glUseProgram(renderShaderID);

		//if (draw_points)
		{
			glPointSize(4.0f);
			glDrawArrays(GL_POINTS, 0, POINTS_TOTAL);
		}

		//if (draw_lines)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
			glDrawElements(GL_LINES, CONNECTIONS_TOTAL * 2, GL_UNSIGNED_INT, NULL);
		}


		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glfwTerminate();
	return 0;
}