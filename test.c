/*=============================================================================*/
/* ��������� ������������ �������, ����������� �������� � ����������� �������. */
/* �����: ��������� ����� ���������, 2019 �.                                   */
/* ���� ����������������: ��.                                                  */
/* ����������: Digital Mars C++ Compiler.                                      */
/*=============================================================================*/
#include <stdio.h>
#include "iadf.h"
int TestSample (int line, const char* s);
int IadfEqually (struct IADF* df1, struct IADF* df2);
const char* SkipOver (const char* s, const char* t);
int main ()
{
	int res, r1, r2;
	int line;
	char fn[] = "test.txt";	/* ��� ����� � ��������� ��������� */
	char s[256];		/* ����� ��� ������ ����� �� ����� */
	const char* p;		/* ��������� �� ������� � ������ */
	FILE* fp;		/* ��������� �� �������� � ����� */
	/* ���������� � ������ �������� �������� �� �����. */
	fp = fopen (fn, "r");
	if (fp != NULL) {
		/* ��������� �� �������� ������������. */
		printf ("IADFCAPACITY = %d\n", IADFCAPACITY);
		printf ("----------------------------------------------------------\n");
		/* ���������� ��������� ����������� �����. */
		line = 0;
		r1 = r2 = 0;
		while (fgets (s, sizeof s / sizeof (char), fp)) {
			line++;
			/* ������� ����� � �������������. */
			p = SkipOver (s, " \t");
			if (*p == '#')
				continue;
			/* ������ ��������� �������. */
			if (TestSample (line, s))
				r1++;
			else
				r2++;
		}
		fclose (fp);
		/* ��������� � ���������� ��������. */
		printf ("----------------------------------------------------------\n");
		printf ("Samples TOTAL:  %d\n", r1 + r2);
		printf ("Samples PASSED: %d\n", r1);
		printf ("Samples ERROR:  %d\n", r2);
		printf ("Summary: %s", r2 > 0? "ERROR": "PASSED");
		res = 0;
	}
	else {
		/* ������ �������� ����� ��� ������. */
		printf ("ERROR: Cannot open the file \"%s\" for reading.\n");
		res = 1;
	}
	return res;
}
/*===========================================================*/
/* ������ ��������� �������.                                 */
/* �����: line - ���������� ����� ������ � �����,            */
/*        s - ��������� �� ������, ���������� ������.        */
/* �������: 1 - �������� ������ ������ ��������,             */
/*          0 - ������ ��� ���������� ��������� �������.     */
/*===========================================================*/
#define DEBUG 0
int TestSample (int line, const char* s)
{
	char buf[64];
	struct IADF df1, df2, df3;
	int res;
	char op;		/* ���� �������� */
	int ec, rc;		/* ��� ���������� */
	const char* p;		/* ��������� �� ������� ������� � ������ */
	int ef;			/* ������� ������ */
	int i, n;
	ef = 0;
	/* ������� ��������. */
	p = SkipOver (s, " \t");
	/* ���������� ������� ��������. */
	n = iadfInit (&df1, p);
	p += n;
	ef = !n;
	if (!ef) {
		/* ������� ��������. */
		p = SkipOver (p, " \t");
		/* ���������� ������� ��������. */
		if (*p != '\0')
			op = *p;
		ef = op != '+' && op != '-' && op != '*' && op != '/';
	}
	if (!ef) {
		/* ������� ��������. */
		p = SkipOver (p + 1, " \t");
		/* ���������� ������� ��������. */
		n = iadfInit (&df2, p);
		p += n;
		ef = !n;
	}
	if (!ef) {
		/* ������� ��������. */
		p = SkipOver (p, " \t");
		/* ���������� ������� '='. */
		ef = *p != '=';
	}
	if (!ef) {
		/* ������� ��������. */
		p = SkipOver (p + 1, " \t");
		/* ���������� ����������. */
		n = iadfInit (&df3, p);
		p += n;
		ef = !n;
	}
	if (!ef) {
		/* ������� ��������. */
		p = SkipOver (p, " \t");
		/* ���������� ���� ����������. */
		ef = *p < '0' || *p > '9';
		if (!ef)
			ec = *p - '0';
	}
	/* ��������� ������ � ��������. */
	if (ef) {
		/* ��������� ������ ��������������� ������� ������. */
		printf ("Line #%d - sample string parsing ERROR:\n", line);
		puts (s);
		n = p - s;
		for (i = 0; i < n; i++)
			putchar (' ');
		puts ("^-- parsing error occures");
		res = 0;
	}
	else {
		/* �������� ����������� � ������ �������. */
		#if DEBUG == 1
			printf ("Line #%d string parsed:\n", line);
			puts (s);
			iadfToStr (&df1, buf, sizeof buf / sizeof (char));
			printf ("DEBUG first operand:  [%s]\n", buf);
			printf ("DEBUG operation:      [%c]\n", op);
			iadfToStr (&df2, buf, sizeof buf / sizeof (char));
			printf ("DEBUG second operand: [%s]\n", buf);
			iadfToStr (&df3, buf, sizeof buf / sizeof (char));
			printf ("DEBUG result value:   [%s]\n", buf);
			printf ("DEBUG result code: %d\n", ec);
		#endif
		/* ���������� ��������, ����������� � �������. */
		switch (op) {
			case '+':	/* ��������. */
				rc = iadfAdd (&df1, &df2);
				break;
			case '-':	/* ���������. */
				rc = iadfSub (&df1, &df2);
				break;
			case '*':	/* ���������. */
				rc = iadfMul (&df1, &df2);
				break;
			case '/':	/* �������. */
				rc = iadfDiv (&df1, &df2);
		}
		/* ������ ����������� ����������. */
		if (!IadfEqually (&df1, &df3) || ec != rc) {
			printf ("Line #%d sample checking error:\n", line);
			printf ("> %s\n", s);
			iadfToStr (&df3, buf, sizeof buf / sizeof (char));
			printf ("> Expected result:   [%d] - [%s]\n", ec, buf);
			iadfToStr (&df1, buf, sizeof buf / sizeof (char));
			printf ("> Calculated result: [%d] - [%s]\n", rc, buf);
			res = 0;
		}
		else
			res = 1;
	}
	return res;
}
/*============================================*/
/* �������� ��������� ���� ���������� ������. */
/* �����: df1 - ��������� �� ������ �����,    */
/*        df2 - ��������� �� ������ �����.    */
/* �������: 1 - ����� �����,                  */
/*          0 - ����� �� �����.               */
/*============================================*/
int IadfEqually (struct IADF* df1, struct IADF* df2)
{
	int res;
	int i;
	res = 1;
	res = res && df1->n == df2->n;
	res = res && df1->m == df2->m;
	res = res && df1->s == df2->s;
	if (res)
		for (i = 0; i < df1->n; i++)
			res = res && df1->v[i] == df2->v[i];
	return res;
}
/*===========================================================*/
/* ������� �������� � ������.                                */
/* �����: s - ��������� �� ��������� ������� � ������,       */
/*        t - ��������� �� ������ � ������������� ���������. */
/* �������: ��������� �� ������� � ������, ��������� ��      */
/*          ������������ ���������.                          */
/*===========================================================*/
const char* SkipOver (const char* s, const char* t)
{
	const char* p;
	do {
		/* �������� ���������� �������� ������� ������ � ����� �� ������������ ��������. */
		p = t;
		while (*p && *s != *p)
			p++;
		/* ������� ������� � ������ ����������. */
		if (*p)
			s++;
	} while (*p);
	return s;
}