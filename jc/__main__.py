from .parser import Lexer
from pprint import pprint
import sys


def main():
    if len(sys.argv) < 2:
        return print("Usage: python -m jc file.jc")

    lexer = Lexer(open(sys.argv[1]).read())
    pprint(lexer.tokens())


if __name__ == "__main__":
    main()
