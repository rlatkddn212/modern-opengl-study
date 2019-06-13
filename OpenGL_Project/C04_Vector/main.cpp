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

	// �ܼ��� ��Ģ����
	glm::vec4 v3 = v1 + v2;
	printf(" v1 + v2 = %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);
	v3 = v1 - v2;
	printf(" v1 - v2 = %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);
	v3 = v1 * v2;
	printf(" v1 * v2 = %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);
	v3 = v1 / v2;
	printf(" v1 / v2 = %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);


	// ������ ��� scale�� ���� ������
	float dot = glm::dot(v1, v2);
	printf(" dot(v1, v2) =%f\n", dot);
	

	// ������ ��� vector�� ���� �� �ִ�. ������ ��� 3���������� �������� �ǹ̸� ���´�.
	glm::vec3 v4 = glm::vec3(1.0f, 2.0f, 3.0f);
	glm::vec3 v5 = glm::vec3(2.0f, 1.0f, -3.0f);

	glm::vec3 v6 = glm::cross(v4, v5);
	printf(" cross(v4, v5) = %f, %f, %f\n", v6.x, v6.y, v6.z);

	// �ݻ� result = I - 2.0 * dot(N, I) * N
	// I�� �Ի� ����, N�� ������ ���, result�� �ݻ� ����
	// �� ������ v1�� �Ի� ����, v2�� ������ �ΰ� v3�� �ݻ� ���ͷ� �д�.
	v3 = glm::reflect(v1, glm::normalize(v2));
	printf(" reflect(v1, v2) = %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);

	// ������ ���������� �Ի� ����, ������ ����� �Է����� �ް� �߰��� ���� ������ �ʿ��ϴ�.
	// ������ ���͸� ��ȯ�Ѵ�.
	float refractIndex = 0.6f;
	v3 = glm::refract(v1, glm::normalize(v2), refractIndex);
	printf(" refract(v1, v2) = %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);

	return 0;
}