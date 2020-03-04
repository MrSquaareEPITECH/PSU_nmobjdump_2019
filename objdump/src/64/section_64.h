/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** section_64.h
*/

#ifndef OBJDUMP_SECTION_64_H
#define OBJDUMP_SECTION_64_H

#include <elf.h>

void section_64_print(const Elf64_Shdr *sec_hdr, const Elf64_Ehdr *elf_hdr);
char *section_64_get_name(const Elf64_Shdr *sec_hdr, const Elf64_Ehdr *elf_hdr);

#endif  // OBJDUMP_SECTION_64_H
