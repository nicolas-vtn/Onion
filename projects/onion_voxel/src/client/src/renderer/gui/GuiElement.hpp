#pragma once

#include <atomic>
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "../Variables.hpp"
#include "../inputs_manager/inputs_manager.hpp"
#include "../shader/shader.hpp"

namespace onion::voxel
{
	class Shader;
	class InputsSnapshot;

	class GuiElement
	{
	  public:
		GuiElement(const std::string& name);
		virtual ~GuiElement();

		virtual void Render() = 0;
		virtual void Initialize() = 0;
		virtual void Delete() = 0;

		std::string GetName() const;
		void SetName(const std::string& name);

		static void SetScreenSize(int screenWidth, int screenHeight);
		static void SetInputsSnapshot(std::shared_ptr<InputsSnapshot> inputsSnapshot);

	  protected:
		void SetInitState(bool state);
		void SetDeletedState(bool state);

	  protected:
		static Shader m_ShaderSprites;
		static glm::mat4 m_ProjectionMatrix;
		static int m_ScreenWidth;
		static int m_ScreenHeight;

		static std::shared_ptr<InputsSnapshot> m_InputsSnapshot;

	  private:
		std::string m_Name;

		std::atomic_bool m_HasBeenInit{false};
		std::atomic_bool m_HasBeenDeleted{false};
	};
} // namespace onion::voxel
