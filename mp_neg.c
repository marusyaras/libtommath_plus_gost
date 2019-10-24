#include "tommath_private.h"
#ifdef MP_NEG_C
/* LibTomMath, multiple-precision integer library -- Tom St Denis */
/* SPDX-License-Identifier: Unlicense */

/* b = -a */
mp_err mp_neg(const mp_int *a, mp_int *b)
{
   mp_err err;
   if (a != b) {
      if ((err = mp_copy(a, b)) != MP_OKAY) {
         return err;
      }
   }

   if (!mp_iszero(b)) {
      b->sign = (a->sign == MP_ZPOS) ? MP_NEG : MP_ZPOS;
   } else {
      b->sign = MP_ZPOS;
   }

   return MP_OKAY;
}
#endif
