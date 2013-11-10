#pragma once
#include "vector.hpp"
#include "orbit.hpp"
#include "constants.h"
#include <cmath>
#include <string>

namespace sim {
	struct Body {
		Orbit orbit;
		double mass, radius, aop, lan, anomaly, time;
		std::string name, orb_desc;
		Body& central_mass;
		bool Sun;

		double grav_param() const {
			return newtons_constant * mass;
		}
		
		double period() const {
			return 2 * pi * sqrt(pow(orbit.semimajor, 3) / central_mass.grav_param());
		}
		
		void update(double delta_t) {
			double mean = sqrt(central_mass.grav_param()/(orbit.semimajor * orbit.semimajor * orbit.semimajor)) * (time + delta_t);
			double eccent_anom = 0;
			for(int i = 0; i < 10; ++i) {
				eccent_anom -= eccent_anom - ((orbit.eccentricity * sin(eccent_anom))-mean)/(1 - (orbit.eccentricity * cos(eccent_anom)));
			}
			double tan_anom = sqrt((1 + orbit.eccentricity) / (1 - orbit.eccentricity)) * tan(eccent_anom / 2);
			
			double old_anomaly = anomaly;
			double old_time = time;
			anomaly = 2 * atan(tan_anom);
			if(anomaly < 0) {
				anomaly += 2*pi;
			}
			if(anomaly < pi && old_anomaly > pi) {
				time = (anomaly / ((2*pi - old_anomaly) + anomaly)) * delta_t;
			} else {
				time += delta_t;
			}
		}
		
		Vector pos() {
			double semilatus = orbit.semimajor * (1 + (orbit.eccentricity * orbit.eccentricity));
			double distance = semilatus / (1 + (orbit.eccentricity * cos(anomaly)));
			Vector peri_pos = {distance * cos(anomaly), distance * sin(anomaly), 0};
			Vector R_1 = {cos(lan)*cos(aop) - sin(lan)*sin(aop)*cos(orbit.inclination), -cos(lan)*sin(aop) - sin(lan)*cos(aop)*cos(orbit.inclination), sin(lan)*sin(orbit.inclination)};
			Vector R_2 = {sin(lan)*cos(aop) + cos(lan)*cos(aop)*cos(orbit.inclination), -sin(lan)*sin(aop) + cos(lan)*cos(aop)*cos(orbit.inclination), -cos(lan)*sin(orbit.inclination)};
			Vector R_3 = {sin(aop)*sin(orbit.inclination), cos(aop)*sin(orbit.inclination), cos(orbit.inclination)};
			Vector result = {Vector::dot(peri_pos, R_1), Vector::dot(peri_pos, R_2), Vector::dot(peri_pos, R_3)};
			return result;
		}
	};
}
