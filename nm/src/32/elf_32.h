/*
** EPITECH PROJECT, 2020
** nm
** File description:
** elf_32.h
*/

#ifndef NM_ELF_32_H
#define NM_ELF_32_H

#include <elf.h>

Elf32_Shdr *elf_32_get_section_header_by_name(
    const Elf32_Ehdr *elf_hdr, const char *name);
Elf32_Shdr *elf_32_get_section_header_by_type(
    const Elf32_Ehdr *elf_hdr, Elf32_Word type);

#endif // NM_ELF_32_H
