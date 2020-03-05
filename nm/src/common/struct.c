/*
** EPITECH PROJECT, 2020
** nm
** File description:
** struct.c
*/

#include "struct.h"

#include <elf.h>

const symbol_shndx_type_t SYM_SHNDX_TYPES[] = {
    {'A', SHN_ABS},
    {'C', SHN_COMMON},
    {'U', SHN_UNDEF},
    {0, 0},
};

const symbol_sec_name_type_t SYM_SEC_NAME_TYPES[] = {
    {'B', ".bss"},
    {'D', ".data"},
    {'D', ".data1"},
    {'N', ".debug"},
    {'R', ".rodata"},
    {'R', ".rodata1"},
    {'T', ".fini_array"},
    {'T', ".fini"},
    {'T', ".init"},
    {'T', ".init_array"},
    {'T', ".text"},
    {0, 0},
};

const symbol_sec_mask_type_t SYM_SEC_FLAGS_TYPES[] = {
    {'T', SHF_EXECINSTR},
    {'D', SHF_WRITE},
    {'R', SHF_ALLOC},
    {0, 0},
};