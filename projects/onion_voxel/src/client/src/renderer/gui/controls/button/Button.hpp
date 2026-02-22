#pragma once

#include "../../../texture/texture.hpp"
#include "../../GuiElement.hpp"

#include <Event.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace onion::voxel
{
	class Button : public GuiElement
	{
	  public:
		Button(const std::string& name);
		~Button();

		void Render();

		void Initialize();
		void Delete();

		void SetText(const std::string& text);
		std::string GetText() const;

		void SetSize(const glm::vec2& size);
		glm::vec2 GetSize() const;

		void SetPosition(double posX, double posY);
		void SetPosition(const glm::vec2& pos);
		glm::vec2 GetPosition() const;

		bool IsEnabled() const;
		void SetEnabled(bool enabled);

		void SetScaleUpOnHover(bool scaleUp);

		// Events
	  public:
		Event<const Button&> OnClick;
		Event<const Button&> OnHover;
		Event<const Button&> OnUnhover;

	  private:
		bool IsHovered() const;

		void GenerateBuffers();
		void DeleteBuffers();
		void InitBuffers();

	  private:
		std::string m_Text;
		bool m_IsEnabled = true;
		bool m_ScaleUpOnHover = true;

		glm::vec2 m_Position{0, 0};
		glm::vec2 m_Size{1, 1};

		static Texture s_Texture;
		static Texture s_TextureDisabled;
		static Texture s_TextureHighlighted;

		struct Vertex
		{
			float posX, posY, posZ;
			float texX, texY;
		};

		static std::vector<Vertex> s_Vertices;
		static std::vector<unsigned int> s_Indices;

		GLuint m_VAO = 0;
		GLuint m_VBO = 0;
		GLuint m_EBO = 0;

		bool m_WasHovered = false;
		bool m_WasClicked = false;
	};
} // namespace onion::voxel
