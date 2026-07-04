#pragma once

// Lua bindings for RmlUi using sol2.
// This file and its .cpp companion must be compiled with exceptions enabled,
// as sol2 requires C++ exception support. The CMake configuration handles this
// by setting /EHsc for this specific translation unit.

#include "wiRmlUi.h"

namespace wi::lua::rmlui
{
	// Register all RmlUi Lua bindings.
	// Must be called from wi::lua::Initialize() after the Lua state is created.
	void Bind();
}
