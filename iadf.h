/*==========================================================*/
/* Модуль операций  с  десятичными дробями, представленными */
/* в формате заданной разрядности с естественным положением */
/* десятичной запятой.                                      */
/*                Заголовочный файл iadf.h                  */
/*----------------------------------------------------------*/
/* Автор: Орещенков Игорь Сергеевич, 2019 г.                */
/* Язык программирования: Си.                               */
/* Компилятор: Digital Mars C/C++ Compiler.                 */
/*==========================================================*/
#ifndef IADF_H
#define IADF_H 1
#define IADFCAPACITY 10
struct IADF {
	int n;	/* общее количество цифр */
	int m;	/* количество цифр в целой части */
	int s;	/* знак числа */
	unsigned char v[IADFCAPACITY];	/* значение числа */
};
int iadfInit (struct IADF* df, const char* s);
int iadfToStr (const struct IADF* df, char* buf, int n);
int iadfAbsCompare (const struct IADF* df1, const struct IADF* df2);
int iadfAdd (struct IADF* df1, const struct IADF* df2);
int iadfSub (struct IADF* df1, const struct IADF* df2);
int iadfMul (struct IADF* df1, const struct IADF* df2);
int iadfDiv (struct IADF* df1, const struct IADF* df2);
#endif