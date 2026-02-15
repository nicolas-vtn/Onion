#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <atomic>
#include <stop_token>
#include <string>
#include <thread>

namespace onion::voxel
{
	class Renderer
	{
	  public:
		Renderer();
		~Renderer();

		void Start();
		void Stop();

		bool IsRunning() const noexcept;

	  private:
		void InitWindow();
		void InitOpenGlState();
		void CleanupOpenGl();

		std::atomic_bool m_IsRunning{false};
		void RenderThreadFunction(std::stop_token st);
		std::jthread m_ThreadRenderer;

		//GLFW
	  private:
		GLFWwindow* m_Window = nullptr;
		int m_WindowWidth = 800;
		int m_WindowHeight = 600;
		std::string m_WindowTitle = "Onion Voxel";

	  private:
		double m_DeltaTime = 0.0f;
		double m_LastFrame = 0.0f;
	};

}; // namespace onion::voxel
