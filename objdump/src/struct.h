/*
** EPITECH PROJECT, 2020
** nm
** File description:
** struct.h
*/

#ifndef NM_STRUCT_H
#define NM_STRUCT_H

#include "flags.h"

typedef struct elf_machine_s {
    char *str;
    uint16_t e_machine;
} elf_machine_t;

typedef struct bfd_flag_s {
    char *str;
    unsigned long flag;
} bfd_flag_t;

const elf_machine_t ELF_MACHINE_ISA[] = {
    {"none", EM_NONE},
    {"i386", EM_386},
    {"x86", EM_860},
    {"i386:x86-64", EM_X86_64},
    {NULL, 0},
};

const bfd_flag_t BFD_FLAGS[] = {
    {"HAS_RELOC", HAS_RELOC},
    {"EXEC_P", EXEC_P},
    {"HAS_LINENO",HAS_LINENO},
    {"HAS_DEBUG", HAS_DEBUG},
    {"HAS_SYMS", HAS_SYMS},
    {"HAS_LOCALS", HAS_LOCALS},
    {"DYNAMIC", DYNAMIC},
    {"WP_TEXT", WP_TEXT},
    {"D_PAGED", D_PAGED},
    {NULL, 0},
};

#endif  // NM_STRUCT_H
