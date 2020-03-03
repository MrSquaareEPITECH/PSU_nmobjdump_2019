/*
** EPITECH PROJECT, 2020
** nm
** File description:
** symbol_64.h
*/

#ifndef NM_SYMBOL_64_H
#define NM_SYMBOL_64_H

#include <elf.h>

char symbol_64_get_type(const Elf64_Sym *sym, const Elf64_Ehdr *elf_header);

#endif  // NM_SYMBOL_64_H
