#ifdef __MACH__
#include <mach/machine/vm_param.h>
    .align PAGE_MAX_SHIFT
CNAME(ffi_closure_trampoline_table_page):
    .rept PAGE_MAX_SIZE / FFI_TRAMPOLINE_SIZE
    adr x16, -PAGE_MAX_SIZE
    ldp x17, x16, [x16]
    br x16
	nop		/* each entry in the trampoline config page is 2*sizeof(void*) so the trampoline itself cannot be smaller that 16 bytes */
    .endr
#endif