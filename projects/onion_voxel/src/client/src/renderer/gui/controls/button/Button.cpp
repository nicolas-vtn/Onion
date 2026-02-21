#include "Button.hpp"

#include <iostream>

namespace onion::voxel
{

	// -------- Static Data --------

	std::vector<Button::Vertex> Button::m_Vertices = {
		{0.f, 0.f, 0.f, 0.f, 0.f}, {1.f, 0.f, 0.f, 1.f, 0.f}, {1.f, 1.f, 0.f, 1.f, 1.f}, {0.f, 1.f, 0.f, 0.f, 1.f}};

	std::vector<unsigned int> Button::m_Indices = {0, 1, 2, 2, 3, 0};

	// -------- Constructor --------

	Button::Button(const std::string& name)
		: GuiElement(name),
		  m_Texture((GetAssetsPath() / "minecraft/textures/gui/sprites/widget/button.png").string().c_str())
	{
	}

	Button::~Button() {}

	// -------- Public API --------

	void Button::Render()
	{
		glm::vec2 updatedSize = m_Size;
		glm::vec2 updatedPos = m_Position;

		if (IsHovered())
		{
			if (!m_WasHovered)
			{
				std::cout << "Button '" << GetName() << "' hovered!" << std::endl;
				OnHover.Trigger(*this);
			}

			float scaleFactor = 1.05f;
			updatedSize *= scaleFactor;

			glm::vec2 delta = updatedSize - m_Size;
			updatedPos -= delta * 0.5f;

			// Check if it's clicked
			if (m_InputsSnapshot->Mouse.LeftButtonPressed && !m_WasClicked)
			{
				std::cout << "Button '" << GetName() << "' clicked!" << std::endl;
				OnClick.Trigger(*this);
				m_WasClicked = true;
			}
			else if (!m_InputsSnapshot->Mouse.LeftButtonPressed)
			{
				m_WasClicked = false;
			}

			m_WasHovered = true;
		}
		else
		{
			if (m_WasHovered)
			{
				std::cout << "Button '" << GetName() << "' unhovered!" << std::endl;
				OnUnhover.Trigger(*this);
			}
			m_WasHovered = false;
		}

		m_ShaderSprites.Use();
		m_ShaderSprites.setVec2("uPos", updatedPos.x, updatedPos.y);
		m_ShaderSprites.setVec2("uSize", updatedSize.x, updatedSize.y);
		m_ShaderSprites.setInt("uTexture", 0);

		glActiveTexture(GL_TEXTURE0);
		m_Texture.Bind();

		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Render text centered in the button
		if (!m_Text.empty())
		{
			m_TextFont.RenderText(m_Text, 100, 200, 5.0f, {0.f, 1.f, 1.f});
		}
	}

	void Button::Initialize()
	{
		GenerateBuffers();
		InitBuffers();
		SetInitState(true);
	}

	void Button::Delete()
	{
		DeleteBuffers();
		SetDeletedState(true);
	}

	void Button::SetText(const std::string& text)
	{
		m_Text = text;
	}

	std::string Button::GetText() const
	{
		return m_Text;
	}

	void Button::SetSize(const glm::vec2& size)
	{
		m_Size = size;
	}

	glm::vec2 Button::GetSize() const
	{
		return m_Size;
	}

	void Button::SetPosition(double posX, double posY)
	{
		m_Position = {static_cast<float>(posX), static_cast<float>(posY)};
	}

	void Button::SetPosition(const glm::vec2& pos)
	{
		m_Position = pos;
	}

	glm::vec2 Button::GetPosition() const
	{
		return m_Position;
	}

	// -------- Hover Logic --------

	bool Button::IsHovered() const
	{
		if (!m_InputsSnapshot)
		{
			return false;
		}

		int mouseX = m_InputsSnapshot->Mouse.Xpos;
		int mouseY = m_InputsSnapshot->Mouse.Ypos;

		bool hovered = mouseX >= m_Position.x && mouseX <= m_Position.x + m_Size.x && mouseY >= m_Position.y &&
			mouseY <= m_Position.y + m_Size.y;

		return hovered;
	}

	// -------- OpenGL Buffer Setup --------

	void Button::GenerateBuffers()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);
	}

	void Button::DeleteBuffers()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);

		m_VAO = 0;
		m_VBO = 0;
		m_EBO = 0;
	}

	void Button::InitBuffers()
	{
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), m_Indices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, posX));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texX));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

} // namespace onion::voxel
