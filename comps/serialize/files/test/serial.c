
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "boz/serialize.h"
#include "binn/binn.h"

#define DIE(fmt, ...)                        \
    fprintf(stderr, fmt "\n", ##__VA_ARGS__);     \
    exit(EXIT_FAILURE);             

#define DATA_LG    (64)

static const char* cmd_name= "test_send";
static char inner_data[DATA_LG];
static char *outer_data=0;

///////////////////////////////////////////////////////////////////////////////
int main(int ac, char** av) {
    (void)ac;
    (void)av;

    char* str=0;
    char* p=0;
    
    srand(time(0));
    
    for(int i=0; i<DATA_LG; i++)
        inner_data[i]=rand();
       
    str=boz_serialize(BOZ_SERIALIZE_SEND, cmd_name, inner_data, DATA_LG);
    if(!str) {
        DIE("command not serialized");
    }
    
    fprintf(stderr, "serialized data (%s)\n", str);
    
    outer_data=strdup(str);
    free(str);
    
    boz_serialize_type_t out_type=boz_unserialize_get_type(outer_data);
    if(out_type!=BOZ_SERIALIZE_SEND) {
        DIE("Bad command type retreived");
    }
    
    p=boz_unserialize_get_name(outer_data);
    if(!p) {
        DIE("No command name retreived");
    }
    else if(!strcmp(p, cmd_name)) {
        DIE("Bad command name retreived");
    }
    
    p=boz_unserialize_get_data(outer_data);
    if(!p) {
        DIE("No command data retreived");
    }
    
    // fprintf(stderr, "retreived data (%s)\n", p);
    for(int i=0; i<DATA_LG; i++) {
        if(p[i]!=inner_data[i]) {
            DIE("Bad command data found, index (%d), expected (%02x), current (%02x)", i, inner_data[i], p[i]);
        }
    }
    
    fprintf(stderr, "All succeded\n");
    
    free(outer_data);
    binn_term();
    return 0;
}
