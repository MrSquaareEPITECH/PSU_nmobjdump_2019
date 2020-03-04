/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** elf_64.h
*/

#ifndef OBJDUMP_ELF_64_H
#define OBJDUMP_ELF_64_H

#include <elf.h>

void elf_64_print(const Elf64_Ehdr *elf_hdr, const char *path);
Elf64_Shdr *elf_64_get_section_header_by_name(
    const Elf64_Ehdr *elf_hdr, const char *name);

#endif  // OBJDUMP_ELF_64_H
