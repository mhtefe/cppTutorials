//
// File: svd1.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-May-2019 18:54:44
//

// Include Files
#include <cmath>
#include <string.h>
#include "rt_nonfinite.h"
#include "smoother.h"
#include "svd1.h"
#include "xrot.h"
#include "xrotg.h"
#include "sqrt.h"
#include "xswap.h"
#include "xaxpy.h"
#include "xdotc.h"
#include "xnrm2.h"

// Function Definitions

//
// Arguments    : const double A[289]
//                double U[289]
//                double s[17]
//                double V[289]
// Return Type  : void
//
void b_svd(const double A[289], double U[289], double s[17], double V[289])
{
  double b_A[289];
  double e[17];
  double work[17];
  int q;
  int m;
  int qp1;
  int qq;
  boolean_T apply_transform;
  double nrm;
  int k;
  int qjj;
  int qp1jj;
  double snorm;
  double r;
  int exitg1;
  boolean_T exitg2;
  double scale;
  double sm;
  double sqds;
  double b;
  memcpy(&b_A[0], &A[0], 289U * sizeof(double));
  memset(&s[0], 0, 17U * sizeof(double));
  memset(&e[0], 0, 17U * sizeof(double));
  memset(&work[0], 0, 17U * sizeof(double));
  memset(&U[0], 0, 289U * sizeof(double));
  memset(&V[0], 0, 289U * sizeof(double));
  for (q = 0; q < 16; q++) {
    qp1 = q + 2;
    qq = (q + 17 * q) + 1;
    apply_transform = false;
    nrm = xnrm2(17 - q, b_A, qq);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[qq - 1] < 0.0) {
        nrm = -nrm;
      }

      s[q] = nrm;
      if (std::abs(nrm) >= 1.0020841800044864E-292) {
        nrm = 1.0 / nrm;
        qp1jj = (qq - q) + 16;
        for (k = qq; k <= qp1jj; k++) {
          b_A[k - 1] *= nrm;
        }
      } else {
        qp1jj = (qq - q) + 16;
        for (k = qq; k <= qp1jj; k++) {
          b_A[k - 1] /= s[q];
        }
      }

      b_A[qq - 1]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0;
    }

    for (k = qp1; k < 18; k++) {
      qjj = q + 17 * (k - 1);
      if (apply_transform) {
        xaxpy(17 - q, -(xdotc(17 - q, b_A, qq, b_A, qjj + 1) / b_A[q + 17 * q]),
              qq, b_A, qjj + 1);
      }

      e[k - 1] = b_A[qjj];
    }

    for (k = q + 1; k < 18; k++) {
      qjj = (k + 17 * q) - 1;
      U[qjj] = b_A[qjj];
    }

    if (q + 1 <= 15) {
      nrm = b_xnrm2(16 - q, e, q + 2);
      if (nrm == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -nrm;
        } else {
          e[q] = nrm;
        }

        nrm = e[q];
        if (std::abs(e[q]) >= 1.0020841800044864E-292) {
          nrm = 1.0 / e[q];
          for (k = qp1; k < 18; k++) {
            e[k - 1] *= nrm;
          }
        } else {
          for (k = qp1; k < 18; k++) {
            e[k - 1] /= nrm;
          }
        }

        e[q + 1]++;
        e[q] = -e[q];
        for (k = qp1; k < 18; k++) {
          work[k - 1] = 0.0;
        }

        for (k = qp1; k < 18; k++) {
          b_xaxpy(16 - q, e[k - 1], b_A, (q + 17 * (k - 1)) + 2, work, q + 2);
        }

        for (k = qp1; k < 18; k++) {
          c_xaxpy(16 - q, -e[k - 1] / e[q + 1], work, q + 2, b_A, (q + 17 * (k -
                    1)) + 2);
        }
      }

      for (k = qp1; k < 18; k++) {
        V[(k + 17 * q) - 1] = e[k - 1];
      }
    }
  }

  m = 15;
  s[16] = b_A[288];
  e[15] = b_A[287];
  e[16] = 0.0;
  memset(&U[272], 0, 17U * sizeof(double));
  U[288] = 1.0;
  for (q = 15; q >= 0; q--) {
    qp1 = q + 2;
    qq = q + 17 * q;
    if (s[q] != 0.0) {
      for (k = qp1; k < 18; k++) {
        qjj = (q + 17 * (k - 1)) + 1;
        xaxpy(17 - q, -(xdotc(17 - q, U, qq + 1, U, qjj) / U[qq]), qq + 1, U,
              qjj);
      }

      for (k = q + 1; k < 18; k++) {
        qjj = (k + 17 * q) - 1;
        U[qjj] = -U[qjj];
      }

      U[qq]++;
      for (k = 0; k < q; k++) {
        U[k + 17 * q] = 0.0;
      }
    } else {
      memset(&U[q * 17], 0, 17U * sizeof(double));
      U[qq] = 1.0;
    }
  }

  for (q = 16; q >= 0; q--) {
    if ((q + 1 <= 15) && (e[q] != 0.0)) {
      qp1 = q + 2;
      qjj = (q + 17 * q) + 2;
      for (k = qp1; k < 18; k++) {
        qp1jj = (q + 17 * (k - 1)) + 2;
        xaxpy(16 - q, -(xdotc(16 - q, V, qjj, V, qp1jj) / V[qjj - 1]), qjj, V,
              qp1jj);
      }
    }

    memset(&V[q * 17], 0, 17U * sizeof(double));
    V[q + 17 * q] = 1.0;
  }

  qq = 0;
  snorm = 0.0;
  for (q = 0; q < 17; q++) {
    if (s[q] != 0.0) {
      nrm = std::abs(s[q]);
      r = s[q] / nrm;
      s[q] = nrm;
      if (q + 1 < 17) {
        e[q] /= r;
      }

      qjj = 17 * q;
      qp1jj = qjj + 17;
      for (k = qjj + 1; k <= qp1jj; k++) {
        U[k - 1] *= r;
      }
    }

    if ((q + 1 < 17) && (e[q] != 0.0)) {
      nrm = std::abs(e[q]);
      r = nrm / e[q];
      e[q] = nrm;
      s[q + 1] *= r;
      qjj = 17 * (q + 1);
      qp1jj = qjj + 17;
      for (k = qjj + 1; k <= qp1jj; k++) {
        V[k - 1] *= r;
      }
    }

    nrm = std::abs(s[q]);
    r = std::abs(e[q]);
    if ((nrm > r) || rtIsNaN(r)) {
      r = nrm;
    }

    if ((!(snorm > r)) && (!rtIsNaN(r))) {
      snorm = r;
    }
  }

  while ((m + 2 > 0) && (qq < 75)) {
    k = m;
    do {
      exitg1 = 0;
      q = k + 1;
      if (k + 1 == 0) {
        exitg1 = 1;
      } else {
        nrm = std::abs(e[k]);
        if ((nrm <= 2.2204460492503131E-16 * (std::abs(s[k]) + std::abs(s[k + 1])))
            || (nrm <= 1.0020841800044864E-292) || ((qq > 20) && (nrm <=
              2.2204460492503131E-16 * snorm))) {
          e[k] = 0.0;
          exitg1 = 1;
        } else {
          k--;
        }
      }
    } while (exitg1 == 0);

    if (k + 1 == m + 1) {
      qjj = 4;
    } else {
      qp1jj = m + 2;
      qjj = m + 2;
      exitg2 = false;
      while ((!exitg2) && (qjj >= k + 1)) {
        qp1jj = qjj;
        if (qjj == k + 1) {
          exitg2 = true;
        } else {
          nrm = 0.0;
          if (qjj < m + 2) {
            nrm = std::abs(e[qjj - 1]);
          }

          if (qjj > k + 2) {
            nrm += std::abs(e[qjj - 2]);
          }

          r = std::abs(s[qjj - 1]);
          if ((r <= 2.2204460492503131E-16 * nrm) || (r <=
               1.0020841800044864E-292)) {
            s[qjj - 1] = 0.0;
            exitg2 = true;
          } else {
            qjj--;
          }
        }
      }

      if (qp1jj == k + 1) {
        qjj = 3;
      } else if (qp1jj == m + 2) {
        qjj = 1;
      } else {
        qjj = 2;
        q = qp1jj;
      }
    }

    switch (qjj) {
     case 1:
      r = e[m];
      e[m] = 0.0;
      qp1jj = m + 1;
      for (k = qp1jj; k >= q + 1; k--) {
        xrotg(&s[k - 1], &r, &sm, &sqds);
        if (k > q + 1) {
          b = e[k - 2];
          r = -sqds * b;
          e[k - 2] = b * sm;
        }

        xrot(V, 1 + 17 * (k - 1), 1 + 17 * (m + 1), sm, sqds);
      }
      break;

     case 2:
      r = e[q - 1];
      e[q - 1] = 0.0;
      for (k = q + 1; k <= m + 2; k++) {
        xrotg(&s[k - 1], &r, &sm, &sqds);
        b = e[k - 1];
        r = -sqds * b;
        e[k - 1] = b * sm;
        xrot(U, 1 + 17 * (k - 1), 1 + 17 * (q - 1), sm, sqds);
      }
      break;

     case 3:
      qjj = m + 1;
      nrm = s[m + 1];
      scale = std::abs(nrm);
      r = std::abs(s[m]);
      if ((!(scale > r)) && (!rtIsNaN(r))) {
        scale = r;
      }

      r = std::abs(e[m]);
      if ((!(scale > r)) && (!rtIsNaN(r))) {
        scale = r;
      }

      r = std::abs(s[q]);
      if ((!(scale > r)) && (!rtIsNaN(r))) {
        scale = r;
      }

      r = std::abs(e[q]);
      if ((!(scale > r)) && (!rtIsNaN(r))) {
        scale = r;
      }

      sm = nrm / scale;
      nrm = s[m] / scale;
      r = e[m] / scale;
      sqds = s[q] / scale;
      b = ((nrm + sm) * (nrm - sm) + r * r) / 2.0;
      nrm = sm * r;
      nrm *= nrm;
      if ((b != 0.0) || (nrm != 0.0)) {
        r = b * b + nrm;
        b_sqrt(&r);
        if (b < 0.0) {
          r = -r;
        }

        r = nrm / (b + r);
      } else {
        r = 0.0;
      }

      r += (sqds + sm) * (sqds - sm);
      nrm = sqds * (e[q] / scale);
      for (k = q + 1; k <= qjj; k++) {
        xrotg(&r, &nrm, &sm, &sqds);
        if (k > q + 1) {
          e[k - 2] = r;
        }

        b = e[k - 1];
        nrm = s[k - 1];
        e[k - 1] = sm * b - sqds * nrm;
        r = sqds * s[k];
        s[k] *= sm;
        xrot(V, 1 + 17 * (k - 1), 1 + 17 * k, sm, sqds);
        s[k - 1] = sm * nrm + sqds * b;
        xrotg(&s[k - 1], &r, &sm, &sqds);
        b = e[k - 1];
        r = sm * b + sqds * s[k];
        s[k] = -sqds * b + sm * s[k];
        nrm = sqds * e[k];
        e[k] *= sm;
        xrot(U, 1 + 17 * (k - 1), 1 + 17 * k, sm, sqds);
      }

      e[m] = r;
      qq++;
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
        qjj = 17 * q;
        qp1jj = qjj + 17;
        for (k = qjj + 1; k <= qp1jj; k++) {
          V[k - 1] = -V[k - 1];
        }
      }

      qp1 = q + 1;
      while ((q + 1 < 17) && (s[q] < s[qp1])) {
        nrm = s[q];
        s[q] = s[qp1];
        s[qp1] = nrm;
        xswap(V, 1 + 17 * q, 1 + 17 * (q + 1));
        xswap(U, 1 + 17 * q, 1 + 17 * (q + 1));
        q = qp1;
        qp1++;
      }

      qq = 0;
      m--;
      break;
    }
  }
}

//
// File trailer for svd1.cpp
//
// [EOF]
//
