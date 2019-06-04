//
// File: smoother_emxAPI.h
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//
#ifndef SMOOTHER_EMXAPI_H
#define SMOOTHER_EMXAPI_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "smoother_types.h"

// Function Declarations
extern emxArray_uint8_T *emxCreateND_uint8_T(int numDimensions, int *size);
extern emxArray_uint8_T *emxCreateWrapperND_uint8_T(unsigned char *data, int
  numDimensions, int *size);
extern emxArray_uint8_T *emxCreateWrapper_uint8_T(unsigned char *data, int rows,
  int cols);
extern emxArray_uint8_T *emxCreate_uint8_T(int rows, int cols);
extern void emxDestroyArray_uint8_T(emxArray_uint8_T *emxArray);
extern void emxInitArray_uint8_T(emxArray_uint8_T **pEmxArray, int numDimensions);

#endif

//
// File trailer for smoother_emxAPI.h
//
// [EOF]
//
