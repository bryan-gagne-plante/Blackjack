#pragma once

#include <SFML/Graphics.hpp>

#include "Event/Event.h"

#include "GUIElement.h"

namespace TGUIWSFML {
	namespace Event {
		struct MouseEvent {
			int x;
			int y;
			bool left;
			bool middle;
			bool right;

			const GUIElement* source = nullptr;

			static MouseEvent FromSFMLMove(const GUIElement* GUIElement, const sf::Event& event);
			static MouseEvent FromSFMLClick(const GUIElement* GUIElement, const sf::Event& event);
		};
	}
}
