#include <lpae.h>

#include <log/print.h>
#include <log/uart_print.h>

/**
 * \defgroup LPAE_address_mask
 *
 * The address mask of each level descriptors.
 * - TTBL_L1_OUTADDR_MASK[47:39] Level0 Block address mask.
 * - TTBL_L1_OUTADDR_MASK[47:30] Level1 Block address mask.
 * - TTBL_L2_OUTADDR_MASK[47:21] Level2 Block Address mask.
 * - TTBL_L3_OUTADDR_MASK[47:12] Page address mask.
 *
 * - TTBL_L0_TABADDR_MASK[47:12] Level0 table descriptor address mask.
 * - TTBL_L1_TABADDR_MASK[47:12] Level1 table descriptor address mask.
 * - TTBL_L2_TABADDR_MASK[47:12] Level2 table descriptor address mask.
 * - TTBL_L3_TABADDR_MASK[47:12] Level3 table descriptor address mask.
 * @{
 */
#define TTBL_L0_OUTADDR_MASK    0x0000FF8000000000ULL
#define TTBL_L1_OUTADDR_MASK    0x0000FFFFC0000000ULL
#define TTBL_L2_OUTADDR_MASK    0x0000FFFFFFE00000ULL
#define TTBL_L3_OUTADDR_MASK    0x0000FFFFFFFFF000ULL

#define TTBL_L0_TABADDR_MASK    0x0000FFFFFFFFF000ULL
#define TTBL_L1_TABADDR_MASK    0x0000FFFFFFFFF000ULL
#define TTBL_L2_TABADDR_MASK    0x0000FFFFFFFFF000ULL
#define TTBL_L3_TABADDR_MASK    0x0000FFFFFFFFF000ULL
/**
 * @}
 */

/*
 * Level 2 Block, 2MB, entry in LPAE Descriptor format
 * for the given physical address
 */
union lpaed lpaed_host_l2_block(uint64_t pa,
        enum memattr mattr)
{
    /* lpae.c */
    union lpaed lpaed;
    /* Valid Block Entry */
    lpaed.pt.valid = 1;
    lpaed.pt.table = 0;
    lpaed.bits &= ~TTBL_L2_OUTADDR_MASK;
    lpaed.bits |= pa & TTBL_L2_OUTADDR_MASK;
    lpaed.p2m.sbz3 = 0;
    /* Lower block attributes */
    lpaed.p2m.mattr = mattr & 0x0F;
    lpaed.p2m.read = 1;        /* Read/Write */
    lpaed.p2m.write = 1;
    lpaed.p2m.sh = 0;    /* Non-shareable */
    lpaed.p2m.af = 1;    /* Access Flag set to 1?  */
    lpaed.p2m.sbz4 = 0;
    /* Upper block attributes */
    lpaed.p2m.hint = 0;
    lpaed.p2m.sbz2 = 0;
    lpaed.p2m.xn = 0;    /* eXecute Never = 0 */
    lpaed.p2m.sbz1 = 0;
    return lpaed;
}

/*
 * Level 1 Block, 1GB, entry in LPAE Descriptor format
 * for the given physical address
 */
union lpaed lpaed_host_l1_block(uint64_t pa, uint8_t attr_idx)
{
    /* lpae.c */
    union lpaed lpaed;
    printh("[mm] hvmm_mm_lpaed_l1_block:\n\r");
    printh(" pa:");
    uart_print_hex64(pa);
    printh("\n\r");
    printh(" attr_idx:");
    uart_print_hex32((uint32_t) attr_idx);
    printh("\n\r");
    /* Valid Block Entry */
    lpaed.pt.valid = 1;
    lpaed.pt.table = 0;
    lpaed.bits &= ~TTBL_L1_TABADDR_MASK;
    lpaed.bits |= pa & TTBL_L1_OUTADDR_MASK;
    lpaed.pt.sbz = 0;
    /* Lower block attributes */
    lpaed.pt.ai = attr_idx;
    lpaed.pt.ns = 1;    /* Allow Non-secure access */
    lpaed.pt.user = 1;
    lpaed.pt.ro = 0;
    lpaed.pt.sh = 3;    /* Outher Shareable */
    lpaed.pt.af = 1;    /* Access Flag set to 1? */
    lpaed.pt.ng = 1;
    /* Upper block attributes */
    lpaed.pt.hint = 0;
    lpaed.pt.pxn = 0;
    lpaed.pt.xn = 0;    /* eXecute Never = 0 */
    return lpaed;
}

