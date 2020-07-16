#version 330 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec3 a_color;
out vec4 v_color;

void main() {
	v_color = vec4(a_color, 1);
	//v_color = vec4(a_position.xy * 0.5 + 0.5, 0, 1);
	gl_Position = vec4(a_position, 0, 2);
}
