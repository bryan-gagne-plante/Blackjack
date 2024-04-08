#include "Component/Label.h"

namespace TGUIWSFML {
	namespace Component {
		Label::Label(const int& left, const int& top, const int& width, const int& height, const std::string& text)
			: Component(left, top, width, height)
			, m_SFMLText()
			, m_debugTextBounding(sf::Vector2f(5, 5))
			, m_debugTextBaseline(sf::Vector2f(5, 5))
		{
			this->textAlignment(TextAlignment::LEFT);
			this->m_SFMLText.setString(text);
			this->m_SFMLText.setCharacterSize(20);

			this->normalBackgroundColor(sf::Color::Transparent);
			this->overBackgroundColor(sf::Color::Transparent);
			this->backgroundColor(this->normalBackgroundColor());
		}

		Label::~Label()
		{
			;
		}

		float calculateDescenderHeight(const sf::String& text, const sf::Font& font, unsigned int characterSize)
		{
			float descenderHeight = 0.0f;

			for (sf::Uint32 character : text)
			{
				// Get the glyph information for the current character
				sf::Glyph glyph = font.getGlyph(character, characterSize, false);

				// Calculate the descent of the current character
				float characterDescent = glyph.bounds.height + glyph.bounds.top;
				descenderHeight = std::max(descenderHeight, characterDescent);
			}

			return descenderHeight;
		}

		void Label::resize() {
			Component::resize();

			float descenderHeight = 0.0f;
			if (this->m_SFMLText.getFont()) {
				descenderHeight = calculateDescenderHeight(this->m_SFMLText.getString(),
					*this->m_SFMLText.getFont(), this->m_SFMLText.getCharacterSize());
			}

			this->m_SFMLText.setPosition(0, 0);
			sf::FloatRect textBounds = this->m_SFMLText.getGlobalBounds();
			int textTop = ((this->height() - (int)textBounds.height + (int)descenderHeight) >> 1) + this->top();
			int textLeft = this->innerLeft();

			switch (this->m_textAlignment)
			{
			case TextAlignment::LEFT:
				break;

			case TextAlignment::CENTER:
				textLeft += (this->innerWidth() - (int)textBounds.width) >> 1;
				break;

			case TextAlignment::RIGHT:
				textLeft += this->innerWidth() - (int)textBounds.width;
				break;

			default:
				break;
			}

			this->m_SFMLText.setPosition(textLeft - textBounds.left, textTop - textBounds.top);


			this->m_debugTextBounding.setPosition((float)textLeft, (float)textTop);
			this->m_debugTextBounding.setSize(sf::Vector2f(textBounds.width, textBounds.height));

			this->m_debugTextBaseline.setPosition((float)textLeft, (float)textTop + textBounds.height - descenderHeight);
			this->m_debugTextBaseline.setSize(sf::Vector2f(textBounds.width, 0));
		}

		void Label::draw(sf::RenderWindow& renderWindow) {
			Component::draw(renderWindow);

			if (drawingDebug) {
				renderWindow.draw(this->m_debugTextBounding);
				renderWindow.draw(this->m_debugTextBaseline);
			}

			renderWindow.draw(this->m_SFMLText);
		}

		int Label::minWidth() const {
			sf::FloatRect textBounds = this->m_SFMLText.getGlobalBounds();

			return (int)(textBounds.width) + ((this->innerBorder() + this->cornerRadius()) << 1);
		}

		int Label::minHeight() const {
			sf::FloatRect textBounds = this->m_SFMLText.getGlobalBounds();

			return (int)(textBounds.height) + ((this->innerBorder() + this->cornerRadius()) << 1);
		}

		void Label::init() {
			sf::Font* arialFont = font("arial");

			this->m_SFMLText.setFont(*arialFont);
			this->m_SFMLText.setFillColor(sf::Color::Black);

			this->m_debugTextBounding.setFillColor(sf::Color::Transparent);
			this->m_debugTextBounding.setOutlineColor(sf::Color::Blue);
			this->m_debugTextBounding.setOutlineThickness(1.0f);

			this->m_debugTextBaseline.setFillColor(sf::Color::Transparent);
			this->m_debugTextBaseline.setOutlineColor(sf::Color::Cyan);
			this->m_debugTextBaseline.setOutlineThickness(1.0f);

			Component::init();
		}

	}
}