/* Level 0 Table, each entry refer level1 page table */
union lpaed lpaed_host_l0_table(uint64_t pa)
{
    union lpaed lpaed;
    /* Valid Table Entry */
    lpaed.pt.valid = 1;
    lpaed.pt.table = 1;
    /* Next-level table address [47:12] */
    lpaed.bits &= ~TTBL_L0_TABADDR_MASK;
    lpaed.bits |= pa & TTBL_L0_TABADDR_MASK;
    /* UNK/SBZP [51:40] */
    lpaed.pt.sbz = 0;
    lpaed.pt.pxnt = 0;  /* PXN limit for subsequent levels of lookup */
    lpaed.pt.xnt = 0;   /*  XN limit for subsequent levels of lookup */
    /*  Access permissions limit for subsequent levels of lookup */
    lpaed.pt.apt = 0;
    /*  Table address is in the Non-secure physical address space */
    lpaed.pt.nst = 1;
    return lpaed;
}


/* Level 1 Table, 1GB, each entry refer level2 page table */
union lpaed lpaed_host_l1_table(uint64_t pa)
{
    union lpaed lpaed;
    /* Valid Table Entry */
    lpaed.pt.valid = 1;
    lpaed.pt.table = 1;
    /* Next-level table address [39:12] */
    lpaed.bits &= ~TTBL_L1_TABADDR_MASK;
    lpaed.bits |= pa & TTBL_L1_TABADDR_MASK;
    /* UNK/SBZP [51:40] */
    lpaed.pt.sbz = 0;
    lpaed.pt.pxnt = 0;  /* PXN limit for subsequent levels of lookup */
    lpaed.pt.xnt = 0;   /*  XN limit for subsequent levels of lookup */
    /*  Access permissions limit for subsequent levels of lookup */
    lpaed.pt.apt = 0;
    /*  Table address is in the Non-secure physical address space */
    lpaed.pt.nst = 1;
    return lpaed;
}

/* Level 2 Table, 2MB, each entry refer level3 page table.*/
union lpaed lpaed_host_l2_table(uint64_t pa)
{
    union lpaed lpaed;
    /* Valid Table Entry */
    lpaed.pt.valid = 1;
    lpaed.pt.table = 1;
    /* Next-level table address [39:12] */
    lpaed.bits &= ~TTBL_L2_TABADDR_MASK;
    lpaed.bits |= pa & TTBL_L2_TABADDR_MASK;
    /* UNK/SBZP [51:40] */
    lpaed.pt.sbz = 0;
    lpaed.pt.pxnt = 0;  /* PXN limit for subsequent levels of lookup */
    lpaed.pt.xnt = 0;   /* XN limit for subsequent levels of lookup */
    /* Access permissions limit for subsequent levels of lookup */
    lpaed.pt.apt = 0;
    /* Table address is in the Non-secure physical address space */
    lpaed.pt.nst = 1;
    return lpaed;
}

/* Level 3 Table, each entry refer 4KB physical address */
union lpaed lpaed_host_l3_table(uint64_t pa,
        uint8_t attr_idx, uint8_t valid)
{
    union lpaed lpaed;
    /*  Valid Table Entry */
    lpaed.pt.valid = valid;
    lpaed.pt.table = 1;
    /*  4KB physical address [39:12] */
    lpaed.bits &= ~TTBL_L3_OUTADDR_MASK;
    lpaed.bits |= pa & TTBL_L3_OUTADDR_MASK;
    /*  UNK/SBZP [51:40] */
    lpaed.pt.sbz = 0;
    /* Lower page attributes */
    lpaed.pt.ai = attr_idx;
    lpaed.pt.ns = 1;    /*  Allow Non-secure access */
    lpaed.pt.user = 1;
    lpaed.pt.ro = 0;
    lpaed.pt.sh = 2;    /*  Outher Shareable */
    lpaed.pt.af = 1;    /*  Access Flag set to 1? */
    lpaed.pt.ng = 1;
    /*  Upper page attributes */
    lpaed.pt.hint = 0;
    lpaed.pt.pxn = 0;
    lpaed.pt.xn = 0;    /*  eXecute Never = 0 */
    return lpaed;
}

