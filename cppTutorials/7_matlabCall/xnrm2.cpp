//
// File: xnrm2.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//

// Include Files
#include <cmath>
#include "rt_nonfinite.h"
#include "smoother.h"
#include "xnrm2.h"

// Function Definitions

//
// Arguments    : int n
//                const double x[17]
//                int ix0
// Return Type  : double
//
double b_xnrm2(int n, const double x[17], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  kend = (ix0 + n) - 1;
  for (k = ix0; k <= kend; k++) {
    absxk = std::abs(x[k - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * std::sqrt(y);
}

//
// Arguments    : int n
//                const double x[289]
//                int ix0
// Return Type  : double
//
double xnrm2(int n, const double x[289], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  kend = (ix0 + n) - 1;
  for (k = ix0; k <= kend; k++) {
    absxk = std::abs(x[k - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * std::sqrt(y);
}

//
// File trailer for xnrm2.cpp
//
// [EOF]
//
