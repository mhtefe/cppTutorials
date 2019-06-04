//
// File: xrot.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//

// Include Files
#include "rt_nonfinite.h"
#include "smoother.h"
#include "xrot.h"

// Function Definitions

//
// Arguments    : double x[289]
//                int ix0
//                int iy0
//                double c
//                double s
// Return Type  : void
//
void xrot(double x[289], int ix0, int iy0, double c, double s)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 17; k++) {
    temp = c * x[ix] + s * x[iy];
    x[iy] = c * x[iy] - s * x[ix];
    x[ix] = temp;
    iy++;
    ix++;
  }
}

//
// File trailer for xrot.cpp
//
// [EOF]
//
