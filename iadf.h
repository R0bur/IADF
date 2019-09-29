/*==========================================================*/
/* ������ ��������  �  ����������� �������, ��������������� */
/* � ������� �������� ����������� � ������������ ���������� */
/* ���������� �������.                                      */
/*                ������������ ���� iadf.h                  */
/*----------------------------------------------------------*/
/* �����: ��������� ����� ���������, 2019 �.                */
/* ���� ����������������: ��.                               */
/* ����������: Digital Mars C/C++ Compiler.                 */
/*==========================================================*/
#ifndef IADF_H
#define IADF_H 1
#define IADFCAPACITY 10
struct IADF {
	int n;	/* ����� ���������� ���� */
	int m;	/* ���������� ���� � ����� ����� */
	int s;	/* ���� ����� */
	unsigned char v[IADFCAPACITY];	/* �������� ����� */
};
int iadfInit (struct IADF* df, const char* s);
int iadfToStr (const struct IADF* df, char* buf, int n);
int iadfAbsCompare (const struct IADF* df1, const struct IADF* df2);
int iadfAdd (struct IADF* df1, const struct IADF* df2);
int iadfSub (struct IADF* df1, const struct IADF* df2);
int iadfMul (struct IADF* df1, const struct IADF* df2);
int iadfDiv (struct IADF* df1, const struct IADF* df2);
#endif