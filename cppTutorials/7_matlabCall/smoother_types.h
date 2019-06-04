//
// File: smoother_types.h
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//
#ifndef SMOOTHER_TYPES_H
#define SMOOTHER_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct emxArray_int8_T
{
  signed char *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct emxArray_uint32_T
{
  unsigned int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct emxArray_uint8_T
{
  unsigned char *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif

//
// File trailer for smoother_types.h
//
// [EOF]
//
