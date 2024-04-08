#pragma once

#include <map>

#include <SFML/Graphics.hpp>

#include "Event/Event.h"

namespace TGUIWSFML {
	namespace Component {
		class Component;
	}

	namespace Event {
		struct MouseEvent;
		class Event;
	}

	class GUIElement {
	public:
		GUIElement(const int& left, const int& top, const int& width, const int& height);

		virtual void init();

		virtual ~GUIElement() = 0;

		void addComponent(Component::Component* component);

		inline int left() const { return this->m_left; }
		inline void left(const int& value) { this->m_left = value; this->resize(); }

		inline int top() const { return this->m_top; }
		inline void top(const int& value) { this->m_top = value; this->resize(); }

		inline int width() const { return this->m_width; }
		inline void width(const int& value) {
			this->m_width = value;
			this->resize();
		}
		virtual int minWidth() const = 0;

		inline int height() const { return this->m_height; }
		inline void height(const int& value) {
			this->m_height = value;
			this->resize();
		}
		virtual int minHeight() const = 0;

		inline virtual bool inBounds(const int& x, const int& y) const {
			return x >= this->m_left
				&& x <= this->m_left + this->m_width
				&& y >= this->m_top
				&& y <= this->m_top + this->m_height;
		}

		virtual int innerLeft() const;
		virtual int innerTop() const;
		virtual int innerWidth() const;
		virtual int innerHeight() const;
		virtual int innerBorder() const;

		virtual void draw(sf::RenderWindow& renderWindow);

		inline void backgroundColor(const sf::Color& value) { this->m_backgroundColor = value; }
		inline sf::Color backgroundColor() const { return this->m_backgroundColor; }

		inline void normalBackgroundColor(const sf::Color& value) { this->m_normalBackgroundColor = value; this->backgroundColor(value); }
		inline sf::Color normalBackgroundColor() const { return this->m_normalBackgroundColor; }

		inline void overBackgroundColor(const sf::Color& value) { this->m_overBackgroundColor = value; }
		inline sf::Color overBackgroundColor() const { return this->m_overBackgroundColor; }

		inline void outlineColor(const sf::Color& value) { this->m_outlineColor = value; }
		inline sf::Color outlineColor() const { return this->m_outlineColor; }

		inline void normalOutlineColor(const sf::Color& value) { this->m_normalOutlineColor = value; }
		inline sf::Color normalOutlineColor() const { return this->m_normalOutlineColor; }

		inline void overOutlineColor(const sf::Color& value) { this->m_overOutlineColor = value; }
		inline sf::Color overOutlineColor() const { return this->m_overOutlineColor; }

		inline void cornerRadius(const int& value) {
			this->m_cornerRadius = value;
			this->resize();
		}
		inline int cornerRadius() const { return this->m_cornerRadius; }

		inline void outlineThickness(const float& value) { this->m_outlineThickness = value; }
		inline float outlineThickness() const { return this->m_outlineThickness; }

		inline void addMouseMoveHandler(Event::MouseEventHandler meh) { this->m_onMouseMoveHandlers.push_back(meh); }
		inline void addMouseLeftHandler(Event::MouseEventHandler meh) { this->m_onMouseLeftHandlers.push_back(meh); }
		inline void addMouseClickHandler(Event::MouseEventHandler meh) { this->m_onMouseClickHandlers.push_back(meh); }

		inline void backgroundTexture(sf::Texture* texture) {
			if (!texture) throw std::invalid_argument("texture is null !");

			this->m_backgroundTexture = texture;
			this->normalBackgroundColor(sf::Color::White);
			this->backgroundColor(this->normalBackgroundColor());
			if (texture) { this->m_currentBackgroundTexture = texture; }
		}
		inline void overBackgroundTexture(sf::Texture* texture) {
			if (!texture) throw std::invalid_argument("texture is null !");

			this->m_overBackgroundTexture = texture;
			this->normalBackgroundColor(sf::Color::White);
			this->backgroundColor(this->normalBackgroundColor());
		}
		inline sf::Texture* currentBackgroundTexture() const {
			return this->m_currentBackgroundTexture;
		}

		virtual void onMouseMove(const Event::MouseEvent& mouseEvent);
		virtual void onMouseLeft(const Event::MouseEvent& mouseEvent);
		virtual void onMouseClick(const Event::MouseEvent& mouseEvent);

		static sf::Font* font(const std::string& fontname);
		static sf::Texture* texture(const std::string& texturename);
		static void clearTinyGUISFMLRessources();

		static bool drawingDebug;

		GUIElement(const GUIElement&) = delete;
		GUIElement(GUIElement&&) = delete;
		GUIElement& operator=(const GUIElement&) = delete;
		GUIElement& operator=(GUIElement&&) = delete;

	protected:
		std::vector<Component::Component*> m_components;

		bool m_onOverBackgroundChange;

		inline virtual void resize() {
			this->m_width = std::max(this->m_width, this->minWidth());
			this->m_height = std::max(this->m_height, this->minHeight());

			this->m_debugBoundingBox.setPosition(this->m_left, this->m_top);
			this->m_debugBoundingBox.setSize(sf::Vector2f(this->m_width, this->m_height));
		};

		inline bool onOverBackgroundChange() const { return this->m_onOverBackgroundChange; }
		inline void onOverBackgroundChange(bool value) { this->m_onOverBackgroundChange = value; }

	private:
		int m_left;
		int m_top;

		int m_width;
		int m_height;

		int m_cornerRadius;

		float m_outlineThickness;

		sf::Color m_backgroundColor;
		sf::Color m_normalBackgroundColor;
		sf::Color m_overBackgroundColor;

		sf::Color m_outlineColor;
		sf::Color m_normalOutlineColor;
		sf::Color m_overOutlineColor;

		std::vector<Event::MouseEventHandler> m_onMouseMoveHandlers;
		std::vector<Event::MouseEventHandler> m_onMouseLeftHandlers;
		std::vector<Event::MouseEventHandler> m_onMouseClickHandlers;

		sf::Texture* m_backgroundTexture;
		sf::Texture* m_overBackgroundTexture;
		sf::Texture* m_currentBackgroundTexture;

		sf::RectangleShape m_debugBoundingBox;

		static std::map<std::string, sf::Font*> fonts;
		static std::map<std::string, sf::Texture*> textures;
	};

	enum TextAlignment {
		LEFT = 1,
		CENTER = 2,
		RIGHT = 3
	};
}
