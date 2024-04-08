#include "Component/Button.h"

namespace TGUIWSFML {
	namespace Component {
		Button::Button(int left, int top, int width, int height, const std::string& text)
			: Label(left, top, width, height, text)
		{
			this->textAlignment(TextAlignment::CENTER);
			this->onOverBackgroundChange(true);

			this->outlineColor(sf::Color::Black);
			this->outlineThickness(1.0f);

			this->normalBackgroundColor(sf::Color(0xec, 0xec, 0xec));
			this->backgroundColor(this->normalBackgroundColor());
			this->overBackgroundColor(sf::Color(0xcd, 0xde, 0xf3));
		}

		Button::~Button() {
			;
		}

		void Button::draw(sf::RenderWindow& renderWindow) {
			Label::draw(renderWindow);
		};

		void Button::resize() {
			Label::resize();

			if (this->currentBackgroundTexture()) {
				this->outlineThickness(0.0f);
			}
		}
	}
}