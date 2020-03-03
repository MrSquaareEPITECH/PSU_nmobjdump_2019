/*
** EPITECH PROJECT, 2020
** nm
** File description:
** symbol_32.h
*/

#ifndef NM_SYMBOL_32_H
#define NM_SYMBOL_32_H

#include <elf.h>

char symbol_32_get_type(const Elf32_Sym *sym, const Elf32_Ehdr *elf_header);

#endif  // NM_SYMBOL_32_H
