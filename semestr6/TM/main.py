from ply.lex import LexToken
from ply import yacc
from sys import argv
import subprocess

class Node:
    def parts_str(self):
        st = []
        for part in self.parts:
            st.append(str(part))
        return "\n".join(st)

    def __repr__(self):
        return self.type + ":\n\t" + self.parts_str().replace("\n", "\n\t")

    def add_parts(self, parts):
        self.parts += parts
        return self

    def __init__(self, type, parts):
        self.type = type
        self.parts = parts


start = 'function'

variables = []


def token_in_stack(name, stack):
    for item in stack:
        if isinstance(item, LexToken) and item.value == name:
            return True
    return False


tokens = (
    'NAME',
    'COUT',
    'LESS',
    'MORE',
    'LSHIFT',
    'RETURN_TYPE',
    'NUMBER',
    'INTEGER',
    'VAR',
    'SEMICOLON',
    'COMMA',
    'IF',
    'ELSE',
    'ASSIGN',
    'EQUAL',
    'NOTEQUAL',
    'LPAREN',
    'RPAREN',
    'LBRACE',
    'RBRACE',
    'LBRACKET',
    'RBRACKET',
    'WHILE',
    'OPERATOR',
    'STRING',
    'FLOAT',
    'RETURN',
    'STRINGLIT',
)


def p_cout(p):
    '''cout : COUT LSHIFT args SEMICOLON'''
    p[0] = Node('cout', p[3:])


def p_initlist(p):
    '''init_list : LBRACE args RBRACE'''
    p[0] = Node('init_list', p[1:])


def p_function(p):
    '''function : func_header block'''
    p[0] = Node('function', p[1:])


def p_func_header(p):
    '''func_header : RETURN_TYPE NAME LPAREN args RPAREN'''
    p[0] = Node('func_declaration', [p[2], p[4]])


def p_args(p):
    '''args : expr
            | args COMMA expr
            | args LESS expr SEMICOLON
    '''
    if len(p) <= 2:
        p[0] = Node('args', p[1:] if p[1:] else ['EMPTY'])
    else:
        p[0] = p[1].add_parts([p[3]])



def p_if_s(p):
    '''if_s : IF LPAREN condition RPAREN block
            | IF LPAREN condition RPAREN line SEMICOLON
            | IF LPAREN condition RPAREN cout'''

    p[0] = Node('if', [p[3], p[5]])


def p_block(p):
    '''block : LBRACE body RBRACE'''
    p[0] = Node('block', [p[2]])


def p_body(p):
    '''body : line SEMICOLON
            | multiline'''
    if len(p) > 1:
        if p[1] is None:
            p[1] = Node('body', [])
        p[0] = p[1].add_parts([p[2]])
    else:
        p[0] = Node('body', [])


def p_multiline(p):
    '''multiline : while_statement
                 | if_s
                 | else'''
    p[0] = p[1]


def p_line(p):
    '''line : assign
            | func
            | RETURN expr
            | RETURN func'''
    if len(p) == 3:
        p[0] = Node('return', [p[2]])
    else:
        p[0] = p[1]


def p_else(p):
    '''else : ELSE block
            | ELSE line SEMICOLON
            | ELSE cout'''
    p[0] = Node('else', [p[2]])


def p_while_statement(p):
    '''while_statement : WHILE LPAREN condition RPAREN block
                       | WHILE LPAREN condition RPAREN line SEMICOLON'''
    p[0] = Node('while', [p[3], p[5]])


def p_condition(p):
    '''condition : expr cond_sign expr'''
    p[0] = Node('condition', [p[1], p[2], p[3]])


def p_cond_sign(p):
    '''cond_sign : NOTEQUAL
                 | EQUAL
                 | LESS
                 | MORE
    '''
    p[0] = p[1]
    

def p_assign_array(p):
    '''assign : INTEGER variable LBRACKET NUMBER RBRACKET ASSIGN expr'''

    if len(p) == 5:
        value = p[2]
        if value in variables:
            raise VariableOverridingError(value, lexer.lineno)
        else:
            variables.append(value)
            p[0] = Node('assign_array', [p[2], p[4]])
    else:
        value = p[1]
        if value not in variables:
            raise NotAssignedVariableError(value, lexer.lineno)
        p[0] = Node('assign_array', [p[1], p[3]])


def p_assign(p):
    '''assign : variable ASSIGN expr
              | VAR variable ASSIGN expr
              | VAR variable ASSIGN function
              | INTEGER variable ASSIGN expr
              | INTEGER variable ASSIGN function
              | INTEGER variable ASSIGN init_list'''

    if len(p) == 5:
        value = p[2]
        if value in variables:
            raise VariableOverridingError(value, lexer.lineno)
        else:
            variables.append(value)
        variable_list.append({p[2]: p[4]})
        p[0] = Node('assign', [p[2], p[4]])
    else:
        value = p[1]
        if value not in variables and '[' not in value and '"' not in value:
            raise NotAssignedVariableError(value, lexer.lineno)
        variable_list.append(
        {p[2]: p[4]})
        p[0] = Node('assign', [p[1], p[3]])


