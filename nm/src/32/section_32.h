/*
** EPITECH PROJECT, 2020
** nm
** File description:
** section_32.h
*/

#ifndef NM_SECTION_32_H
#define NM_SECTION_32_H

#include <elf.h>

char *section_32_get_name(const Elf32_Shdr *sec_hdr, const Elf32_Ehdr *elf_hdr);

#endif // NM_SECTION_32_H
