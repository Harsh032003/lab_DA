import ast
import subprocess
import argparse


def extract_python_ast_blocks(source_file):
    try:
        with open(source_file, "r") as file:
            code = file.read()
        print(code)
        ast_tree = ast.parse(code)
        code_blocks = [node for node in ast.walk(ast_tree) if isinstance(
            node, (ast.Assign, ast.If, ast.For, ast.While))]
        return code_blocks
    except Exception as error:
        print(f"Error processing Python AST: {error}")
        return []

def extract_cpp_ast_blocks(source_file):
    try:
        clang_command = ["clang++", "-Xclang",
                         "-ast-dump", "-fsyntax-only", source_file]
        process_result = subprocess.run(
            clang_command, capture_output=True, text=True)
        if process_result.returncode != 0:
            raise RuntimeError("Failed to generate C++ AST")
        return process_result.stdout
    except Exception as error:
        print(f"Error processing C++ AST: {error}")
        return ""

def show_ast_blocks(code_blocks, lang):
    if lang == "python":
        for index, block in enumerate(code_blocks, start=1):
            print(f"\nAST for Code Block {index}:")
            print(ast.dump(block, indent=4))
    elif lang == "cpp":
        print("\nAST for C++ code:")
        print(code_blocks)
    else:
        print("Unsupported language")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Process a source file to extract AST blocks.")
    parser.add_argument("source_file", type=str, help="Path to the source file")
    parser.add_argument("lang", type=str, choices=["python", "cpp"], help="Programming language of the source file")

    args = parser.parse_args()

    source_file = args.source_file
    lang = args.lang

    if lang == "python":
        code_blocks = extract_python_ast_blocks(source_file)
    elif lang == "cpp":
        code_blocks = extract_cpp_ast_blocks(source_file)
    else:
        print("Unsupported language")
        code_blocks = []

    show_ast_blocks(code_blocks, lang)
