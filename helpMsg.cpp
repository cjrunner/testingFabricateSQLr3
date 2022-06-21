//
//  helpMsg.cpp
//  testingFabricateSQL3r3
//
//  Created by Clifford Campo on 2/18/21.
//  Copyright © 2021 CliffordCampo. All rights reserved.
//

#include "helpMsg.hpp"

void helpMsg(char **p) {
    printf("The purpose of this program, named %s,\n", *p);
    printf("is to drive the testing of the dylib named fabricateSQLr3. The parameters driving this test are as follows:\n");
    printf("--siteid or -S: defines the siteid as defined in database LocalWeather, on any working port, \
           table named tbl_site_names [Default 0]\n");
    printf("--somedate or -D: defines the date of interest. MANDATORY. Must be in YYYY-MM-DD format\n");
    printf("--beforedatapoints or -b: defines the number of tuples (rows) prior to the data of interest [Default 4]\n");
    printf("--afterdatapoints or -a: defines the number of tuples (rows) aftr the data of interest [Default 4]\n");
    printf("--field or -F: Specifies the field name. Field names are as described by LocalWeather database's table, \
           named tbl_sun_loc_site. Most fields (table columns) are of double precision data type. [Default: zenithdistance]\n");
    printf("--event or -E: Specifies the event for which fabricateSQLr3 will create SQL to extract the data from tbl_sun_loc_site \
           to characterize the event of interest. Typical events are SunRise (specified by -E SR), SunSet (specified by -E SS), noon \
           (specified by -E NoonMin), or Earth Rotation Angle = 0 (Specified by -E ERA)\n Other events for future implementation are gast = 0 \
           (-E gast), last = 0 (-E last), arrival of Spring (-E Spring), arrival of Summer (-E Summer), arrival of Fall or Autumn (-E Fall or \
           -E Autumn), arrival of Winter (-E Winter)\n");
    printf("--Year or -Y: Year for which we desire to find the occurance of Summer, or Fall/Autumn, or Winter, or Spring. \
           Note that when Year [or -Y] is specified --somedate or -D may be ignored.\n");
    printf("--sunrisedefiningion or -r: specifies the zenithdistance when sunrise occurs. [Default: 90.58333333º]\n" );
    printf("--sunsetdefiningion or -s: specifies the zenithdistance when sunset occurs. [Default: 90.58333333º]\n");
    printf("--db1 or -1: Debug mode 1: Debug early intermediate values of testingFabricateSQLr3\n" );
    printf("--db2 or -2: Debug mode 2: Debug the parameter substitution, from values obtained \
           from the command line, into the 2D arrays, known as sunSetArray, sunRiseArray, and noonArray, which contain the \
           Token/Replacement pairs driving the processing of the fabricateSQLr3.dylib\n");
    printf("--db3 or -3: View development of parameters that are sent to the fabricateSQLr3.dylib.\n");
    printf("--db4 or -4: debug fabricateSQL4.dylib itself so this dylib displays its intermediate results as its processing \
           proceeds\n");
}
