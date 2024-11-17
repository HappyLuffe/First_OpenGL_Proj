#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// out vec3 ourColor;
out vec3 outPos;

uniform float xOffset;
uniform float yOffset;

void main(){
	gl_Position = vec4(aPos.x + xOffset, aPos.y + yOffset, aPos.z, 1.0);
	outPos = vec3(abs(aPos.x + xOffset), abs(aPos.y + yOffset), aPos.z);
	// ourColor = aColor;
}