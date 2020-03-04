/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** section_32.h
*/

#ifndef OBJDUMP_SECTION_32_H
#define OBJDUMP_SECTION_32_H

#include <elf.h>

void section_32_print(const Elf32_Shdr *sec_hdr, const Elf32_Ehdr *elf_hdr);
char *section_32_get_name(const Elf32_Shdr *sec_hdr, const Elf32_Ehdr *elf_hdr);

#endif  // OBJDUMP_SECTION_32_H
