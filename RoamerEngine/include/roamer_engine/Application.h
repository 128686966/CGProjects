#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <string_view>
#include "display/Shaders.h"

namespace qy::cg {

	class Application {

	public:
		static int VERSION_MAJOR;
		static int VERSION_MINOR;


	private:
		GLFWwindow* window;

	public:
		Application() {
			//glfw��ʼ��
			if (!glfwInit()) {
				std::exit(EXIT_FAILURE);
			}
			//���ڰ汾
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR); //���汾��
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR); //�ΰ汾��
			window = nullptr;
		}

		~Application() {
			if (window) glfwDestroyWindow(window);
			glfwTerminate();
			exit(EXIT_SUCCESS);
		}

		Application* createWindow(int width, int height, std::string_view title) {
			window = glfwCreateWindow(800, 800, title.data(), nullptr, nullptr);
			glfwMakeContextCurrent(window);
			//���û���ˢ��ʱ��
			glfwSwapInterval(1);
			//glew��ʼ��
			if (glewInit() != GLEW_OK) {
				exit(EXIT_FAILURE);
			}
			return this;
		}

		Application* run() {
			internal_init();
			init();
			//�¼�ѭ�������������¼�
			while (!glfwWindowShouldClose(window)) {
				display(); //���ƺ���������
				glfwSwapBuffers(window); //������ɫ����
				glfwPollEvents(); // �����û�д���ʲô�¼�������������롢����ƶ��ȣ�
			}
			return this;
		}

	private:
		void internal_init() {
			Shaders::__INIT__();
		}

	protected:

		virtual void init() = 0;
		virtual void display() = 0;
	};
}

int qy::cg::Application::VERSION_MAJOR = 4;
int qy::cg::Application::VERSION_MINOR = 3;