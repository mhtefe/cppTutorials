//
// File: imfilter.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//

// Include Files
#include "rt_nonfinite.h"
#include "smoother.h"
#include "imfilter.h"
#include "smoother_emxutil.h"

// Function Definitions

//
// Arguments    : const emxArray_uint8_T *a_tmp
//                const double pad[3]
//                emxArray_uint8_T *a
// Return Type  : void
//
void padImage(const emxArray_uint8_T *a_tmp, const double pad[3],
              emxArray_uint8_T *a)
{
  double sizeA_idx_0;
  double sizeA_idx_1;
  double sizeA_idx_2;
  unsigned int sizeA_tmp;
  int i2;
  unsigned int b_sizeA_tmp;
  double sizeA[3];
  unsigned int ex;
  unsigned int u1;
  int loop_ub;
  emxArray_int32_T *idxA;
  emxArray_uint32_T *y;
  emxArray_uint32_T *idxDir;
  emxArray_int32_T *r0;
  int i3;
  int j;
  int i4;
  int i;
  if ((a_tmp->size[0] == 0) || (a_tmp->size[1] == 0) || (a_tmp->size[2] == 0)) {
    sizeA_idx_0 = (double)a_tmp->size[0] + 2.0 * pad[0];
    sizeA_idx_1 = (double)a_tmp->size[1] + 2.0 * pad[1];
    sizeA_idx_2 = (double)a_tmp->size[2] + 2.0 * pad[2];
    i2 = a->size[0] * a->size[1] * a->size[2];
    a->size[0] = (int)sizeA_idx_0;
    a->size[1] = (int)sizeA_idx_1;
    a->size[2] = (int)sizeA_idx_2;
    emxEnsureCapacity_uint8_T(a, i2);
    loop_ub = (int)sizeA_idx_0 * (int)sizeA_idx_1 * (int)sizeA_idx_2;
    for (i2 = 0; i2 < loop_ub; i2++) {
      a->data[i2] = 0U;
    }
  } else {
    sizeA_idx_0 = a_tmp->size[0];
    sizeA_idx_1 = a_tmp->size[1];
    sizeA_idx_2 = a_tmp->size[2];
    sizeA_tmp = (unsigned int)sizeA_idx_0;
    b_sizeA_tmp = (unsigned int)sizeA_idx_1;
    sizeA[2] = (unsigned int)sizeA_idx_2;
    ex = (unsigned int)(16.0 + (double)sizeA_tmp);
    u1 = (unsigned int)(16.0 + (double)b_sizeA_tmp);
    if (ex < u1) {
      ex = u1;
    }

    if (ex < (unsigned int)sizeA[2]) {
      ex = (unsigned int)sizeA[2];
    }

    emxInit_int32_T(&idxA, 2);
    i2 = idxA->size[0] * idxA->size[1];
    idxA->size[0] = (int)ex;
    idxA->size[1] = 3;
    emxEnsureCapacity_int32_T(idxA, i2);
    emxInit_uint32_T(&y, 2);
    i2 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(unsigned int)sizeA_idx_0;
    emxEnsureCapacity_uint32_T(y, i2);
    loop_ub = (int)(unsigned int)sizeA_idx_0 - 1;
    for (i2 = 0; i2 <= loop_ub; i2++) {
      y->data[i2] = 1U + i2;
    }

    emxInit_uint32_T(&idxDir, 2);
    i2 = idxDir->size[0] * idxDir->size[1];
    idxDir->size[0] = 1;
    idxDir->size[1] = y->size[1] + 16;
    emxEnsureCapacity_uint32_T(idxDir, i2);
    for (i2 = 0; i2 < 8; i2++) {
      idxDir->data[i2] = 1U;
    }

    loop_ub = y->size[1];
    for (i2 = 0; i2 < loop_ub; i2++) {
      idxDir->data[i2 + 8] = y->data[i2];
    }

    for (i2 = 0; i2 < 8; i2++) {
      idxDir->data[(i2 + y->size[1]) + 8] = sizeA_tmp;
    }

    emxInit_int32_T(&r0, 1);
    loop_ub = idxDir->size[1];
    i2 = r0->size[0];
    r0->size[0] = loop_ub;
    emxEnsureCapacity_int32_T(r0, i2);
    for (i2 = 0; i2 < loop_ub; i2++) {
      r0->data[i2] = i2;
    }

    loop_ub = r0->size[0];
    for (i2 = 0; i2 < loop_ub; i2++) {
      idxA->data[r0->data[i2]] = (int)idxDir->data[i2];
    }

    i2 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(unsigned int)sizeA_idx_1;
    emxEnsureCapacity_uint32_T(y, i2);
    loop_ub = (int)(unsigned int)sizeA_idx_1 - 1;
    for (i2 = 0; i2 <= loop_ub; i2++) {
      y->data[i2] = 1U + i2;
    }

    i2 = idxDir->size[0] * idxDir->size[1];
    idxDir->size[0] = 1;
    idxDir->size[1] = y->size[1] + 16;
    emxEnsureCapacity_uint32_T(idxDir, i2);
    for (i2 = 0; i2 < 8; i2++) {
      idxDir->data[i2] = 1U;
    }

    loop_ub = y->size[1];
    for (i2 = 0; i2 < loop_ub; i2++) {
      idxDir->data[i2 + 8] = y->data[i2];
    }

    for (i2 = 0; i2 < 8; i2++) {
      idxDir->data[(i2 + y->size[1]) + 8] = b_sizeA_tmp;
    }

    loop_ub = idxDir->size[1];
    i2 = r0->size[0];
    r0->size[0] = loop_ub;
    emxEnsureCapacity_int32_T(r0, i2);
    for (i2 = 0; i2 < loop_ub; i2++) {
      r0->data[i2] = i2;
    }

    loop_ub = r0->size[0];
    for (i2 = 0; i2 < loop_ub; i2++) {
      idxA->data[r0->data[i2] + idxA->size[0]] = (int)idxDir->data[i2];
    }

    i2 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(unsigned int)sizeA_idx_2;
    emxEnsureCapacity_uint32_T(y, i2);
    loop_ub = (int)(unsigned int)sizeA_idx_2 - 1;
    for (i2 = 0; i2 <= loop_ub; i2++) {
      y->data[i2] = 1U + i2;
    }

    i2 = idxDir->size[0] * idxDir->size[1];
    idxDir->size[0] = 1;
    idxDir->size[1] = y->size[1];
    emxEnsureCapacity_uint32_T(idxDir, i2);
    loop_ub = y->size[1];
    for (i2 = 0; i2 < loop_ub; i2++) {
      idxDir->data[i2] = y->data[i2];
    }

    emxFree_uint32_T(&y);
    loop_ub = idxDir->size[1];
    i2 = r0->size[0];
    r0->size[0] = loop_ub;
    emxEnsureCapacity_int32_T(r0, i2);
    for (i2 = 0; i2 < loop_ub; i2++) {
      r0->data[i2] = i2;
    }

    loop_ub = r0->size[0];
    for (i2 = 0; i2 < loop_ub; i2++) {
      idxA->data[r0->data[i2] + (idxA->size[0] << 1)] = (int)idxDir->data[i2];
    }

    emxFree_int32_T(&r0);
    emxFree_uint32_T(&idxDir);
    sizeA_idx_0 = (double)a_tmp->size[0] + 2.0 * pad[0];
    sizeA_idx_1 = (double)a_tmp->size[1] + 2.0 * pad[1];
    sizeA_idx_2 = (double)a_tmp->size[2] + 2.0 * pad[2];
    i2 = a->size[0] * a->size[1] * a->size[2];
    a->size[0] = (int)sizeA_idx_0;
    a->size[1] = (int)sizeA_idx_1;
    a->size[2] = (int)sizeA_idx_2;
    emxEnsureCapacity_uint8_T(a, i2);
    i2 = a->size[2];
    for (loop_ub = 0; loop_ub < i2; loop_ub++) {
      i3 = a->size[1];
      for (j = 0; j < i3; j++) {
        i4 = a->size[0];
        for (i = 0; i < i4; i++) {
          a->data[(i + a->size[0] * j) + a->size[0] * a->size[1] * loop_ub] =
            a_tmp->data[((idxA->data[i] + a_tmp->size[0] * (idxA->data[j +
            idxA->size[0]] - 1)) + a_tmp->size[0] * a_tmp->size[1] * (idxA->
            data[loop_ub + (idxA->size[0] << 1)] - 1)) - 1];
        }
      }
    }

    emxFree_int32_T(&idxA);
  }
}

//
// File trailer for imfilter.cpp
//
// [EOF]
//
