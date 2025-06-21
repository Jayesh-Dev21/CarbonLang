#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "transpiler.h"

typedef enum{
    true, false
} bool;

char* trim_leading_whitespace(char *str) {
    while(*str == ' ' || *str == '\t') str++;
    return str;
}

static bool if_condition = false;
static bool else_if_condition = false;


void line_parser(char *line, FILE *fp){
    
    // Handleing Print Statements
    if(strncmp(line, "println!", 8) == 0){
        char* content = strchr(line, '"') + 1;
        int len = strlen(content);
        printf("%.*s\n", (int)(len - 2), content);
    } 
    
    else if(strncmp(line, "printn!", 7) == 0){
        char* content = strchr(line, '"') + 1;
        int len = strlen(content);
        printf("%.*s", (int)(len - 2), content);

    }

    else if(strncmp(line, "var_c", 5) == 0){
        initialize_variable(line);
    }

    else if(strncmp(line, "if ", 2) == 0){
        char a[50], b[50], condition[10];
        sscanf(line, "if %s %s %s {", a, condition, b);
        
        Variable *a_var = var_convert(a);
        Variable *b_var = var_convert(b);
        

        if (!a_var || !b_var) {
            printf("Error: Undefined variable(s).\n");
            return;
        }

        if(a_var->type != b_var->type) {
            printf("Error: Type mismatch between variables %s and %s.\n", a_var->name, b_var->name);
            return;
        }

        bool result = false;

        if (a_var->type == VAR_LONG) {
            long long val_a = a_var->value.i;
            long long val_b = b_var->value.i;

            if (strcmp(condition, "==") == 0) result = (val_a == val_b);
            else if (strcmp(condition, "!=") == 0) result = (val_a != val_b);
            else if (strcmp(condition, ">") == 0) result = (val_a > val_b);
            else if (strcmp(condition, "<") == 0) result = (val_a < val_b);
            else if (strcmp(condition, ">=") == 0) result = (val_a >= val_b);
            else if (strcmp(condition, "<=") == 0) result = (val_a <= val_b);
        }

        else if (a_var->type == VAR_DOUBLE) {
            double val_a = a_var->value.f;
            double val_b = b_var->value.f;
            
            if (strcmp(condition, "==") == 0) result = (val_a == val_b);
            else if (strcmp(condition, "!=") == 0) result = (val_a != val_b);
            else if (strcmp(condition, ">") == 0) result = (val_a > val_b);
            else if (strcmp(condition, "<") == 0) result = (val_a < val_b);
            else if (strcmp(condition, ">=") == 0) result = (val_a >= val_b);
            else if (strcmp(condition, "<=") == 0) result = (val_a <= val_b);
        }

        else if (a_var->type == VAR_CHAR) {
            char val_a = a_var->value.c;
            char val_b = b_var->value.c;
            if (strcmp(condition, "==") == 0) result = (val_a == val_b);
            else if (strcmp(condition, "!=") == 0) result = (val_a != val_b);
        }

        if(result){
            char block_line[256];
            while (fgets(block_line, sizeof(block_line), fp)) {
                if (block_line[0] == '}') break;
                char *inner_line = trim_leading_whitespace(block_line);
                if (inner_line[0] != '}') {
                    line_parser(inner_line, fp);
                }
            }
            if_condition = true;  
        } 
        else{
            char skip_line[256];
            int brace = 1;
            while (fgets(skip_line, sizeof(skip_line), fp)) {
                if (strchr(skip_line, '{')) brace++;
                if (strchr(skip_line, '}')) brace--;
                if (brace == 0) break;
            }
        }
    }
    
    else if(strncmp(line, "else if ", 7) == 0){
        
        char a[50], b[50], condition[10];
        sscanf(line, "else if %s %s %s {", a, condition, b);
        
        Variable *a_var = var_convert(a);
        Variable *b_var = var_convert(b);
        

        if (!a_var || !b_var) {
            printf("Error: Undefined variable(s).\n");
            return;
        }

        if(a_var->type != b_var->type) {
            printf("Error: Type mismatch between variables %s and %s.\n", a_var->name, b_var->name);
            return;
        }

        bool result = false;

        if(!if_condition){
            if (a_var->type == VAR_LONG) {
                long long val_a = a_var->value.i;
                long long val_b = b_var->value.i;

                if (strcmp(condition, "==") == 0) result = (val_a == val_b);
                else if (strcmp(condition, "!=") == 0) result = (val_a != val_b);
                else if (strcmp(condition, ">") == 0) result = (val_a > val_b);
                else if (strcmp(condition, "<") == 0) result = (val_a < val_b);
                else if (strcmp(condition, ">=") == 0) result = (val_a >= val_b);
                else if (strcmp(condition, "<=") == 0) result = (val_a <= val_b);
            }

            else if (a_var->type == VAR_DOUBLE) {
                double val_a = a_var->value.f;
                double val_b = b_var->value.f;
                
                if (strcmp(condition, "==") == 0) result = (val_a == val_b);
                else if (strcmp(condition, "!=") == 0) result = (val_a != val_b);
                else if (strcmp(condition, ">") == 0) result = (val_a > val_b);
                else if (strcmp(condition, "<") == 0) result = (val_a < val_b);
                else if (strcmp(condition, ">=") == 0) result = (val_a >= val_b);
                else if (strcmp(condition, "<=") == 0) result = (val_a <= val_b);
            }

            else if (a_var->type == VAR_CHAR) {
                char val_a = a_var->value.c;
                char val_b = b_var->value.c;
                if (strcmp(condition, "==") == 0) result = (val_a == val_b);
                else if (strcmp(condition, "!=") == 0) result = (val_a != val_b);
            }
        }
        if(result){
            char block_line[256];
            while (fgets(block_line, sizeof(block_line), fp)) {
                if (block_line[0] == '}') break;
                char *inner_line = trim_leading_whitespace(block_line);
                if (inner_line[0] != '}') {
                    line_parser(inner_line, fp);
                }
            }
            else_if_condition = true;
        } 
        else{
            char skip_line[256];
            int brace = 1;
            while (fgets(skip_line, sizeof(skip_line), fp)){
                if (strchr(skip_line, '{')) brace++;
                if (strchr(skip_line, '}')) brace--;
                if (brace == 0) break;
            }
        }
    }

    else if(strncmp(line, "else ", 4) == 0){
        if(!if_condition && !else_if_condition){
            char block_line[256];
            while (fgets(block_line, sizeof(block_line), fp)) {
                if (block_line[0] == '}') break;
                char *inner_line = trim_leading_whitespace(block_line);
                if (inner_line[0] != '}') {
                    line_parser(inner_line, fp);
                }
            }
        }
        else{
            char skip_line[256];
            int brace = 1;
            while (fgets(skip_line, sizeof(skip_line), fp)){
                if (strchr(skip_line, '{')) brace++;
                if (strchr(skip_line, '}')) brace--;
                if (brace == 0) break;
            }
        }
    }

    else if(strncmp(line, "\n", 1) == 0){return;}
    
    else{
        printf("Synatx Not Recoganized \"%s\"", line);
    }
}