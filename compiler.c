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

char* sub(char *c, char l) { //substring
	char *ret, *str = ret;
	while(*c != l) *ret++ = *c++;
	return str; 
}

size_t ssplen(char* c, char l) { //string split length 
	size_t ret = 0;
	while(*c != '\0') {
		if(*c == l) {
			while(*c++ == l);
			ret++;
		}
	}
	return ret;
}

int ssplc(char* ret[], char* c, char l, char ca) { //string split case
	size_t t = 0, a = 0;
	while(*c != '\0') {
		if(*c == l) {
			a = 0;
			while(*c++ == l);
			t++;
		}
		if(*c == ca) return;
		*c++ = ret[t][a++];
	}
	return ret;
}

int preprocess(char *c) {
	//while(	
}

int syntax(char *c) { //checks if the string is properly formatted for compiling (1st pass)

}

int compile(char *c) { //compiles a properly-formatted string into code (2nd pass)
	unsigned char *out;
	int* labels;
	while(c++ != 0x00) { //this makes me cringe i'll fix it later
		char *ln = sub(c, '\n');
		char* parse[ssplen(ln, ' ')];
		ssplc(ln, ' ', ';');
		if(parse[0] == "db") {
			*out = atoi(parse[1]);
		}
		else if(parse[0] == "mov") {

		}
	}
}

int optimise(unsigned char *o) { //first-pass optimisation algorithms applied to code (3rd pass)

}

//further optimisation passes can be down here. compiler constraints also need to be a thing.
