#include"Math.h"
#include<math.h>

float OriginalMath::Math::CosineTheorem90(float a, float b)
{
	float c = 0;

	if (a < 0)
	{
		a * (-1);
	}
	if (b < 0)
	{
		b * (-1);
	}

	c = a * a + b * b;

	return sqrt(c);
}