#version 330 core

in vec3 vColor;
out vec4 FragColor;

uniform float uTime;

void main()
{
	vec3 animated = vec3(
		sin(uTime) * 0.5 + 0.5,
		sin(uTime + 2.094) * 0.5 + 0.5, // 2.094~2pi/3
		sin(uTime + 4.188) * 0.5 + 0.5  // 4.188~4pi/3
	);
	FragColor = vec4(animated, 1.0);
}
