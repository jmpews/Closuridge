#include <mach/mach.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _BridageTable {
    vm_address_t entry;
    vm_address_t data_page;
    vm_address_t trampoline_page;

    uint16_t used_count;

    struct _BridageTable *prev;
    struct _BridageTable *next;
} BridageTable;

typedef struct _ClosuridgeCore {
    BridageTable *head;
    BridageTable *tail;
    uint16_t count;
} ClosuridgeCore;

static BridageTable *BridageTableAllocate(void) {
    vm_address_t data_page;
    vm_address_t trampoline_page;

    kern_return_t kt;

    /* Allocate two pages -- a config page and a placeholder page */
    data_page = 0x0;
    kt        = vm_allocate(mach_task_self(), &config_page, PAGE_MAX_SIZE * 2, VM_FLAGS_ANYWHERE);
    if (kt != KERN_SUCCESS)
        return NULL;
    return NULL;
}