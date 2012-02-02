#include <math.h>

double jinc(double x)
{
    return (fabs(x) < 1e-8) ? 0.5 : j1(x) / x;
}
