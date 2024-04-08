#define _USE_MATH_DEFINES
#include <math.h>

#include "CustomShape/RoundedRectangleShape.h"

namespace TGUIWSFML {
	namespace CustomShape {
		RoundedRectangleShape::RoundedRectangleShape(float width, float height, float cornerRadius, unsigned int cornerPointCount)
			: m_width(width), m_height(height), m_cornerRadius(cornerRadius), m_cornerPointCount(cornerPointCount)
		{
			update();
		}

		void RoundedRectangleShape::setCornerRadius(float cornerRadius)
		{
			this->m_cornerRadius = cornerRadius;
			update();
		}

		float RoundedRectangleShape::getCornerRadius() const
		{
			return this->m_cornerRadius;
		}

		unsigned long long RoundedRectangleShape::getPointCount() const
		{
			if (this->m_cornerRadius == 0) { return 4; }
			return m_cornerPointCount * 4 + 2;
		}

		sf::Vector2f RoundedRectangleShape::getPoint(unsigned long long index) const
		{
			sf::Vector2f res;
			int cornerPointCount = this->m_cornerPointCount;
			if (this->m_cornerRadius == 0) {
				switch (index)
				{
				case 0:
					res = sf::Vector2f(0, 0);
					break;
				case 1:
					res = sf::Vector2f(this->m_width, 0);
					break;
				case 2:
					res = sf::Vector2f(this->m_width, this->m_height);
					break;
				case 3:
					res = sf::Vector2f(0, this->m_height);
					break;
				}
				cornerPointCount = 1; 
			} else if (index < cornerPointCount)  // upper left corner
			{
				res = sf::Vector2f(this->m_cornerRadius * (1 - (float)std::cos(index * M_PI / 2 / cornerPointCount)),
					this->m_cornerRadius * (1 - (float)std::sin(index * M_PI / 2 / cornerPointCount)));
			}
			else if (index < 2 * cornerPointCount) // upper right corner
			{
				res = sf::Vector2f(this->m_width - this->m_cornerRadius * (1 - (float)std::sin((index - cornerPointCount) * M_PI / 2 / cornerPointCount)),
					this->m_cornerRadius * (1 - (float)std::cos((index - cornerPointCount) * M_PI / 2 / cornerPointCount)));
			}
			else if (index < 3 * cornerPointCount) // lower right corner
			{
				res = sf::Vector2f(this->m_width - this->m_cornerRadius * (1 - (float)std::cos((index - 2 * cornerPointCount) * M_PI / 2 / cornerPointCount)),
					this->m_height - this->m_cornerRadius * (1 - (float)std::sin((index - 2 * cornerPointCount) * M_PI / 2 / cornerPointCount)));
			}
			else if (index < 4 * cornerPointCount) // lower left corner
			{
				res = sf::Vector2f(this->m_cornerRadius * (1 - (float)std::sin((index - 3 * cornerPointCount) * M_PI / 2 / cornerPointCount)),
					this->m_height - this->m_cornerRadius * (1 - (float)std::cos((index - 3 * cornerPointCount) * M_PI / 2 / cornerPointCount)));
			}
			else // close the shape (upper left corner)
			{
				res = sf::Vector2f(cornerPointCount * (1 - (float)std::sin(M_PI / 2 * (index - 3 * cornerPointCount) / cornerPointCount)),
					this->m_height - cornerPointCount * (1 - (float)std::cos(M_PI / 2 * (index - 3 * cornerPointCount) / cornerPointCount)));
			}

			return res;
		}
	}
}
