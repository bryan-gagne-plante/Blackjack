#include <sstream>

#include "Window/Window.h"

#include "Event/MouseEvent.h"

#include "Component/Component.h"

namespace TGUIWSFML {
	namespace Window {
		Window::Window(const std::string& formTitle) : Window(640, 480, formTitle) {
			;
		}

		Window::Window(const int& width, const int& height, const std::string& formTitle)
			: GUIElement(0, 0, width, height),
			m_window(sf::VideoMode(width, height), formTitle, sf::Style::Default, sf::ContextSettings(0, 0, 8)),
			m_showFPS(false),
			m_counter(0),
			m_lastFPS(0),
			m_lastOverComponent(nullptr),
			m_FPSLimit(0)
		{
			this->FPSLimit(60);
			this->m_window.display();
			this->backgroundColor(sf::Color(255, 255, 255));
			this->onOverBackgroundChange(false);
			sf::Font* arialFont = font("arial");

			this->m_SFMLText.setFont(*arialFont);
			this->m_SFMLText.setCharacterSize(18);
			this->m_SFMLText.setString("");
			this->m_SFMLText.setFillColor(sf::Color::Black);
		}

		Window::~Window() {
			if (this->m_window.isOpen()) {
				this->m_window.close();
			}
		}

		bool Window::loop() {
			this->handleEvents();
			this->renderIfNeeded();

			return this->m_window.isOpen();
		}

		std::vector<Component::Component*>filterInBounds(std::vector<Component::Component*> components, int x, int y) {
			std::vector<Component::Component*> filteredControls;
			std::copy_if(components.begin(), components.end(),
				std::back_inserter(filteredControls),
				[&](Component::Component* component) { return component->inBounds(x, y); });

			return filteredControls;
		}

		void Window::handleEvents() {
			sf::Event event;

			while (this->m_window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::MouseButtonPressed:
					break;
				case sf::Event::MouseButtonReleased:
				{
					std::vector<Component::Component*> overControls = filterInBounds(this->m_components, event.mouseButton.x, event.mouseButton.y);
					Component::Component* topLevelComponent = nullptr;
					if (overControls.size() >= 1) {
						topLevelComponent = overControls[overControls.size() - 1];

						Event::MouseEvent mouseEvent = Event::MouseEvent::FromSFMLClick(topLevelComponent, event);
						topLevelComponent->onMouseClick(mouseEvent);
					}
				}
				break;
				case sf::Event::MouseEntered:

					break;
				case sf::Event::MouseLeft:
					break;
				case sf::Event::MouseMoved:
				{
					std::vector<Component::Component*> overComponents = filterInBounds(this->m_components, event.mouseMove.x, event.mouseMove.y);
					Component::Component* topLevelComponent = nullptr;
					if (overComponents.size() >= 1) {
						topLevelComponent = overComponents[overComponents.size() - 1];
					}

					if (this->m_lastOverComponent && this->m_lastOverComponent != topLevelComponent) {
						Event::MouseEvent mouseEvent = Event::MouseEvent::FromSFMLMove(this->m_lastOverComponent, event);
						this->m_lastOverComponent->onMouseLeft(mouseEvent);
						this->m_lastOverComponent = nullptr;
					}

					this->m_lastOverComponent = topLevelComponent;

					if (this->m_lastOverComponent) {
						Event::MouseEvent mouseEvent = Event::MouseEvent::FromSFMLMove(this->m_lastOverComponent, event);
						this->m_lastOverComponent->onMouseMove(mouseEvent);
					}
				}
				break;

				case sf::Event::KeyPressed:
					break;
				case sf::Event::KeyReleased:
					break;

				case sf::Event::GainedFocus:
					break;
				case sf::Event::LostFocus:
					break;
				case sf::Event::Resized:
				{
					sf::FloatRect visibleArea(0.0f, 0.0f, (float)event.size.width, (float)event.size.height);
					this->m_window.setView(sf::View(visibleArea));
					this->height(event.size.height);
					this->width(event.size.width);
				}
				break;
				case sf::Event::Closed:
					this->m_window.close();
					break;
				default:
					break;
				}
			}
		}

		void Window::renderIfNeeded() {
			this->render();

		}

		void Window::render() {
			this->m_window.clear(this->backgroundColor());

			GUIElement::draw(this->m_window);

			++this->m_counter;
			if (this->m_lastLoop.getElapsedTime().asSeconds() >= 1.0f) {
				this->m_lastFPS = this->m_counter;
				this->m_counter = 0;
				this->m_lastLoop.restart();
			}

			if (this->m_showFPS) {
				std::stringstream ss;
				ss << this->m_lastFPS << " fps";
				this->m_SFMLText.setString(ss.str());
				sf::FloatRect textBounding = this->m_SFMLText.getGlobalBounds();
				this->m_SFMLText.setPosition(sf::Vector2f(this->innerWidth() - textBounding.width, 1));
				this->m_window.draw(this->m_SFMLText);
			}

			this->m_window.display();
		}

		int Window::minWidth() const {
			return 50;
		}

		int Window::minHeight() const {
			return 50;
		}

		void Window::showFPS() {
			this->m_showFPS = true;
		}

		void Window::hideFPS() {
			this->m_showFPS = false;
		}

	}
}