/* Level 0 Table, Setting validate, table and level1 base address bits */
void lpaed_guest_stage2_conf_l0_table(union lpaed *ttbl0,
        uint64_t baddr, uint8_t valid)
{
    ttbl0->pt.valid = valid ? LPAED_VALID : LPAED_INVALID;
    ttbl0->pt.table = valid ? LPAED_VALID : LPAED_INVALID;
    ttbl0->bits &= ~TTBL_L0_TABADDR_MASK;
    ttbl0->bits |= baddr & TTBL_L0_TABADDR_MASK;
}

/* Level 1 Table, Setting validate, table and level2 base address bits */
void lpaed_guest_stage2_conf_l1_table(union lpaed *ttbl1,
        uint64_t baddr, uint8_t valid)
{
    ttbl1->pt.valid = valid ? LPAED_VALID : LPAED_INVALID;
    ttbl1->pt.table = valid ? LPAED_VALID : LPAED_INVALID;
    ttbl1->bits &= ~TTBL_L1_TABADDR_MASK;
    ttbl1->bits |= baddr & TTBL_L1_TABADDR_MASK;
}

/* Level 2 Table, Setting validate, table and level3 base address bits */
void lpaed_guest_stage2_conf_l2_table(union lpaed *ttbl2,
        uint64_t baddr, uint8_t valid)
{
    ttbl2->pt.valid = valid ? LPAED_VALID : LPAED_INVALID;
    ttbl2->pt.table = valid ? LPAED_VALID : LPAED_INVALID;
    ttbl2->bits &= ~TTBL_L2_TABADDR_MASK;
    ttbl2->bits |= baddr & TTBL_L2_TABADDR_MASK;
}

/* Level 2 Table, enable table descriptor */
void lpaed_guest_stage2_enable_l2_table(union lpaed *ttbl2)
{
    ttbl2->pt.valid = LPAED_VALID;
    ttbl2->pt.table = LPAED_VALID;
}

/* Level 2 Table, disalbe table descriptor */
void lpaed_guest_stage2_disable_l2_table(union lpaed *ttbl2)
{
    ttbl2->pt.valid = LPAED_INVALID;
}

/* Level 3 Table, disalbe table descriptor */
void lpaed_guest_stage1_disable_l3_table(union lpaed *ttbl3)
{
    ttbl3->pt.valid = LPAED_INVALID;
}

/* Map physical address to page or block descriptor */
void lpaed_guest_stage2_map_page(union lpaed *pte, uint64_t pa,
        enum memattr mattr)
{
    pte->pt.valid = LPAED_VALID;
    pte->pt.table = LPAED_VALID;
    pte->bits &= ~TTBL_L3_OUTADDR_MASK;
    pte->bits |= pa & TTBL_L3_OUTADDR_MASK;
    pte->p2m.sbz3 = 0;
    /* Lower block attributes */
    pte->p2m.mattr = mattr & 0xF;
    pte->p2m.read = 1;        /* Read/Write */
    pte->p2m.write = 1;
    pte->p2m.sh = 0;    /* Non-shareable */
    pte->p2m.af = 1;    /* Access Flag set to 1? */
    pte->p2m.sbz4 = 0;
    /* Upper block attributes */
    pte->p2m.hint = 0;
    pte->p2m.sbz2 = 0;
    pte->p2m.xn = 0;    /* eXecute Never = 0 */
    pte->p2m.sbz1 = 0;
}
