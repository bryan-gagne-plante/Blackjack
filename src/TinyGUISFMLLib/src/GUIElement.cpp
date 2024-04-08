#include <vector>

#include "Event/Event.h"
#include "Event/MouseEvent.h"
#include "Component/Component.h"

#include "GUIElement.h"

namespace TGUIWSFML {
	GUIElement::GUIElement(const int& left, const int& top, const int& width, const int& height)
		: m_onOverBackgroundChange(false),
		m_left(left), m_top(top), m_width(width), m_height(height),
		m_backgroundTexture(nullptr), m_overBackgroundTexture(nullptr), m_currentBackgroundTexture(nullptr),
		m_debugBoundingBox()
	{
		this->normalBackgroundColor(sf::Color(0xbf, 0xbf, 0xbf));
		this->backgroundColor(this->normalBackgroundColor());
		this->overBackgroundColor(sf::Color(0xdf, 0xdf, 0xdf));
		this->m_debugBoundingBox.setFillColor(sf::Color::Transparent);
		this->m_debugBoundingBox.setOutlineThickness(1.0f);
		this->m_debugBoundingBox.setOutlineColor(sf::Color::Magenta);
	}

	void GUIElement::init() {
		for (Component::Component* component : this->m_components) {
			component->init();
		}

		// Force min size
		this->resize();
	}

	GUIElement::~GUIElement() {
		this->m_components.clear();
	}

	void GUIElement::draw(sf::RenderWindow& renderWindow) {
		for (Component::Component* componentToDraw : this->m_components) {
			componentToDraw->draw(renderWindow);
		}

		if (this->drawingDebug) {
			renderWindow.draw(this->m_debugBoundingBox);
		}
	}

	int GUIElement::innerBorder() const {
		return 2;
	}

	int GUIElement::innerLeft() const {
		return this->m_left + std::max(this->innerBorder(), this->cornerRadius());
	}

	int GUIElement::innerTop() const {
		return this->m_left + std::max(this->innerBorder(), this->cornerRadius());
	}

	int GUIElement::innerWidth() const {
		return this->m_width - (std::max(this->innerBorder(), this->cornerRadius()) << 1);
	}

	int GUIElement::innerHeight() const {
		return this->m_height - (std::max(this->innerBorder(), this->cornerRadius()) << 1);
	}

	void GUIElement::onMouseMove(const Event::MouseEvent& mouseEvent)
	{
		if (this->m_onOverBackgroundChange) {
			this->backgroundColor(this->overBackgroundColor());
			this->m_currentBackgroundTexture = this->m_overBackgroundTexture ? this->m_overBackgroundTexture : this->m_backgroundTexture;
		}

		for (Event::MouseEventHandler meh : this->m_onMouseMoveHandlers) {
			meh(mouseEvent);
		}
	}

	void GUIElement::onMouseLeft(const Event::MouseEvent& mouseEvent)
	{
		if (this->m_onOverBackgroundChange) {
			this->backgroundColor(this->normalBackgroundColor());
			this->m_currentBackgroundTexture = this->m_backgroundTexture;
		}

		for (Event::MouseEventHandler meh : this->m_onMouseLeftHandlers) {
			meh(mouseEvent);
		}
	}

	void GUIElement::onMouseClick(const Event::MouseEvent& mouseEvent)
	{
		for (Event::MouseEventHandler meh : this->m_onMouseClickHandlers) {
			meh(mouseEvent);
		}
	}

	void GUIElement::addComponent(Component::Component* component) {
		if (!component) throw std::invalid_argument("component is null !");

		this->m_components.push_back(component);
	}

	// Fonts cache
	sf::Font* GUIElement::font(const std::string& fontname) {
		if (fonts.find(fontname) == fonts.end()) {
			sf::Font* font = new sf::Font();
			font->loadFromFile("assets/fonts/" + fontname + ".ttf");
			fonts[fontname] = font;
		}

		// operator[] create a new item if key is not present
		return fonts[fontname];
	}

	// Textures cache
	sf::Texture* GUIElement::texture(const std::string& texturename) {
		if (textures.find(texturename) == textures.end()) {
			sf::Texture* texture = new sf::Texture();
			texture->loadFromFile("assets/textures/" + texturename + ".png");
			textures[texturename] = texture;
		}

		// operator[] create a new item if key is not present
		return textures[texturename];
	}

	void GUIElement::clearTinyGUISFMLRessources() {
		for (std::pair<std::string, sf::Font*> font : fonts)
		{
			delete font.second;
		}
		fonts.clear();

		for (std::pair<std::string, sf::Texture*> texture : textures)
		{
			delete texture.second;
		}
		textures.clear();
	}

	std::map<std::string, sf::Font*> GUIElement::fonts;
	std::map<std::string, sf::Texture*> GUIElement::textures;
	bool GUIElement::drawingDebug = false;

}
