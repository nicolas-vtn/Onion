#include "DemoPanel.hpp"

namespace onion::voxel
{

	DemoPanel::DemoPanel(const std::string& name) : GuiElement(name), m_Button("DemoButton")
	{
		m_Button.SetPosition(0, 0);
		m_Button.SetSize({400.f, 40.f});
		m_Button.SetText("Cliiiick me!");
		m_Button.SetEnabled(true);
		m_Button.SetScaleUpOnHover(false);
	}

	void DemoPanel::Render()
	{
		float buttonScaleFactorY = 0.1f;
		float xRatio = 0.5f;
		float yRatio = 0.3f;

		const glm::vec2 buttonPos{s_ScreenWidth * xRatio, s_ScreenHeight * yRatio};
		float buttonHeight = s_ScreenHeight * buttonScaleFactorY;
		const glm::vec2 buttonSize{buttonHeight * 10, buttonHeight};

		m_Button.SetPosition(buttonPos);
		m_Button.SetSize(buttonSize);

		m_Button.Render();
	}

	void DemoPanel::Initialize()
	{
		GuiElement::s_TextFont.Load();
		m_Button.Initialize();
		SetInitState(true);
	}

	void DemoPanel::Delete()
	{
		m_Button.Delete();
		SetDeletedState(true);
	}

} // namespace onion::voxel
