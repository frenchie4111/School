#include <math.h>		// M_PI
#include "circle.h"

float getAreas(int radius) {
	return M_PI * radius * radius;
}

float getCircumference(int radius) {
	return 2 * M_PI * radius;
}
