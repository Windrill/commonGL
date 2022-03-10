// Entrypoint for all drivers
// Why this is 'common'???? This should ever only be included once.

// maybe this ought to
// no class definitions should be made............................................here
// since everybody needs this common module
#pragma once

// meta guard....
// end...

#include "common/glad_driver/module.h"
// This should only ever be included once
// hmmmm link only here then, since GUint depends on driver, which is GLAD
#include <iostream>

void Init();

void LoadDriver();

