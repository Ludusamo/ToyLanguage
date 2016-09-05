#include "tests.h"
#include "unit_test.h"
#include "string_util.h"
#include "map.h"
#include "token.h"

void initialize() {
	init_mem();
	num_tests = 0;
	create_test("String Equality", &test_str_equal);
	create_test("String Add", &test_str_add);
	create_test("ATOI", &test_atoi);
	create_test("ITOA", &test_itoa);
	create_test("String Copy", &test_str_copy);
	create_test("String Less Than", &test_str_lt);
	create_test("Create Map", &test_create_map);
	create_test("Map Insert", &test_map_add);
	create_test("Map Remove", &test_map_rem);
	create_test("Map Find", &test_map_find);
	create_test("Destroy Map", &test_destroy_map);
	create_test("Create Linked List", &test_create_linked_list);
	create_test("Add Link", &test_add_link);
	create_test("Remove Link", &test_remove_link);
	create_test("Destroy Linked List", &test_destroy_linked_list);
	create_test("File Input", &test_fileio_read);
	create_test("File Output", &test_fileio_write);	
	create_test("Create FilePath", &test_create_filepath);
	create_test("FilePath To String", &test_filepath_to_string);
	create_test("Create Token", &test_create_token);
	create_test("Identify Token", &test_identify_token);
	create_test("Create Statement", &test_create_statement);
	create_test("Tokenize Statement", &test_tokenize_statement);
	create_test("Lexical Analyzer", &test_lex);
	create_test("Parser", &test_parse);
	create_test("RHS", &test_rhs);
	create_test("AST", &test_ast);
	create_test("Semantic Analysis", &test_semantic_analysis);
	create_test("Compile", &test_compile);
}

void compile_file(const char* filepath) {
	init_mem();
	FILE *file = fopen(filepath, "r");
	if (!file) {
		fprintf(stderr, "Error: File %s Does Not Exist\n", filepath);
		exit(EXIT_FAILURE);
	}
	Statement *statements = lex(file);
	fclose(file);
	ASTNode *prog = parse(statements);
	Linked_List *instructions = compile(prog);	
	FilePath *fp = create_filepath(filepath);
	
	char *bytecode_path = str_copy("");
	for (int i = 0; i < fp->num_dir; i++) {
		bytecode_path = str_add(bytecode_path, fp->dirs[i]);
		bytecode_path = str_add(bytecode_path, "/");
	}
	bytecode_path = str_add(bytecode_path, fp->filename);
	bytecode_path = str_add(bytecode_path, ".");
	bytecode_path = str_add(bytecode_path, "bytecode");

	FILE *file_out = fopen(bytecode_path, "w");
	fprintf(file_out, "0\n");
	fprintf(file_out, "%d\n", instructions->length);
	Link *head = instructions->head;
	while (head) {
		fprintf(file_out, "%i\n", head->val);
		head = head->next;
	}
	fclose(file_out);
	deinit_mem();
}

int main(int argc, const char* argv[]) {
	if (argc == 1) {
		printf("Running Test Mode\n");
		initialize();
			
		run_tests();
		deinit_mem();
		printf("Tests Complete\n");
	} else if (argc == 2) {
		printf("Attempting Compilation\n");
		compile_file(argv[1]);	
		printf("Compilation Complete\n");
	} else {
		printf("Too many args\n");
	}
	return 0;
}
