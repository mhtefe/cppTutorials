//
// File: diag.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//

// Include Files
#include "rt_nonfinite.h"
#include "smoother.h"
#include "diag.h"

// Function Definitions

//
// Arguments    : const double v[289]
//                double d[17]
// Return Type  : void
//
void diag(const double v[289], double d[17])
{
  int k;
  for (k = 0; k < 17; k++) {
    d[k] = v[k + 17 * k];
  }
}

//
// File trailer for diag.cpp
//
// [EOF]
//
