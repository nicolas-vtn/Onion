#include "GuiElement.hpp"

#include <cassert>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

namespace onion::voxel
{

	// -------- Static Member Definitions --------

	Shader GuiElement::m_ShaderSprites((GetAssetsPath() / "shaders/sprite.vert").string().c_str(),
									   (GetAssetsPath() / "shaders/sprite.frag").string().c_str());

	glm::mat4 GuiElement::m_ProjectionMatrix{1.0f};
	int GuiElement::m_ScreenWidth = 800;
	int GuiElement::m_ScreenHeight = 600;

	std::shared_ptr<InputsSnapshot> GuiElement::m_InputsSnapshot = nullptr;

	// -------- Constructor / Destructor --------

	GuiElement::GuiElement(const std::string& name) : m_Name(name) {}

	GuiElement::~GuiElement()
	{
		if (m_HasBeenInit.load() && !m_HasBeenDeleted.load())
		{
			std::string errorMessage =
				"The GuiElement '" + m_Name + "' destructor was called before GuiElement::Delete()";

			std::cerr << errorMessage << std::endl;
			assert(false);
		}
	}

	// -------- Public API --------

	std::string GuiElement::GetName() const
	{
		return m_Name;
	}

	void GuiElement::SetName(const std::string& name)
	{
		m_Name = name;
	}

	void GuiElement::SetScreenSize(int screenWidth, int screenHeight)
	{
		m_ScreenWidth = screenWidth;
		m_ScreenHeight = screenHeight;

		m_ProjectionMatrix =
			glm::ortho(0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight), 0.0f, -1.0f, 1.0f);

		m_ShaderSprites.Use();
		m_ShaderSprites.setMat4("uProjection", m_ProjectionMatrix);
	}

	void GuiElement::SetInputsSnapshot(std::shared_ptr<InputsSnapshot> inputsSnapshot)
	{
		m_InputsSnapshot = inputsSnapshot;
	}

	// -------- Protected --------

	void GuiElement::SetInitState(bool state)
	{
		m_HasBeenInit.store(state);
	}

	void GuiElement::SetDeletedState(bool state)
	{
		m_HasBeenDeleted.store(state);
	}

} // namespace onion::voxel
