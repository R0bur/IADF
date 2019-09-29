# IADF
The fixed-capacity decimal arithmetic for the numbers with the decimal point natural placement (this representation used for financial hardware calculators).

The Author: Ihar Areshchankau, 2019.

## Usage:

1. Specify the needed capacity of the arithmetic into the file "iadf.h":
  ```c
  ...
  #define IADFCAPACITY 10
  ...
  ```
2. Include the header "iadf.h" into the program and use the abilities it provides:
```c
  #include "iadf.h"
  #define N (IADFCAPACITY + 4)
  ...
  char a[] = "1234.56789";
  char b[] = "-98765.4321";
  char c[N];
  struct IADF dfa, dfb;
  ...
  iadfInit (&dfa, a);
  iadfInit (&dfb, b);
  iadfAdd (&dfa, &dfb);
  iadfToStr (&dfa, c, N);
  printf ("Addition: (%s) + (%s) = (%s)\n", a, b, c);
```
3. Please look the file "demo.c" for the more descriptive example.
