#pragma once

#include "body.h"
#include "converter.hpp"

namespace sim {
	Body Sun = {{0, 0, 0}, 1.9891E30, 6.96342E8, 0, 0, 0, 0, "Sun", "helion", NULL, true};
	Body Mercury = {{5.79091E10, 0.20563, deg_to_rad(3.38)}, 3.3022E23, 2.4397E6, deg_to_rad(29.124), deg_to_rad(48.331), 0, 0, "Mercury", "hermion", &Sun, false};
	Body Venus = {{1.08208E11, 0.0067, deg_to_rad(3.86)}, 4.8676E24, 6.0518E6, deg_to_rad(55.186), deg_to_rad(76.678), 0, 0, "Venus", "cytherion", &Sun, false};
	Body Earth = {{1.49598261E11, 0.01671123, deg_to_rad(7.155)}, 5.97219E24, 6.371E6, deg_to_rad(114.20783), deg_to_rad(348.73936), 0, 0, "Earth", "gee", &Sun, false};
	Body Mars = {{2.279391E11, 0.093315, deg_to_rad(5.65)}, 6.4185E23, 3.3962E6, deg_to_rad(286.537), deg_to_rad(49.562), 0, 0, "Mars", "areion", &Sun, false};
	Body Jupiter = {{7.785472E11, 0.048775, deg_to_rad(6.09)}, 1.8986E27, 6.9911E7, deg_to_rad(275.066), deg_to_rad(100.492), 0, 0, "Jupiter", "jove", &Sun, false};
	Body Saturn = {{1.43344937E12, 0.055723219, deg_to_rad(5.51)}, 5.6846E26, 6.0268E7, deg_to_rad(336.013862), deg_to_rad(113.642811), 0, 0, "Saturn", "krone", &Sun, false};
	Body Uranus = {{2.876679082E12, 0.044405586, deg_to_rad(6.48)}, 8.681E25, 2.5559E7, deg_to_rad(96.541318), deg_to_rad(73.989821), 0, 0, "Uranus", "uranion", &Sun, false};
	Body Neptune = {{4.503443661E12, 0.011214269, deg_to_rad(6.43)}, 1.0243E26, 2.4764E7, deg_to_rad(265.646853), deg_to_rad(131.79431), 0, 0, "Neptune", "poseidion", &Sun, false};
	Body Moon = {{3.84399E8, 0.0549, deg_to_rad(23.435)}, 7.3477E22, 1.7371E6, deg_to_rad(125.08), deg_to_rad(318.15), 0, 0, "Moon", "selene", &Earth, false};
	Body Phobos = {{9.3772E6, 0.0151, deg_to_rad(1.093)}, 1.072E16, 1.11E4, deg_to_rad(150.247), deg_to_rad(164.931), 0, 0, "Phobos", "apsis", &Mars, false};
	Body Deimos = {{2.346E7, 0.0002, deg_to_rad(0.93)}, 1.48E15, 6.2E3, deg_to_rad(290.496), deg_to_rad(339.6), 0, 0, "Deimos", "apsis", &Mars, false};
	Body Ganymede = {{1.0704E9, 0.0013, deg_to_rad(0.2)}, 1.4819E23, 2.6341E6, deg_to_rad(192.417), deg_to_rad(63.552), 0, 0, "Ganymede", "apsis", &Jupiter, false};
	Body Callisto = {{1.8827E9, 0.0074, deg_to_rad(0.281)}, 1.075938E23, 2.4103E6, deg_to_rad(52.643), deg_to_rad(298.848), 0, 0, "Callisto", "apsis", &Jupiter, false};
	Body Io = {{4.217E8, 0.0041, deg_to_rad(0.05)}, 8.9319E22, 1.8213E6, deg_to_rad(84.129), deg_to_rad(43.977), 0, 0, "Io", "apsis", &Jupiter, false};
	Body Europa = {{6.709E8, 0.009, deg_to_rad(0.47)}, 4.7998E22, 1.5608E6, deg_to_rad(88.97), deg_to_rad(219.106), 0, 0, "Europa", "apsis", &Jupiter, false};
	Body Titan = {{1.22187E9, 0.0288, deg_to_rad(0.34854)}, 1.3452E23, 2.576E6, deg_to_rad(185.671), deg_to_rad(24.5), 0, 0, "Titan", "apsis", &Saturn, false};
	Body Rhea = {{5.27108E8, 0.0012583, deg_to_rad(0.345)}, 2.306518E21, 7.638E5, deg_to_rad(256.609), deg_to_rad(311.531), 0, 0, "Rhea", "apsis", &Saturn, false};
	Body Iapetus = {{3.56082E9, 0.0286125, deg_to_rad(15.47)}, 1.805635E21, 7.345E5, deg_to_rad(275.921), deg_to_rad(75.831), 0, 0, "Iapetus", "apsis", &Saturn, false};
	Body Dione = {{3.77396E8, 0.0022, deg_to_rad(0.019)}, 1.095452E21, 5.614E5, deg_to_rad(168.82), deg_to_rad(168.909), 0, 0, "Dione", "apsis", &Saturn, false};
	Body Tethys = {{2.94619E8, 0.0001, deg_to_rad(1.12)}, 6.17449E20, 5.311E5, deg_to_rad(262.845), deg_to_rad(330.882), 0, 0, "Tethys", "apsis", &Saturn, false};
	Body Enceladus = {{2.37948E8, 0.0047, deg_to_rad(0.019)}, 1.08022E20, 2.521E5, deg_to_rad(211.923), deg_to_rad(93.204), 0, 0, "Enceladus", "apsis", &Saturn, false};
	Body Titania = {{4.3591E8, 0.0011, deg_to_rad(97.4)}, 3.527E21, 7.884E5, deg_to_rad(284.4), deg_to_rad(99.771), 0, 0, "Titania", "apsis", &Uranus, false};
	Body Oberon = {{5.8352E8, 0.0014, deg_to_rad(97.6)}, 3.014E21, 7.614E5, deg_to_rad(104.4), deg_to_rad(279.771), 0, 0, "Oberon", "apsis", &Uranus, false};
	Body Ariel = {{1.9102E8, 0.0012, deg_to_rad(97.4)}, 1.353E21, 5.789E5, deg_to_rad(115.349), deg_to_rad(22.394), 0, 0, "Ariel", "apsis", &Uranus, false};
	Body Umbriel = {{2.66E8, 0.0039, deg_to_rad(97.6)}, 1.172E21, 5.847E5, deg_to_rad(84.709), deg_to_rad(33.485), 0, 0, "Umbriel", "apsis", &Uranus, false};
	Body Triton = {{3.54759E8, 0.000016, deg_to_rad(156.885)}, 2.14E22, 1.3534E6, deg_to_rad(344.046), deg_to_rad(172.431), 0, 0, "Triton", "apsis", &Neptune, false};
	const int body_no = 26;
	Body bodies[body_no] = {Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune, Moon, Phobos, Deimos, Ganymede, Callisto, Io, Europa, Titan, Rhea, Iapetus, Dione, Tethys, Enceladus, Titania, Oberon, Ariel, Umbriel, Triton};
}
