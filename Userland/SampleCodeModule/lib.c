/*
	sysCallHandler -> int 80
	Hacer sys call
		rdi - rci - rdx - rbx

*/
#include <stdarg.h>
#include "lib.h"
#include "define.h"
#include "libasm.h"

#include <stdarg.h>		

void putChar( char c ) 
{
	execSysCall(SYS_WRITE, STDOUT, &c, 1);
}

char getChar()
{
	char c = -1;
	execSysCall(SYS_READ, STDIN, &c, 1);
	return c;
}


void printf(char * s, ...)
{
	// TODO
	int i = 0;
	for ( i = 0; s[i] != '\0'; i++) {
		putChar( s[i] );
	}
}

void concat(char * first, char * second, char * to) 
{
	int i = 0;
	int j = 0;

	for ( i = 0; first[i] != '\0'; i++ ) {
		to[i] = first[i];
	}
	for ( j = 0; second[i] != '\0'; i++, j++ ) {
		to[i] = second[j];
	}
	to[i] = '\0';
}

// printf( "gilada %d%d\n", 2, 3 )

int sscanf(const char * source, const char * format, ...) 
{
	int count;
	va_list vl;

	va_start(vl, format);
	count = vsscanf(source, format, vl);
	va_end(vl);
	return count;
}

int vsscanf(const char * s, const char * f, va_list vl)
{
	int i, count = 0;
	char * strBuffer;
	char intBuffer[25]; // We can read numbers only 25 digits long

	while (*s != '\0' && *f != '\0') {
		// Read till first non space character
		while (*f == ' ')
			f++;

		if (*f == '%') { // Maybe found a format specifier
			f++;

			if (*f == 's') { // String format
				f++;
				// Read till first non space character found
				while (*s == ' ')
					s++;

				// Ready to copy till the first space or end of string
				strBuffer = va_arg(vl, char *);
				i = 0;
				while (*s != ' ' && *s != '\0') {
					strBuffer[i] = *s;
					s++;
					i++;
				}

				count++;
			} else if (*f == 'd') { // Number format
				f++;

				while (*s == ' ')
					s++;

				// Check if we have a number 
				if (cindex(*s, "0123456789") >= 0) {
					i = 0;
					// Being careful with intBuffer size; it's 25 chars long,
					// so we have to write 24 chars max, so there's space for \0
					while (*s != ' ' && *s != '\0' && cindex(*s, "0123456789") >= 0 && i < 24) {
						intBuffer[i] = *s;
						s++;
						i++;
					}
					intBuffer[i] = '\0';
					*(va_arg(vl, int *)) = stoi(intBuffer);

					count++;
				} else {
					break;
				}
			} 
			// else do nothing, it's a '%' alone

		} else { // Normal character
			// Read until first non space character
			while (*s == ' ')
				s++;

			// At the first non equal set of characters, end function
			if (*s != *f) {
				break;
			} else {
				s++;
				f++;
			}
		}
	}

	return count;
}

// to = placeHolder
void to_s ( int f, char* to )
{
    char const digits[] = "0123456789";
	int aux = f;

	do {
		to++;
		aux = aux / 10;
	} while ( aux != 0 );
	
	*to = '\0';
	to--;
	int digit = f;
	
	do {
		digit = f % 10;
		f /= 10;
		*to = digits[digit%10];
		to--;
	} while ( f != 0 );
}

/*
 * Returns the index of the char in str, -1 if not in str
 */
int cindex(char c, const char * str)
{
	int i = -1;

	while (str[++i] != '\0') {
		if (c == str[i])
			break;
	}

	return i;
}

/*
 * String representation of an int to int (base 10)
 */
int stoi(const char * str)
{
	int i = 0;
	while (*str != '\0') {
		i = i * 10 + *str - '0';
		str++;
	}

	return i;
}

// Variable args

void printf_v( char* s, ... ) {
	
  	va_list ap;
   	int i;
   	va_start(ap, s);
	
   	for ( i = 0; s[i] != '\0'; i++) {
   		if( s[i] == '%' ){
			if ( s[i+1] = 'd' ) {
				int aux = va_arg(ap, int);
				char istring[ (int_length(aux)) ];
				to_s(aux, istring);
				printf( istring );
				i++;
			} else if ( s[i+1] = 'c' ) {
				char aux = va_arg(ap, char);
				char letter[2];
				to_c (aux, letter);
				printf(letter);
				i++;
			} else if ( s[i+1] = 's' ) {
				char* aux = va_arg(ap, char*);
				printf(aux);
				i++;
			} else
				putChar('%');
		} else 
			putChar( s[i] );
   	}
   	va_end(ap);
}

int int_length ( int i ) {
	int aux = 0;
	do {
		i = i / 10;
		aux ++;
	} while ( i != 0 );
	return aux;
}

int strlen ( char * s ) {
	int i = 0;
	while (s[i] != '\0')
		i++;
	return i;
} 

void to_c (int i, char* to ) {
	to[0] = (char) i;
	to[1] = '\0';
}

int strcmp(const char * str1, const char * str2)
{
	while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0') {
		str1++;
		str2++;
	}

	return *str1 - *str2;
}

