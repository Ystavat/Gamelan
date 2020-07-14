#version 330 core

in vec2 v_texCoord;
uniform sampler2D u_texture;
layout(location = 0) out vec4 color;

void main() {
	color = texture2D(u_texture, v_texCoord);
}
