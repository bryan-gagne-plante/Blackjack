#pragma once

#include <string>

#include "GUIElement.h"

namespace TGUIWSFML {
	namespace Window {
		class Window : public GUIElement {
		public:
			Window(const std::string& formTitle = "Main window");
			Window(const int& width, const int& height, const std::string& formTitle = "Main window");

			virtual ~Window() override;
			
			virtual int minWidth() const;
			virtual int minHeight() const;

			void showFPS();
			void hideFPS();

			inline void FPSLimit(const int& value) { this->m_FPSLimit = value; this->m_window.setFramerateLimit(this->m_FPSLimit); }
			inline int FPSLimit() { return this->m_FPSLimit; }

			virtual void componentsInitialization() = 0;

			bool loop();

			inline void show() { 
				this->componentsInitialization(); 
				this->init(); 
				while (loop());
			}

			Window(const Window&) = delete;
			Window(Window&&) = delete;
			Window& operator=(const Window&) = delete;
			Window& operator=(Window&&) = delete;
		private:
			sf::RenderWindow m_window;

			bool m_showFPS;
			int m_counter;
			int m_lastFPS;
		    Component::Component* m_lastOverComponent;

			sf::Clock m_lastLoop;

			sf::Text m_SFMLText;

			int m_FPSLimit;

			void renderIfNeeded();
			void render();

			void handleEvents();
		};
	}
}
