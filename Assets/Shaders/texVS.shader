#version 330 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_texCoord;
out vec2 v_texCoord;

void main() {
	v_texCoord = vec2(a_texCoord.x, 1-a_texCoord.y);
	gl_Position = vec4(a_position, 0, 2);
}
