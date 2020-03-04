/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** elf_32.h
*/

#ifndef OBJDUMP_ELF_32_H
#define OBJDUMP_ELF_32_H

#include <elf.h>

void elf_32_print(const Elf32_Ehdr *elf_hdr, const char *path);
Elf32_Shdr *elf_32_get_section_header_by_name(
    const Elf32_Ehdr *elf_hdr, const char *name);

#endif  // OBJDUMP_ELF_32_H
