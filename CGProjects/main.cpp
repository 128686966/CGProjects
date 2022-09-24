#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <numbers>
#include <random>
#include "Utils.h"
#include <roamer_engine/display/ShaderProgram.h>
#include <roamer_engine/display/MeshRenderer.h>

using namespace std;

//ȫ�ֱ���
qy::cg::ShaderProgram renderingProgram;
qy::cg::MeshRenderer* meshRenderer;
qy::cg::MeshRenderer* meshRenderer2;

constexpr int numDiv = 36;
constexpr float r1 = 0.4f, r2 = 0.7f;

//������ɫ������ʼ������
void init(GLFWwindow* window)
{
	meshRenderer = new qy::cg::MeshRenderer();
	meshRenderer2 = new qy::cg::MeshRenderer();
	renderingProgram = qy::cg::ShaderProgram("vertShader.glsl", "fragShader.glsl");
	meshRenderer->setShader(renderingProgram);
	meshRenderer2->setShader(renderingProgram);

	auto&& mesh = meshRenderer->getMesh();
	mesh.setVertices({{0.0f, 0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}});
	mesh.setColors({{1.0f, 0.0f, 0.0f,1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}});
	mesh.setTriangles({0, 1, 2});
	auto&& mesh2 = meshRenderer2->getMesh();
	mesh2.setVertices({{0.5f, 0.5f, 0.0f}, {0.0f, -0.5f, 0.0f}, {1.0f, -0.5f, 0.0f}});
	mesh2.setColors({{1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 0.5f}});
	mesh2.setTriangles({0, 1, 2});
}
//��������
void display(GLFWwindow* window, double currentTime)
{
	glClearColor(0.5f, 0.8f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	meshRenderer->render();
	meshRenderer2->render();
}

int main(void)
{
	//glfw��ʼ��
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	//���ڰ汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //�ΰ汾��

	//��������
	GLFWwindow* window = glfwCreateWindow(800, 800, "Not simple", NULL, NULL);
	glfwMakeContextCurrent(window);
	//���û���ˢ��ʱ��
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)//glew��ʼ��
	{
		exit(EXIT_FAILURE);
	}

	//������ɫ���������Ͱ�VAO��VBO
	init(window);

	//�¼�ѭ�������������¼�
	while (!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime()); //���ƺ���������
		glfwSwapBuffers(window); //������ɫ����
		glfwPollEvents(); // �����û�д���ʲô�¼�������������롢����ƶ��ȣ�
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}