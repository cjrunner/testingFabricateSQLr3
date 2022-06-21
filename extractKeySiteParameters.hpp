//
//  extractKeySiteParameters.hpp
//  testingFabricateSQL3r3
//
//  Created by Clifford Campo on 11/23/20.
//  Copyright © 2020 CliffordCampo. All rights reserved.
//

#ifndef extractKeySiteParameters_hpp
#define extractKeySiteParameters_hpp
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <getopt.h>
#include <iostream>
#include <databaseOps.h>  //NOTE: "/usr/local/include/databaseOps" Needs to be in System Header Search path rather \
than User Header Search Path
// #include "testingFabricateSQL3.hpp"
#include <fabricateSQLr3.h> //timings structure is found here. 
//#include <fabricateSQLr3.hpp>
typedef struct timings {
    unsigned long constructorTime;  //Time for fabricateSQLr3's time to execute the constructor
    unsigned long fabricateTime;    //Time for fabricateSQLr3's time to execute the fabrication of the SQL
    unsigned long deleteTime;       //Time for fabricateSQLr3's time to execute the destructor
    unsigned long totalTime;        //Total execution time; is the sum of the above three times.
} timings;
typedef struct {
    char **fa;
    char *myTemplate;
    unsigned int  templateSize;
    unsigned int  numberOfTokenReplacementPairs;
} fabstruct;
typedef struct sqlArray {
    char *psql;
    unsigned long ulsql;
} sqlArray;
typedef struct {
    const char *token;
    const char **replacement;
} arrayEntry;
class Constants {
private:
public:
    char *Year;
    int opField  = -1;
    int opsrd    = -2;
    int opssd    = -3;
    int opbdp    = -4;
    int opadp    = -5;
    int ophelp   = -6;
    int opfile   = -7;
    int optsid   = -8;
    int opevnt   = -9;
    int op1      = -10;
    int op2      = -11;
    int op3      = -12;
    int op4      = -13;
    int opsd     = -14;
    int opYear   = -15;
    int oprc=0;
    int optionIndex;
    char *name;
    int val;
    int flag;
    int has_arg;
    int j=1;
    int i=0;
    int k=0;
    int db1=0;
    int db2=0;
    int db3=0;
    bool db4=false;
    FILE *fp;
    const char *ptrSS = "SS";
    const char *outputFileName = "/Users/cjc/sql/testingFabricateSQL3.sql";
    const char *theArguments = "S:D:b:a:F:E:r:s:1234hf:Y:";
    char theSiteID[3] = {'0'}; //Max of 2 characters
    const char *ptrToSiteID = theSiteID;
    const char theDate[12] = {'0'}; //The date we're looking for in YYYY-MM-DD Format: 10 characters + 0x'00' c-string terminator character
    const char *ptrToDate = &theDate[0];
    char **ppLeft, **ppRight, **ppLeft0, **ppRight0;
    char *pLeft, *pRight;
/* ==W A R N I N G======W A R N I N G=======W A R N I N G===========W I L L    R O B I N S O N==================================== \
Through much trial and error, I discovered that the order of the targets of these pointers MUST be in the same order as appearying \
in the 2Dimentional arrays of pointers to pointers!! THIS IS FUCKING CRITICAL!!!!!! I wasted days and days tracking down this \
problem!!!!!!!!!!! ptrThisSRDef shall appear first, followed by ptrWhatThisSunRiseDefIs, followed by ptrThisPreamble, ... ending \
with ptrWhatThisTermIs. Failure to observe this ordering will result in BAD THINGS HAPPENING: like encountering TERM, which ends \
fabricateSQLr3.dylib processing, prior to having processed all Token/Replacement pairs. */
    
    //const char *ptrThisSRDef = "SRD";
    //const char *ptrWhatThisSunRiseDefIs = "90.58333332";
    
