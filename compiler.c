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
	while (*c!=l&&*c!='\0') *ret++ = *c++;
	str='\0';
	return str; 
}

char *post(char *c, char l)
{
	while (*c!=l&&*c!='\0') c++;
	return ++c; 
}

bool strcont(char *c, char l)
{
	while(*c++!='\0')
	{
		if(*c==1) return true;
	}
	return false;
}

char *removechar(char *c, char l)
{
	char *ret, *str = ret;
	while(*c != '\0')
	{
		*str = *c++;
		if(*str!=l) str++; 
	}
	return ret;
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
	default:
		return 0xFF;
	}
}

int genmodrm(char *arg)
{
	int retval=0;
	int mod=0;
	int rm=0;
	int imm=0;
	char *r1 = sub(arg, ',');
	char *r2 = post(arg, ',');
	if(r1[0]=='[')
	{
		if(strcont(r1, '+'))
		{
			if(isnum(sub(r1, '+'))) return -1; //oops
			char *rn = sub(r1, '+');
			char *tbd = post(r1, '+');
			if(reg8(rn)) return -1; //oops
			else if(reg16(rn))
			{
				if(rn!="BX"&&rn!="BP"&&rn!="SI"&&rn!="DI") return -1;
				char *tbd = sub(r1,']');
			}
		}
		else 
		{
			mod=0;
		}
		rmbrck(r1);
	}
}

