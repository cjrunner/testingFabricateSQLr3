//
//  main.c
//  testingFabricateSQL3
//
//  Created by Clifford Campo on 8/10/20.
//  Copyright © 2020 CliffordCampo. All rights reserved.
//


#include "testingFabricateSQL3.hpp"
//#include "constants.hpp"
#include "extractKeySiteParameters.hpp"
#include "helpMsg.hpp"
#define SITEID 1
#define SOMEDATE 2
#define BEFOREDATAPOINTS 4
#define AFTERDATAPOINTS 5
// #include <fabricateSQLr3.h>
void fabricateSQLr3(timings *, const char **, const char *, int t, char *, size_t *, bool);
// void fabricateSQLr3(timings *sb, const char **theTokensReplacements, const  char *oSQLt, int t, char *cStringBuffer, size_t *outsize, bool debug);
// P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E
//void fabricateSQL(int numberOfTokensEqualToNumberOfReplacements, /* number of tokens (and replacements) to process */ \
//                  char **tokens, /*  an array of pointers to characters forming the tokens */ \
//                  char **replacements, /* an array of pointers to characters forming the replacemnet strings */ \
//                  char *input_c_string_template_buffer, /* points to the buffer containing the template */ \
//                  char *resulting_c_StringBuffer, /* points to the buffer contining the resulting sql */ \
//                  int sizeOf_resulting_c_StringBuffer, /* size of the previous buffer */  \
//                  int debugFlag /* output debug messages when set to >0 [TRUE] */     );
//void fabricateSQLr3(timings *sb, char **theTokensReplacements, char *oSQLt, int t, char *cStringBuffer, size_t *outsize, bool debug);
int main(int argc, const char **argv, const char **env, const char **somethingElse) { //const char *argv[] is the same as **argv
    timings *ptrPerformanceBuffer = nullptr;
    Constants  c; // Instantiate the Constants object.
//    Dbc *dbc = (Dbc *)calloc(sizeof(Dbc),1);  // Dbc is defined in include file:  /usr/local/include/databaseOps/databaseOps.h
    c.dbc = (Dbc *)calloc(sizeof(Dbc),1);  // Dbc is defined in include file:  /usr/local/include/databaseOps/databaseOps.h
    //Set the parameters' default values.
    c.dbc->conn     = NULL;
    c.dbc->res      = NULL;
    c.dbc->dbname   = "LocalWeather";
    c.dbc->portId   = "5436";
    c.dbc->hostName = "localhost";
    c.dbc->userId   = "cjc";
    c.dbc->debug    = 0;

// *************************************************************************************************************************** \
    Note: fabricateSQL, the dylib under test, is found at: \
    /Users/cjc/Library/Developer/Xcode/DerivedData/Build/Products/Debug/libfabricateSQL.dylib \
    This program can load the above dynamic library (dylib) which this program tests, then before compiling: \
    a) place `/Users/cjc/Library/Developer/Xcode/DerivedData/Build/Products/Debug/libfabricateSQL.dylib` in \
    "Dynamic Library Install Name"; \
    b) Place `-lfabricateSQL` in "Other Linker Flags". \
