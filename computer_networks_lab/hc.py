def calculate_parity_bits(data: str) -> str:
    """
    Calculate the Hamming code by adding parity bits to the data.
    :param data: The binary string data (without parity bits).
    :return: The data with parity bits added.
    """
    n = len(data)
    r = 0

    # Determine the number of parity bits required
    while (2**r < n + r + 1):
        r += 1

    # Create a list to hold the data and parity bits
    hamming_code = ['0'] * (n + r)
    
    # Place the original data in the appropriate positions
    j = 0
    for i in range(1, len(hamming_code) + 1):
        # Skip positions that are powers of 2 (reserved for parity bits)
        if i & (i - 1) != 0:
            hamming_code[i - 1] = data[j]
            j += 1

    # Calculate parity bits
    for i in range(r):
        pos = 2 ** i
        parity = 0
        for j in range(1, len(hamming_code) + 1):
            if j & pos and j != pos:
                parity ^= int(hamming_code[j - 1])
        hamming_code[pos - 1] = str(parity)

    return ''.join(hamming_code)

def detect_and_correct_error(hamming_code: str) -> str:
    """
    Detect and correct a single-bit error in the received Hamming code.
    :param hamming_code: The received Hamming code (binary string).
    :return: The corrected Hamming code (binary string).
    """
    n = len(hamming_code)
    r = 0

    # Determine the number of parity bits
    while (2 ** r < n + 1):
        r += 1

    # Calculate the error position (if any)
    error_pos = 0
    for i in range(r):
        pos = 2 ** i
        parity = 0
        for j in range(1, n + 1):
            if j & pos:
                parity ^= int(hamming_code[j - 1])
        if parity != 0:
            error_pos += pos

    # Correct the error if there's any
    if error_pos != 0:
        print(f"Error detected at position {error_pos}")
        hamming_code = list(hamming_code)
        hamming_code[error_pos - 1] = '1' if hamming_code[error_pos - 1] == '0' else '0'
        corrected_code = ''.join(hamming_code)
        return corrected_code
    else:
        print("No error detected.")
        return hamming_code

def sender(data: str) -> str:
    """
    Sender module: Takes binary data as input and returns the Hamming code with parity bits.
    :param data: The binary string data to be sent.
    :return: The encoded Hamming code.
    """
    hamming_code = calculate_parity_bits(data)
    print(f"Hamming code to be sent: {hamming_code}")
    return hamming_code

def receiver(hamming_code: str) -> str:
    """
    Receiver module: Verifies and corrects errors in the received Hamming code.
    :param hamming_code: The received Hamming code (binary string).
    :return: The corrected Hamming code or the same code if no errors are detected.
    """
    corrected_code = detect_and_correct_error(hamming_code)
    print(f"Received Hamming code: {hamming_code}")
    print(f"Corrected Hamming code: {corrected_code}")
    return corrected_code

# Sender sends the data with Hamming code
data = input("Enter original data: ")  # Example binary data
hamming_code = sender(data)

# Simulate error during transmission by flipping a bit
choice = input("Do you want to simulate an error during transmission? (y/n): ")
if choice.lower() == 'y':
    hamming_code_with_error = hamming_code[:5] + ('0' if hamming_code[5] == '1' else '1') + hamming_code[6:]
    print(f"Hamming code with error: {hamming_code_with_error}")

# Receiver verifies and corrects the data
corrected_code = receiver(hamming_code_with_error)
