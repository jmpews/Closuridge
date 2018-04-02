#include <mach/mach.h>
#include <mach/vm_page_size.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "debuglog_kit.h"

extern void *trampoline_table_page_template;

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
    vm_address_t trampoline_page_template;
    vm_prot_t cur_prot;
    vm_prot_t max_prot;

    kern_return_t kt;

    /* Allocate two pages -- a config page and a placeholder page */
    data_page = 0x0;
    kt        = vm_allocate(mach_task_self(), &data_page, PAGE_MAX_SIZE * 2, VM_FLAGS_ANYWHERE);
    if (kt != KERN_SUCCESS) {
        COMMON_ERROR_LOG();
        return NULL;
    }

    // Remap the trampoline table on top of the placeholder page
    trampoline_page          = data_page + PAGE_MAX_SIZE;
    trampoline_page_template = (vm_address_t)&trampoline_table_page_template;
#ifdef __arm__
    // ffi_closure_trampoline_table_page can be thumb-biased on some ARM archs
    trampoline_page_template &= ~1UL;
#endif
    kt = vm_remap(mach_task_self(), &trampoline_page, PAGE_MAX_SIZE, 0x0, VM_FLAGS_OVERWRITE, mach_task_self(),
                  trampoline_page_template, FALSE, &cur_prot, &max_prot, VM_INHERIT_SHARE);
    if (kt != KERN_SUCCESS) {
        vm_deallocate(mach_task_self(), data_page, PAGE_MAX_SIZE * 2);
        return NULL;
    }
    return NULL;
}