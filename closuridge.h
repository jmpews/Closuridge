#if defined(__arm64__) || defined(__aarch64__)
typedef union FPReg_ {
    __int128_t q;
    struct {
        double d1;
        double d2;
    } d;
    struct {
        float f1;
        float f2;
        float f3;
        float f4;
    } f;
} FPReg;

typedef struct _RegState {
    char *sp;

    union {
        uint64_t x[29];
        struct {
            uint64_t x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21,
                x22, x23, x24, x25, x26, x27, x28;
        } regs;
    } general;

    uint64_t fp;
    uint64_t lr;

    union {
        FPReg q[8];
        struct {
            FPReg q0, q1, q2, q3, q4, q5, q6, q7;
        } regs;
    } floating;
} RegState;
#elif defined(__arm__)
typedef struct _RegState {
    uint32_t sp;

    union {
        uint32_t r[13];
        struct {
            uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12;
        } regs;
    } general;

    uint32_t lr;
} RegState;
#endif

typedef void (*PRECALL)(RegState *rs);