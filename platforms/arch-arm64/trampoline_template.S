#if defined(__WIN32__) || defined(__APPLE__)
#define cdecl(s) _##s
#else
#define cdecl(s) s
#endif

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

#include <mach/machine/vm_param.h>
.align PAGE_MAX_SHIFT

cdecl(forward_bridge):

// ======= RegState Save =======

// store {q0-q7}
sub sp, sp, #(8*16)
stp q6, q7, [sp, #(6*16)]
stp q4, q5, [sp, #(4*16)]
stp q2, q3, [sp, #(2*16)]
stp q0, q1, [sp, #(0*16)]

// store {x1-x30}
sub sp, sp, #(30*8)
// stp fp, lr, [sp, #(28*8)]
stp x29, x30, [sp, #(28*8)]
stp x27, x28, [sp, #(26*8)]
stp x25, x26, [sp, #(24*8)]
stp x23, x24, [sp, #(22*8)]
stp x21, x22, [sp, #(20*8)]
stp x19, x20, [sp, #(18*8)]
stp x17, x18, [sp, #(16*8)]
stp x15, x16, [sp, #(14*8)]
stp x13, x14, [sp, #(12*8)]
stp x11, x12, [sp, #(10*8)]
stp x9, x10, [sp, #(8*8)]
stp x7, x8, [sp, #(6*8)]
stp x5, x6, [sp, #(4*8)]
stp x3, x4, [sp, #(2*8)]
stp x1, x2, [sp, #(0*8)]

// store {x0, sp}
// store x0 and reserve sp, but this is trick
sub sp, sp, #(2*8)
str x0, [sp, #8]
add x1, sp, #(8*16+30*8+2*8)
str x1, [sp, #0]

// ======= Jump to Common Bridge Handle =======

mov x0, sp
sub x16, x16, 0x4000
ldr x16, [x16, #0x0]
mov x1, x16
ldr x16, [x16, #(3*8)] ; current x16 is internal_common_bridge_start
blr x16

// ======= RegState Restore =======

// restore {x0}
ldr x0, [sp, #8]
add sp, sp, #(2*8)

// restore {x1-x30}
ldp x1, x2, [sp], #16
ldp x3, x4, [sp], #16
ldp x5, x6, [sp], #16
ldp x7, x8, [sp], #16
ldp x9, x10, [sp], #16
ldp x11, x12, [sp], #16
ldp x13, x14, [sp], #16
ldp x15, x16, [sp], #16
ldp x17, x18, [sp], #16
ldp x19, x20, [sp], #16
ldp x21, x22, [sp], #16
ldp x23, x24, [sp], #16
ldp x25, x26, [sp], #16
ldp x27, x28, [sp], #16
// ldp fp, lr, [sp], #16
ldp x29, x30, [sp], #16

// restore {q0-q7}
ldp q0, q1, [sp], #32
ldp q2, q3, [sp], #32
ldp q4, q5, [sp], #32
ldp q6, q7, [sp], #32

ret lr

cdecl(trampoline_table):
.rept  (PAGE_MAX_SIZE - 0x24 * 4) / 8
adr x16, #0
b cdecl(forward_bridge)
.endr