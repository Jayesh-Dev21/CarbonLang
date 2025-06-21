#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "transpiler.h"

typedef long long int llint;


#define MAX_VARS 100

// variable manager //
Variable vars[MAX_VARS];
static int var_count = 0;


void initialize_variable(char *line){
    char temp_name[50];
    char eq_sign[2];
    char temp_value[20];

    char* endptr;

    var_count++;
    if(var_count > MAX_VARS) {
        fprintf(stderr, "Error: Maximum variable limit reached.\n");
        return;
    }

    // Parse the variable declaration line
    sscanf(line, "var_c %s %s %s", temp_name, eq_sign, temp_value);

    if (strcmp(eq_sign, "=") != 0) {
        fprintf(stderr, "Error: Invalid declaration of variable using var_c.\nSyntax not Defined\n");
        return;
    }

    Variable local_Var;
    strcpy(local_Var.name, temp_name);   
    if (strchr(temp_value, '.')) {
        local_Var.type = VAR_DOUBLE;
        local_Var.value.f = strtod(temp_value, &endptr);
    } else if (strlen(temp_value) == 3) {
        local_Var.type = VAR_CHAR;
        local_Var.value.c = temp_value[1];
    } else {
        local_Var.type = VAR_LONG;
        local_Var.value.i = strtoll(temp_value, &endptr, 10);
    }

    vars[var_count - 1] = local_Var;
}

Variable* var_convert(const char* name){
    for(int i = 0; i < var_count; i++){
        if(strcmp(vars[i].name, name) == 0){
            return &vars[i];
        }
    }
    return NULL;
}
