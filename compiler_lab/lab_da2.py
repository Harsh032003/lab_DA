import ast
import subprocess

def extract_python_ast_blocks(source_file):
    try:
        with open(source_file, "r") as file:
            code = file.read()
        ast_tree = ast.parse(code)
        code_blocks = [
            node
            for node in ast.walk(ast_tree)
            if isinstance(node, (ast.Assign, ast.If, ast.For, ast.While))
        ]
        return code_blocks
    except Exception as error:
        print(f"Error processing Python AST: {error}")
        return []


def extract_cpp_ast_blocks(source_file):
    try:

        clang_command = [
            "clang++",
            "-Xclang",
            "-ast-dump",
            "-fsyntax-only",
            source_file,
        ]
        process_result = subprocess.run(clang_command, capture_output=True, text=True)
        if process_result.returncode != 0:
            raise RuntimeError("Failed to generate C++ AST")
        return process_result.stdout
    except Exception as error:
        print(f"Error processing C++ AST: {error}")
        return ""


def show_ast_blocks(code_blocks, lang):
    if lang == "python":
        print(f"\nAST for factorial.py input file : \nThe Preorder traversal of AST: \n")
        for index, block in enumerate(code_blocks, start=1):
            print(ast.dump(block, indent=4))
    elif lang == "cpp":
        print("\nAST for C++ code:")
        print(code_blocks)
    else:
        print("Unsupported language")


if __name__ == "__main__":
    source_file = r"C:\Users\14har\OneDrive\Desktop\lab_DA\compiler_lab\factorial.py"
    lang = "python"

    if lang == "python":
        code_blocks = extract_python_ast_blocks(source_file)
    elif lang == "cpp":
        code_blocks = extract_cpp_ast_blocks(source_file)
    else:
        print("Unsupported language")
        code_blocks = []

    show_ast_blocks(code_blocks,lang)