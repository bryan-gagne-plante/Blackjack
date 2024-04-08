#include "Component/Component.h"

namespace TGUIWSFML {
	namespace Component {
		Component::Component(const int& left, const int& top, const int& width, const int& height)
			: GUIElement(left, top, width, height)
		{
			;
		}
		Component::~Component() { ; }

		void Component::init() {
			GUIElement::init();
		}

		void Component::resize() {
			GUIElement::resize();

			this->m_border.setSize(sf::Vector2f((float)this->width(), (float)this->height()));
			this->m_border.setPosition((float)this->left(), (float)this->top());
			this->m_border.setCornerRadius((float)this->cornerRadius());
		}

		void Component::draw(sf::RenderWindow& renderWindow) {
			GUIElement::draw(renderWindow);

			this->m_border.setOutlineThickness(this->outlineThickness());
			this->m_border.setOutlineColor(this->outlineColor());
			this->m_border.setFillColor(this->backgroundColor());
			this->m_border.setTexture(this->currentBackgroundTexture());

			renderWindow.draw(this->m_border);
		}

	}
}