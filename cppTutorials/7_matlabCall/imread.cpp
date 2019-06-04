//
// File: imread.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//

// Include Files
#include "rt_nonfinite.h"
#include "smoother.h"
#include "imread.h"
#include "smoother_emxutil.h"
#include "libmwjpegreader.h"

// Function Definitions

//
// Arguments    : const char varargin_1[9]
//                emxArray_uint8_T *X
// Return Type  : void
//
void imread(const char varargin_1[9], emxArray_uint8_T *X)
{
  int i0;
  char fname_tmp[10];
  char libjpegWarnBuffer[200];
  double outDimsInit[3];
  signed char fileStatus;
  signed char colorSpaceStatus;
  double libjpegMsgCode;
  signed char errWarnType;
  double outDims_data[3];
  int outNumDims;
  emxArray_int8_T *out;
  int loop_ub;
  int i1;
  signed char libjpegReadDone;
  for (i0 = 0; i0 < 9; i0++) {
    fname_tmp[i0] = varargin_1[i0];
  }

  fname_tmp[9] = '\x00';
  for (i0 = 0; i0 < 200; i0++) {
    libjpegWarnBuffer[i0] = ' ';
  }

  jpegreader_getimagesize(fname_tmp, outDimsInit, &fileStatus, &colorSpaceStatus,
    &libjpegMsgCode, libjpegWarnBuffer, &errWarnType);
  if (outDimsInit[2] == 3.0) {
    outDims_data[0] = outDimsInit[0];
    outDims_data[1] = outDimsInit[1];
    outDims_data[2] = 3.0;
    outNumDims = 3;
  } else {
    outDims_data[0] = outDimsInit[0];
    outDims_data[1] = outDimsInit[1];
    outNumDims = 2;
  }

  emxInit_int8_T(&out, 2);
  if ((fileStatus == -1) || (colorSpaceStatus == -2) || (colorSpaceStatus == -1)
      || (errWarnType == -1)) {
    if (outNumDims == 3) {
      X->size[0] = 0;
      X->size[1] = 0;
      X->size[2] = 0;
    } else {
      X->size[0] = 0;
      X->size[1] = 0;
      X->size[2] = 1;
    }
  } else {
    if (outNumDims == 3) {
      i0 = X->size[0] * X->size[1] * X->size[2];
      X->size[0] = (int)outDims_data[0];
      X->size[1] = (int)outDims_data[1];
      X->size[2] = 3;
      emxEnsureCapacity_uint8_T(X, i0);
    } else {
      i0 = out->size[0] * out->size[1];
      loop_ub = (int)outDims_data[0];
      out->size[0] = loop_ub;
      i1 = (int)outDims_data[1];
      out->size[1] = i1;
      emxEnsureCapacity_int8_T(out, i0);
      loop_ub *= i1;
      for (i0 = 0; i0 < loop_ub; i0++) {
        out->data[i0] = 1;
      }

      i0 = X->size[0] * X->size[1] * X->size[2];
      X->size[0] = out->size[0];
      X->size[1] = out->size[1];
      X->size[2] = 1;
      emxEnsureCapacity_uint8_T(X, i0);
    }

    jpegreader_uint8(fname_tmp, &X->data[0], &outDims_data[0], (double)
                     outNumDims, &fileStatus, &libjpegReadDone, &libjpegMsgCode,
                     libjpegWarnBuffer, &errWarnType);
    if ((fileStatus == -1) || (libjpegReadDone == 0) || (errWarnType == -1)) {
      if (outNumDims == 3) {
        X->size[0] = 0;
        X->size[1] = 0;
        X->size[2] = 0;
      } else {
        X->size[0] = 0;
        X->size[1] = 0;
        X->size[2] = 1;
      }
    }
  }

  emxFree_int8_T(&out);
}

//
// File trailer for imread.cpp
//
// [EOF]
//
