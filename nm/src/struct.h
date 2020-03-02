/*
** EPITECH PROJECT, 2020
** nm
** File description:
** struct.h
*/

#ifndef NM_STRUCT_H
#define NM_STRUCT_H

typedef struct sym_type_s {
    char letter;
    Elf64_Section st_shndx;
    Elf64_Word sh_type;
    Elf64_Xword sh_flags;
    unsigned char st_bind;
    unsigned char st_type;
    const char *secName;
} sym_type_t;

const sym_type_t SYM_TYPES[] = {
    {'A', SHN_ABS, 0, 0, 0, 0, NULL},
    {'B', 0, SHT_NOBITS, SHF_ALLOC + SHF_WRITE, 0, 0, ".bss"},
    {'C', SHN_COMMON, 0, 0, 0, NULL},
    {'D', 0, SHT_PROGBITS, SHF_ALLOC + SHF_WRITE, 0, 0, ".data"},
    {'F', 0, 0, 0, 0, STT_FILE, NULL},
    {'l', 0, SHT_PROGBITS, 0, 0, 0, ".line"},
    {'G', SHN_MIPS_SCOMMON, 0, 0, 0, 0, NULL},
    {'i', 0, 0, 0, 0, STT_GNU_IFUNC, NULL},
    {'I', 0, 0, 0, 0, 0, NULL},
    {'N', 0, SHT_PROGBITS, 0, 0, 0, ".debug"},
    {'n', 0, SHT_PROGBITS, SHF_ALLOC, 0, 0, ".rodata"},
    {'p', 0, 0, 0, 0, 0, NULL},
    {'R', 0, SHT_PROGBITS, SHF_ALLOC, 0, 0, ".rodata"},
    {'S', SHN_MIPS_SUNDEFINED, 0, 0, 0, 0, NULL},
    {'T', 0, SHT_PROGBITS, SHF_ALLOC + SHF_EXECINSTR, 0, 0, ".text"},
    {'U', SHN_UNDEF, 0, 0, 0, 0, NULL},
    {'V', 0, 0, 0, STB_WEAK, 0, NULL},
    {'W', SHN_UNDEF, 0, 0, STB_WEAK, 0, NULL},
};

#endif  // NM_STRUCT_H
