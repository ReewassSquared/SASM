/**
 *
 * Copyright 2018 Brandon Koerner
 * https://github.com/ReewassSquared/
 * Licensed under the Apache License 2.0
 *
 */
#pragma once
#ifndef _SASM_H
#define _SASM_H
/**
 * 16-BIT REGISTERS
 */
#define _AX 0
#define _CX 1
#define _DX 2
#define _BX 3
#define _SP 4
#define _BP 5
#define _SI 6
#define _DI 7
/**
 * 8-BIT REGISTERS
 */
#define _AL 0
#define _CL 1
#define _DL 2
#define _BL 3
#define _AH 4
#define _CH 5
#define _DH 6
#define _BH 7
/**
 * 32-BIT REGISTERS
 */
#define _EAX 0
#define _ECX 1
#define _EDX 2
#define _EBX 3
#define _ESP 4
#define _EBP 5
#define _ESI 6
#define _EDI 7
/**
 * SEGMENT REGISTERS
 */
#define _ES 0
#define _CS 1
#define _SS 2
#define _DS 3
#define _FS 4
#define _GS 5
/**
 * MACROS
 */
#define _S3(X) (X<<3)
/**
 * STRINGS
 */
const char *ax = "AX";
const char *cx = "CX";
const char *dx = "DX";
const char *bx = "BX";
const char *sp = "SP";
const char *bp = "BP";
const char *si = "SI";
const char *di = "DI";
const char *al = "AL";
const char *cl = "CL";
const char *dl = "DL";
const char *bl = "BL";
const char *ah = "AH";
const char *ch = "CH";
const char *dh = "DH";
const char *bh = "BH";
const char *eax = "EAX";
const char *ecx = "ECX";
const char *edx = "EDX";
const char *ebx = "EBX";
const char *esp = "ESP";
const char *ebp = "EBP";
const char *esi = "ESI";
const char *edi = "EDI";
const char *es = "ES";
const char *cs = "CS";
const char *ss = "SS";
const char *ds = "DS";
const char *fs = "FS";
const char *gs = "GS";
/**
 * OPCODES FOR x86
 */
#ifndef _X86_OPCODES_H
#define _X86_OPCODES_H
#define MOVRI8 0xB0
#ifdef _BITS16
#define MOVRI16 0x66B8
#else
#define MOVRI16 0xB8
#define MOVRI32 0xB8
#endif
#define MOVRR8 0x89
#ifdef _BITS16
#define MOVRR16 0x6689
#else
#define MOVRR16 0x89
#define MOVRR32 0x89
#endif
#define MOVMR 0x89
#ifdef _BITS16
#define MOVMR20 0x6789
#endif
#define MOVRM8 0x8A
#ifdef _BITS16
#define MOVRM16 0x668B
#else
#define MOVRM16 0x8B
#define MOVRM32 0x8B
#endif
#define MOVSM 0x8E
#define MOVSM16 0x8E
#ifdef _BITS32
#define MOVSM32 0x8E
#endif
#define MOVSR 0x8E
#define MOVRS 0x8C
#ifdef _BITS16
#define MOVRS16 0x668C
#else
#define MOVRS16 0x8C
#define MOVRS32 0x8C
#endif
#define MOVMS 0x8C
#ifdef _BITS16
#define MOVMS16 0x678C
#else
#define MOVMS16 0x8C
#define MOVMS32 0x8C
#endif

const char *mov = "MOV";
/**
 * NOTE:
 * no need to store the other variables as strings
 * since we decided to not use the original "pure"
 * version of SASM formatting (although this does
 * not mean that we won't implement it later).
 *
 */

/**
 * MORE STUFF GOES HERE (IK THIS COMMENT IS BAD)
 */

/**
 * TYPEDEFS
 */

typedef struct __attribute__((packed)) LABEL {
  char *name; //label recognition
  int loc; //location in code
} label;

#ifndef _MALLOC_H

#endif