def p_func(p):
    '''func : NAME LPAREN args RPAREN'''
    p[0] = Node('func_call', [p[1], p[3]])
    eval(p[0])


def p_expr(p):
    '''expr : fact
            | expr OPERATOR fact'''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[0] = Node(p[2], [p[1], p[3]])
        eval(p[0])


def p_fact(p):
    '''fact : term
            | fact OPERATOR term'''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[0] = Node(p[2], [p[1], p[3]])
        eval(p[0])


def p_term(p):
    '''term : arg
            | LPAREN expr RPAREN'''
    if len(p) == 2:
        p[0] = p[1]
        variables_list[p[0]] = p[1]
    else:
        p[0] = p[2]
        variables_list[p[0]] = p[2]


def p_arg(p):
    '''arg : STRING
           | variable
           | NUMBER
           | FLOAT
           | func
           | STRINGLIT'''
    if len(p) == 3:
        p[1], p[2] = p[2], p[1]
    value = p[1]
    if isinstance(value, str):
        if token_in_stack('function', p.stack):
            variables.append(value)
        elif value not in variables and '[' not in value and '"' not in value:

            raise NotAssignedVariableError(value, lexer.lineno)
    p[0] = Node('arg', [p[1]])


def p_variable(p):
    """variable : NAME"""
    p[0] = p[1]


parser_errors = []


def p_error(p):
    if p.value == 'include':
        return
    print('Unexpected token in line %d: %s' % (p.lineno, p))


parser = yacc.yacc()


def read_file(filename):
    with open(filename) as f:
        lines = f.readlines()
    with open(filename) as f:
        characters = f.read()
    executive = filename.split(".")[0]
    subprocess.run([f"g++", "-o", executive, filename])
    subprocess.run(["chmod", "+x", executive])
    subprocess.run(f"./{executive}")
    subprocess.run(["rm", "-rf", executive])
    return lines, characters

def build_tree(code):
    return parser.parse(code)


operations = {
    '+': lambda x, y: x + y,
    '-': lambda x, y: x - y,
    '*': lambda x, y: x * y,
    '/': lambda x, y: x / y,
}

__variables = {}


def parse_tree(tree):
    try:
        tree_type = tree.type
        parts = tree.parts
    except AttributeError:
        return tree
    if tree_type == 'assign':
        __variables[parts[0]] = parse_tree(parts[1])
        return
    if tree_type == 'arg':
        arg = parts[0]
        if isinstance(arg, int):
            return arg
        elif arg in __variables:
            return __variables[arg]
        else:
            return 'method'
    if tree_type in operations:
        first = parse_tree(parts[0])
        second = parse_tree(parts[1])
        if tree_type == '/' and second == 0:
            raise CustomZeroDivisionError(11)
        return operations[tree_type](first, second)
    for part in parts:
        parse_tree(part)


if __name__ == '__main__':
    filename = argv[1:2][0]
    lines, characters = read_file(filename)

    try:
        tree = build_tree(characters)
        parse_tree(tree)
    except Exception as e:
        k = str(e).split()
        if k[0] == "CustomZeroDivisionError":
            print(f"Division by zero: line {k[3]} char {lines[int(k[3])].find(k[6][1:-1])}")
            print(lines[int(k[3])][:-1])
            print(' ' * lines[int(k[3])].find('/') + '^')
        if k[0] == "NotAssignedVariableError":
            print(f"Unknown variable: line {k[3]} char {lines[int(k[3]) - 1].find(k[6][1:-1])}")
            print(lines[int(k[3]) - 1][:-1])
            print(' ' * lines[int(k[3]) - 1].find(k[6][1:-1]) + '^')
        if k[0] == "VariableOverridingError":
            print(f"Variable declared: line {k[3]} char {lines[int(k[3]) - 1].find(k[6][1:-1])}")
            print(lines[int(k[3]) - 1][:-1])
            print(' ' * lines[int(k[3]) - 1].find(k[6][1:-1]) + '^')
        if k[0] == "ArgumentLessError":
            print(
                f"Insuffient number of agruments({k[3]}) arguments( {lines[int(k[3]) - 1].find(k[6][1:-1])} line {k[4]} char {k[5]}")
            print(lines[int(k[4])])
            print(' ' * lines[int(k[4]) - 1].find(k[6][1:-1]) + '^')
            if k[0] == "ArgumentMoreError":
                print(
                    f"Excessive number of agruments({k[3]}) arguments( {lines[int(k[3]) - 1].find(k[6][1:-1])} line {k[4]} char {k[5]}")
            print(lines[int(k[4])])
            print(' ' * lines[int(k[4]) - 1].find(k[6][1:-1]) + '^')

            for error in parser_errors:
                print(error)
