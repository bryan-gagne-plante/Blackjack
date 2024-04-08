#pragma once

#include <SFML/Graphics.hpp>

namespace TGUIWSFML {
	namespace CustomShape {
		class RoundedRectangleShape : public sf::Shape
		{
		public:
			explicit RoundedRectangleShape(float width = 0, float height = 0, float cornerRadius = 0, unsigned int cornerPointCount = 20);

			void setCornerRadius(float cornerRadius);
			float getCornerRadius() const;

			inline void setSize(const sf::Vector2f& newSize) { this->m_width = newSize.x, this->m_height = newSize.y; }

			virtual unsigned long long getPointCount() const override;
			virtual sf::Vector2f getPoint(unsigned long long index) const override;

		private:
			float m_width;
			float m_height;
			float m_cornerRadius;
			unsigned int m_cornerPointCount;
		};
	}
}