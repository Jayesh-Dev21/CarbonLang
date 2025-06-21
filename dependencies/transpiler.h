#ifndef TRANSPILER_H
#define TRANSPILER_H

typedef enum{
    VAR_DOUBLE,
    VAR_CHAR,
    VAR_LONG
} VarType;

typedef struct {
    char name[50];
    VarType type;
    union {
        long long i;
        double f;
        char c;
    } value;
} Variable;

void initialize_variable(char *);
Variable* var_convert(const char* name);

#endif