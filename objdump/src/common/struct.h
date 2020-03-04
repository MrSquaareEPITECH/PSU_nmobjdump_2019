/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** struct.h
*/

#ifndef OBJDUMP_STRUCT_H
#define OBJDUMP_STRUCT_H

#include "flags.h"

typedef struct elf_machine_arch_s {
    char *str;
    unsigned long e_machine;
} elf_machine_arch_t;

typedef struct elf_bfd_flag_s {
    char *str;
    unsigned long flag;
} elf_bfd_flag_t;

extern const elf_machine_arch_t ELF_MACHINE_ARCH[];
extern const elf_bfd_flag_t ELF_BFD_FLAGS[];

#endif  // OBJDUMP_STRUCT_H
