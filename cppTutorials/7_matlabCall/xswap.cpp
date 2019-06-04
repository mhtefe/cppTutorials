//
// File: xswap.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//

// Include Files
#include "rt_nonfinite.h"
#include "smoother.h"
#include "xswap.h"

// Function Definitions

//
// Arguments    : double x[289]
//                int ix0
//                int iy0
// Return Type  : void
//
void xswap(double x[289], int ix0, int iy0)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 17; k++) {
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

//
// File trailer for xswap.cpp
//
// [EOF]
//
