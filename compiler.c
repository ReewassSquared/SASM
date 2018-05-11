/**
 *
 * Copyright 2018 Brandon Koerner]
 * https://github.com/ReewassSquared/
 * Licensed under the Apache License 2.0
 *
 */

/**
 *
 * SASM: THE STUPID ASSEMBLER
 * PURPOSE: IT STANDS ALONE, ALL BY ITSELF, AND ASSEMBLES.
 *          BASICALLY, IT'S A SIMPLE ASSEMBLER THAT TAKES 
 *			IN SASM-FORMATTED ASSEMBLY CODE AND ASSEMBLES
 *			IT FOR X86 IA32. SIMPLE ENOUGH REALLY. STUPID.
 *
 * NOTE: ALL IMM VALUES AND DB AND EVERYTHING ARE ALL LITTLE-ENDIAN! FUCK YOU INTEL!
 *
 * REGISTER VALUES:
 * EAX, AX, AL: 000
 * EBX, BX, BL: 011
 * ECX, CX, CL: 001
 * EDX, DX, DL: 010
 * ESP, SP, AH: 100
 * EBP, EP, CH: 101
 * ESI, SI, DH: 110 
 * EDI, DI, BH: 111
 *
 * A TABLE:
 * FOR "MOV REG, IMM":
 * 			-THIS IS ACTUALLY SIMPLE-
 *			OPCODE: 
 *				IF REG IS 8-BIT:
 *					OPCODE IS 1 BYTE, AND IS B0 + REGISTER CODE
 *				IF REG IS 16-BIT:
 *					OPCODE IS 1 BYTE, AND IS B8 + REGISTER CODE
 *				IF REG IS 32-BIT:
 *					OPCODE IS 2 BYTES, AND IS 66 B8+REGCODE
 *			IMM:
 *				EITHER 1 BYTES, 2 BYTES, OR 4 BYTES, DEPENDING ON DATA ENTERED AND REGISTER USED.
 *			EXAMPLE:
 *				MOV EBX, 551122H -> 66 BB 22 11 55 00
 * FOR "MOV REG, REG":
 *			-A LITTLE MORE COMPLICATED-
 *			OPCODE:
 *				FOR 16/32-BIT:
 *			
 */
#include "compiler.h"

char* sub(char *c, char l) //substring
{ 
	char *ret, *str = ret;
	while (*c != l) *ret++ = *c++;
	return str; 
}

char* strch(char *c, char l, char ca)
{
	int i = 0;
	while (c[i++] != l);
	c[i] = ca;
	return c;
}

size_t ssplen(char* c, char l) //string split length
{
	size_t ret = 0;
	while (*c != '\0')
	{
		if (*c == l)
		{
			while (*c++ == l);
			ret++;
		}
	}
	return ret;
}

int ssplc(char* ret[], char* c, char l, char ca) //string split case
{
	size_t t = 0, a = 0;
	while (*c != '\0')
	{
		if (*c == l)
		{
			a = 0;
			while (*c++ == l);
			t++;
		}
		if (*c == ca)
		{
			return;
		}
		*c++ = ret[t][a++];
	}
	return ret;
}

int seg(char *cr)
{
	int c = CHKS(cr);
	switch (c)
	{
	case es:
		return 0x0;
	case cs:
		return 0x1;
	case ss:
		return 0x2;
	case ds:
		return 0x3;
	case fs:
		return 0x4;
	case gs:
		return 0x5;
	}
}

int reg(char *cr)
{
	int ret = 0;
	if(cr[0]=='[')
	{
		c++;
		c = strch(c, ']', '\0');
		ret += 0x30;
	}
	int c = CHKS(cr);
	switch (c)
	{
	case al:
		ret += 0x00;
	case ax:
		ret += 0x10;
	case eax:
		ret += 0x20;
	case cl:
		ret += 0x01;
	case cx:
		ret += 0x11;
	case ecx:
		ret += 0x21;
	case dx:
		ret += 0x02;
	case dl:
		ret += 0x12;
	case edx:
		ret += 0x22;
	case bx:
		ret += 0x03;
	case bl:
		ret += 0x13;
	case ebx:
		ret += 0x23;
	case sp:
		ret += 0x04;
	case ah:
		ret += 0x14;
	case esp:
		ret += 0x24;
	case bp:
		ret += 0x05;
	case ch:
		ret += 0x15;
	case ebp:
		ret += 0x25;
	case si:
		ret += 0x06;
	case dh:
		ret += 0x16;
	case esi:
		ret += 0x26;
	case di:
		ret += 0x07;
	case bh:
		ret += 0x17;
	case edi:
		ret += 0x27;
	default:
		ret += 0xFF;
	}
	return ret;
}

