import ast

def print_ast_nodes(node, indent=""):
    # Creating a list to hold the outputs to keep them in a single block
    output = []

    if isinstance(node, ast.Assign):
        output.append(f"{indent}Assignment: {ast.dump(node)}")
    elif isinstance(node, ast.For):
        output.append(f"{indent}For Loop: {ast.dump(node)}")
    elif isinstance(node, ast.While):
        output.append(f"{indent}While Loop: {ast.dump(node)}")
    elif isinstance(node, ast.If):
        output.append(f"{indent}If Condition: {ast.dump(node)}")

    # Traverse child nodes
    for child in ast.iter_child_nodes(node):
        output.extend(print_ast_nodes(child, indent + "  "))

    return output

def generate_ast_from_file(file_path):
    with open(file_path, "r") as source_code:
        tree = ast.parse(source_code.read())

    print("AST for each functional block (assignments, loops, and conditions):\n")

    # Collecting all outputs in a single block
    ast_outputs = print_ast_nodes(tree)
    print("\n".join(ast_outputs))  # Printing as a single block

# Main block
if __name__ == "__main__":
    print("The pre-order traversal is: ")
    generate_ast_from_file(r"C:\Users\14har\OneDrive\Desktop\lab_DA\compiler_lab\factorial.py")
