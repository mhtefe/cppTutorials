//
// File: svd.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//

// Include Files
#include <string.h>
#include "rt_nonfinite.h"
#include "smoother.h"
#include "svd.h"
#include "svd1.h"
#include "anyNonFinite.h"

// Function Definitions

//
// Arguments    : const double A[289]
//                double U[289]
//                double S[289]
//                double V[289]
// Return Type  : void
//
void svd(const double A[289], double U[289], double S[289], double V[289])
{
  int i;
  double s[17];
  if (!anyNonFinite()) {
    b_svd(A, U, s, V);
  } else {
    for (i = 0; i < 289; i++) {
      U[i] = rtNaN;
    }

    for (i = 0; i < 17; i++) {
      s[i] = rtNaN;
    }

    for (i = 0; i < 289; i++) {
      V[i] = rtNaN;
    }
  }

  memset(&S[0], 0, 289U * sizeof(double));
  for (i = 0; i < 17; i++) {
    S[i + 17 * i] = s[i];
  }
}

//
// File trailer for svd.cpp
//
// [EOF]
//
