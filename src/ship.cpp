#include "ship.h"
#include <math.h>

namespace sim {
	void Ship::rotate(double x, double y, double z) {
		Vector postx;
		postx.x = rotation.x;
		double xmag = sqrt((rotation.y*rotation.y)+(rotation.z*rotation.z));
		postx.y = cos(asin(rotation.z/xmag) + x) * xmag;
		postx.z = sin(asin(rotation.z/xmag) + x) * xmag;
		
		Vector posty;
		posty.y = postx.y;
		double ymag = sqrt((postx.x*postx.x)+(postx.z*postx.z));
		posty.x = cos(asin(postx.z/ymag) + y) * ymag;
		posty.z = sin(asin(postx.z/ymag) + y) * ymag;

		Vector postz;
		postz.z = posty.z;
		double zmag = sqrt((posty.x*posty.x)+(posty.y*posty.y));
		posty.x = cos(asin(posty.y/zmag) + z) * zmag;
		posty.z = sin(asin(posty.y/zmag) + z) * zmag;
	
		rotation = postz;
	}
}
