#ifndef TESTS_H
#define TESTS_H

#include "unit_test.h"
#include "string_util.h"
#include "map.h"
#include "file_io.h"
#include "token.h"
#include "statement.h"
#include "lex.h"
#include "parser.h"
#include "ast.h"
#include "shared_values.h"
#include "semantic.h"
#include "linked_list.h"
#include "compiler.h"
#include "filepath.h"

#define MAX_TESTS 1000

Unit_Test tests[MAX_TESTS];

int num_tests;

void create_test(const char *name, int (*test_func)());
void run_tests();

int test_str_equal();
int test_str_add();
int test_atoi();
int test_itoa();
int test_str_copy();
int test_str_lt();

int test_create_map();
int test_map_add();
int test_map_rem();
int test_map_find();
int test_destroy_map();

int test_create_linked_list();
int test_add_link();
int test_remove_link();
int test_remove_last_link();
int test_destroy_linked_list();

int test_fileio_read();
int test_fileio_write();

int test_create_filepath();
int test_filepath_to_string();

int test_create_token();
int test_identify_token();

int test_create_statement();
int test_tokenize_statement();

int test_lex();

int test_parse();
int test_rhs();

int test_ast();

int test_semantic_analysis();

int test_compile();

#endif // TESTS_H
