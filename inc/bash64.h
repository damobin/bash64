#ifndef BASH64_H
#define BASH64_H
#include "public.h"
#include "iostream"
using namespace std;

#define MAXLEN	0x100

class BASH64{
public:
	template<typename str_any> friend str_any &operator <<(str_any &,BASH64 &bash64);
	BASH64();
	BASH64(uint8_t *origin);
	BASH64(char *origin);
	BASH64(const char *origin);
	BASH64(const uint8_t *origin);
	int bashfun();
	int rebashfun();
	void setBashSrc(uint8_t *source);
private:
	static uint8_t bash64table[65];
	uint8_t src[MAXLEN]={0};
	uint16_t getOutLen=0;
	uint8_t out[MAXLEN]={0};
	uint16_t regetOutLen=0;
};

template<typename str_any> str_any &operator <<(str_any &os,BASH64 &bash64)
{
	os<< "src exc out =" <<endl;
	PRINTSTRCHAR(bash64.out,bash64.getOutLen,50);
	os<< "out exc src =" <<endl;
	PRINTSTRCHAR(bash64.src,bash64.regetOutLen,50);
	return os;
}

#endif