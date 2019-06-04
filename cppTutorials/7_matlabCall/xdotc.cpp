//
// File: xdotc.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//

// Include Files
#include "rt_nonfinite.h"
#include "smoother.h"
#include "xdotc.h"

// Function Definitions

//
// Arguments    : int n
//                const double x[289]
//                int ix0
//                const double y[289]
//                int iy0
// Return Type  : double
//
double xdotc(int n, const double x[289], int ix0, const double y[289], int iy0)
{
  double d;
  int ix;
  int iy;
  int k;
  ix = ix0;
  iy = iy0;
  d = 0.0;
  for (k = 0; k < n; k++) {
    d += x[ix - 1] * y[iy - 1];
    ix++;
    iy++;
  }

  return d;
}

//
// File trailer for xdotc.cpp
//
// [EOF]
//
