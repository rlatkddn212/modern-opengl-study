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

int main()
{
	glm::vec4 v1 = glm::vec4(1.0f, 2.0f, 3.0f, 1.0f);
	glm::vec4 v2 = glm::vec4(2.0f, 1.0f, -3.0f, 1.0f);

	// 단순한 사칙연산
	glm::vec4 v3 = v1 + v2;
	printf(" v1 + v2 = %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);
	v3 = v1 - v2;
	printf(" v1 - v2 = %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);
	v3 = v1 * v2;
	printf(" v1 * v2 = %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);
	v3 = v1 / v2;
	printf(" v1 / v2 = %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);


	// 내적의 경우 scale를 얻을 수있음
	float dot = glm::dot(v1, v2);
	printf(" dot(v1, v2) =%f\n", dot);
	

	// 외적의 경우 vector를 얻을 수 있다. 외적의 경우 3차원에서만 기하학적 의미를 갖는다.
	glm::vec3 v4 = glm::vec3(1.0f, 2.0f, 3.0f);
	glm::vec3 v5 = glm::vec3(2.0f, 1.0f, -3.0f);

	glm::vec3 v6 = glm::cross(v4, v5);
	printf(" cross(v4, v5) = %f, %f, %f\n", v6.x, v6.y, v6.z);

	// 반사 result = I - 2.0 * dot(N, I) * N
	// I는 입사 벡터, N은 매질의 노멀, result는 반사 벡터
	// 이 예제는 v1을 입사 벡터, v2를 매질로 두고 v3를 반사 벡터로 둔다.
	v3 = glm::reflect(v1, glm::normalize(v2));
	printf(" reflect(v1, v2) = %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);

	// 굴절도 마찬가지로 입사 벡터, 매질의 노멀을 입력으로 받고 추가로 굴절 비율이 필요하다.
	// 굴절된 벡터를 반환한다.
	float refractIndex = 0.6f;
	v3 = glm::refract(v1, glm::normalize(v2), refractIndex);
	printf(" refract(v1, v2) = %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);

	return 0;
}