#pragma once

namespace sim {
	struct Part {
		enum {control, tank, engine} type;
		char* contents; //For example electricity for a control, fuel for tank...
		double quantity;
	};
}
