/*	Desenvolva a função ​ ftoi​ , que retorna a parte inteira de ​ val​ . Se a parte inteira de ​ val exceder ​ INT_MAX​ , a
	função retorna ​ INT_MAX​ . Se a parte inteira de ​ val for menor do que ​ INT_MIN​ , a função retorna ​ INT_MIN​ . Na
	implementação interna só podem ser utilizadas operações aritméticas e lógicas sobre inteiros. Qualquer
	operação de vírgula flutuante invalida o exercício.*/
	
#include <stdio.h>
#define FLT_FRAC_BIT		23		/* frac field bits */
#define FLT_EXP_BIT		8		/* exp field bits */
#define FLT_SIGN_BIT		1		/* sign field bits */

struct flt_bits {
	unsigned int frac : FLT_FRAC_BIT;
	unsigned int exponent : FLT_EXP_BIT;
	unsigned int sign : FLT_SIGN_BIT;
};

union flt_union {
	float _float;
	unsigned int _uint;
	struct flt_bits _bits;
};

int _ftoi (float val){
	union flt_union fu;
	fu._float=val;
        unsigned int exp = fu._bits.exponent & (64-1);  // remove last bit from exponent
        unsigned int mantissa = fu._bits.frac >> (FLT_FRAC_BIT-exp-1);  //shift floating point part from the mantissa
        return (2 << exp) + mantissa; //2^exp and sum with integer part of mantissa
}

int main (){
    float _float[] = {39.683, 24.124, 1, 0, 200, 2.5000};
    for (int i = 0; i < sizeof(_float)/sizeof(_float[0]); i++){
        int _int = _ftoi(_float[i]);
        printf("Floating point number: %f; Integer part: %u\n", _float[i], _int);
    }
    return 0;
}