*******************************************************************************************************************************

    const struct option long_options[] = {
 //        const char *name points to the long option name of this argument
 //        int val: is one of three possible values: no_argument, required_argument, or optional argument;
 //        int *flag:
 //        • If flag IS a null pointer then val is the value which identifies this option.
 //        • If flag IS NOT a null pointer then flag should point to an int variable which is interpred as the flag for this option.
 //        int val: The value in val is the value to store in the flag to indicate that the option was seen.
 //        int val the value of the short option -------------+
 //        int *flag ------------------------------+          |
 //        int has_arg ----------+                 |          |
 //        const char *name      |                 |          |
 //        |                     |                 |          |
 //        V                     V                 V          V
        {"siteid",            required_argument,  &c.optsid,  'S'}, // 00 Default is 0; see LocalWeather’s database table \
        named tbl_site_names for a list of possible sitenames. This test program may read from this table.
        {"somedate",          required_argument,  &c.opsd,    'D'}, // 01 Enterning a date is mandatory;
        {"beforedatapoints", optional_argument,   &c.opbdp,   'b'}, // 02 Default = 4
        {"afterdatapoints",  optional_argument,   &c.opadp,   'a'}, // 03 Default = 4
        {"field",              optional_argument, &c.opField, 'F'}, // 04 Default value is zenithdistance and is associated with \
        SunRise and SunSet. Other values are ERA (Earth Rotation Angle), last (local astronomical sideral time), and gast \
        (geocentric astronomical sideral time). Other values (e.g. Spring (when geocentric right ascension = 0º or 0 hours) \
        to be defined later.
        {"event",              required_argument, &c.opevnt,  'E'}, // 05 Typical values are SR (i.e., Sunrise),  SS (i.e., SunSet), \
        and N (Noon)
        {"sunrisedefinition", optional_argument,  &c.opsrd,   'r'}, // 06 Default value is 90.58333333º
        {"sunsetdefinition",  optional_argument,  &c.opssd,   's'}, // 07 Default value is 90.58333333º
        {"Year",              optional_argument,  &c.opYear,  'Y'}, // 08 Default Year is 2021
        {"db1",               no_argument,        &c.op1,     '1'}, // 09 Debug Level 1: Debug early intermediate values of \
        testingFabricateSQLr3
        {"db2",               no_argument,        &c.op2,     '2'}, // 10 Debug Level 2: Debug the parameter substitution, \
        from values obtained from the command line, into the 2D arrays, known as sunSetArray, sunRiseArray, and noonArray, \
        which contain the Token/Replacement pairs driving the processing of the fabricateSQLr3.dylib.
        {"db3",               no_argument,        &c.op3,     '3'}, // 11 Debug Level 3: View development of parameters that are \
        sent to the fabricateSQLr3.dylib.
        {"db4",               no_argument,        &c.op4,     '4'}, // 12 Debug Level 4: debug fabricateSQL4.dylib itself.
        {"help",              no_argument,        &c.ophelp,  'h'}, // 13 Outputs a help message and then quits.
        {"file",              optional_argument,  &c.opfile,  'f'}, // 14 Alternative name of the output file holding the SQL produced \
        by fabricateSQLr3. Default name of this file is
        {0, 0, 0, 0}                                                // 15 End of array indicator.
    };
    while (c.oprc >= 0) {
        c.oprc = getopt_long(argc, (char * const *)argv, c.theArguments, long_options, &c.optionIndex);
        if (c.oprc < 0) break;
        switch (c.oprc) {

            case 'S':
                c.ptrWhatThisSiteIdIs = optarg;
                *(long_options + 0)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                break;
            case 'D':
                c.ptrWhatThisSomeDateIs = optarg;
                *(long_options + 1)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                break;
            case  'b':
                c.ptrWhatThisBeforeDataPointsIs = optarg;
                *(long_options + 2)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                break;
            case 'a':
                c.ptrWhatThisAfterDataPointsIs = optarg;
                *(long_options + 3)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                break;
            case 'F':
                c.ptrWhatThisFieldIs = optarg;
                *(long_options + 4)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                break;
            case 'E':
                c.ptrWhatThisEventIs = optarg;
                printf("BEFORE: *long_options[5].flag: %d\n", *(long_options + 5)->flag );
                *(long_options + 5)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                printf("AFTER:  *long_options[5].flag: %d\n", *(long_options + 5)->flag );
                if (strcmp (optarg, "Summer") == 0) {
                    c.ptrWhatThisDefIs = "6";
                    c.ptrWhatThisGeocentricraSeasonIs = c.ptrWhatThisDefIs;
                } else if (strcmp (optarg, "Spring") == 0) {
                    c.ptrWhatThisDefIs = "0";
                    c.ptrWhatThisGeocentricraSeasonIs = "0";
                } else if ( (strcmp (optarg, "Fall") == 0)  || (strcmp (optarg, "Autumn" ) == 0)) {
                    c.ptrWhatThisDefIs = "12";
                    c.ptrWhatThisGeocentricraSeasonIs = "12";
                } else if (strcmp (optarg, "Winter") == 0) {
                    c.ptrWhatThisDefIs = "18";
                    c.ptrWhatThisGeocentricraSeasonIs = "12";
                } else {
                    ;
                }
                printf("/n Event specified as %s", c.ptrWhatThisEventIs );
                break;
            case 'r':
                c.ptrWhatThisDefIs = optarg;
                *(long_options + 6)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                break;
            case 's':
                c.ptrWhatThisDefIs = optarg;
                *(long_options + 7)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                break;
            case 'Y':
                c.ptrWhatThisSomeYearIs = optarg;
                *(long_options + 8)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                break;
            case '1':
                c.db1 = 1;
                *(long_options + 9)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                break;
            case '2':
                c.db2 = 1;
                *(long_options + 10)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                break;
            case '3':
                c.db3 = 1;
                *(long_options + 11)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                break;
            case '4':
                c.db4 = true;
                *(long_options + 12)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                break;
            case 'h':
                c.name = (char *)long_options->name;
                c.val  = long_options->val;
                c.flag = *long_options->flag;
                c.has_arg = long_options->has_arg;
                *(long_options + 13)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                helpMsg((char **)(argv+0));
                exit (1);
                break;
            case 'f':
                *(long_options + 14)->flag *= -1; //Turn this value positive so we can tell that it has been modified.
                c.outputFileName = optarg;
                break;
            default:
                printf("Encountered unknown parameter: --%s or -%c. Legal parameters are as follows:\n", \
                       long_options[c.optionIndex].name, long_options[c.optionIndex].val);
                helpMsg((char **)(argv+0));
                break;
        } //End of switch
    } //End of while loop
    /*
     long_options->name;
     long_options->val;
     long_options->flag;
     long_options->has_arg;
    */
    c.fp = fopen(c.outputFileName, "w");
    if (c.db1) {
        printf("===============================================somethingElse==============================================\n");
        
        while (*(somethingElse+c.j) ) {
            printf("%02d. (note: j=0 is a pointer to 0x0…0, so we'll skip it) somethingElse address %p value %s\n", c.j, \
                   (somethingElse+c.j), *(somethingElse + c.j));
            c.j++;
        }
        
        printf("=====================================================env=======================================================\n");
        while (*( env + c.i) ) {
            printf("%02d. env address %p value %s\n", c.i, (env+c.i), *(env + c.i));
            c.i++;
        }
        printf("======================================================argv=====================================================\n");
        while ( *(argv + c.k) ) {
            printf("%02d. argv address %p value %s\n", c.k, (argv+c.k), *(argv + c.k));
            c.k++;
        }
    }
    c.fabricate2DArrays[0] = &c.sunRiseArray[0][0];
    c.fabricate2DArrays[1] = &c.noonArray[0][0];
    c.fabricate2DArrays[2] = &c.sunSetArray[0][0];
    c.fabricate2DArrays[3] = &c.sunTemplate4Seasons[0][0];
    
    c.k=0;
/*

*/
    if (c.ptrWhatThisEventIs) { //If this has any address then do subsequent processing.
        do {
            if ( (strcmp(c.ptrWhatThisEventIs, "Summer" ) == 0) ||
                 (strcmp(c.ptrWhatThisEventIs, "Spring" ) == 0) ||
                 (strcmp(c.ptrWhatThisEventIs, "Autumn" ) == 0) ||
                 (strcmp(c.ptrWhatThisEventIs, "Fall"   ) == 0) ||
                 (strcmp(c.ptrWhatThisEventIs, "Winter" ) == 0)
                ) {
//                c.ptrPtrSome2Darray = (char *)c.sunTemplate4SEASONS[0][0];
//                c.ptrSome2Darray = *c.ptrPtrSome2Darray;
                c.some2Darray = (char *)c.sunTemplate4Seasons[0][0];
                c.some1Darray = (char *)c.sqlTemplate4Seasons;
                c.some1DArraySize = (int)strlen(c.sqlTemplate4Seasons);
                c.some2DArraySize = 1 + sizeof((char **)c.sunTemplate4Seasons);
//                c.ptrWhatThisEventIs = "Summer";
            } else if ( strcmp(c.ptrWhatThisEventIs, "NoonMin") == 0 ) {
                c.some2Darray = (char *)c.noonArray[0][0];
                c.some1Darray = (char *)c.ptrSQLTemplateNOON;
                c.some1DArraySize = (int)strlen(c.ptrSQLTemplateNOON);
                c.some2DArraySize = 1 + sizeof((char **)c.noonArray);
//                c.ptrWhatThisEventIs = "NoonMin";
                
            } else if ( strcmp(c.ptrWhatThisEventIs, "SR") == 0 ) {
                
                c.some2Darray = (char *)c.sunRiseArray[0][0];
                c.some1Darray = (char *)c.ptrSQLTemplateSR;
                c.some1DArraySize = (int)strlen(c.ptrSQLTemplateSR);
                c.some2DArraySize = sizeof((char **)c.sunRiseArray);
 //               c.ptrWhatThisEventIs = "SR";
                
            } else if (strcmp(c.ptrWhatThisEventIs, "SS") == 0) {
                c.some2Darray = (char *)c.sunSetArray[0][0];
                c.some1Darray = (char *)c.ptrSQLTemplateSS;
                c.some1DArraySize = (int)strlen(c.ptrSQLTemplateSS);
                c.some2DArraySize = 1 + sizeof((char **)c.sunSetArray);
 //               c.ptrWhatThisEventIs = "SS";
                
            } else {
                printf ("Event entered via command line, %s, does not match any of: \"Noon\", \"NoonMin\", \"SR\", \"SunRise\", \"SS\", \
                        or \"SunSet\"\n", c.ptrWhatThisEventIs);
            }
            
            //   const char ***f2d = fabricate2DArrays[0]; // Mon Dieu, triple indirection!!
            
  /*
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
 //           timings *ptrPerformanceBuffer = NULL;
            
            //        some2Darray = (char **)(f2d + k);
            c.numberOf2Dentries = 1 + c.some2DArraySize;
            
            
            c.outBufSize = (c.some1DArraySize>>1) + c.some1DArraySize; //Make outBufSize 50% larger than the size of the SQL template.
            c.cbb_results = (char *)calloc(c.outBufSize, 1);    //Now allocate a buffer whose size is specified by c.outBufSize
            c.pbSize = sizeof(*ptrPerformanceBuffer);
            ptrPerformanceBuffer = (timings *)calloc(c.pbSize, 1);
            
// /////////////////////////////////////////// Start of `do-while` Loop ////////////////////////////////////////////////////////////
            if (c.db3) {
//               printf ("04.%d ========> about to call fabricateSQL with db4 set to %d\n This of sunRiseArray is %d \
//                       bytes, or %d Token/Replacement pairs\n", c.k, c.db4, c.sizeOf_sunRiseArray, c.sizeOf_sunRiseArray>>4);
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /*            for (c.i=0; c.i <  c.numberOf2Dentries; c.i++) {
                    c.ppLeft0 = (char **)c.sunTemplate4Seasons[c.i][0];
                    c.ppLeft  = c.ptrSome2Darray[c.i][0];
                    c.pLeft = *c.ppLeft;
                    c.ppRight0 = (char **)c.sunTemplate4Seasons[c.i][1];
                    c.ppRight = (char **)c.ptrSome2Darray[c.i][1];
                    c.pRight = *c.ppRight;
                    printf("%02d. For event %s, some2Darray[%d][0]: %s\t\tsome2Darray[%d][1]: %s\n",c.i, c.ptrWhatThisEventIs, c.i, *c.ppLeft0, c.i, *c.ppRight0);
                }
*/
/*                for (c.i=0; c.i < 10; c.i++) {
                    printf("%02d. For event %s, *(anotherSunRiseArray + %d)->token: %s\t\t\
                           (char *)*(anotherSunRiseArray + %d)->replacement: %s\n", \
                           c.i, \
                           c.ptrWhatThisEventIs, \
                           c.i, \
                           (c.ptr_anotherSunRiseArray + c.i)->token,   \
                           c.i, \
                           (char *)*(c.ptr_anotherSunRiseArray + c.i)->replacement);  //NOTE the `(char *)*` type coersion/casting \
                    What doesn't work: \
                    (char **)(anotherSunRiseArray + i)->replacement), or \
                    **(anotherSunRiseArray + i)->replacement), or \
                    (char)**(anotherSunRiseArray + i)->replacement)
                }
 */
            }
/* /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
//            fabricateSQLr3(ptrPerformanceBuffer, c.some2Darray, c.some1Darray, c.numberOf2Dentries, c.cbb_results, &c.outBufSize, false);
void        fabricateSQLr3(timings *,             const char **,               const char *,    int t,              char *,        size_t *,     bool);
            fabricateSQLr3(ptrPerformanceBuffer, (const char **)c.some2Darray, c.some1Darray, c.numberOf2Dentries, c.cbb_results, &c.outBufSize, true);
/* /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
            if (c.db3) printf("05.%d =======> Returned from fabricateSQL\n", c.k);
            if (c.db3) printf("06.%d Call-back buffer, cbb, looks like:\n", c.k);
            printf  ("07.%d %s\n", c.k, c.cbb_results);
            c.oprc=fputs( c.cbb_results,  c.fp); //Number of bytes written is found in c.oprc.
            printf("outBufSize is %zu, strlen(cbb_results) is %lu, ∆ is %lu\n", c.outBufSize, strlen(c.cbb_results), c.outBufSize - strlen(c.cbb_results));
            c.charactersWrittenToFile += fwrite(c.cbb_results, strlen(c.cbb_results), 1, c.fp); // Output into the output file the \
            first logical record, the SQL COPY statement.
            if (c.charactersWrittenToFile>0) {
                printf("09a.%d Got a non-zero return code from fprintf of %d \n", c.k, c.charactersWrittenToFile);
            } else {
                printf("09b.%d ERROR: got a negative return code from fwrite or %d \n)", c.k, c.charactersWrittenToFile);
            }
            if (c.db3) printf("10.%d  Done =============================================================================\n", c.k);
            printf("fabricateSQL's total execution time: %lu nsec;\ntime to do constructor processing: %lu nsec;\ntime to do fabricate \
                   processing: %lu nsec;\ntime to do delete processing: %lu nsec.\n", \
                   ptrPerformanceBuffer->totalTime, \
                   ptrPerformanceBuffer->constructorTime, \
                   ptrPerformanceBuffer->fabricateTime, \
                   ptrPerformanceBuffer->deleteTime
                   );
//            if (ptrPerformanceBuffer) free(ptrPerformanceBuffer); //Do this if(ptrPerformanceBuffer) so we don't try to \
            free non-existant allocated memory
            if (c.cbb_results) {
                free(c.cbb_results); //Do this if(cbb_results) so we don't try to free memory that was never calloc'ed.
                c.cbb_results = nullptr; //Mark c.cbb_results as freed so we won't try to free it again and thus cause an abnormal \
                termination.
            }
            c.k++;
        } while (c.k < 1); //2020-11-11 Just do this once for now.
    } else {
        c.cbb_results = (char *)calloc(2000, 1); //Gather sufficient storage for the buffer containing fabricated SQL;
        // Right here we need to: \
        //    •connect to the database
        
        strcat (c.ptr_connectionString, "dbname=");
        strcat (c.ptr_connectionString, c.dbc->dbname);
        strcat (c.ptr_connectionString, " user=");
        strcat (c.ptr_connectionString, c.dbc->userId);
        strcat (c.ptr_connectionString, " port=");
        strcat (c.ptr_connectionString, c.dbc->portId);
        strcat (c.ptr_connectionString, " host=");
        strcat (c.ptr_connectionString, c.dbc->hostName);
        
//        connectToDatabase(c.dbc);
//        connectToDatabase(c.dbc); //Use standard: dbname [LocalWeather]; port [5436]; user name [cjc]; \
        host [localhost]; password [as taken from ~/.pgpass. Return pointer to PostgreSQL's connection structure of type PGconn, named \
        pgc.
        //     •execute the SQL we created in cbb_results

//        res = PQexec(pgc, cbb_results);
        //        •use gsl interpolation routines to covert the SQL output into a row of data that satisfies our event \
        (e.g., SunRise, SunSet, NoonMin, Spring, Summer, ERA, etc., etc.) \
        •Create an INSERT INTO … to get our iterpolated datat into the database. \
        •close the database connection \
        •cleanup \
        •exit. \
        These should be done as separate operations, possibly in c++ (TBR).
//        PQfinish(pgc);
//        free(c.cbb_results);//moved to destructor
    }
//    free(c.dbc);           //Moved to destructor
//    c.rc = fclose(c.fp);   //Moved to destructor
    if (ptrPerformanceBuffer) {
        free(ptrPerformanceBuffer);
        ptrPerformanceBuffer = nullptr;
    }
    return (int)c.rc;
}

 Constants::Constants(void) { 
    ; //Constructor
     std::cout << "Entered Constants constructor " << std::endl;
     ptr_connectionString = connectionString;
}
 Constants::~Constants(void) {
    ; //Destructors
    std::cout << "Entered Constants destructor " << std::endl;
     if (cbb_results) {
         free(cbb_results);
         cbb_results = nullptr;
     }
     if (dbc) {
         free(dbc);
         dbc = nullptr;
    }
    if(fp) {
         rc = fclose(fp);
         fp = nullptr;
    }
}

