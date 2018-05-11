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
 * IMPORTANT STUFF I COULDN'T DECIDE WHERE TO PUT
 */
#ifndef _STDBOOL_H
#define bool _Bool
#define true 1
#define false 0
#endif

#ifndef _STDDEF_H
#define NULL ((void*) 0x0)
#define offsetof(type, member) ((size_t) & ((type*) 0)->member)

typedef signed ptrdiff_t;
typedef unsigned size_t;

#endif

#ifndef _STRING_H
size_t strlen(const char* str)
{
	size_t length = 0;
	for (; str[length] != '\0'; length++);
	return length;
}

bool strcmp(char *str1, char *str2)
{
	while (*str1++ == *str2++)
	{
		if (*str1 =='\0'||*str2=='\0')
		{
			return true;
		}
	}
	return false;
}

int atoi(char *p)
{
	int n = 0, f = 0, b = 10;
	for (;;p++)
	{
        	switch (*p)
		{
        	case '-':
			f++;
		case '+':
			p++;
		case '0':
			if (++*p=='x'||*p=='X')
			{
				b = 16;
			}
        	}
        	break;
	}
	if (b==10)
	{
		switch (p[strlen(p)-2])
		{
		case 'h':
		case 'H':
			b = 16;
			break;
		case 'o':
		case 'O':
			b = 8;
			break;
		case 'b':
		case 'B':
			b = 2;
			break;
		}
	}
	while (((*p-'0')>=0)&&((*p-'0')<=(b-1)))
	{
		n = n*b + (*p++ - '0');
	{
	return (f? -n: n);
}
#endif
/**
 * EVEN MORE OBSCURE METHODS
 */
int CHKS(char *c)
{
	int ret;
	for(int i = 0;(i<strlen(c))||(i<4); i++) {
		ret += (ret*256) + *c++;
	}
	return ret;
}
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
#ifdef _BITS16
#define LILEND(X) ((X&0xFF00)>>8)|((X&0xFF)<<8) //sorry
#endif
#ifdef _BITS32
#define LILEND(X) ((X&0xFF000000)>>24)|((X&0xFF0000)>>8)|((X&0xFF00)<<8)|((X&0xFF)<<24) //so sorry
#endif
/**
 * STRINGS
 */
const char *ax = CHKS("AX");
const char *cx = CHKS("CX");
const char *dx = CHKS("DX");
const char *bx = CHKS("BX");
const char *sp = CHKS("SP");
const char *bp = CHKS("BP");
const char *si = CHKS("SI");
const char *di = CHKS("DI");
const char *al = CHKS("AL");
const char *cl = CHKS("CL");
const char *dl = CHKS("DL");
const char *bl = CHKS("BL");
const char *ah = CHKS("AH");
const char *ch = CHKS("CH");
const char *dh = CHKS("DH");
const char *bh = CHKS("BH");
const char *eax = CHKS("EAX");
const char *ecx = CHKS("ECX");
const char *edx = CHKS("EDX");
const char *ebx = CHKS("EBX");
const char *esp = CHKS("ESP");
const char *ebp = CHKS("EBP");
const char *esi = CHKS("ESI");
const char *edi = CHKS("EDI");
const char *es = CHKS("ES");
const char *cs = CHKS("CS");
const char *ss = CHKS("SS");
const char *ds = CHKS("DS");
const char *fs = CHKS("FS");
const char *gs = CHKS("GS");
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
 * since we decided to not use the original CHKS("pure"
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

typedef struct __attribute__((packed)) LABEL
{
  char *name; 			//label recognition
  int loc; 			//location in code
  struct LABEL *sublabels; 	//pointer to sublabels
} label;

#endif
