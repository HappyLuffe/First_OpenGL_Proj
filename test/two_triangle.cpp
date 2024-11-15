#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource =
"#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
"}\0";

const char* vertexShaderSource_2 =
"#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"	vertexColor = aColor;\n"
"}\0";

const char* fragmentShaderSource =
"#version 460 core\n"
"out vec4 FragColor;\n"
"in vec3 vertexColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(vertexColor, 1.0f);\n"
"}\n\0";

const char* fragmentShaderSource_2 =
"#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.5f, 0.0f, 0.2f, 1.0f);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_HEIGHT, SCR_WIDTH, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ����������ɫ��
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// �ж���ɫ���Ƿ����ɹ�
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ����������ɫ��2
	unsigned int vertexShader_2 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader_2, 1, &vertexShaderSource_2, NULL);
	glCompileShader(vertexShader_2);

	// �ж���ɫ���Ƿ����ɹ�
	glGetShaderiv(vertexShader_2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader_2, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ����Ƭ����ɫ��
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	

	// ����Ƭ����ɫ��2
	unsigned int fragmentShader_2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_2, 1, &fragmentShaderSource_2, NULL);
	glCompileShader(fragmentShader_2);

	glGetShaderiv(fragmentShader_2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader_2, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ������ɫ������
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader_2);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	unsigned int shaderProgram_2 = glCreateProgram();
	glAttachShader(shaderProgram_2, vertexShader);
	glAttachShader(shaderProgram_2, fragmentShader_2);
	glLinkProgram(shaderProgram_2);



	// ������Ӵ���
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// ���ӳɹ���ɾ����ɫ������
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	/*
		* �����������Vertex Array Object��VAO
		* ���㻺�����Vertex Buffer Object��VBO
		* Ԫ�ػ������Element Buffer Object��EBO �� ����������� Index Buffer Object��IBO
		*/
	float firstVertices[] = {
		 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	float secondVertices[] = {
		 0.0f, -0.5f, 0.0f,
		 0.5f, 0.5f, 0.0f,
		 1.0f, -0.5f, 0.0f
	};
	

	/*
	* һ�����������Ƕ����������ú�Ӧʹ�õ�VBO�Ķ����������һ�㵱�������ƶ������ʱ����
	* ����Ҫ����/�������е�VAO���ͱ����VBO������ָ��)��Ȼ�󴢴����ǹ�����ʹ�á������Ǵ����
	* �������ʱ����ó���Ӧ��VAO��������������������ٽ��VAO��
	*/
	unsigned int VBOs[2], VAOs[2], EBO;
	// ���ٻ���ռ�
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	// װ�ػ���
	glBindVertexArray(VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstVertices), firstVertices, GL_STATIC_DRAW);

	// ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// װ�ػ���
	glBindVertexArray(VAOs[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondVertices), secondVertices, GL_STATIC_DRAW);

	// ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind
	glBindVertexArray(0); // unbind



	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		// ����
		processInput(window);

		// ��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		glUseProgram(shaderProgram);
		// ����uniform��ɫ
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/

		// ����������
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram_2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// �������岢��ѯIO�¼�
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}