#pragma once

#include <SFML/Graphics.hpp>

#include "Label.h"

namespace TGUIWSFML {
	namespace Component {
		class Button : public Label {
		public:
			Button(int left, int top, int width, int height, const std::string& text);

			virtual ~Button() override;

			virtual void draw(sf::RenderWindow& renderWindow) override;

			Button(const Button&) = delete;
			Button(Button&&) = delete;
			Button& operator=(const Button&) = delete;
			Button& operator=(Button&&) = delete;
		protected:
			virtual void resize() override;

		private:

		};
	}
}
