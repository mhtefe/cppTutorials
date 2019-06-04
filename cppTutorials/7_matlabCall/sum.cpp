//
// File: sum.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//

// Include Files
#include "rt_nonfinite.h"
#include "smoother.h"
#include "sum.h"

// Function Definitions

//
// Arguments    : const boolean_T x[17]
// Return Type  : double
//
double sum(const boolean_T x[17])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 16; k++) {
    y += (double)x[k + 1];
  }

  return y;
}

//
// File trailer for sum.cpp
//
// [EOF]
//