bool reg8(char *cr)
{
	int c = CHKS(cr);
	switch (c)
	{
	case al:
	case bl:
	case cl:
	case dl:
	case ah:
	case bh:
	case ch:
	case dh:
		return true;
	default:
		return false;
	}
}

bool reg16(char *cr)
{
	int c = CHKS(cr);
	switch (c)
	{
	case ax:
	case bx:
	case cx:
	case dx:
	case sp:
	case bp:
	case si:
	case di:
		return true;
	default:
		return false;
	}
}

#ifdef _BITS32
bool reg32(char *cr)
{
	int c = CHKS(cr);
	switch (c)
	{
	case eax:
	case ebx:
	case ecx:
	case edx:
	case esp:
	case ebp:
	case esi:
	case edi:
		return true;
	default:
		return false;
	}
}
#endif

int preprocess(char *c)
{
	//while(	
}

int syntax(char *c) { //checks if the string is properly formatted for compiling (1st pass)

}

int compile(char *c) { //compiles a properly-formatted string into code (2nd pass)
	unsigned char *out;
	int* labels;
	while (c++ != 0x00) //this makes me cringe i'll fix it later
	{
		char *ln = sub(c, '\n');
		char* parse[ssplen(ln, ' ')];
		ssplc(ln, ' ', ';');
		if (strcmp(parse[0], "DB"))
		{
			*out++ = atoi(parse[1]);
		}
		else if(strcmp(parse[0], "MOV"))
		{
			int r1 = reg(parse[1]);
			int r2 = reg(parse[2]);
			if (r1!=0xFF)
			{
				#ifdef _BITS16
				if (reg32(r1)) return -1;
				#endif
				if (r2!=0xFF&&r1<0x30) //reg<-reg
				{

					switch ((r2&0xF0)>>4)
					{
					case 1: //8
						if ((r1&0xF0)>>4!=1)
						{
							return -1; //error- operands must be same size
						}
						*out++ = 0x89;
						*out++ = 0xC0+S3(r1&0xF)+(r2&0xF);
						break;
					case 0:
						if((r1&0xF0)>>4==1)
						{
							return -1;
						}
						#ifdef _BITS16
						*out++ = 0x66;
						#endif
						*out++ = 0x89;
						*out++ = 0xC0+S3(r1&0xF)+(r2&0xF);
						break;
					case 2:
						if((r1&0xF0)>>4==1)
						{
							return -1;
						}
						#ifdef _BITS32
						*out++ = 0x66;
						#endif
						*out++ = 0x89;
						*out++ = 0xC0+S3(r1&0xF)+(r2&0xF);
						break;
					case 3: //reg<-[reg]
						if((r1&0xF0)>>4==1)
						{
							return -1;
						}
						#ifdef _BITS16
						*out++ = 0x66;
						#endif
						*out++ = 0x8B;
						*out++ = S3(r1&0xF)+(r2&0xF);
					case 4:
						if((r1&0xF0)>>4!=1)
						{
							return -1;
						}
						*out++ = 0x8A;
						*out++ = S3(r1&0xF)+(r2&0xF);
					case 5:
						if((r1&0xF0)>>4==1)
						{
							return -1;
						}
						#ifdef _BITS32
						*out++ = 0x66;
						#endif
						*out++ = 0x8B;
						*out++ = S3(r1&0xF)+(r2&0xF);
					}
				}
				else if(r1<0x30)
				{
					
				}
			}
			else
			{
				
			}
			
		}
	}
}

int optimise(unsigned char *o) { //first-pass optimisation algorithms applied to code (3rd pass)

}

//further optimisation passes can be down here. compiler constraints also need to be a thing.
