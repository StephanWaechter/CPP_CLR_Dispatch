#pragma once
#include "NativeLibrary/Serialize/Type1.h"
#include <sstream>

namespace NativeLibrary::Serialize::Type1
{
	Type1Device read()
	{
		static int count = 0;
		std::stringstream ss;
		ss << "Item - " << count;
		return Type1Device(ss.str());
	}
}