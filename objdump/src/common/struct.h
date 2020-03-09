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

typedef struct elf_type_flag_s {
    unsigned long flag;
    unsigned short e_type;
} elf_type_flag_t;

typedef struct elf_sec_name_flag_s {
    unsigned long flag;
    char *name;
} elf_sec_name_flag_t;

typedef struct elf_sec_type_flag_s {
    unsigned long flag;
    unsigned int sh_type;
} elf_sec_type_flag_t;

typedef struct elf_bfd_flag_s {
    char *str;
    unsigned long flag;
} elf_bfd_flag_t;

extern const char *ELF_SEC_NAME_SKIP[];
extern const elf_machine_arch_t ELF_MACHINE_ARCH[];
extern const elf_type_flag_t ELF_TYPE_FLAGS[];
extern const elf_sec_name_flag_t ELF_SEC_NAME_FLAGS[];
extern const elf_sec_type_flag_t ELF_SEC_TYPE_FLAGS[];
extern const elf_bfd_flag_t ELF_BFD_FLAGS[];

#endif // OBJDUMP_STRUCT_H
