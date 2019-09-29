/*=============================================================================*/
/* Программа тестирования функций, реализующих операции с десятичными дробями. */
/* Автор: Орещенков Игорь Сергеевич, 2019 г.                                   */
/* Язык программирования: Си.                                                  */
/* Компилятор: Digital Mars C++ Compiler.                                      */
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
	char fn[] = "test.txt";	/* имя файла с тестовыми примерами */
	char s[256];		/* буфер для чтения строк из файла */
	const char* p;		/* указатель на позицию в буфере */
	FILE* fp;		/* указатель на сведения о файле */
	/* Подготовка к чтению тестовых примеров из файла. */
	fp = fopen (fn, "r");
	if (fp != NULL) {
		/* Сообщение об условиях тестирования. */
		printf ("IADFCAPACITY = %d\n", IADFCAPACITY);
		printf ("----------------------------------------------------------\n");
		/* Построчная обработка содержимого файла. */
		line = 0;
		r1 = r2 = 0;
		while (fgets (s, sizeof s / sizeof (char), fp)) {
			line++;
			/* Пропуск строк с комментариями. */
			p = SkipOver (s, " \t");
			if (*p == '#')
				continue;
			/* Прогон тестового примера. */
			if (TestSample (line, s))
				r1++;
			else
				r2++;
		}
		fclose (fp);
		/* Сообщение о результате проверки. */
		printf ("----------------------------------------------------------\n");
		printf ("Samples TOTAL:  %d\n", r1 + r2);
		printf ("Samples PASSED: %d\n", r1);
		printf ("Samples ERROR:  %d\n", r2);
		printf ("Summary: %s", r2 > 0? "ERROR": "PASSED");
		res = 0;
	}
	else {
		/* Ошибка открытия файла для чтения. */
		printf ("ERROR: Cannot open the file \"%s\" for reading.\n");
		res = 1;
	}
	return res;
}
/*===========================================================*/
/* Прогон тестового примера.                                 */
/* Вызов: line - порядковый номер строки в файле,            */
/*        s - указатель на строку, содержащую пример.        */
/* Возврат: 1 - тестовый пример прошёл проверку,             */
/*          0 - ошибка при выполнении тестового примера.     */
/*===========================================================*/
#define DEBUG 0
int TestSample (int line, const char* s)
{
	char buf[64];
	struct IADF df1, df2, df3;
	int res;
	char op;		/* знак операции */
	int ec, rc;		/* код завершения */
	const char* p;		/* указатель на текущую позицию в строке */
	int ef;			/* признак ошибки */
	int i, n;
	ef = 0;
	/* Пропуск пробелов. */
	p = SkipOver (s, " \t");
	/* Считывание первого операнда. */
	n = iadfInit (&df1, p);
	p += n;
	ef = !n;
	if (!ef) {
		/* Пропуск пробелов. */
		p = SkipOver (p, " \t");
		/* Считывание символа операции. */
		if (*p != '\0')
			op = *p;
		ef = op != '+' && op != '-' && op != '*' && op != '/';
	}
	if (!ef) {
		/* Пропуск пробелов. */
		p = SkipOver (p + 1, " \t");
		/* Считывание второго операнда. */
		n = iadfInit (&df2, p);
		p += n;
		ef = !n;
	}
	if (!ef) {
		/* Пропуск пробелов. */
		p = SkipOver (p, " \t");
		/* Считывание символа '='. */
		ef = *p != '=';
	}
	if (!ef) {
		/* Пропуск пробелов. */
		p = SkipOver (p + 1, " \t");
		/* Считывание результата. */
		n = iadfInit (&df3, p);
		p += n;
		ef = !n;
	}
	if (!ef) {
		/* Пропуск пробелов. */
		p = SkipOver (p, " \t");
		/* Считывание кода завершения. */
		ef = *p < '0' || *p > '9';
		if (!ef)
			ec = *p - '0';
	}
	/* Обработка строки с примером. */
	if (ef) {
		/* Произошла ошибка синтаксического разбора строки. */
		printf ("Line #%d - sample string parsing ERROR:\n", line);
		puts (s);
		n = p - s;
		for (i = 0; i < n; i++)
			putchar (' ');
		puts ("^-- parsing error occures");
		res = 0;
	}
	else {
		/* Проверка записанного в строке примера. */
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
		/* Выполнение операции, приведенной в примере. */
		switch (op) {
			case '+':	/* Сложение. */
				rc = iadfAdd (&df1, &df2);
				break;
			case '-':	/* Вычитание. */
				rc = iadfSub (&df1, &df2);
				break;
			case '*':	/* Умножение. */
				rc = iadfMul (&df1, &df2);
				break;
			case '/':	/* Деление. */
				rc = iadfDiv (&df1, &df2);
		}
		/* Сверка полученного результата. */
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
/* Проверка равенства двух десятичных дробей. */
/* Вызов: df1 - указатель на первую дробь,    */
/*        df2 - указатель на вторую дробь.    */
/* Возврат: 1 - дроби равны,                  */
/*          0 - дроби не равны.               */
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
/* Пропуск символов в строке.                                */
/* Вызов: s - указатель на начальную позицию в строке,       */
/*        t - указатель на строку с пропускаемыми символами. */
/* Возврат: указатель на позицию в строке, следующую за      */
/*          пропущенными символами.                          */
/*===========================================================*/
const char* SkipOver (const char* s, const char* t)
{
	const char* p;
	do {
		/* Проверка совпадения текущего символа строки с одним из пропускаемых символов. */
		p = t;
		while (*p && *s != *p)
			p++;
		/* Пропуск символа в случае совпадения. */
		if (*p)
			s++;
	} while (*p);
	return s;
}