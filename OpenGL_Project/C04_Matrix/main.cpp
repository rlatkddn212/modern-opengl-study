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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

void printMat(glm::mat4& mt)
{
	for (int i = 0; i < mt.length(); ++i)
	{
		cout << "{ ";
		for (int j = 0; j < mt[i].length(); ++j)
		{
			cout << " " << mt[i][j] << ",";
		}
		cout << "}\n";
	}
}

int main()
{
	glm::mat4 mt01 = { {1,2,3,4 }, {4,3,2,1}, {1,2,3,4}, {4,3,2,1} };
	glm::mat4 mt02 = { {5,6,7,8 }, {4,3,2,1}, {1,2,3,4}, {8,7,6,5} };
	
	// 행렬 덧셈
	cout << "행렬 덧셈\n";
	glm::mat4 mt03 = mt01 + mt02;
	printMat(mt03);

	// 행렬 곱셈
	cout << "행렬 곱셈\n";
	mt03 = mt01 * mt02;
	printMat(mt03);

	// 동차 좌표 변환을 사용하려면 w가 1이어야함
	glm::vec4 v = glm::vec4(1.0, 2.0, 3.0, 1.0);
	printf("벡터 : %f %f %f %f 에 대한 좌표계 변환\n", v.x, v.y, v.z, v.w);
	// 이동 행렬

	// x로 10만큼 이동
	glm::mat4 translation_matrix = glm::translate(glm::mat4(1.f), glm::vec3(10.f, 0.f, 0.f));
	//glm::mat4  = glm::translate(glm::mat4(1), glm::vec3(10, 0, 0));
	// 이동 행렬
	cout << "이동 행렬\n";
	printMat(translation_matrix);
	v = translation_matrix * v;
	printf("이동 변환 결과 벡터 : %f %f %f %f\n", v.x, v.y, v.z, v.w);

	glm::mat4 rotate_matrix = glm::rotate(glm::mat4(1.f), 90.f, glm::vec3(0.f, 0.f, 1.f));
	cout << "회전 행렬\n";
	printMat(rotate_matrix);
	v = rotate_matrix * v;
	printf("회전 변환 결과 벡터 : %f %f %f %f\n", v.x, v.y, v.z, v.w);

	return 0;
}