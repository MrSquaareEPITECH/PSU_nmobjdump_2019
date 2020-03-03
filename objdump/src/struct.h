/*
** EPITECH PROJECT, 2020
** nm
** File description:
** struct.h
*/

#ifndef NM_STRUCT_H
#define NM_STRUCT_H

typedef struct elf_machine_s {
    char *str;
    uint16_t e_machine;
} elf_machine_t;

const elf_machine_t ELF_MACHINE_ISA[] = {
    {"none", EM_NONE},
    {"i386", EM_386},
    {"x86", EM_860},
    {NULL, 0},
};

#endif  // NM_STRUCT_H
