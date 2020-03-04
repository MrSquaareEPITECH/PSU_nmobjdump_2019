/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** struct.c
*/

#include "struct.h"

#include <elf.h>
#include <stddef.h>

const elf_machine_arch_t ELF_MACHINE_ARCH[] = {
    {"none", EM_NONE},
    {"i386", EM_386},
    {"i386:x86-64", EM_X86_64},
    {NULL, 0},
};

const elf_bfd_flag_t ELF_BFD_FLAGS[] = {
    {"HAS_RELOC", HAS_RELOC},
    {"EXEC_P", EXEC_P},
    {"HAS_LINENO", HAS_LINENO},
    {"HAS_DEBUG", HAS_DEBUG},
    {"HAS_SYMS", HAS_SYMS},
    {"HAS_LOCALS", HAS_LOCALS},
    {"DYNAMIC", DYNAMIC},
    {"WP_TEXT", WP_TEXT},
    {"D_PAGED", D_PAGED},
    {NULL, 0},
};