OPTAB = {
    "LOAD": "01",
    "STORE": "02",
    "ADD": "03",
    "SUB": "04",
    "JMP": "05"
}

# Example Assembler Directives
DIRECTIVES = ["START", "END", "WORD", "RESW", "RESB"]

# Symbol Table (SYMTAB) and Intermediate Code
SYMTAB = {}
intermediate_code = []

# Pass-I: Generates the symbol table and intermediate code
def pass1(input_lines):
    locctr = 0
    start_address = 0
    for line in input_lines:
        label, opcode, operand = parse_line(line.strip())

        if opcode == "START":
            start_address = int(operand)
            locctr = start_address
            intermediate_code.append((locctr, label, opcode, operand))
            continue

        # Process label
        if label:
            if label in SYMTAB:
                print(f"Error: Duplicate symbol {label}")
            SYMTAB[label] = locctr

        # Process opcode
        if opcode in OPTAB:
            intermediate_code.append((locctr, label, opcode, operand))
            locctr += 3  # Assume all instructions are 3 bytes
        elif opcode in DIRECTIVES:
            if opcode == "WORD":
                locctr += 3
            elif opcode == "RESW":
                locctr += 3 * int(operand)
            elif opcode == "RESB":
                locctr += int(operand)
            elif opcode == "END":
                intermediate_code.append((locctr, label, opcode, operand))
                break
        else:
            print(f"Error: Invalid opcode {opcode}")

    return start_address, intermediate_code

# Parse a line of input (splits line into label, opcode, operand)
def parse_line(line):
    parts = line.split()
    label = parts[0] if len(parts) == 3 else None
    opcode = parts[1] if len(parts) == 3 else parts[0]
    operand = parts[2] if len(parts) == 3 else parts[1] if len(parts) == 2 else None
    return label, opcode, operand

# Pass-II: Generates the final machine code
def pass2(start_address, intermediate_code):
    final_code = []
    for locctr, label, opcode, operand in intermediate_code:
        if opcode in OPTAB:
            machine_code = OPTAB[opcode]
            if operand in SYMTAB:
                address = format(SYMTAB[operand], '04X')  # 4-digit hex address
            else:
                address = '0000'  # Default if symbol not found
            final_code.append(f"{locctr:04X} {machine_code} {address}")
        elif opcode == "WORD":
            final_code.append(f"{locctr:04X} {int(operand):06X}")
        elif opcode == "RESW" or opcode == "RESB":
            final_code.append(f"{locctr:04X} ----")
        elif opcode == "END":
            final_code.append(f"{locctr:04X} END")
    return final_code

# Main function to read the input file and run both passes
def main():
    # Read the assembly code from input.txt
    with open("pass1source.txt", "r") as file:
        input_lines = file.readlines()

    # Run Pass-I
    start_address, intermediate_code = pass1(input_lines)

    # Display Symbol Table and Intermediate Code
    print("\nPass-I Output:")
    print("Symbol Table (SYMTAB):", SYMTAB)
    print("\nIntermediate Code:")
    for entry in intermediate_code:
        print(entry)

    # Run Pass-II
    final_code = pass2(start_address, intermediate_code)

    # Display Final Machine Code
    print("\nPass-II Output (Final Machine Code):")
    for code in final_code:
        print(code)

# Run the main function
if __name__ == "__main__":
    main()
