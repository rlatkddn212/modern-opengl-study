#version 410 core

// xyz는 위치 w는 질량
layout(location = 0) in vec4 position_mass;
// 버텍스의 현재 속도
layout(location = 1) in vec3 velocity;
// 연결 벡터
layout(location = 2) in ivec4 connection;

// TBO
uniform samplerBuffer tex_position;

//  버텍스 쉐이더의 feedback 데이터 출력
out vec4 tf_position_mass;
out vec3 tf_velocity;

// 시간 간격
uniform float t = 0.07;

// 스프링 상수
uniform float k = 7.1;

// 중력
const vec3 gravity = vec3(0.0, -0.08, 0.0);

// 댐핑 상수
uniform float c = 1.8;

// 스프링 정지 길이
uniform float rest_length = 0.88;

void main(void)
{
	vec3 p = position_mass.xyz;    // 위치
	float m = position_mass.w;     // 질량
	vec3 u = velocity;             // 초기 속도
	vec3 F = gravity * m - c * u;  // 힘 = 중력 * 질량 - 댐핑 상수 * 속도
	bool fixed_node = true;        // 힘이 적용될 때 false가 된다.

	for (int i = 0; i < 4; i++) 
	{
		if (connection[i] != -1) 
		{
			// q는 다른 버텍스의 위치
			vec3 q = texelFetch(tex_position, connection[i]).xyz;
			// 현재 위치 - 다른 위치
			vec3 d = q - p;
			// 거리 x
			float x = length(d);
			// 힘을 누적시킨다. 힘 += - 스프링 상수 * (스프링 정지 길이 - 다른 위치까지 거리) * 방향
			F += -k * (rest_length - x) * normalize(d);
			fixed_node = false;
		}
	}

	// If this is a fixed node, reset force to zero
	if (fixed_node)
	{
		F = vec3(0.0);
	}

	// F = ma
	vec3 a = F / m;

	// 거리 = vt + 1/2at^2
	vec3 s = u * t + 0.5 * a * t * t;

	// 속도 = 초기속도 + 가속도 * 시간
	vec3 v = u + a * t;

	// 이동 크기를 제한한다.
	s = clamp(s, vec3(-25.0), vec3(25.0));

	// 피드백~ p + s 현재 위치에 s를 추가함
	tf_position_mass = vec4(p + s, m);
	tf_velocity = v;
}
