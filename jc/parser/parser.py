from . import Lexer, Token


class Parser:
    def __init__(self, tokens: str | list[Token]):
        if isinstance(tokens, str):
            tokens = Lexer(tokens).tokens()
        self.tokens = tokens
        self.token_number = len(tokens)
        self.cursor = 0

    def advance(self):
        if self.end():
            raise EOFError()
        ret = self.tokens[self.cursor]
        self.cursor += 1
        return ret

    def peek(self):
        if self.end():
            return None
        return self.tokens[self.cursor]

    def end(self):
        return self.cursor >= self.token_number

    def parse_statement(self):
        return self.parse_expression()

    def parse_expression(self):
        return self.parse_e_sum() or self.parse_literal()

    def parse_e_sum(self):
        return self.parse_expression()

    def parse_literal(self):
        return
