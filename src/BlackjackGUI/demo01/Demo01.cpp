#include "Event/MouseEvent.h"

#include "Demo01.h"

Demo01::Demo01()
	: Window(640, 480, "Ma fenetre"), 
	m_labelHello(nullptr), 
	m_FPSOn(nullptr), 
	m_FPSOff(nullptr),
	m_testHover(nullptr),
	m_labelLeftAligned(nullptr),
	m_labelCenterAligned(nullptr),
	m_labelRightAligned(nullptr),
	m_imageAsCoeur(nullptr),
	m_drawingDebugOff(nullptr),
	m_drawingDebugOn(nullptr)
{
	;
}

void Demo01::componentsInitialization() {
	// m_FPSOn
	this->m_FPSOn = new TGUIWSFML::Component::Button(1, 1, 50, 15, "FPS On");
	this->addComponent(this->m_FPSOn);
	this->m_FPSOn->addMouseClickHandler([&](const TGUIWSFML::Event::MouseEvent& me) { this->showFPS(); });

	// m_FPSOff
	this->m_FPSOff = new TGUIWSFML::Component::Button(150, 1, 50, 15, "FPS Off");
	this->addComponent(this->m_FPSOff);
	this->m_FPSOff->addMouseClickHandler([&](const TGUIWSFML::Event::MouseEvent& me) { this->hideFPS(); });

	// m_labelHello
	this->m_labelHello = new TGUIWSFML::Component::Label();
	this->m_labelHello->text("Hello");
	this->m_labelHello->top(65);
	this->m_labelHello->left(1);
	this->addComponent(this->m_labelHello);
	this->m_labelHello->cornerRadius(5);

	// m_testHover
	this->m_testHover = new TGUIWSFML::Component::Button(150, 65, 50, 15, "Test hover");
	this->m_testHover->backgroundTexture(texture("hoverButton"));
	this->m_testHover->overBackgroundTexture(texture("normalButton"));
	this->addComponent(this->m_testHover);
	this->m_testHover->cornerRadius(5);


	// m_labelLeftAligned
	this->m_labelLeftAligned = new TGUIWSFML::Component::Label(1, 100, 300, 30, "Left aligned text");
	this->m_labelLeftAligned->cornerRadius(10);
	this->addComponent(this->m_labelLeftAligned);

	// m_labelCenterAligned
	this->m_labelCenterAligned = new TGUIWSFML::Component::Label(1, 145, 300, 30, "Centered text");
	this->m_labelCenterAligned->textAlignment(TGUIWSFML::TextAlignment::CENTER);
	this->m_labelCenterAligned->cornerRadius(10);
	this->addComponent(this->m_labelCenterAligned);

	// m_labelRightAligned
	this->m_labelRightAligned = new TGUIWSFML::Component::Label(1, 190, 300, 35, "Right aligned text");
	this->m_labelRightAligned->textAlignment(TGUIWSFML::TextAlignment::RIGHT);
	this->m_labelRightAligned->cornerRadius(10);
	this->addComponent(this->m_labelRightAligned);

	// m_imageAsCoeur
	this->m_imageAsCoeur = new TGUIWSFML::Component::Label(350, 1, 234, 333, "");
	this->m_imageAsCoeur->backgroundTexture(texture("svg_playing_cards/fronts/png_96_dpi/hearts_ace"));
	this->addComponent(this->m_imageAsCoeur);

	// m_drawingDebugOff
	this->m_drawingDebugOff = new TGUIWSFML::Component::Button(1, 250, 300, 40, "Drawing debug Off");
	this->addComponent(this->m_drawingDebugOff);
	this->m_drawingDebugOff->addMouseClickHandler([&](const TGUIWSFML::Event::MouseEvent& me) { TGUIWSFML::GUIElement::drawingDebug = false; });

	// m_drawingDebugOn
	this->m_drawingDebugOn = new TGUIWSFML::Component::Button(1, 300, 300, 40, "Drawing debug On");
	this->addComponent(this->m_drawingDebugOn);
	this->m_drawingDebugOn->addMouseClickHandler([&](const TGUIWSFML::Event::MouseEvent& me) { TGUIWSFML::GUIElement::drawingDebug = true; });

	// m_toogleFPSLimit
	this->m_toogleFPSLimit = new TGUIWSFML::Component::Button(1, 25, 50, 15, "Toogle FPS Limit");
	this->m_toogleFPSLimit->cornerRadius(5);
	this->m_toogleFPSLimit->outlineColor(sf::Color::Red);
	this->m_toogleFPSLimit->outlineThickness(3.0f);
	this->addComponent(this->m_toogleFPSLimit);
	this->m_toogleFPSLimit->addMouseClickHandler([&](const TGUIWSFML::Event::MouseEvent& me) { this->FPSLimit() ? this->FPSLimit(0) : this->FPSLimit(60); });
	this->m_toogleFPSLimit->overBackgroundColor(sf::Color(21, 215, 152));
	this->m_toogleFPSLimit->normalBackgroundColor(sf::Color(93, 217, 177));

}

Demo01::~Demo01() {
	this->m_components.clear();

	delete this->m_FPSOn;
	this->m_FPSOn = nullptr;

	delete this->m_FPSOff;
	this->m_FPSOff = nullptr;

	delete this->m_labelHello;
	this->m_labelHello;

	delete this->m_testHover;
	this->m_testHover = nullptr;

	delete this->m_labelLeftAligned;
	this->m_labelLeftAligned = nullptr;

	delete this->m_labelCenterAligned;
	this->m_labelCenterAligned = nullptr;

	delete this->m_labelRightAligned;
	this->m_labelRightAligned = nullptr;

	delete this->m_imageAsCoeur;
	this->m_imageAsCoeur = nullptr;

	delete this->m_drawingDebugOff;
	this->m_drawingDebugOff = nullptr;

	delete this->m_drawingDebugOn;
	this->m_drawingDebugOn = nullptr;

	delete this->m_toogleFPSLimit;
	this->m_toogleFPSLimit = nullptr;
}