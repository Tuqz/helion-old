#include "body.h"

namespace sim {
	Body Body::operator =(Body body) {
		orbit.semimajor = body.orbit.semimajor;
		orbit.eccentricity = body.orbit.eccentricity;
		orbit.inclination = body.orbit.inclination;
		mass = body.mass;
		radius = body.radius;
		aop = body.aop;
		lan = body.lan;
		anomaly = body.anomaly;
		time = body.time;
		name = body.name;
		orb_desc = body.orb_desc;
		central_mass = body.central_mass;
		Sun = body.Sun;
		return *this;
	}
	
	double Body::grav_param() const {
		return newtons_constant * mass;
	}

	double Body::period() const {
		return 2 * pi * sqrt(pow(orbit.semimajor, 3) / central_mass->grav_param());
	}

	void Body::update(double delta_t) {
		double mean = sqrt(central_mass->grav_param()/(orbit.semimajor * orbit.semimajor * orbit.semimajor)) * (time + delta_t); //Based on Kepler's formula.
		double eccent_anom = 0;
		for(int i = 0; i < 10; ++i) {
			eccent_anom -= ((orbit.eccentricity * sin(eccent_anom))-mean)/(1 - (orbit.eccentricity * cos(eccent_anom)));
		}
		double tan_anom = sqrt((1 + orbit.eccentricity) / (1 - orbit.eccentricity)) * tan(eccent_anom / 2);
		
		double old_anomaly = anomaly;
		double old_time = time;
		anomaly = 2 * atan(tan_anom);
		if(anomaly < 0) {
			anomaly += 2*pi;
		}
		if(anomaly <= pi && old_anomaly >= pi) {
			time = (anomaly / ((2*pi - old_anomaly) + anomaly)) * delta_t;
		} else {
			time += delta_t;
		}
	}

	Vector Body::pos() {
		double semilatus = orbit.semimajor * (1 - (orbit.eccentricity * orbit.eccentricity));
		double distance = semilatus / (1 + (orbit.eccentricity * cos(anomaly)));
		Vector result = {distance*(cos(lan)*cos(aop+anomaly)-sin(lan)*sin(aop+anomaly)*cos(orbit.inclination)), distance*(sin(lan)*cos(aop+anomaly)+cos(lan)*sin(aop+anomaly)*cos(orbit.inclination)), distance*sin(aop+anomaly)*sin(orbit.inclination)}; //Conversion from perifocal to *centric coordinates.
		return result;
	}
}
