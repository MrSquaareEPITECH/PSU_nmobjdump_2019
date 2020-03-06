/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** struct.c
*/

#include "struct.h"

#include <elf.h>

const char *ELF_SEC_NAME_SKIP[] = {
    ".bss",
    ".shstrtab",
    ".strtab",
    ".symtab",
    0,
};

const elf_machine_arch_t ELF_MACHINE_ARCH[] = {
    {"none", EM_NONE},
    {"i386", EM_386},
    {"i386:x86-64", EM_X86_64},
    {0, 0},
};

const elf_type_flag_t ELF_TYPE_FLAGS[] = {
    {DYNAMIC, ET_DYN},
    {EXEC_P, ET_EXEC},
    {HAS_RELOC, ET_REL},
    {0, 0},
};

const elf_sec_name_flag_t ELF_SEC_NAME_FLAGS[] = {
    {HAS_DEBUG, ".debug"},
    {HAS_LINENO, ".line"},
    {0, 0},
};

const elf_sec_type_flag_t ELF_SEC_TYPE_FLAGS[] = {
    {D_PAGED, SHT_DYNAMIC},
    {HAS_SYMS, SHT_DYNSYM},
    {HAS_SYMS, SHT_SYMTAB},
    {0, 0},
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
    {0, 0},
};