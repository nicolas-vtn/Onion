#pragma once

#include "../../GuiElement.hpp"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../../../texture/texture.hpp"

namespace onion::voxel
{
	class Button : public GuiElement
	{
	  public:
		Button(const std::string& name) : GuiElement(name) {};
		~Button() {};

		void Render() const
		{
			glm::vec2 updatedSize = m_Size;
			glm::vec2 updatedPos = m_Position;
			bool hovered = IsHovered();

			if (hovered)
			{
				float scaleFactor = 1.05f;
				updatedSize *= scaleFactor;

				// Offset so scaling happens from center
				glm::vec2 delta = updatedSize - m_Size;
				updatedPos -= delta * 0.5f;
			}

			glm::vec2 uRatio((float) m_Texture.GetWidth(), (float) m_Texture.GetHeight());
			uRatio = glm::normalize(uRatio);

			m_ShaderSprites.Use();
			m_ShaderSprites.setVec2("uPos", updatedPos.x, updatedPos.y);
			m_ShaderSprites.setVec2("uSize", updatedSize.x, updatedSize.y);

			glActiveTexture(GL_TEXTURE0);
			m_Texture.Bind();

			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		void Initialize()
		{
			GenerateBuffers();
			InitBuffers();
			SetInitState(true);
		}

		void Delete()
		{
			DeleteBuffers();
			SetDeletedState(true);
		}

	  public:
		void SetText(const std::string& text) { m_Text = text; }
		std::string GetText() const { return m_Text; }

		void SetSize(const glm::vec2& size) { m_Size = size; }
		glm::vec2 GetSize() const { return m_Size; }

		void SetPosition(double posX, double posY) { m_Position = {posX, posY}; }
		void SetPosition(const glm::vec2& pos) { m_Position = {pos.x, pos.y}; }
		glm::vec2 GetPosition() const { return m_Position; }

	  private:
		std::string m_Text;

		glm::vec2 m_Position{0, 0};
		glm::vec2 m_Size{1, 1};

		Texture m_Texture{(GetAssetsPath() / "minecraft/textures/gui/sprites/widget/button.png").string().c_str()};

		struct Vertex
		{
			float posX, posY, posZ, texX, texY;
		};

	  private:
		static inline std::vector<Vertex> m_Vertices = {
			{0.f, 0.f, 0.f, 0.f, 0.f}, {1.f, 0.f, 0.f, 1.f, 0.f}, {1.f, 1.f, 0.f, 1.f, 1.f}, {0.f, 1.f, 0.f, 0.f, 1.f}};

		static inline std::vector<unsigned int> m_Indices = {
			0,
			1,
			2, // First triangle
			2,
			3,
			0 // Second triangle
		};

	  private:
		GLuint m_VAO = 0;
		GLuint m_VBO = 0;
		GLuint m_EBO = 0;

		void GenerateBuffers()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			glGenBuffers(1, &m_EBO);
		}

		void DeleteBuffers()
		{
			glDeleteVertexArrays(1, &m_VAO);
			glDeleteBuffers(1, &m_VBO);
			glDeleteBuffers(1, &m_EBO);
			m_VAO = 0;
			m_VBO = 0;
			m_EBO = 0;
		}

		void InitBuffers()
		{
			glBindVertexArray(m_VAO);

			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(
				GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), m_Indices.data(), GL_STATIC_DRAW);
			// Position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, posX));
			glEnableVertexAttribArray(0);

			// Texture coordinate attribute
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texX));
			glEnableVertexAttribArray(1);

			glBindVertexArray(0);
		}

		bool IsHovered() const
		{
			int mouseX = GetMouseX();
			int mouseY = GetMouseY();
			bool hovered = mouseX >= m_Position.x && mouseX <= m_Position.x + m_Size.x && mouseY >= m_Position.y &&
				mouseY <= m_Position.y + m_Size.y;

			std::cout << "Mouse Position: (" << mouseX << ", " << mouseY << ") - Button Position: (" << m_Position.x
					  << ", " << m_Position.y << ") - Button Size: (" << m_Size.x << ", " << m_Size.y
					  << ") - Hovered: " << (hovered ? "Yes" : "No") << std::endl;

			return hovered;
		}
	};
}; // namespace onion::voxel