    const char *ptrThisDef = "ZDDEF";  //If doing season processing then change "ZDEAF" to "SEASON"
    const char *ptrWhatThisDefIs  = "90.58333333";  //Default zenithdefinition defining sunrise or sunset
    const char *ptrThisPreamble = "PREAMBLE";
    const char *ptrWhatThisPreambleIs = "BEGIN; DECLARE srnoonssportal CURSOR FOR ";  //Default Preamble
    const char *ptrThisSiteid = "SITEID";
    const char *ptrWhatThisSiteIdIs = "0";   //Default Siteid is 0 [KPAPAOLI10]  which is found on port5436 of the LocalWeather \
    database in table tbl_site_names.
    const char *ptrThisSomeDate = "SOMEDATE"; //Dates are of the format YYYY-MM-DD as per ISO 8601.
    const char *ptrWhatThisSomeDateIs = ""; //Default Date [i.e., no default date]
    const char *ptrThisBeforeDataPoints = "BEFOREDATAPOINTS";
    const char *ptrWhatThisBeforeDataPointsIs = "4";
    const char *ptrThisAfterDataPoints = "AFTERDATAPOINTS";
    const char *ptrWhatThisAfterDataPointsIs = "4"; //Default: the same as the value associated with before data points
    const char *ptrThisEvent = "SRorSS";
    const char *ptrWhatThisEventIs = "";
    const char *ptrThisField = "FIELD";
    const char *ptrWhatThisFieldIs = "zenithdistance"; // = "zenithdistance"; //Default Field but can also be \
    geocentricra, topocentricra, era, last, or gast as of this time [2022-06-11T09:16:58]
    const char *ptrThisPostamble = "POSTAMBLE";
    const char *ptrWhatThisPostambleIs = " FETCH ALL srnoonssportal; CLOSE srnoonssportal; END;";
    const char *ptrThisSomeYear = "YEAR";
    const char *ptrWhatThisSomeYearIs = "2021";
    const char *ptrWhatThisGeocentricraSeasonIs = "6";  //Default to 6 => Summer
    // MAKE SURE TERM appears LAST in the 2D array before we go off and declare/define 2 dimensional (2D) arrays of \
    pointers to pointers to characters.
    const char *ptrThisTerm = "TERM";
    const char *ptrWhatThisTermIs = "TERM";
    // =============================================================================================================================
    //siteid |  sitename  | latitude | longitude | altitude |  hostid   | portid | timezone | solarradiation
    //-------+------------+----------+-----------+----------+-----------+--------+----------+----------------
    //0      | KPAPAOLI10 |  40.0461 |    -75.48 |      504 | localhost | 5436   |       -5 | t
    
    const char *getSiteParameters = "SELECT siteid, sitename, latitude, longitude, altitude, hostid, portid, timezone, solarradiation FROM tbl_site_names WHERE siteid=";
    // =============================================================================================================================
    // 4SEASONS    4SEASONS    4SEASONS    4SEASONS    4SEASONS    4SEASONS    4SEASONS    4SEASONS    4SEASONS    4SEASONS    4SEASONS
    const char *ptrEndCap;
 //   const char *ptrThisSomeYear = "YEAR";
//    const char *ptrWhatThisSomeYearIs ="date_part('Year', now())"; //Defaults to current year.
// NOT USED    const char *ptrThisSeason = "SEASON";
    const char *ptrWhatThisSeasonIs = "?"; // "0" => Spring, "6" => Summer, "12" => Autumn/Fall, "18" => Winter
    //2022-06-08T12:55:29 this version worked when plugged into psql
    const char *sqlTemplate4Seasons = "PREAMBLE SELECT *, date_part('Hour', lt) FROM tbl_sun_loc_site WHERE id \
    BETWEEN \
    - BEFOREDATAPOINTS + \
    (SELECT id FROM tbl_sun_loc_site WHERE events IS NULL AND siteid = SITEID AND abs(FIELD - ZDDEF) = \
    (SELECT  min(abs(FIELD - ZDDEF))  FROM tbl_sun_loc_site WHERE events IS NULL AND siteid=SITEID AND \
    date_part('Year',lt) = YEAR ) AND events IS NULL) \
    AND \
    + AFTERDATAPOINTS + \
    (SELECT id FROM tbl_sun_loc_site WHERE events is NULL AND siteid = SITEID AND abs(FIELD - ZDDEF) = \
    (SELECT  min(abs(FIELD - ZDDEF))  FROM tbl_sun_loc_site WHERE events IS NULL AND siteid=SITEID AND \
    date_part('Year',lt) = YEAR ) AND events IS NULL) \
    AND events IS NULL ORDER BY jdlocal ASC;POSTAMBLE";

