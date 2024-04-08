#pragma once

#include <functional>

namespace TGUIWSFML {
	namespace Event {
		struct MouseEvent;
		typedef std::function<void(const MouseEvent& mouseEvent)> MouseEventHandler;
	}
}
