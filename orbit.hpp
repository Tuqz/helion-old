#pragma once

namespace sim {
	struct Orbit {
		double semimajor, eccentricity, inclination;
		double apoapsis() const {
			return semimajor * (1 + eccentricity);
		}
		double periapsis() const {
			return semimajor * (1 - eccentricity);
		}
	};
}
