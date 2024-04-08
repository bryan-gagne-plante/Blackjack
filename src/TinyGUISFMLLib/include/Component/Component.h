#pragma once

#include <SFML/Graphics.hpp>

#include "GUIElement.h"

#include "CustomShape/RoundedRectangleShape.h"

namespace TGUIWSFML {
	namespace Component {
		class Component : public GUIElement {
		public:
			Component(const int& left, const int& top, const int& width, const int& height);

			virtual ~Component() = 0;

			virtual void init() override;

			virtual void draw(sf::RenderWindow& renderWindow) override;

			Component(const Component&) = delete;
			Component(Component&&) = delete;
			Component& operator=(const Component&) = delete;
			Component& operator=(Component&&) = delete;
		protected:
			virtual void resize() override;

		private:
			CustomShape::RoundedRectangleShape m_border;
		};
	}
}
