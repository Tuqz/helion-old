#pragma once

namespace sim {
	struct Orbit {
		Orbit operator =(const Orbit& param) {
			return {param.semimajor, param.eccentricity, param.inclination};
		}
            
		double semimajor, eccentricity, inclination;
		double apoapsis() const {
			return semimajor * (1 + eccentricity);
		}
		double periapsis() const {
			return semimajor * (1 - eccentricity);
		}
	};
}
