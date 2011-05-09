/*
 * bugger.h
 *
 *  Created on: May 8, 2011
 *      Author: nickmain
 */

#ifndef BUGGER_H_
#define BUGGER_H_

#include <stdio.h>

FILE* debugFile;

#define OPEN_DEBUG // debugFile = fopen( "/home/nickmain/Desktop/debug.log", "w" );

#define CLOSE_DEBUG // fclose( debugFile );

#define DEBUG( msg ) // fprintf( debugFile, "%s\n", msg ); fflush( debugFile );
#define DEBUGI( msg, i ) // fprintf( debugFile, "%s %lu\n", msg, i ); fflush( debugFile );

#endif /* BUGGER_H_ */