int reg(char *cr)
{
	int ret = 0;
	if(cr[0]=='[')
	{
		c++;
		c = strch(c, ']', '\0');
		if(strocc(c, '+'))
		{
			ret += 0x08;
		}
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
	case cr0:
		ret += 0x70;
	case cr1:
		ret += 0x71;
	case cr2:
		ret += 0x72;
	case cr3:
		ret += 0x73;
	case cr4:
		ret += 0x74;
	case cr5:
		ret += 0x75;
	case cr6:
		ret += 0x76;
	case cr7:
		ret += 0x77;
	case db0:
		ret += 0x80;
	case db1:
		ret += 0x81;
	case db2:
		ret += 0x82;
	case db3:
		ret += 0x83;
	case db4:
		ret += 0x84;
	case db5:
		ret += 0x85;
	case db6:
		ret += 0x86;
	case db7:
		ret += 0x87;
	default:
		ret = 0xFF;
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

bool regseg(char *cr)
{
	int c = CHKS(cr);
	switch (c)
	{
	case es:
	case cs:
	case ss:
	case ds:
	case fs:
	case gs:
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

char* rmbrck(char* c)
{
	char *ret = ++c;
	for(int i = 0; i < strlen(ret); i++)
	{
		if(ret[i]==']') ret[i]='\0';
	}
	return ret;
}

bool isnum(char *c)
{
	if(*c>0x2F&&*c<0x3A)
	{
		return true;	
	}
	for(int i = 0; i < strlen(c)-1; i++) //hex check case
	{
		if(*c<0x30||(*c>0x39&&*c<0x40)||(*c>0x45))
		{
			return false;	
		}
	}
	return true; //reached if it is a hex code
}

int preprocess(char *c)
{
	//while(	
}

int syntax(char *c) { //checks if the string is properly formatted for compiling (1st pass)

}

int compile(char *c) { //compiles a properly-formatted string into code (2nd pass)
	unsigned char *out;
	int* labels;
	while (++*c != '\0') //this makes me cringe i'll fix it later
	{
		char *ln = sub(c, '\n');
		c += strlen(ln);
		static char* parse[ssplen(ln, ' ')];
		parse[0] = sub(ln, ' ');
		ln = sub(ln, ' '); //gets instruction
		if(!iskeyword(parse[0]))
		{
			//parser for labels
		}
		else if(strcmp(parse[0], "TIMES"))
		{
			//special handler for times
		}
		else
		{	
			if (strcmp(parse[0], "DB"))
			{
				*out++ = atoi(parse[1]);
			}
			else if (strcmp(parse[1], "IN"))
			{
				r1 = reg(parse[1]);
				r2 = reg(parse[2]);
				if (r1==r2)
				{
					return -1;
				}
				if ((r2!=0x02&&!isnum(parse[2]))||(r1&0xF!=0))
				{
					return -1;
				}
				if (isnum(parse[2]))
				{
					int imm8 = atoi(parse[2]);
					if (imm8 > 0xFF)
					{
						return -1;
					}
					switch ((r1&0xF0)>>4)
					{
					case 0:
						#ifdef _BITS32
						*out++ = 0x66;
						#endif
						*out++ = 0xE5;
						*out++ = (unsigned char) imm8;
						break;
					case 1:
						*out++ = 0xE4;
						*out++ = (unsigned char) imm8;
						break;
					case 2:
						*out++ = 0xE5;
						*out++ = (unsigned char) imm8;
						break;
					default:
						return -1;
					}
				}
				else
				{
					switch ((r1&0xF0)>>4)
					{
						case 0:
							#ifdef _BITS32
							*out++ = 0x66;
							#endif
							*out++ = 0xED;
							break;
						case 1:
							*out++ = 0xEC;
							break;
						case 2:
							*out++ = 0xED;
							break;
						default:
							return -1;
					}
				}
			}
			else if (strcmp(parse[0], "OUT"))
			{
				r1 = reg(parse[1]);
				r2 = reg(parse[2]);
				if (r1==r2)
				{
					return -1;
				}
				if ((r1!=0x02&&!isnum(parse[1]))||(r2&0xF!=0))
				{
					return -1;
				}
				if (isnum(parse[1]))
				{
					int imm8 = atoi(parse[1]);
					if (imm8 > 0xFF)
					{
						return -1;
					}
					switch ((r1&0xF0)>>4)
					{
					case 0:
						#ifdef _BITS32
						*out++ = 0x66;
						#endif
						*out++ = 0xE7;
						*out++ = (unsigned char) imm8;
						break;
					case 1:
						*out++ = 0xE6;
						*out++ = (unsigned char) imm8;
						break;
					case 2:
						*out++ = 0xE7;
						*out++ = (unsigned char) imm8;
						break;
					default:
						return -1;
					}
				}
				else
				{
					switch ((r1&0xF0)>>4)
					{
						case 0:
							#ifdef _BITS32
							*out++ = 0x66;
							#endif
							*out++ = 0xEF;
							break;
						case 1:
							*out++ = 0xEE;
							break;
						case 2:
							*out++ = 0xEF;
							break;
						default:
							return -1;
					}
				}
			}
			else if (strcmp(parse[0], "INT"))
			{
				if (isnum(parse[1]))
				{
					return -1;
				}
				else
				{
					imm8 = atoi(parse[1]);
					if (imm8>0xFF)
					{
						return -1
					}
					else if (imm8==3)
					{
						*out++ = 0xCC;
					}
					else
					{
						*out++ = 0xCD;
						*out++ = (unsigned char) imm8;
					}
				}
			}
			else if (strcmp(parse[0], "IRET"))
			{
				*out++ = 0xCF;	
			}
			else if (strcmp(parse[0], "MOV"))
			{
				int r1 = reg(parse[1]);
				int r2 = reg(parse[2]);
				if (r1!=0xFF)
				{
					#ifdef _BITS16
					if (reg32(r1)) return -1;
					#endif
					if (r2!=0xFF&&r2>=0x70)
					{
						if (r2>=0xA0)
						{
							return -1; //dbn, crn access must be reg<-reg
						}
						if (r1>=0x70)
						{
							return -1; //dbn, cbn cannot access each other	
						}
						else
						{
							*out++ = 0x0F;
							*out++ = 0x20 + ((r2&0x80)>>7); //magic
							*out++ = 0xC0 + ((r2&0x0F)<<3) + (r1&0xF0);
						}
					}
					else if (r2!=0xFF) //reg<-reg
					{
						if (r1>=0x70)
						{
							*out++ = 0x0F;
							*out++ 0x22 + ((r1&0x80)>>7);
							*out++ = 0xC0 + ((r2&0x0F)>>3) + (r1&0x0F);
						}
						else
						{
							switch ((r2&0xF0)>>4)
							{
							case 1: //8
								if ((r1&0xF0)>>4!=1)
								{
									return -1; //error- operands must be same size
								}
								*out++ = 0x89;
								if (r1>=0X30)
								{
									if (!(((r1&0x7==0x6)||(r1&0x7==0x7))&&((r1&0xF0)>>4)!=4))
									{
										return -1;
									}
									*out++ = 0x67;
									*out++ = (r1&0x8) ? (0x40+S3(r1&0xF)+(r2&0xF)) : (S3(r1&0xF)+(r2&0xF));
									if(r1&0x8)
									{
										int imm8 = parse_offset(parse[1]);
									}
								}
								else 
								{
									*out++ = 0xC0+S3(r1&0xF)+(r2&0xF);
								}
								break;
							case 0:
								if ((r1&0xF0)>>4==1)
								{
									return -1;
								}
								if (r1>=0X30)
								{
									if (!(((r1&0xF==0x6)||(r1&0xF==0x7))&&((r1&0xF0)>>4)!=4))
									{
										return -1;
									}
									*out++ = 0x67;
									#ifdef _BITS32
									*out++ = 0x66;
									#endif
									*out++ = 0x89;
									*out++ = S3(r1&0xF)+(r2&0xF);
								}
								else 
								{
									#ifdef _BITS32
									*out++ = 0x66;
									#endif
									*out++ = 0x89;
									*out++ = 0xC0+S3(r1&0xF)+(r2&0xF);
								}
								break;
							case 2:
								if ((r1&0xF0)>>4==1)
								{
									return -1;
								}
								if (r1>=0X30)
								{
									if (!(((r1&0xF==0x6)||(r1&0xF==0x7))&&((r1&0xF0)>>4)!=4))
									{
										return -1;
									}
									*out++ = 0x67;
									*out++ = 0x89;
									*out++ = S3(r1&0xF)+(r2&0xF);
								}
								else 
								{
									*out++ = 0x89;
									*out++ = 0xC0+S3(r1&0xF)+(r2&0xF);
								}
								break;
							case 3: //reg<-[reg]
								if ((r1&0xF0)>>4==1)
								{
									return -1;
								}
								#ifdef _BITS32
								*out++ = 0x66;
								#endif
								*out++ = 0x8B;
								*out++ = S3(r1&0xF)+(r2&0xF);
								break;
							case 4:
								if ((r1&0xF0)>>4!=1)
								{
									return -1;
								}
								*out++ = 0x8A;
								*out++ = S3(r1&0xF)+(r2&0xF);
								break;
							case 5:
								if ((r1&0xF0)>>4==1)
								{
									return -1;
								}
								*out++ = 0x8B;
								*out++ = S3(r1&0xF)+(r2&0xF);
								break;
							}
						}
					}
					else if (regseg(parse[2]))
					{
						r2 = seg(parse[2]);
						if (r1>=0x70||r2==0xFF)
						{
							return -1;
						}
						if (isnum(rmbrck(parse[1])))
						{
							int imm = LILEND(atoi(rmbrck(parse[1])));
							*out++ = 0x8C;
							*out++ = 5 + S3(r2);
							#ifdef _BITS16
							*out++ = ((imm&0xFF00)>>8);
							*out++ = imm&0xFF;
							#else
							*out++ = ((imm&0xFF000000)>>24);
							*out++ = ((imm&0xFF0000)>>16);
							*out++ = ((imm&0xFF00)>>8);
							*out++ = (imm&0xFF);
							#endif
						}
						else
						{
							switch ((r1&0xF0)>>4)
							{
							case 0:	
							case 2:
								*out++ = 0x8C;
								*out++ = C0+S3(r2)+(r1&0xF);
								break;
							case 3:
								if (r1&0xF!=3)
								{
									return -1;	
								}
								*out++ = 0x67;
								*out++ = 0x8C;
								*out++ = S3(r2&0xF)+0x7;
							case 5:
								*out++ = 0x8C;
								*out++ = S3(r2)+(r1&0xF);
								break;
							case 1:
							case 4:
								return -1;
							}
						}
					}
					else if (r2==0xFF) //either imm mem or imm
					{
						if (r1>=0x70)
						{
							return -1;
						}
						if (parse[2][0]=='['&&isnum(rmbrck(parse[2]))) //mem
						{
							parse[2] = rmbrck(parse[2]);
							int imm = atoi(parse[2]);
							if (reg8(parse[1]))
							{
								if (r1&0xF==0)
								{
									imm = LILEND(imm);
									*out++ = 0xA0;
									*out++ = ((imm&0xFF00)>>8);
									*out++ = imm&0xFF;
								}
								else
								{
									imm = LILEND(imm);
									*out++ = 0x8A;
									*out++ = ((imm&0xFF00)>>8);
									*out++ = imm&0xFF;
								}
							}
							else
							{
								if (r1&0xF==0)
								{
									imm = LILEND(imm);
									#ifdef _BITS16
									*out++ = 0xA1;
									*out++ = ((imm&0xFF00)>>8);
									*out++ = imm&0xFF;
									#else
									if (reg16(r1))
									{
										*out++ = 0x66;
									}
									*out++ = 0xA1;
									*out++ = ((imm&0xFF000000)>>24);
									*out++ = ((imm&0xFF0000)>>16);
									*out++ = ((imm&0xFF00)>>8);
									*out++ = (imm&0xFF);
									#endif
								}
								else
								{
									imm = LILEND(imm);
									#ifdef _BITS16
									*out++ = 0x8A;
									*out++ = (((r1&0xF)<<3) + 5);
									*out++ = ((imm&0xFF00)>>8);
									*out++ = imm&0xFF;
									#else
									if (reg16(r1))
									{
										*out++ = 0x66;
									}
									*out++ = 0x8B;
									*out++ = (((r1&0xF)<<3) + 5);
									*out++ = ((imm&0xFF000000)>>24);
									*out++ = ((imm&0xFF0000)>>16);
									*out++ = ((imm&0xFF00)>>8);
									*out++ = (imm&0xFF);
									#endif
								}
							}
						}
						else if (isnum(parse[2]))
						{
							int imm = atoi(parse[2]);
							if (reg8(parse[1]))
							{
								*out++ = (0xB0 + (r1&0xF));
								*out++ = ((imm&0xFF00)>>8);
								*out++ = imm&0xFF;
							}
							else
							{
								#ifdef _BITS16
								*out++ = (0xB8 + (r1&0xF));
								*out++ = ((imm&0xFF00)>>8);
								*out++ = imm&0xFF;
								#else
								if (reg16(r1))
								{
									*out++ = 0x66;
								}
								*out++ = (0xB8 + (r1&0xF));
								*out++ = ((imm&0xFF000000)>>24);
								*out++ = ((imm&0xFF0000)>>16);
								*out++ = ((imm&0xFF00)>>8);
								*out++ = (imm&0xFF);
								#endif
							}
						}
					}
				}
				else if (regseg(parse[1]))
				{
					r1 = seg(parse[1]);
					if(r2>=0x70||r1==0xFF)
					{
						return -1;
					}
					if (isnum(rmbrck(parse[2])))
					{
						int imm = LILEND(atoi(rmbrck(parse[2])));
						*out++ = 0x8E;
						*out++ = 5 + S3(r1);
						#ifdef _BITS16
						*out++ = ((imm&0xFF00)>>8);
						*out++ = imm&0xFF;
						#else
						*out++ = ((imm&0xFF000000)>>24);
						*out++ = ((imm&0xFF0000)>>16);
						*out++ = ((imm&0xFF00)>>8);
						*out++ = (imm&0xFF);
						#endif
					}
					else
					{
						switch((r2&0xF0)>>4)
						{
						case 0:	
						case 2:
							*out++ = 0x8E;
							*out++ = C0+S3(r1)+(r2&0xF);
							break;
						case 3:
						case 5:
							*out++ = 0x8E;
							*out++ = S3(r1)+((r2&0xF);
							break;
						case 1:
						case 4:
							return -1;
						}
					}
				}
				else //means r1 is a mem address
				{
					if (parse[1][0]!='['&&isnum(rmbrck(parse[1])))
					{
						return -1;
					}
					else if (parse[1][0]=='['&&isnum(rmbrck(parse[1]))) //literal address given
					{

						int imm = LILEND(atoi(rmbrck(parse[1])));
						*out++ = 0x89;
						*out++ = 5 + S3(r2);
						#ifdef _BITS16
						*out++ = ((imm&0xFF00)>>8);
						*out++ = imm&0xFF;
						#else
						*out++ = ((imm&0xFF000000)>>24);
						*out++ = ((imm&0xFF0000)>>16);
						*out++ = ((imm&0xFF00)>>8);
						*out++ = (imm&0xFF);
						#endif

					}
					else if (parse[1][0]=='[') //valid address of label
					{

					}
					else //valid label
					{

					}
				}
			}
		}
	}
}

int optimise(unsigned char *o) { //first-pass optimisation algorithms applied to code (3rd pass)

}

//further optimisation passes can be down here. compiler constraints also need to be a thing.
