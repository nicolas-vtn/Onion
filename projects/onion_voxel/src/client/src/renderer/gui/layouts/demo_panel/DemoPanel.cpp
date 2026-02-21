#include "DemoPanel.hpp"

namespace onion::voxel
{

	DemoPanel::DemoPanel(const std::string& name) : GuiElement(name), m_Button("DemoButton")
	{
		m_Button.SetPosition(200, 50);
		m_Button.SetSize({400.f, 40.f});
	}

	void DemoPanel::Render()
	{
		m_Button.Render();
	}

	void DemoPanel::Initialize()
	{
		m_Button.Initialize();
		SetInitState(true);
	}

	void DemoPanel::Delete()
	{
		m_Button.Delete();
		SetDeletedState(true);
	}

} // namespace onion::voxel
