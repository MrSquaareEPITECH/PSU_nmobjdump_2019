/*
** EPITECH PROJECT, 2020
** nm
** File description:
** main.c
*/

#include <ctype.h>
#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "def.h"

int elf32(Elf32_Ehdr *ehdr)
{
    (void)ehdr;

    return 0;
}

char *symbol_alpha(char *symbol)
{
    unsigned long length = strlen(symbol);
    unsigned long alpha_length = 0;

    for (unsigned long i = 0; i < length; ++i)
        alpha_length += (isalpha(symbol[i]) != 0);

    char *symbol_alpha = malloc(sizeof(char) * (alpha_length + 1));

    if (!symbol_alpha) return (NULL);

    memset(symbol_alpha, 0, (alpha_length + 1));

    for (unsigned long i = 0, j = 0; i < length; ++i) {
        if (isalpha(symbol[i])) {
            symbol_alpha[j] = symbol[i];

            j++;
        }
    }

    return symbol_alpha;
}

void symbols_sort(char **symbols, char **symbols_alpha, unsigned int length)
{
    for (unsigned int i = 1; i < length; ++i) {
        for (unsigned int j = 1; j < length; ++j) {
            int result = strcasecmp(symbols_alpha[j - 1], symbols_alpha[j]);

            if (result == 0) result = strcasecmp(symbols[j - 1], symbols[j]);

            if (result > 0) {
                char *swap = symbols[j - 1];

                symbols[j - 1] = symbols[j];
                symbols[j] = swap;

                swap = symbols_alpha[j - 1];

                symbols_alpha[j - 1] = symbols_alpha[j];
                symbols_alpha[j] = swap;
            }
        }
    }
}

int strcmp_alpha(const char *s1, const char *s2)
{
    unsigned long len1 = strlen(s1), len2 = strlen(s2);

    for (unsigned long i = 0, j = 0; (i < len1) && (j < len2); ++i, ++j) {
        while (!isalpha(s1[i]) && (i < len1)) i++;
        while (!isalpha(s2[j]) && (j < len2)) j++;

        if (s1[i] != s2[j]) return (s1[i] - s2[j]);
    }

    return (0);
}

int strcasecmp_alpha(const char *s1, const char *s2)
{
    unsigned long len1 = strlen(s1), len2 = strlen(s2);
    int c1 = 0, c2 = 0;

    for (unsigned long i = 0, j = 0; (i < len1) && (j < len2); ++i, ++j) {
        while (!isalpha(s1[i]) && (i < len1)) i++;
        while (!isalpha(s2[j]) && (j < len2)) j++;

        c1 = tolower(s1[i]);
        c2 = tolower(s2[j]);

        if (c1 != c2) return (c1 - c2);
    }

    return (0);
}

void symbols_idx_sort(
    Elf64_Sym *symtab, char *strtab, int *idx, unsigned int length)
{
    Elf64_Sym sym1, sym2;
    char *str1, *str2;

    for (unsigned int i = 1; i < length; ++i) {
        for (unsigned int j = 1; j < length; ++j) {
            sym1 = symtab[idx[j - 1]];
            sym2 = symtab[idx[j]];
            str1 = &strtab[sym1.st_name];
            str2 = &strtab[sym2.st_name];

            int result = strcasecmp_alpha(str1, str2);

            if (result == 0) result = strcasecmp(str1, str2);

            if (result > 0) {
                int swap = idx[j - 1];

                idx[j - 1] = idx[j];
                idx[j] = swap;
            }
        }
    }
}

int elf64(Elf64_Ehdr *elfHdr)
{
    Elf64_Shdr *secHdr = PTR_CREMENT(elfHdr, elfHdr->e_shoff);
    Elf64_Shdr *symtabHdr = NULL;

    for (int i = 0; !symtabHdr && (i < elfHdr->e_shnum); ++i)
        if (secHdr[i].sh_type == SHT_SYMTAB) symtabHdr = secHdr + i;

    if (!symtabHdr) {
        fprintf(stderr, ".symtab header not found.");

        return 84;
    }

    Elf64_Shdr *symtabLink = secHdr + symtabHdr->sh_link;
    Elf64_Sym *symtab = PTR_CREMENT(elfHdr, symtabHdr->sh_offset);
    char *strtab = PTR_CREMENT(elfHdr, symtabLink->sh_offset);

    unsigned int num = symtabHdr->sh_size / symtabHdr->sh_entsize;
    unsigned int real_num = 0;
    Elf64_Sym sym;

    for (unsigned int i = 0; i < num; ++i) {
        sym = symtab[i];

        real_num += ((sym.st_name != 0) && (sym.st_info != STT_FILE));
    }

    char **symbols = malloc(sizeof(char *) * real_num);

    if (!symbols) {
        fprintf(stderr, "symbols malloc failed.");

        return 84;
    }

    memset(symbols, 0, real_num);

    char **symbols_alpha = malloc(sizeof(char *) * real_num);

    if (!symbols_alpha) {
        fprintf(stderr, "symbols_alpha malloc failed.");

        return 84;
    }

    memset(symbols_alpha, 0, real_num);

    int *symbols_idx = malloc(sizeof(int) * real_num);

    if (!symbols_idx) {
        fprintf(stderr, "symbols_alpha malloc failed.");

        return 84;
    }

    memset(symbols_idx, 0, real_num);

    for (unsigned int i = 0, j = 0; i < num; ++i) {
        sym = symtab[i];

        if ((sym.st_name != 0) && (sym.st_info != STT_FILE)) {
            symbols[j] = strdup(&strtab[sym.st_name]);
            symbols_alpha[j] = symbol_alpha(&strtab[sym.st_name]);
            symbols_idx[j] = (int)(i);

            j++;
        }
    }

    symbols_sort(symbols, symbols_alpha, real_num);
    symbols_idx_sort(symtab, strtab, symbols_idx, real_num);

    for (unsigned int i = 0; i < real_num; ++i) {
        if (symbols[i]) printf("%s\n", symbols[i]);
    }

    for (unsigned int i = 0; i < real_num; ++i) {
        sym = symtab[symbols_idx[i]];

        printf("sym: %s\n", &strtab[sym.st_name]);
    }

    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Invalid number of arguments.");

        return 84;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        fprintf(stderr, "Failed while opening file.");

        return 84;
    }

    struct stat stat;

    fstat(fd, &stat);

    char *buffer = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    byte *arch = PTR_CREMENT(buffer, 4);

    if (*arch == 1)
        elf32((Elf32_Ehdr *)(buffer));
    else if (*arch == 2)
        elf64((Elf64_Ehdr *)(buffer));

    munmap(buffer, stat.st_size);
    close(fd);
}
