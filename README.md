# Carbon (Programming Language)

A simple interpreted scripting language created as part of CSOC INFOSEC.

## Overview

Carbon is a basic scripting language featuring a custom lexer and transpiler. It reads `.crb` script files, parses them line by line, and executes them via an interpreter written in C.

## Features

- Custom syntax, lexer, and transpiler
- Strict `.crb` extension check for scripts
- Simple file handling and output
- Example script included

## Directory Structure
```
.
├── carbon_run
├── .gitignore
├── Instructions.txt
├── main.c
├── Makefile
├── README.md
├── script.crb
└── src
    ├── lexer.c
    ├── lexer.h
    ├── transpiler.c
    └── transpiler.h
```

---
To run CarbonLang 
use-->
```bash
./carbon_run <filename.crb>
```

**Outpur in Terminal**

```bash
❯ ./carbon_run file.crb
Hello, Carbon
No, new line See I told you.
Text
Hi, this works Carbon is awesome
CoCo is a good girl
```
---

**Cleaning Up**

To remove the compiled executable:
```bash
make clean
```

