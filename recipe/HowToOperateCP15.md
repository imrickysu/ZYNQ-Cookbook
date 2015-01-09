# How to Operate CP15 with SDK

CP15 is the coprocessor of ARM. It takes charge of MMU, Cache, etc.

It doesn't have direct memory space access from AXI bus. CPU needs to use `MCR` and `MRC` assembly to access CP15 registers. External masters can't access CP15 registers.

While it is possible to embed [inline assembly](http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html) in C applications, SDK provides some helper functions to make CP15 register accessing easier. In `xpseudo_asm_gcc.h`, it has `mtcp()` and `mfcp()` functions for Microprocessor accessing to and from coprocessor.

Here is an example reading CP15 Affinity Register to check which CPU number this program is running on.

```C
#include <stdio.h>
#include "xreg_cortexa9.h"  // CP15 register names
#include "xpseudo_asm_gcc.h" // CP15 accessing helper functions

int main()
{
  int id;

  id = mfcp(XREG_CP15_MULTI_PROC_AFFINITY);
  xil_printf("Affinity Register %x", id);

  return 0;
}


```
