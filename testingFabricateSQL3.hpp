//
//  testingFabricateSQL3.h
//  testingFabricateSQL3
//
//  Created by Clifford Campo on 8/11/20.
//  Copyright © 2020 CliffordCampo. All rights reserved.
//

#ifndef testingFabricateSQL3_h
#define testingFabricateSQL3_h
#include <stddef.h>
#include <libpq-fe.h>
#include <fabricateSQL/fabricateSQLr3.h>   //fabricateSQLr3.dylib is in /usr/local/lib; \
fabricateSQLr3.h is found in -rw-r--r--@ 1 cjc  admin  4423 Feb 22  2021  /usr/local/include/fabricateSQL/fabricateSQLr3.h
//#include "/usr/local/include/databaseOps/databaseOps.h"
//#include "/usr/local/include/fabricateSQL/fabricateSQLr3.h" //timings structure is found here.
//#include "connectToDatabase.hpp"
//#include "/usr/local/include/fabricateSQL/fabricateSQLr2.h"

#define OFFSET_SITEID 1
#define OFFSET_DATE 2
#define OFFSET_BEFOREDATAPOINTS 4
#define OFFSET_AFTERDATAPOINTS 5
#define BYTES_PER_CHARACTER 1
#define SIZEOFSSARRAY 11
#define SIZEOFSRARRAY 11
#define SIZEOFNOONARRAY 9

/*
// P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E
void fabricateSQLr3(timings *pd, //Pointer to buffer containing fabricateSQL's performance data. If NULL then no performance data
  char **tokensAndReplacements, //  a 2-dimensional array of pointers to characters forming the tokens and \
       replacements. Note that the first parameter of fabricateSQLr3, above, defines the size of this array.
  char *input_c_string_template_buffer,  // points to the buffer containing the template
  int  sizeOfTemplate,                   // Size, in bytes, of the input_c_string_template_buffer
  char *resulting_c_StringBuffer,        // points to the buffer contining the resulting sql, having all Tokens replaced by their \
    replacement c-strings.
  size_t *sizeOf_resulting_c_StringBuffer, // size of the resulting_c_string buffer
  int debugFlag );                      // output debug messages when set to >0 [TRUE]
*/
//Above is how one calls the c++-coded dylib, named fabricateSQL

static const char *SUNRISE = "<";
static const char *SUNSET =  ">";
static const char *ptr_preamble_replacement = "BEGIN; DECLARE CURSOR srnoonssportal ";
static const char *ptr_postamble_replacement = "FETCH ALL srnoonssportal; CLOSE srnoonssportal; END;";
static const char *ptr_field_replacement = "zenithdistance";


#endif /* testingFabricateSQL3_h */
