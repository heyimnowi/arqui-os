#ifndef _LIB_H
#define _LIB_H

void putChar( char c );
void printf( char* s );
void to_s ( int f, char* to );
void concat (char* first, char* second, char* to);
void getChar ( char c );
void scanf ( char* s);

void printf_v ( char* s, ... );
int int_length ( int i );
int strlen ( char* s );
void to_c (int i, char* to );

#endif