    const char **sunTemplate4Seasons[9][2] = {                       /* 9 rows of 2 columns per row */   \
        {&ptrThisDef,              &ptrWhatThisGeocentricraSeasonIs},  /* [0][0] [0][1] */   \
        {&ptrThisPreamble,         &ptrWhatThisPreambleIs},            /* [1][0] [1][1] */   \
        {&ptrThisSiteid,           &ptrWhatThisSiteIdIs},              /* [2][0] [2][1] */   \
        {&ptrThisSomeYear,         &ptrWhatThisSomeYearIs},            /* [2][0] [2][1] */   \
        {&ptrThisBeforeDataPoints, &ptrWhatThisBeforeDataPointsIs},    /* [4][0] [4][1] */   \
        {&ptrThisAfterDataPoints,  &ptrWhatThisAfterDataPointsIs},     /* [5][0] [5][1] */   \
        {&ptrThisField,            &ptrWhatThisFieldIs},               /* [6][0] [6][1] */   \
        {&ptrThisPostamble,        &ptrWhatThisPostambleIs},           /* [7][0] [7][1] */   \
        {&ptrThisTerm,             &ptrWhatThisTermIs}};               /* [8][0] [8][1] */
// 4SEASONS    4SEASONS    4SEASONS    4SEASONS    4SEASONS    4SEASONS    4SEASONS    4SEASONS    4SEASONS    4SEASONS    4SEASONS

    
    
    
    // =============================================================================================================================
    const char *sqlTemplateSS = "PREAMBLE SELECT * FROM tbl_sun_loc_site \
    WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND id BETWEEN \
    -BEFOREDATAPOINTS + ( SELECT id FROM (SELECT *,abs(FIELD - ZDDEF) \
    FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS (SELECT avg(id) FROM tbl_sun_loc_site \
    WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL)) a WHERE abs(FIELD - ZDDEF) = \
    (SELECT min(abs(FIELD - ZDDEF)) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS \
    (SELECT avg(id) FROM tbl_sun_loc_site where lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL))  ) \
    AND     \
    +AFTERDATAPOINTS + ( SELECT id FROM (SELECT *,abs(FIELD - ZDDEF) \
    FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS (SELECT avg(id) FROM tbl_sun_loc_site \
    WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL)) a WHERE abs(FIELD - ZDDEF) = \
    (SELECT min(abs(FIELD - ZDDEF)) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS \
    (SELECT avg(id) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL))   ) \
    ORDER BY id; POSTAMBLE\n";
    //Define a 2-dimensional array of pointers to characters used to construct the above SQL for determining sun set
    const char **sunSetArray[10][2] = {   \
        {&ptrThisDef,              &ptrWhatThisDefIs},    \
        {&ptrThisPreamble,         &ptrWhatThisPreambleIs},     \
        {&ptrThisSiteid,           &ptrWhatThisSiteIdIs},       \
        {&ptrThisSomeDate,         &ptrWhatThisSomeDateIs},   \
        {&ptrThisBeforeDataPoints, &ptrWhatThisBeforeDataPointsIs}, \
        {&ptrThisAfterDataPoints,  &ptrWhatThisAfterDataPointsIs},  \
        {&ptrThisEvent,            &ptrSS}, \
        {&ptrThisField,            &ptrWhatThisFieldIs}, \
        {&ptrThisPostamble,        &ptrWhatThisPostambleIs}, \
        {&ptrThisTerm,             &ptrWhatThisTermIs}};
    unsigned long sizeOfTemplateSS = sizeof(sqlTemplateSS); //Get the number of characters, including the string-terminating '\0' character.
    const char *ptrSQLTemplateSS = &sqlTemplateSS[0];
    const char *sqlTemplateNOON =
    "PREAMBLE\nSELECT * FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id BETWEEN \n\
    -BEFOREDATAPOINTS + (SELECT id FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND FIELD = \
    (SELECT min(FIELD) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL) ) \n \
    AND \n \
    +AFTERDATAPOINTS + (SELECT id FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND FIELD = \
    (SELECT min(FIELD) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL) ) ORDER BY id; POSTAMBLE\n";
    //From the above sqlTemplateNOON[], note how the SQL comments need to be bracketed between `\n` characters to delineate the \
    sql comment from the REAL SQL
    unsigned long sizeOfTemplateNOON = sizeof(sqlTemplateNOON); //Get the number of characters, including the string-terminating '\0' character.
    const char *ptrSQLTemplateNOON = &sqlTemplateNOON[0];
    //Define a 2-dimensional array of pointers to characters used to construct the above SQL for determining sun set
    const char **noonArray[8][2] = { \
        {&ptrThisPreamble,         &ptrWhatThisPreambleIs},  \
        {&ptrThisSiteid,           &ptrWhatThisSiteIdIs},      \
        {&ptrThisSomeDate,         &ptrWhatThisSomeDateIs},  \
        {&ptrThisField,            &ptrWhatThisFieldIs}, \
        {&ptrThisBeforeDataPoints, &ptrWhatThisBeforeDataPointsIs},  \
        {&ptrThisAfterDataPoints,  &ptrWhatThisAfterDataPointsIs},     \
        {&ptrThisPostamble,        &ptrWhatThisPostambleIs},  \
        {&ptrThisTerm,             &ptrWhatThisTermIs}};
    
