//
// File: xaxpy.h
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//
#ifndef XAXPY_H
#define XAXPY_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "smoother_types.h"

// Function Declarations
extern void b_xaxpy(int n, double a, const double x[289], int ix0, double y[17],
                    int iy0);
extern void c_xaxpy(int n, double a, const double x[17], int ix0, double y[289],
                    int iy0);
extern void xaxpy(int n, double a, int ix0, double y[289], int iy0);

#endif

//
// File trailer for xaxpy.h
//
// [EOF]
//
