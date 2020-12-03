#include "bash64.h"

uint8_t BASH64::bash64table[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

BASH64::BASH64()
{
	for(int i=0;i<MAXLEN;i++){
		src[i] = 0;
	}
	getOutLen = 0;
	regetOutLen = 0;
}

BASH64::BASH64(uint8_t *origin)
{
	for(int i=0;i<MAXLEN;i++){
		src[i] = origin[i];
	}
	getOutLen = 0;
	regetOutLen = 0;	
}
BASH64::BASH64(char *origin)
{
	for(int i=0;i<MAXLEN;i++){
		src[i] = origin[i];
	}
	getOutLen = 0;
	regetOutLen = 0;	
}
BASH64::BASH64(const char *origin)
{
	for(int i=0;i<MAXLEN;i++){
		src[i] = origin[i];
	}
	getOutLen = 0;
	regetOutLen = 0;
}
BASH64::BASH64(const uint8_t *origin)
{
	for(int i=0;i<MAXLEN;i++){
		src[i] = origin[i];
	}
	getOutLen = 0;
	regetOutLen = 0;
}
void BASH64::setBashSrc(uint8_t *source)
{
	for(int i=0;i<MAXLEN;i++){
		src[i] = source[i];
	}
}
 //子函数 - 取密文的索引  
static inline char GetCharIndex(char c) //内联函数能够省去函数调用过程。提速  
{
	if((c >= 'A') && (c <= 'Z'))  
	{   
		return c - 'A';  
	}else if((c >= 'a') && (c <= 'z'))  
	{   
		return c - 'a' + 26;  
	}else if((c >= '0') && (c <= '9'))  
	{   
		return c - '0' + 52;  
	}else if(c == '+')  
	{   
		return 62;  
	}else if(c == '/')  
	{   
		return 63;  
	}else if(c == '=')  
	{   
		return 0;  
	}  
	return 0;  
}  

//输出生成长度
int BASH64::bashfun()
{
	int sLen = strlen((const char *)src);
	uint8_t *srctemp=src;
	uint8_t *outemp=out;
	int vLen = 0;  //寄存器局部变量，提速  
	while(sLen > 0)      //处理整个字符串  
	{
		*outemp++ = bash64table[(srctemp[0] >> 2 ) & 0x3F];  //右移两位，与00111111是防止溢出，自加  
		if(sLen > 2) //够3个字符  
		{   *outemp++ = bash64table[((srctemp[0] & 3) << 4) | (srctemp[1] >> 4)];  
			*outemp++ = bash64table[((srctemp[1] & 0xF) << 2) | (srctemp[2] >> 6)];  
			*outemp++ = bash64table[srctemp[2] & 0x3F];  
		}else  
		{   switch(sLen)    //追加“=”  
			{   case 1:  
					*outemp ++ = bash64table[(srctemp[0] & 3) << 4 ];  
					*outemp ++ = '=';  
					*outemp ++ = '=';  
					break;  
				case 2:  
					*outemp ++ = bash64table[((srctemp[0] & 3) << 4) | (srctemp[1] >> 4)];  
					*outemp ++ = bash64table[((srctemp[1] & 0x0F) << 2) | (srctemp[2] >> 6)];  
					*outemp ++ = '=';  
					break;  
			}  
		}
		srctemp += 3;  
		sLen -= 3;  
		vLen +=4;  
	}
	getOutLen = vLen;
	*outemp = 0; 	//最后一个字符 
	return vLen; 
}
int BASH64::rebashfun()
{   
	int sLen = strlen((const char *)out);
	static char lpCode[4];
	uint8_t *srctemp=src;
	uint8_t *outemp=out;
	int vLen = 0;  
	if(sLen % 4)        //Base64编码长度必然是4的倍数，包含'='  
	{   srctemp[0] = '\0';  
		return -1;  
	}  
	while(sLen > 2)      //不足三个字符。忽略  
	{   lpCode[0] = GetCharIndex(outemp[0]);  
		lpCode[1] = GetCharIndex(outemp[1]);  
		lpCode[2] = GetCharIndex(outemp[2]);  
		lpCode[3] = GetCharIndex(outemp[3]);  

		*srctemp++ = (lpCode[0] << 2) | (lpCode[1] >> 4);  
		*srctemp++ = (lpCode[1] << 4) | (lpCode[2] >> 2);  
		*srctemp++ = (lpCode[2] << 6) | (lpCode[3]);  

		outemp += 4;  
		sLen -= 4;  
		vLen += 3;  
	}  
	regetOutLen = vLen;
	return vLen;  
}  
