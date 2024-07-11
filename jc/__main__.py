from .parser import Lexer
import sys


def main():
    if len(sys.argv) < 2:
        return print("Usage: python -m jc file.jc")

    lexer = Lexer(open(sys.argv[1]).read())
    while True:
        try:
            print(lexer.next_token())
        except EOFError:
            break


if __name__ == "__main__":
    main()
