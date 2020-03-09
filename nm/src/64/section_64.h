/*
** EPITECH PROJECT, 2020
** nm
** File description:
** section_64.h
*/

#ifndef NM_SECTION_64_H
#define NM_SECTION_64_H

#include <elf.h>

char *section_64_get_name(const Elf64_Shdr *sec_hdr, const Elf64_Ehdr *elf_hdr);

#endif // NM_SECTION_64_H
