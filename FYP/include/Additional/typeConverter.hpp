#pragma once
#include "TGUI/TGUI.hpp"
#include <iostream>

namespace Convert {
	static int StringToInt(std::string string) {
		if ((string.find_first_not_of("-0123456789") == std::string::npos)) {
			return std::stoi(string);
		}
		else {
			return 0;
		}
	}
}