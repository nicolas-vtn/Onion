#pragma once

#include "../../GuiElement.hpp"

#include "../../controls/button/Button.hpp"

namespace onion::voxel
{

	class DemoPanel : public GuiElement
	{
	  public:
		DemoPanel(const std::string& name) : GuiElement(name)
		{
			m_Button.SetPosition(200, 50);
			m_Button.SetSize({400, 40});
			//m_Button.SetText("Demo Button");
		};
		void Render() const { m_Button.Render(); };

	  public:
		void Initialize()
		{
			m_Button.Initialize();
			SetInitState(true);
		};
		void Delete()
		{
			m_Button.Delete();
			SetDeletedState(true);
		};

	  private:
		Button m_Button{"DemoButton"};
	};

}; // namespace onion::voxel
