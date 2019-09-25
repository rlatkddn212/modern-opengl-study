#version 410 core

// xyz�� ��ġ w�� ����
layout(location = 0) in vec4 position_mass;
// ���ؽ��� ���� �ӵ�
layout(location = 1) in vec3 velocity;
// ���� ����
layout(location = 2) in ivec4 connection;

// TBO
uniform samplerBuffer tex_position;

//  ���ؽ� ���̴��� feedback ������ ���
out vec4 tf_position_mass;
out vec3 tf_velocity;

// �ð� ����
uniform float t = 0.07;

// ������ ���
uniform float k = 7.1;

// �߷�
const vec3 gravity = vec3(0.0, -0.08, 0.0);

// ���� ���
uniform float c = 1.8;

// ������ ���� ����
uniform float rest_length = 0.88;

void main(void)
{
	vec3 p = position_mass.xyz;    // ��ġ
	float m = position_mass.w;     // ����
	vec3 u = velocity;             // �ʱ� �ӵ�
	vec3 F = gravity * m - c * u;  // �� = �߷� * ���� - ���� ��� * �ӵ�
	bool fixed_node = true;        // ���� ����� �� false�� �ȴ�.

	for (int i = 0; i < 4; i++) 
	{
		if (connection[i] != -1) 
		{
			// q�� �ٸ� ���ؽ��� ��ġ
			vec3 q = texelFetch(tex_position, connection[i]).xyz;
			// ���� ��ġ - �ٸ� ��ġ
			vec3 d = q - p;
			// �Ÿ� x
			float x = length(d);
			// ���� ������Ų��. �� += - ������ ��� * (������ ���� ���� - �ٸ� ��ġ���� �Ÿ�) * ����
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

	// �Ÿ� = vt + 1/2at^2
	vec3 s = u * t + 0.5 * a * t * t;

	// �ӵ� = �ʱ�ӵ� + ���ӵ� * �ð�
	vec3 v = u + a * t;

	// �̵� ũ�⸦ �����Ѵ�.
	s = clamp(s, vec3(-25.0), vec3(25.0));

	// �ǵ��~ p + s ���� ��ġ�� s�� �߰���
	tf_position_mass = vec4(p + s, m);
	tf_velocity = v;
}
