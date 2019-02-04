#ifndef _AST_H_
#define _AST_H_
typedef enum{
  SYM_VAR,
  SYM_ARG_VAR,
  SYM_FUNC,
  SYM_KEYWORD,
} Stype;

typedef enum{
  AST_PROGRAM,
  AST_VAR_DECS,
  AST_DEC,
  AST_FUNC_LIST,
  AST_FUNC,
  AST_ARG_LIST,
  AST_ARG,
  AST_STAT_LIST,
  AST_ASSIGN,
  AST_ADD,
  AST_SUB,
  AST_MUL,
  AST_DIV,
  AST_MOD,
  AST_INCRE,
  AST_DECRE,
  AST_WHILE,
  AST_FOR,
  AST_IF,
  AST_EQ,
  AST_LESS,
  AST_GR,
  AST_LSEQ,
  AST_GREQ,
  AST_FUNCCALL,
  AST_PARAM_LIST,
  AST_IDENT,
  AST_NUM,
  AST_ARRAY_REF,
  AST_BREAK,
} Ntype;

typedef enum{
  D_DEFINE,
  D_ARRAY,
} Dtype;

typedef struct dtyp{
  Dtype type;
  struct dtyp *next;
} DTYP;

typedef struct node{
  Ntype type;
  int value; 
  int value2;
  char *name;
  int n_child;
  Dtype dtype[30];
  int   dnum;
  struct node **child;
} Node;

typedef struct symbols{
  int symno;
  char *symbolname;
  Stype type;
  unsigned int size1;
  unsigned int size2;
  unsigned int arg_num; //SYM_FUNCに使用
  unsigned int address; 
  int array_flag;       //set_ident_address内で使用,配列か否かを判断
  Dtype dtype[30];
  struct symbols *next;
  struct symbols *branch;
} Symbols;

typedef struct fours{
  Ntype operand;
  int result;
  
} Fours;

Node *make_num_node(int n);
Node *make_ident_node(Stype type, int symno, Symbols *stable, char *name);
Node *make_new_ident_node(Symbols *stable, Stype type, char *name,
                          Node *num1, Node *num2);
Node *make_nchild_node(Ntype type, ...);
int get_child_num(Ntype type);
int sym_lookup(Symbols *stable, char *name);
Symbols *sym_add(Symbols *stable, char *name, Stype type, unsigned int size1, unsigned int size2);
char *sym_lookup_name(Symbols *stable, int symno);
Symbols *sym_lookup_entry(Symbols *stable, int symno);
Symbols *get_tail_of_stable(Symbols *stable);
char *get_ntype_name(Ntype type);
void print_ast_tree(Node *root, Symbols *gstable, Symbols *lstable, int depth);
void print_symbol_table(Symbols *stable, int depth);

int calc_arg_node_depth(Node *arg_list,int depth);

void generate_program_code(Node *root, Symbols *gstable);
void generate_initial_code();
void generate_function_list_code(Node *node, Symbols *gstable);
void generate_function_code(Node *func, Symbols *gstable, Symbols *lstable);
unsigned int calc_local_variables_size(Node *func);
void generate_global_variables_definitions(Symbols *gstable);
void generate_statement_code(Node *stat, Symbols *gstable, Symbols *lstable, int jlabel);
//assign_functions
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
void generate_assign_code(Node *assign, Symbols *gstable, Symbols *lstable);
int generate_arithmetic_code(Node *exp, Symbols *gstable, Symbols *lstable);
void set_ident_address(Symbols *lstable, int func_arg_size, int stack_size);
int get_ident_address(Node *node, Symbols *gstable, Symbols *lstable);
void get_array_address(Node *array_ref, Symbols *gstable, Symbols *lstable);
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

//while_functions
//########################################################################//
void generate_while_code(Node *while_node, Symbols *gstable, Symbols *lstable);
void generate_expression_code(Node *exp, Symbols *gstable, Symbols *lstable, char *label_name, int bool);
//########################################################################//

//if_functions
//########################################################################//
void generate_if_code(Node *if_node, Symbols *gstable, Symbols *lstable, int skip);
//########################################################################//

//for_functions
//########################################################################//
void generate_for_code(Node *for_node, Symbols *gstable, Symbols *lstable);
//########################################################################//

//funccall_functions
//########################################################################//
void generate_funccall_code(Node *funccall_node, Symbols *gstable, Symbols *lstable);
int ident_check(Node *node, Symbols *gstable, Symbols *lstable);
void set_arg_type(Node *node, Node *arg_list, int i);
void cp_dtype(Symbols *sym, Node *node);
//########################################################################//
#endif // _AST_H_