    const char *sqlTemplateSR = "PREAMBLE\nSELECT * FROM tbl_sun_loc_site \
    WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND id BETWEEN \n \
    -BEFOREDATAPOINTS + ( SELECT id FROM (SELECT *,abs(FIELD-ZDDEF) \
    FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS (SELECT avg(id) FROM tbl_sun_loc_site \
    WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL)) a WHERE abs(FIELD - ZDDEF) = \
    (SELECT min(abs(FIELD - ZDDEF)) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS \
    (SELECT avg(id) FROM tbl_sun_loc_site where lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL))  ) \n \
    AND \n \
    +AFTERDATAPOINTS + ( SELECT id FROM (SELECT *,abs(FIELD - ZDDEF) \
    FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS (SELECT avg(id) FROM tbl_sun_loc_site \
    WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL)) a WHERE abs(FIELD - ZDDEF) = \
    (SELECT min(abs(FIELD - ZDDEF)) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS \
    (SELECT avg(id) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL))   ) \
    ORDER BY id; POSTAMBLE\n";
    unsigned long sizeOfTemplateSR = sizeof(*sqlTemplateSR); //Get the number of characters, including the string-terminating '\0' character.
    const char *ptrSQLTemplateSR = sqlTemplateSR;
    const char **sunRiseArray[10][2] = {  /* The order of the targets of thse pointers MUST be in the same order as appearying \
here!! THIS IS CRITICAL!!!!!! I wasted days tracking down this problem!!!!!!!!!!! ptrThisZDDEFef shall appear first, followed by \
ptrWhatThisSunRiseDefIs, followed by ptrThisPreamble, ... ending with ptrWhatThisTermIs. Failure to observe this ordering will \
result in BAD THINGS HAPPENING: like encountering TERM, which ends fabricateSQLr3.dylib processing, prior to having processed \
all Token/Replacement pairs. */ \
        {&ptrThisDef, &ptrWhatThisDefIs}, \
        {&ptrThisPreamble,&ptrWhatThisPreambleIs}, \
        {&ptrThisSiteid,&ptrWhatThisSiteIdIs}, \
        {&ptrThisSomeDate,&ptrWhatThisSomeDateIs}, \
        {&ptrThisBeforeDataPoints, &ptrWhatThisBeforeDataPointsIs}, \
        {&ptrThisAfterDataPoints,&ptrWhatThisAfterDataPointsIs}, \
        {&ptrThisEvent, &ptrWhatThisEventIs}, \
        {&ptrThisField,&ptrWhatThisFieldIs}, \
        {&ptrThisPostamble, &ptrWhatThisPostambleIs}, \
        {&ptrThisTerm, &ptrWhatThisTermIs} \
    }; //
    int sizeOf_sunRiseArray = sizeof(sunRiseArray);
    const char ***sra = &sunRiseArray[0][0];
    int   numberOfPairs[4] = {10, 8, 10, 9};
    const char  ***fabricate2DArrays[5] = { \
        &sunRiseArray[0][0], \
        &noonArray[0][0],    \
        &sunSetArray[0][0],  \
        &sunTemplate4Seasons[0][0], \
        0}; //Used by test program to loop through the three, 2-dimensional, arrays that will be handed-off to fabricateSQLr3.dylib \
    for testing this dylib.
    
    //fabstruct ptr_fs = fs[0];
    
