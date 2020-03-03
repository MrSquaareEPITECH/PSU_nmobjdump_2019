/*
** EPITECH PROJECT, 2020
** nm
** File description:
** elf_64.h
*/

#ifndef NM_ELF_64_H
#define NM_ELF_64_H

#include <elf.h>

Elf64_Shdr *elf_64_get_section_header_by_name(
    const Elf64_Ehdr *elf_hdr, const char *name);
Elf64_Shdr *elf_64_get_section_header_by_type(
    const Elf64_Ehdr *elf_hdr, Elf64_Word type);

#endif  // NM_ELF_64_H
