// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <openenclave/enclave.h>
#include <openenclave/internal/thread.h>
#include <openenclave/internal/utils.h>

oe_result_t oe_once(oe_once_t* once, void (*func)(void))
{
    if (!once)
        return OE_INVALID_PARAMETER;

    /* Double checked locking (DCLP). */
    /* DCLP Acquire barrier. */
    OE_ATOMIC_MEMORY_BARRIER_ACQUIRE();
    if (*once != 2)
    {
        oe_once_t retval = __sync_val_compare_and_swap(once, 0, 1);
        if (retval == 0)
        {
            if (func)
                func();

            OE_ATOMIC_MEMORY_BARRIER_RELEASE();
            *once = 2;  
        }
        else if (retval == 1)
        {
            while (__sync_val_compare_and_swap(once, 2, 2) != 2)
            {
               asm volatile("pause");
            }
        }
    }

    return OE_OK;
}
