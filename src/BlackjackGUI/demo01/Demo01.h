#pragma once

#include "Window/Window.h"
#include "Component/Label.h"
#include "Component/Button.h"

class Demo01 : public TGUIWSFML::Window::Window {
public:
	Demo01();
	~Demo01();

	virtual void componentsInitialization();
private:
	TGUIWSFML::Component::Label* m_labelHello;
	TGUIWSFML::Component::Button* m_FPSOn;
	TGUIWSFML::Component::Button* m_FPSOff;
	TGUIWSFML::Component::Button* m_testHover;

	TGUIWSFML::Component::Label* m_labelLeftAligned;
	TGUIWSFML::Component::Label* m_labelCenterAligned;
	TGUIWSFML::Component::Label* m_labelRightAligned;

	TGUIWSFML::Component::Label* m_imageAsCoeur;

	TGUIWSFML::Component::Button* m_drawingDebugOff;
	TGUIWSFML::Component::Button* m_drawingDebugOn;
	TGUIWSFML::Component::Button* m_toogleFPSLimit;
};