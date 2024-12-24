#pragma once

#include "HellCommon.hpp"
#include "Input/Input.hpp"

class CameraPerspective
{
public:

	enum class PERSPECTIVE_CAMERA_STATES
	{
		FIRST_PERSON,
		THIRD_PERSON,
		UNDEFINED
	};

	static inline PERSPECTIVE_CAMERA_STATES m_cameraPerspective = PERSPECTIVE_CAMERA_STATES::FIRST_PERSON;

	//void ToggleThirdPerson()
	//{
	//	std::cout << "Toggled Third Person" << std::endl;
	//}

	static void EvaluateCameraPerspectivePress()
	{
		if (Input::KeyPressed(HELL_KEY_V))
		{
			if (m_cameraPerspective == PERSPECTIVE_CAMERA_STATES::FIRST_PERSON)
			{
				m_cameraPerspective = PERSPECTIVE_CAMERA_STATES::THIRD_PERSON;
				std::cout << "Camera Perspective: Third Person" << std::endl;
			}
			else if (m_cameraPerspective == PERSPECTIVE_CAMERA_STATES::THIRD_PERSON)
			{
				m_cameraPerspective = PERSPECTIVE_CAMERA_STATES::FIRST_PERSON;
				std::cout << "Camera Perspective: First Person" << std::endl;
			}
			else if (m_cameraPerspective == PERSPECTIVE_CAMERA_STATES::UNDEFINED)
			{
				m_cameraPerspective = PERSPECTIVE_CAMERA_STATES::FIRST_PERSON;
				std::cerr << "ERROR: PERSPECTIVE_CAMERA_STATES is undefined" << std::endl;
			}
		}
	}

	static void HandleCameraPerspective()
	{

	}
};

