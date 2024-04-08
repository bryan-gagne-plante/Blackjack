#pragma once

#include "Component/Component.h"

namespace TGUIWSFML {
	namespace Component {
		class Label : public Component {
		public:
			Label(const int& left = 1, const int& top = 1, const int& width = 1,const int& height = 1, const std::string& text = "");

			virtual ~Label() override;

			virtual void init() override;

			inline std::string text() const { return this->m_SFMLText.getString(); }
			inline void text(const std::string& text) { this->m_SFMLText.setString(text); this->resize(); }

			inline void textAlignment(const TextAlignment& ta) { this->m_textAlignment = ta; this->resize(); }

			virtual void draw(sf::RenderWindow& renderWindow) override;

			virtual int minWidth() const override;
			virtual int minHeight() const override;

			Label(const Label&) = delete;
			Label(Label&&) = delete;
			Label& operator=(const Label&) = delete;
			Label& operator=(Label&&) = delete;

		protected:
			virtual void resize() override;

		private:
			TextAlignment m_textAlignment;

			sf::Text m_SFMLText;

			sf::RectangleShape m_debugTextBounding;

			sf::RectangleShape m_debugTextBaseline;
		};
	}
}
