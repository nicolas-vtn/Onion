#pragma once

#include <atomic>
#include <cassert>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../shader/shader.hpp"

namespace onion::voxel
{
	class GuiElement
	{
	  public:
		GuiElement(const std::string& name) : m_Name(name) {};

		virtual void Render() const = 0;
		virtual void Initialize() = 0;
		virtual void Delete() = 0;

		virtual ~GuiElement()
		{
			if (m_HasBeenInit.load() && !m_HasBeenDeleted.load())
			{
				std::string errorMessage = "The GuiElement '" + m_Name +
					"' destructor have before called before the function 'GuiElement::Delete'";
				std::cerr << errorMessage << std::endl;
				assert(false);
			}
		}

	  public:
		std::string GetName() const { return m_Name; };
		void SetName(const std::string& name) { m_Name = name; };

	  public:
		static void SetScreenSize(int screenWidth, int screenHeight)
		{
			m_ScreenWidth = screenWidth;
			m_ScreenHeight = screenHeight;

			m_ProjectionMatrix = glm::ortho(0.0f, (float) screenWidth, (float) screenHeight, 0.0f, -1.0f, 1.0f);
			m_ShaderSprites.Use();
			m_ShaderSprites.setMat4("uProjection", m_ProjectionMatrix);
		}

		static void SetMousePosition(int mouseX, int mouseY)
		{
			m_MouseX = mouseX;
			m_MouseY = mouseY;
		}

		static int GetMouseX() { return m_MouseX; }
		static int GetMouseY() { return m_MouseY; }

	  protected:
		void SetInitState(bool state) { m_HasBeenInit.store(state); };
		void SetDeletedState(bool state) { m_HasBeenDeleted.store(state); };

	  protected:
		inline static Shader m_ShaderSprites{(GetAssetsPath() / "shaders/sprite.vert").string().c_str(),
											 (GetAssetsPath() / "shaders/sprite.frag").string().c_str()};

	  private:
		std::string m_Name;

		std::atomic_bool m_HasBeenInit{false};
		std::atomic_bool m_HasBeenDeleted{false};

		static inline glm::mat4 m_ProjectionMatrix{1.f};
		static inline int m_ScreenWidth = 800;
		static inline int m_ScreenHeight = 600;

		static inline int m_MouseX = 0;
		static inline int m_MouseY = 0;
	};
}; // namespace onion::voxel