    const char ***fourArrays[4] = {&sunRiseArray[0][0],  &noonArray[0][0], &sunSetArray[0][0], &sunTemplate4Seasons[0][0]};
    arrayEntry anotherSunRiseArray[10] = { \
        {"PREAMBLE",         &ptrWhatThisPreambleIs}, \
        {"ZDDEF",            &ptrWhatThisDefIs}, \
        {"SITEID",           &ptrWhatThisSiteIdIs}, \
        {"DATE",             &ptrWhatThisSomeDateIs}, \
        {"BEFOREDATAPOINTS", &ptrWhatThisBeforeDataPointsIs}, \
        {"AFTERDATAPOINTS",  &ptrWhatThisAfterDataPointsIs}, \
        {"SRorSS",           &ptrWhatThisEventIs}, \
        {"FIELD",            &ptrWhatThisFieldIs}, \
        {"POSTAMBLE",        &ptrWhatThisPostambleIs}, \
        {"TERM",             &ptrWhatThisTermIs}};
    arrayEntry *ptr_anotherSunRiseArray = &anotherSunRiseArray[0];
    /*
    struct option long_options[15] = {
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
        {"siteid",            required_argument, &optsid,  'S'},  //01 Default is 0 [see LocalWeather database, table tbl_site_names \
        for a list of possible sitenames]. This test program may read from this table]
        {"somedate",          required_argument, &opsd,    'D'},  //02 Enterning a date is mandatory;
        {"beforedatapoints",  optional_argument, &opbdp,   'b'},  //03 Default = 4
        {"afterdatapoints",   optional_argument, &opadp,   'a'},  //04 Default = 4
        {"field",             optional_argument, &opField, 'F'},  //05 Default value is zenithdistance and is associated with \
        SunRise and SunSet. Other values are ERA (Earth Rotation Angle), last (local astronomical sideral time), and gast \
        (geocentric astronomical sideral time). Other values (e.g. Spring (when geocentric right ascension = 0º or 0 hours) \
        to be defined later.
        {"event",             required_argument, &opevnt,  'E'},  //06 Typical values are SR (i.e., Sunrise),  SS (i.e., SunSet), \
        and N (Noon)
        {"sunrisedefinition", optional_argument, &opsrd,   'r'},  //07 Default value is 90.58333333º
        {"sunsetdefinition",  optional_argument, &opssd,   's'},  //08 Default value is 90.58333333º
        {"db1",               no_argument,       &op1,     '1'},  //09 Debug Level 1: Debug early intermediate values of \
        testingFabricateSQLr3
        {"db2",               no_argument,       &op2,     '2'},  //10 Debug Level 2: Debug the parameter substitution, \
        from values obtained from the command line, into the 2D arrays, known as sunSetArray, sunRiseArray, and noonArray, \
        which contain the Token/Replacement pairs driving the processing of the fabricateSQLr3.dylib.
        {"db3",               no_argument,       &op3,     '3'},  //11 Debug Level 3: View development of parameters that are \
        sent to the fabricateSQLr3.dylib.
        {"db4",               no_argument,       &op4,     '4'},  //12 Debug Level 4: debug fabricateSQL4.dylib itself.
        {"help",              no_argument,       &ophelp,  'h'},  //13 Outputs a help message and then quits.
        {"file",              optional_argument, &opfile,  'f'},  //14 Alternative name of the output file holding the SQL produced \
        by fabricateSQLr3. Default name of this file is
        {0, 0, 0, 0}                                              //15 End of array indicator.
    };
    */
    char connectionString[48]={'\0'};
    char *ptr_connectionString;
    Dbc *dbc;  //Dbc is defined in include file /usr/local/include/databaseOps/databaseOps.h
    size_t rc = 0;
    char *cbb_results = nullptr;
    int pbSize = 0;
    int argc;
    char **argv;
    char **env;
    char **somethingElse;
    unsigned int numberOf2Dentries = 0;
    size_t outBufSize=0;
    int charactersWrittenToFile = 0;
    char **ptrPtrSome2Darray = nullptr;
    char *ptrSome2Darray = nullptr;
    char *some2Darray=NULL;
    char *some1Darray=NULL;
    int some2DArraySize=0;
    int some1DArraySize=0;
    

    Constants(void);   //Constructor signature
    ~Constants(void);  //Destructor signature
};

#endif /* extractKeySiteParameters_hpp */
