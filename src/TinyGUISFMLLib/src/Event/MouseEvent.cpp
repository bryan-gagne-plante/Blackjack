#include "Event/MouseEvent.h"

namespace TGUIWSFML {
	namespace Event {
		MouseEvent MouseEvent::FromSFMLMove(const GUIElement* GUIElement, const sf::Event& event) {
			return {
				event.mouseMove.x - GUIElement->left(),
				event.mouseMove.y - GUIElement->top(),

				event.mouseButton.button == sf::Mouse::Button::Left,
				event.mouseButton.button == sf::Mouse::Button::Middle,
				event.mouseButton.button == sf::Mouse::Button::Right,

				GUIElement
			};
		}

		MouseEvent MouseEvent::FromSFMLClick(const GUIElement* GUIElement, const sf::Event& event) {
			return {
				event.mouseButton.x - GUIElement->left(),
				event.mouseButton.y - GUIElement->top(),

				event.mouseButton.button == sf::Mouse::Button::Left,
				event.mouseButton.button == sf::Mouse::Button::Middle,
				event.mouseButton.button == sf::Mouse::Button::Right,

				GUIElement
			};
		}
	}
}