from collections import defaultdict

class LL1Parser:
    def __init__(self, grammar, terminals, non_terminals, start_symbol):
        self.grammar = grammar
        self.terminals = terminals
        self.non_terminals = non_terminals
        self.start_symbol = start_symbol
        self.first = defaultdict(set)
        self.follow = defaultdict(set)
        self.parse_table = defaultdict(dict)
        self.epsilon = 'ε'
        self.end_symbol = '$'

    # Function to compute the First set of each non-terminal
    def compute_first(self):
        for non_terminal in self.non_terminals:
            self.first[non_terminal] = self.first_set(non_terminal)

    def first_set(self, symbol):
        if symbol in self.terminals:
            return {symbol}
        if symbol == self.epsilon:
            return {self.epsilon}
        first = set()
        for production in self.grammar.get(symbol, []):
            if production == '':
                first.add(self.epsilon)
            else:
                for char in production:
                    char_first = self.first_set(char)
                    first |= (char_first - {self.epsilon})
                    if self.epsilon not in char_first:
                        break
                else:
                    first.add(self.epsilon)
        return first

    # Function to compute the Follow set of each non-terminal
    def compute_follow(self):
        self.follow[self.start_symbol].add(self.end_symbol)
        while True:
            updated = False
            for non_terminal, productions in self.grammar.items():
                for production in productions:
                    for i, symbol in enumerate(production):
                        if symbol in self.non_terminals:
                            next_first = set()
                            for j in range(i+1, len(production)):
                                next_first |= self.first_set(production[j]) - {self.epsilon}
                                if self.epsilon not in self.first_set(production[j]):
                                    break
                            else:
                                next_first |= self.follow[non_terminal]
                            if not next_first.issubset(self.follow[symbol]):
                                self.follow[symbol] |= next_first
                                updated = True
            if not updated:
                break

    # Create the LL(1) Parse Table
    def create_parse_table(self):
        for non_terminal, productions in self.grammar.items():
            for production in productions:
                first = self.first_set_of_string(production)
                for terminal in first:
                    if terminal != self.epsilon:
                        self.parse_table[non_terminal][terminal] = production
                if self.epsilon in first:
                    for terminal in self.follow[non_terminal]:
                        self.parse_table[non_terminal][terminal] = production

    # First set of a string (used in Parse Table construction)
    def first_set_of_string(self, string):
        result = set()
        for symbol in string:
            result |= self.first_set(symbol) - {self.epsilon}
            if self.epsilon not in self.first_set(symbol):
                return result
        result.add(self.epsilon)
        return result

    # Function to parse an input string
    def parse_input(self, input_string):
        input_string += self.end_symbol
        stack = [self.end_symbol, self.start_symbol]
        print(f"Stack: {stack}")
        idx = 0

        while stack:
            top = stack.pop()
            current_input = input_string[idx]
            print(f"Stack Top: {top}, Current Input: {current_input}")

            if top == current_input:
                print(f"Matched {current_input}")
                idx += 1
            elif top in self.non_terminals:
                if current_input in self.parse_table[top]:
                    production = self.parse_table[top][current_input]
                    print(f"Apply Production: {top} -> {production}")
                    if production != self.epsilon:
                        stack.extend(reversed(production))
                else:
                    print(f"Error: No rule for {top} -> {current_input}")
                    return False
            else:
                print(f"Error: Mismatch between {top} and {current_input}")
                return False
            print(f"Stack: {stack}")
        
        if stack or idx != len(input_string):
            print(f"Error: Incomplete Parse")
            return False
        
        print(f"Successfully Parsed!")
        return True

    # Function to display First and Follow sets
    def display_first_follow(self):
        print("First Sets:")
        for non_terminal in self.non_terminals:
            print(f"{non_terminal}: {self.first[non_terminal]}")
        print("\nFollow Sets:")
        for non_terminal in self.non_terminals:
            print(f"{non_terminal}: {self.follow[non_terminal]}")

    # Function to display the parse table
    def display_parse_table(self):
        print("\nParse Table:")
        for non_terminal in self.parse_table:
            for terminal in self.parse_table[non_terminal]:
                print(f"M[{non_terminal}, {terminal}] = {self.parse_table[non_terminal][terminal]}")

# Example Usage
grammar = {
    'E': ['TX'],
    'X': ['+TX', 'ε'],
    'T': ['FY'],
    'Y': ['*FY', 'ε'],
    'F': ['(E)', 'id']
}

terminals = ['+', '*', '(', ')', 'id']
non_terminals = ['E', 'X', 'T', 'Y', 'F']
start_symbol = 'E'

# Initialize parser
parser = LL1Parser(grammar, terminals, non_terminals, start_symbol)

# Compute First and Follow sets
parser.compute_first()
parser.compute_follow()

# Display First and Follow sets
parser.display_first_follow()

# Create the Parse Table
parser.create_parse_table()

# Display Parse Table
parser.display_parse_table()

# Parse valid and invalid inputs
print("\nParsing input: id+id*id")
parser.parse_input('id+id*id')

print("\nParsing input: id+*id")
parser.parse_input('id+*id')
