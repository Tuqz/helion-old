#include "helion/body.h"

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
			eccent_anom = eccent_anom - (eccent_anom - (orbit.eccentricity * sin(eccent_anom)) - mean)/(1-(orbit.eccentricity * cos(eccent_anom))); //Newton-Raphson method for f(x) = x - e sin(x) - M
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
		Vector peri_pos = {distance * cos(anomaly), distance * sin(anomaly), 0};
		Vector R[3] = {{cos(lan)*cos(aop) - sin(lan)*sin(aop)*cos(orbit.inclination), -cos(lan)*sin(aop)-sin(lan)*cos(aop)*cos(orbit.inclination), sin(lan)*sin(orbit.inclination)}, {sin(lan)*cos(aop)+cos(lan)*sin(aop)*cos(orbit.inclination), -sin(lan)*sin(aop)+cos(lan)*cos(aop)*cos(orbit.inclination), -cos(lan)*sin(orbit.inclination)}, {sin(aop)*sin(orbit.inclination), cos(aop)*sin(orbit.inclination), cos(orbit.inclination)}}; //Conversion matrix
		Vector result = {Vector::dot(R[0], peri_pos), Vector::dot(R[1], peri_pos), Vector::dot(R[2], peri_pos)};; //Matrix multiplying the position vector by the conversion matrix
		return result;
	}

	Vector Body::vel() {
		double semilatus = orbit.semimajor * (1 - (orbit.eccentricity * orbit.eccentricity));
		Vector peri_vel = {- sqrt(central_mass->grav_param()/semilatus) * sin(anomaly), sqrt(central_mass->grav_param()/semilatus)*(orbit.eccentricity+cos(anomaly)), 0};
		Vector R[3] = {{cos(lan)*cos(aop) - sin(lan)*sin(aop)*cos(orbit.inclination), -cos(lan)*sin(aop)-sin(lan)*cos(aop)*cos(orbit.inclination), sin(lan)*sin(orbit.inclination)}, {sin(lan)*cos(aop)+cos(lan)*sin(aop)*cos(orbit.inclination), -sin(lan)*sin(aop)+cos(lan)*cos(aop)*cos(orbit.inclination), -cos(lan)*sin(orbit.inclination)}, {sin(aop)*sin(orbit.inclination), cos(aop)*sin(orbit.inclination), cos(orbit.inclination)}};
		Vector result = {Vector::dot(R[0], peri_vel), Vector::dot(R[1], peri_vel), Vector::dot(R[2], peri_vel)};
		return result;
	}
}
