/*	Considere vectores de bits representados sobre arrays de unsigned long e que ULONG_BIT é o número de bits
	do tipo unsigned long. No índice n de um array de unsigned long, o bit de menor peso corresponde ao índice
	n * ULONG_BIT do vector de bits, enquanto que o bit de maior peso corresponde ao índice (n + 1) *
	ULONG_BIT - 1​. A função getbits retorna o valor dos bits entre as posições idx e idx + len - 1 do vector
	de ​ bits representado por ​ bits. A função ​ setbits escreve os len bits de menor peso de val nas posições
	entre idx e idx + len - 1 do vector de bits representado por bits. Em ambas as funções, considere que
	len nunca é maior do que ULONG_BIT​. Ex.: para bits = { 0x98761111FCDFEC80, 0xABCDEF001234567A }​,
	a chamada a ​getbits(bits, 56, 20) retorna ​ 0x0000000000067A98​. Usando a linguagem C, defina
	ULONG_BIT​ e escreva as funções ​getbits​ e setbits​.
*/

#include <stdio.h>
#include <limits.h>
typedef unsigned long ulong;
#define ULONG_BIT sizeof(unsigned long)*CHAR_BIT

unsigned long getbits(unsigned long bits[], unsigned idx, unsigned len)
{
	//check idx size and adjusts it
	int ind = 0;
	if (idx>=ULONG_BIT)
	{
		ind = idx/ULONG_BIT;
		idx = idx%ULONG_BIT;
	}
	ulong ret = bits[ind]>>idx;
	
	//check if index goes over to the next value in array so it masks correctly
	if(idx+len > ULONG_BIT)
	{
		ulong mask = ~(~(ulong)0<<(len-(ULONG_BIT-idx)));
		ret = ((bits[ind+1]&mask)<<(ULONG_BIT-idx)) + ret;
	} 
	else 
	{
		ulong mask = ~(~(ulong)0<<len);
		ret &= mask;
	}
	return ret;
};

void setbits(unsigned long bits[], unsigned idx, unsigned len, unsigned long val)
{
	//check idx size and adjusts it
	int ind = 0;
	if (idx>=ULONG_BIT)
	{
		ind = idx/ULONG_BIT;
		idx = idx%ULONG_BIT;
	}
	
	//check if index goes over to the next value in array so it masks correctly
	if(idx+len > ULONG_BIT)
	{
		ulong mask = ~(~(ulong)0<<(idx-4));
		bits[ind] = (bits[ind]&mask) + (val<<(idx-4));
		mask = ~0<<(len-(ULONG_BIT-idx));
		bits[ind+1] =  (bits[ind+1]&mask) + (val>>(len-(ULONG_BIT-idx)));  
	} 
	else 
	{
		ulong mask = ~(~0<<len);
		val &= mask;
		mask = ~(mask << idx);
		bits[ind] = (bits[ind]&mask) + (val << idx);
	}
}

int main() 
{
	ulong bits[] = { 0x98761111FCDFEC80, 0xABCDEF001234567A };
	printf("0x%lX 0x%lX\n", bits[0], bits[1]);
	ulong set = 0x4B8D1F;
	setbits(bits, 56, 20, set);
	printf("0x%lX 0x%lX\n", bits[0], bits[1]);
}
