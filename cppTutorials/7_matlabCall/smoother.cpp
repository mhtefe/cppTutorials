//
// File: smoother.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//

// Include Files
#include <cmath>
#include <string.h>
#include "rt_nonfinite.h"
#include "smoother.h"
#include "smoother_emxutil.h"
#include "svd1.h"
#include "anyNonFinite.h"
#include "imfilter.h"
#include "sum.h"
#include "diag.h"
#include "svd.h"
#include "imread.h"
#include "libmwippfilter.h"
#include "libmwimfilter.h"

// Function Declarations
static double rt_roundd_snf(double u);

// Function Definitions

//
// Arguments    : double u
// Return Type  : double
//
static double rt_roundd_snf(double u)
{
  double y;
  if (std::abs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = std::floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = std::ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

//
// Arguments    : const char pth[9]
//                emxArray_uint8_T *output_args
// Return Type  : void
//
void smoother(const char pth[9], emxArray_uint8_T *output_args)
{
  double outSizeT[3];
  double startT[3];
  static const double h[289] = { 0.00019488687389578179, 0.00031142833774056212,
    0.00046750930690707231, 0.00065929379617042779, 0.00087342237269107809,
    0.0010869917053868189, 0.0012708220536009774, 0.0013957249774454289,
    0.0014400300441611551, 0.0013957249774454289, 0.0012708220536009774,
    0.0010869917053868189, 0.00087342237269107809, 0.00065929379617042779,
    0.00046750930690707231, 0.00031142833774056212, 0.00019488687389578179,
    0.00031142833774056212, 0.00049766106669510749, 0.0007470777452470756,
    0.0010535484864610237, 0.0013957249774454289, 0.0017370077993422159,
    0.0020307678593512817, 0.0022303621633402459, 0.0023011614583617352,
    0.0022303621633402459, 0.0020307678593512817, 0.0017370077993422159,
    0.0013957249774454289, 0.0010535484864610237, 0.0007470777452470756,
    0.00049766106669510749, 0.00031142833774056212, 0.00046750930690707231,
    0.0007470777452470756, 0.0011214965260390572, 0.0015815635990990187,
    0.00209523135104675, 0.0026075575467996021, 0.0030485436274119157,
    0.0033481701655666248, 0.0034544524955085437, 0.0033481701655666248,
    0.0030485436274119157, 0.0026075575467996021, 0.00209523135104675,
    0.0015815635990990187, 0.0011214965260390572, 0.0007470777452470756,
    0.00046750930690707231, 0.00065929379617042779, 0.0010535484864610237,
    0.0015815635990990187, 0.0022303621633402459, 0.0029547498004386975,
    0.0036772455400638166, 0.0042991355919831491, 0.0047216767368435811,
    0.00487155884558024, 0.0047216767368435811, 0.0042991355919831491,
    0.0036772455400638166, 0.0029547498004386975, 0.0022303621633402459,
    0.0015815635990990187, 0.0010535484864610237, 0.00065929379617042779,
    0.00087342237269107809, 0.0013957249774454289, 0.00209523135104675,
    0.0029547498004386975, 0.003914407501478344, 0.00487155884558024,
    0.0056954293079680756, 0.0062552053766150211, 0.0064537669098754889,
    0.0062552053766150211, 0.0056954293079680756, 0.00487155884558024,
    0.003914407501478344, 0.0029547498004386975, 0.00209523135104675,
    0.0013957249774454289, 0.00087342237269107809, 0.0010869917053868189,
    0.0017370077993422159, 0.0026075575467996021, 0.0036772455400638166,
    0.00487155884558024, 0.0060627529394903946, 0.0070880762961266046,
    0.0077847288694039831, 0.0080318426901755027, 0.0077847288694039831,
    0.0070880762961266046, 0.0060627529394903946, 0.00487155884558024,
    0.0036772455400638166, 0.0026075575467996021, 0.0017370077993422159,
    0.0010869917053868189, 0.0012708220536009774, 0.0020307678593512817,
    0.0030485436274119157, 0.0042991355919831491, 0.0056954293079680756,
    0.0070880762961266046, 0.008286800745658433, 0.0091012701196484681,
    0.0093901754458158761, 0.0091012701196484681, 0.008286800745658433,
    0.0070880762961266046, 0.0056954293079680756, 0.0042991355919831491,
    0.0030485436274119157, 0.0020307678593512817, 0.0012708220536009774,
    0.0013957249774454289, 0.0022303621633402459, 0.0033481701655666248,
    0.0047216767368435811, 0.0062552053766150211, 0.0077847288694039831,
    0.0091012701196484681, 0.00999578973033754, 0.010313090157022991,
    0.00999578973033754, 0.0091012701196484681, 0.0077847288694039831,
    0.0062552053766150211, 0.0047216767368435811, 0.0033481701655666248,
    0.0022303621633402459, 0.0013957249774454289, 0.0014400300441611551,
    0.0023011614583617352, 0.0034544524955085437, 0.00487155884558024,
    0.0064537669098754889, 0.0080318426901755027, 0.0093901754458158761,
    0.010313090157022991, 0.010640462780452355, 0.010313090157022991,
    0.0093901754458158761, 0.0080318426901755027, 0.0064537669098754889,
    0.00487155884558024, 0.0034544524955085437, 0.0023011614583617352,
    0.0014400300441611551, 0.0013957249774454289, 0.0022303621633402459,
    0.0033481701655666248, 0.0047216767368435811, 0.0062552053766150211,
    0.0077847288694039831, 0.0091012701196484681, 0.00999578973033754,
    0.010313090157022991, 0.00999578973033754, 0.0091012701196484681,
    0.0077847288694039831, 0.0062552053766150211, 0.0047216767368435811,
    0.0033481701655666248, 0.0022303621633402459, 0.0013957249774454289,
    0.0012708220536009774, 0.0020307678593512817, 0.0030485436274119157,
    0.0042991355919831491, 0.0056954293079680756, 0.0070880762961266046,
    0.008286800745658433, 0.0091012701196484681, 0.0093901754458158761,
    0.0091012701196484681, 0.008286800745658433, 0.0070880762961266046,
    0.0056954293079680756, 0.0042991355919831491, 0.0030485436274119157,
    0.0020307678593512817, 0.0012708220536009774, 0.0010869917053868189,
    0.0017370077993422159, 0.0026075575467996021, 0.0036772455400638166,
    0.00487155884558024, 0.0060627529394903946, 0.0070880762961266046,
    0.0077847288694039831, 0.0080318426901755027, 0.0077847288694039831,
    0.0070880762961266046, 0.0060627529394903946, 0.00487155884558024,
    0.0036772455400638166, 0.0026075575467996021, 0.0017370077993422159,
    0.0010869917053868189, 0.00087342237269107809, 0.0013957249774454289,
    0.00209523135104675, 0.0029547498004386975, 0.003914407501478344,
    0.00487155884558024, 0.0056954293079680756, 0.0062552053766150211,
    0.0064537669098754889, 0.0062552053766150211, 0.0056954293079680756,
    0.00487155884558024, 0.003914407501478344, 0.0029547498004386975,
    0.00209523135104675, 0.0013957249774454289, 0.00087342237269107809,
    0.00065929379617042779, 0.0010535484864610237, 0.0015815635990990187,
    0.0022303621633402459, 0.0029547498004386975, 0.0036772455400638166,
    0.0042991355919831491, 0.0047216767368435811, 0.00487155884558024,
    0.0047216767368435811, 0.0042991355919831491, 0.0036772455400638166,
    0.0029547498004386975, 0.0022303621633402459, 0.0015815635990990187,
    0.0010535484864610237, 0.00065929379617042779, 0.00046750930690707231,
    0.0007470777452470756, 0.0011214965260390572, 0.0015815635990990187,
    0.00209523135104675, 0.0026075575467996021, 0.0030485436274119157,
    0.0033481701655666248, 0.0034544524955085437, 0.0033481701655666248,
    0.0030485436274119157, 0.0026075575467996021, 0.00209523135104675,
    0.0015815635990990187, 0.0011214965260390572, 0.0007470777452470756,
    0.00046750930690707231, 0.00031142833774056212, 0.00049766106669510749,
    0.0007470777452470756, 0.0010535484864610237, 0.0013957249774454289,
    0.0017370077993422159, 0.0020307678593512817, 0.0022303621633402459,
    0.0023011614583617352, 0.0022303621633402459, 0.0020307678593512817,
    0.0017370077993422159, 0.0013957249774454289, 0.0010535484864610237,
    0.0007470777452470756, 0.00049766106669510749, 0.00031142833774056212,
    0.00019488687389578179, 0.00031142833774056212, 0.00046750930690707231,
    0.00065929379617042779, 0.00087342237269107809, 0.0010869917053868189,
    0.0012708220536009774, 0.0013957249774454289, 0.0014400300441611551,
    0.0013957249774454289, 0.0012708220536009774, 0.0010869917053868189,
    0.00087342237269107809, 0.00065929379617042779, 0.00046750930690707231,
    0.00031142833774056212, 0.00019488687389578179 };

  double unusedU0[289];
  double s[289];
  double unusedU1[289];
  double b_s[17];
  int idx;
  int k;
  boolean_T exitg1;
  double tol;
  int i;
  double d0;
  emxArray_uint8_T *a;
  boolean_T c_s[17];
  boolean_T tooBig;
  emxArray_real_T *b_a;
  double hcol[17];
  double padSizeT[3];
  double connDimsT[2];
  boolean_T conn[289];
  double out_size_row[3];
  double start[3];
  static const double nonZeroKernel[289] = { 0.00019488687389578179,
    0.00031142833774056212, 0.00046750930690707231, 0.00065929379617042779,
    0.00087342237269107809, 0.0010869917053868189, 0.0012708220536009774,
    0.0013957249774454289, 0.0014400300441611551, 0.0013957249774454289,
    0.0012708220536009774, 0.0010869917053868189, 0.00087342237269107809,
    0.00065929379617042779, 0.00046750930690707231, 0.00031142833774056212,
    0.00019488687389578179, 0.00031142833774056212, 0.00049766106669510749,
    0.0007470777452470756, 0.0010535484864610237, 0.0013957249774454289,
    0.0017370077993422159, 0.0020307678593512817, 0.0022303621633402459,
    0.0023011614583617352, 0.0022303621633402459, 0.0020307678593512817,
    0.0017370077993422159, 0.0013957249774454289, 0.0010535484864610237,
    0.0007470777452470756, 0.00049766106669510749, 0.00031142833774056212,
    0.00046750930690707231, 0.0007470777452470756, 0.0011214965260390572,
    0.0015815635990990187, 0.00209523135104675, 0.0026075575467996021,
    0.0030485436274119157, 0.0033481701655666248, 0.0034544524955085437,
    0.0033481701655666248, 0.0030485436274119157, 0.0026075575467996021,
    0.00209523135104675, 0.0015815635990990187, 0.0011214965260390572,
    0.0007470777452470756, 0.00046750930690707231, 0.00065929379617042779,
    0.0010535484864610237, 0.0015815635990990187, 0.0022303621633402459,
    0.0029547498004386975, 0.0036772455400638166, 0.0042991355919831491,
    0.0047216767368435811, 0.00487155884558024, 0.0047216767368435811,
    0.0042991355919831491, 0.0036772455400638166, 0.0029547498004386975,
    0.0022303621633402459, 0.0015815635990990187, 0.0010535484864610237,
    0.00065929379617042779, 0.00087342237269107809, 0.0013957249774454289,
    0.00209523135104675, 0.0029547498004386975, 0.003914407501478344,
    0.00487155884558024, 0.0056954293079680756, 0.0062552053766150211,
    0.0064537669098754889, 0.0062552053766150211, 0.0056954293079680756,
    0.00487155884558024, 0.003914407501478344, 0.0029547498004386975,
    0.00209523135104675, 0.0013957249774454289, 0.00087342237269107809,
    0.0010869917053868189, 0.0017370077993422159, 0.0026075575467996021,
    0.0036772455400638166, 0.00487155884558024, 0.0060627529394903946,
    0.0070880762961266046, 0.0077847288694039831, 0.0080318426901755027,
    0.0077847288694039831, 0.0070880762961266046, 0.0060627529394903946,
    0.00487155884558024, 0.0036772455400638166, 0.0026075575467996021,
    0.0017370077993422159, 0.0010869917053868189, 0.0012708220536009774,
    0.0020307678593512817, 0.0030485436274119157, 0.0042991355919831491,
    0.0056954293079680756, 0.0070880762961266046, 0.008286800745658433,
    0.0091012701196484681, 0.0093901754458158761, 0.0091012701196484681,
    0.008286800745658433, 0.0070880762961266046, 0.0056954293079680756,
    0.0042991355919831491, 0.0030485436274119157, 0.0020307678593512817,
    0.0012708220536009774, 0.0013957249774454289, 0.0022303621633402459,
    0.0033481701655666248, 0.0047216767368435811, 0.0062552053766150211,
    0.0077847288694039831, 0.0091012701196484681, 0.00999578973033754,
    0.010313090157022991, 0.00999578973033754, 0.0091012701196484681,
    0.0077847288694039831, 0.0062552053766150211, 0.0047216767368435811,
    0.0033481701655666248, 0.0022303621633402459, 0.0013957249774454289,
    0.0014400300441611551, 0.0023011614583617352, 0.0034544524955085437,
    0.00487155884558024, 0.0064537669098754889, 0.0080318426901755027,
    0.0093901754458158761, 0.010313090157022991, 0.010640462780452355,
    0.010313090157022991, 0.0093901754458158761, 0.0080318426901755027,
    0.0064537669098754889, 0.00487155884558024, 0.0034544524955085437,
    0.0023011614583617352, 0.0014400300441611551, 0.0013957249774454289,
    0.0022303621633402459, 0.0033481701655666248, 0.0047216767368435811,
    0.0062552053766150211, 0.0077847288694039831, 0.0091012701196484681,
    0.00999578973033754, 0.010313090157022991, 0.00999578973033754,
    0.0091012701196484681, 0.0077847288694039831, 0.0062552053766150211,
    0.0047216767368435811, 0.0033481701655666248, 0.0022303621633402459,
    0.0013957249774454289, 0.0012708220536009774, 0.0020307678593512817,
    0.0030485436274119157, 0.0042991355919831491, 0.0056954293079680756,
    0.0070880762961266046, 0.008286800745658433, 0.0091012701196484681,
    0.0093901754458158761, 0.0091012701196484681, 0.008286800745658433,
    0.0070880762961266046, 0.0056954293079680756, 0.0042991355919831491,
    0.0030485436274119157, 0.0020307678593512817, 0.0012708220536009774,
    0.0010869917053868189, 0.0017370077993422159, 0.0026075575467996021,
    0.0036772455400638166, 0.00487155884558024, 0.0060627529394903946,
    0.0070880762961266046, 0.0077847288694039831, 0.0080318426901755027,
    0.0077847288694039831, 0.0070880762961266046, 0.0060627529394903946,
    0.00487155884558024, 0.0036772455400638166, 0.0026075575467996021,
    0.0017370077993422159, 0.0010869917053868189, 0.00087342237269107809,
    0.0013957249774454289, 0.00209523135104675, 0.0029547498004386975,
    0.003914407501478344, 0.00487155884558024, 0.0056954293079680756,
    0.0062552053766150211, 0.0064537669098754889, 0.0062552053766150211,
    0.0056954293079680756, 0.00487155884558024, 0.003914407501478344,
    0.0029547498004386975, 0.00209523135104675, 0.0013957249774454289,
    0.00087342237269107809, 0.00065929379617042779, 0.0010535484864610237,
    0.0015815635990990187, 0.0022303621633402459, 0.0029547498004386975,
    0.0036772455400638166, 0.0042991355919831491, 0.0047216767368435811,
    0.00487155884558024, 0.0047216767368435811, 0.0042991355919831491,
    0.0036772455400638166, 0.0029547498004386975, 0.0022303621633402459,
    0.0015815635990990187, 0.0010535484864610237, 0.00065929379617042779,
    0.00046750930690707231, 0.0007470777452470756, 0.0011214965260390572,
    0.0015815635990990187, 0.00209523135104675, 0.0026075575467996021,
    0.0030485436274119157, 0.0033481701655666248, 0.0034544524955085437,
    0.0033481701655666248, 0.0030485436274119157, 0.0026075575467996021,
    0.00209523135104675, 0.0015815635990990187, 0.0011214965260390572,
    0.0007470777452470756, 0.00046750930690707231, 0.00031142833774056212,
    0.00049766106669510749, 0.0007470777452470756, 0.0010535484864610237,
    0.0013957249774454289, 0.0017370077993422159, 0.0020307678593512817,
    0.0022303621633402459, 0.0023011614583617352, 0.0022303621633402459,
    0.0020307678593512817, 0.0017370077993422159, 0.0013957249774454289,
    0.0010535484864610237, 0.0007470777452470756, 0.00049766106669510749,
    0.00031142833774056212, 0.00019488687389578179, 0.00031142833774056212,
    0.00046750930690707231, 0.00065929379617042779, 0.00087342237269107809,
    0.0010869917053868189, 0.0012708220536009774, 0.0013957249774454289,
    0.0014400300441611551, 0.0013957249774454289, 0.0012708220536009774,
    0.0010869917053868189, 0.00087342237269107809, 0.00065929379617042779,
    0.00046750930690707231, 0.00031142833774056212, 0.00019488687389578179 };

  int trueCount;
  signed char tmp_data[17];
  double nonzero_h_data[17];
  boolean_T densityFlag;
  emxArray_real_T *b;
  signed char b_tmp_data[17];
  static const double b_startT[3] = { 8.0, 0.0, 0.0 };

  unsigned char u0;
  imread(pth, output_args);
  outSizeT[0] = output_args->size[0];
  startT[0] = 8.0;
  outSizeT[1] = output_args->size[1];
  startT[1] = 8.0;
  outSizeT[2] = output_args->size[2];
  startT[2] = 0.0;
  if ((output_args->size[0] != 0) && (output_args->size[1] != 0) &&
      (output_args->size[2] != 0)) {
    svd(h, unusedU0, s, unusedU1);
    diag(s, b_s);
    if (!rtIsNaN(b_s[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k < 18)) {
        if (!rtIsNaN(b_s[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      tol = b_s[0];
    } else {
      tol = b_s[idx - 1];
      i = idx + 1;
      for (k = i; k < 18; k++) {
        d0 = b_s[k - 1];
        if (tol < d0) {
          tol = d0;
        }
      }
    }

    tol = 17.0 * tol * 2.2204460492503131E-16;
    for (i = 0; i < 17; i++) {
      c_s[i] = (b_s[i] > tol);
    }

    emxInit_uint8_T(&a, 3);
    if (sum(c_s) == 1.0) {
      padImage(output_args, startT, a);
      if (!anyNonFinite()) {
        b_svd(h, unusedU0, b_s, unusedU1);
      } else {
        for (i = 0; i < 289; i++) {
          unusedU0[i] = rtNaN;
        }

        for (i = 0; i < 17; i++) {
          b_s[i] = rtNaN;
        }

        for (i = 0; i < 289; i++) {
          unusedU1[i] = rtNaN;
        }
      }

      memset(&s[0], 0, 289U * sizeof(double));
      for (k = 0; k < 17; k++) {
        s[k + 17 * k] = b_s[k];
      }

      for (k = 0; k < 17; k++) {
        b_s[k] = s[k + 17 * k];
      }

      tol = std::sqrt(b_s[0]);
      for (i = 0; i < 17; i++) {
        hcol[i] = unusedU0[i] * tol;
        b_s[i] = unusedU1[i] * tol;
      }

      emxInit_real_T(&b_a, 3);
      i = b_a->size[0] * b_a->size[1] * b_a->size[2];
      b_a->size[0] = a->size[0];
      b_a->size[1] = a->size[1];
      b_a->size[2] = a->size[2];
      emxEnsureCapacity_real_T(b_a, i);
      idx = a->size[0] * a->size[1] * a->size[2];
      for (i = 0; i < idx; i++) {
        b_a->data[i] = a->data[i];
      }

      out_size_row[0] = b_a->size[0];
      start[0] = 0.0;
      out_size_row[1] = (unsigned int)outSizeT[1];
      start[1] = 8.0;
      out_size_row[2] = (unsigned int)outSizeT[2];
      start[2] = 0.0;
      trueCount = 0;
      for (i = 0; i < 17; i++) {
        if (b_s[i] != 0.0) {
          trueCount++;
        }
      }

      idx = 0;
      for (i = 0; i < 17; i++) {
        if (b_s[i] != 0.0) {
          tmp_data[idx] = (signed char)(i + 1);
          idx++;
        }
      }

      for (i = 0; i < trueCount; i++) {
        nonzero_h_data[i] = b_s[tmp_data[i] - 1];
      }

      for (i = 0; i < 17; i++) {
        c_s[i] = (b_s[i] != 0.0);
      }

      densityFlag = false;
      if ((double)trueCount / 17.0 > 0.05) {
        densityFlag = true;
      }

      tooBig = true;
      k = 3;
      if (b_a->size[2] == 1) {
        k = 2;
      }

      for (i = 0; i < k; i++) {
        if (tooBig && ((int)(unsigned int)out_size_row[i] > 65500)) {
          tooBig = true;
        } else {
          tooBig = false;
        }
      }

      if (densityFlag && (!tooBig)) {
        tooBig = true;
      } else {
        tooBig = false;
      }

      emxInit_real_T(&b, 3);
      i = b->size[0] * b->size[1] * b->size[2];
      b->size[0] = (int)out_size_row[0];
      b->size[1] = (int)out_size_row[1];
      b->size[2] = (int)out_size_row[2];
      emxEnsureCapacity_real_T(b, i);
      if (tooBig) {
        k = 3;
        if (b_a->size[2] == 1) {
          k = 2;
        }

        padSizeT[0] = b_a->size[0];
        padSizeT[1] = b_a->size[1];
        padSizeT[2] = b_a->size[2];
        connDimsT[0] = 1.0;
        connDimsT[1] = 17.0;
        ippfilter_real64(&b_a->data[0], &b->data[0], out_size_row, (double)k,
                         padSizeT, b_s, connDimsT, false);
      } else {
        k = 3;
        if (b_a->size[2] == 1) {
          k = 2;
        }

        padSizeT[0] = b_a->size[0];
        padSizeT[1] = b_a->size[1];
        padSizeT[2] = b_a->size[2];
        connDimsT[0] = 1.0;
        connDimsT[1] = 17.0;
        imfilter_real64(&b_a->data[0], &b->data[0], 3.0, out_size_row, (double)k,
                        padSizeT, &nonzero_h_data[0], (double)trueCount, c_s,
                        2.0, connDimsT, start, 3.0, true, false);
      }

      trueCount = 0;
      for (i = 0; i < 17; i++) {
        if (hcol[i] != 0.0) {
          trueCount++;
        }
      }

      idx = 0;
      for (i = 0; i < 17; i++) {
        if (hcol[i] != 0.0) {
          b_tmp_data[idx] = (signed char)(i + 1);
          idx++;
        }
      }

      for (i = 0; i < trueCount; i++) {
        nonzero_h_data[i] = hcol[b_tmp_data[i] - 1];
      }

      for (i = 0; i < 17; i++) {
        c_s[i] = (hcol[i] != 0.0);
      }

      densityFlag = false;
      if ((double)trueCount / 17.0 > 0.05) {
        densityFlag = true;
      }

      tooBig = true;
      k = 3;
      if (b->size[2] == 1) {
        k = 2;
      }

      for (i = 0; i < k; i++) {
        if (tooBig && ((int)(unsigned int)outSizeT[i] > 65500)) {
          tooBig = true;
        } else {
          tooBig = false;
        }
      }

      if (densityFlag && (!tooBig)) {
        tooBig = true;
      } else {
        tooBig = false;
      }

      i = b_a->size[0] * b_a->size[1] * b_a->size[2];
      b_a->size[0] = b->size[0];
      b_a->size[1] = b->size[1];
      b_a->size[2] = b->size[2];
      emxEnsureCapacity_real_T(b_a, i);
      idx = b->size[0] * b->size[1] * b->size[2];
      for (i = 0; i < idx; i++) {
        b_a->data[i] = b->data[i];
      }

      i = b->size[0] * b->size[1] * b->size[2];
      b->size[0] = (int)outSizeT[0];
      b->size[1] = (int)outSizeT[1];
      b->size[2] = (int)outSizeT[2];
      emxEnsureCapacity_real_T(b, i);
      if (tooBig) {
        k = 3;
        if (b_a->size[2] == 1) {
          k = 2;
        }

        padSizeT[0] = b_a->size[0];
        padSizeT[1] = b_a->size[1];
        padSizeT[2] = b_a->size[2];
        connDimsT[0] = 17.0;
        connDimsT[1] = 1.0;
        ippfilter_real64(&b_a->data[0], &b->data[0], outSizeT, (double)k,
                         padSizeT, hcol, connDimsT, false);
      } else {
        k = 3;
        if (b_a->size[2] == 1) {
          k = 2;
        }

        padSizeT[0] = b_a->size[0];
        padSizeT[1] = b_a->size[1];
        padSizeT[2] = b_a->size[2];
        connDimsT[0] = 17.0;
        connDimsT[1] = 1.0;
        imfilter_real64(&b_a->data[0], &b->data[0], 3.0, outSizeT, (double)k,
                        padSizeT, &nonzero_h_data[0], (double)trueCount, c_s,
                        2.0, connDimsT, b_startT, 3.0, true, false);
      }

      emxFree_real_T(&b_a);
      i = output_args->size[0] * output_args->size[1] * output_args->size[2];
      output_args->size[0] = b->size[0];
      output_args->size[1] = b->size[1];
      output_args->size[2] = b->size[2];
      emxEnsureCapacity_uint8_T(output_args, i);
      idx = b->size[0] * b->size[1] * b->size[2];
      for (i = 0; i < idx; i++) {
        d0 = rt_roundd_snf(b->data[i]);
        if (d0 < 256.0) {
          if (d0 >= 0.0) {
            u0 = (unsigned char)d0;
          } else {
            u0 = 0U;
          }
        } else if (d0 >= 256.0) {
          u0 = MAX_uint8_T;
        } else {
          u0 = 0U;
        }

        output_args->data[i] = u0;
      }

      emxFree_real_T(&b);
    } else {
      padImage(output_args, startT, a);
      tooBig = true;
      k = 3;
      if (a->size[2] == 1) {
        k = 2;
      }

      for (i = 0; i < k; i++) {
        if (tooBig && ((int)(unsigned int)outSizeT[i] > 65500)) {
          tooBig = true;
        } else {
          tooBig = false;
        }
      }

      i = output_args->size[0] * output_args->size[1] * output_args->size[2];
      output_args->size[0] = (int)outSizeT[0];
      output_args->size[1] = (int)outSizeT[1];
      output_args->size[2] = (int)outSizeT[2];
      emxEnsureCapacity_uint8_T(output_args, i);
      if (!tooBig) {
        k = 3;
        if (a->size[2] == 1) {
          k = 2;
        }

        padSizeT[0] = a->size[0];
        padSizeT[1] = a->size[1];
        padSizeT[2] = a->size[2];
        connDimsT[0] = 17.0;
        connDimsT[1] = 17.0;
        ippfilter_uint8(&a->data[0], &output_args->data[0], outSizeT, (double)k,
                        padSizeT, h, connDimsT, false);
      } else {
        k = 3;
        if (a->size[2] == 1) {
          k = 2;
        }

        padSizeT[0] = a->size[0];
        padSizeT[1] = a->size[1];
        padSizeT[2] = a->size[2];
        for (i = 0; i < 289; i++) {
          conn[i] = true;
        }

        connDimsT[0] = 17.0;
        connDimsT[1] = 17.0;
        imfilter_uint8(&a->data[0], &output_args->data[0], 3.0, outSizeT,
                       (double)k, padSizeT, nonZeroKernel, 289.0, conn, 2.0,
                       connDimsT, startT, 3.0, true, false);
      }
    }

    emxFree_uint8_T(&a);
  }
}

//
// File trailer for smoother.cpp
//
// [EOF]
//