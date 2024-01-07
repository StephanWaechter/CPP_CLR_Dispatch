#pragma once
#include "NativeLibrary/Serialize/Type2.h"
#include <sstream>

namespace NativeLibrary::Serialize::Type2
{
	Type2Device read()
	{
		static int count = 0;
		std::stringstream ss;
		ss << "Item - " << count;
		return Type2Device(ss.str());
	}
}