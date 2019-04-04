#ifndef GOTOS_H
#define GOTOS_H

#include "system.h"


/*        ____    ____  _______  __       __        ______   ____    __    ____ 
      \   \  /   / |   ____||  |     |  |      /  __  \  \   \  /  \  /   / 
       \   \/   /  |  |__   |  |     |  |     |  |  |  |  \   \/    \/   /  
        \_    _/   |   __|  |  |     |  |     |  |  |  |   \            /   
          |  |     |  |____ |  `----.|  `----.|  `--'  |    \    /\    /    
          |__|     |_______||_______||_______| \______/      \__/  \__/               */
          
const struct odometry_position yellow_table_one_starter = {0,0,0};
const struct goto_fields yellow_table_one[]             = {
    {{0,0}, 50, FORWARD, NULL,NULL}
};

const struct odometry_position yellow_table_two_starter = {0,0,0};
const struct goto_fields yellow_table_two[]             = {
    {{0,0}, 50, FORWARD, NULL,NULL}
};

/*      .______    __    __  .______      .______    __       _______ 
        |   _  \  |  |  |  | |   _  \     |   _  \  |  |     |   ____|
        |  |_)  | |  |  |  | |  |_)  |    |  |_)  | |  |     |  |__   
        |   ___/  |  |  |  | |      /     |   ___/  |  |     |   __|  
        |  |      |  `--'  | |  |\  \----.|  |      |  `----.|  |____ 
        | _|       \______/  | _| `._____|| _|      |_______||_______|  */

const struct odometry_position purple_table_one_starter = {0,0,0};
const struct goto_fields purple_table_one[]             = {
    {{0,0}, 50, FORWARD, NULL,NULL}
};

const struct odometry_position purple_table_two_starter = {0,0,0};
const struct goto_fields purple_table_two[]             = {
    {{0,0}, 50, FORWARD, NULL,NULL}
};

#endif