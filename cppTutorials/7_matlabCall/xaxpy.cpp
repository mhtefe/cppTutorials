//
// File: xaxpy.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//

// Include Files
#include "rt_nonfinite.h"
#include "smoother.h"
#include "xaxpy.h"

// Function Definitions

//
// Arguments    : int n
//                double a
//                const double x[289]
//                int ix0
//                double y[17]
//                int iy0
// Return Type  : void
//
void b_xaxpy(int n, double a, const double x[289], int ix0, double y[17], int
             iy0)
{
  int ix;
  int iy;
  int i6;
  int k;
  if (!(a == 0.0)) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    i6 = n - 1;
    for (k = 0; k <= i6; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

//
// Arguments    : int n
//                double a
//                const double x[17]
//                int ix0
//                double y[289]
//                int iy0
// Return Type  : void
//
void c_xaxpy(int n, double a, const double x[17], int ix0, double y[289], int
             iy0)
{
  int ix;
  int iy;
  int i7;
  int k;
  if (!(a == 0.0)) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    i7 = n - 1;
    for (k = 0; k <= i7; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

//
// Arguments    : int n
//                double a
//                int ix0
//                double y[289]
//                int iy0
// Return Type  : void
//
void xaxpy(int n, double a, int ix0, double y[289], int iy0)
{
  int ix;
  int iy;
  int i5;
  int k;
  if (!(a == 0.0)) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    i5 = n - 1;
    for (k = 0; k <= i5; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

//
// File trailer for xaxpy.cpp
//
// [EOF]
//
