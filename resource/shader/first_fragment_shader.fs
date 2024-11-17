#version 460 core
// in vec3 ourColor;
in vec3 outPos;
out vec4 FragColor;
void main(){
	FragColor = vec4(outPos, 1.0f);
}