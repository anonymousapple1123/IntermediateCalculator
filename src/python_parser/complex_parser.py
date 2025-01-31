import re
import sys

def parse_complex(complex_str):
    
    match = re.match(r'^\s*(-?\d+\.?\d*)\s*\+\s*(-?\d+\.?\d*)i\s*$', complex_str)
    if not match:
        raise ValueError("Invalid complex number format. Expected format: 'a + ib'")
    
    a = float(match.group(1))  # Real part
    b = float(match.group(2))  # Imaginary part
    return a, b

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: complex_parser <complex_number>")
        sys.exit(1)
    
    complex_str = sys.argv[1]
    try:
        a, b = parse_complex(complex_str)
        print(f"{a},{b}")
    except ValueError as e:
        print(f"Error: {e}")
        sys.exit(1)