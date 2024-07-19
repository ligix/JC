from typing import Container, Iterable

from . import ast
from .. import Lexer, Token, TokenTypes


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

    def match(
        self, types: Container[TokenTypes] | Iterable[TokenTypes]
    ) -> Token | None:
        if (p := self.peek()) and p.type_ in types:
            return self.advance()

    def end(self):
        return self.cursor >= self.token_number

    def parse_expression(self):
        node = self.parse_e_add()

        return node

    def parse_e_add(self):
        node = self.parse_e_mul()

        if op := self.match((TokenTypes.OP_PLUS,)):
            return ast.Binary(
                left=node,
                op={
                    TokenTypes.OP_PLUS: ast.Operator.SUM,
                }[op.type_],
                right=self.parse_expression(),
            )
        return node

    def parse_e_mul(self):
        node = self.parse_e_literal()

        if op := self.match((TokenTypes.OP_MUL,)):
            return ast.Binary(
                left=node,
                op={
                    TokenTypes.OP_MUL: ast.Operator.MUL,
                }[op.type_],
                right=self.parse_e_literal(),
            )
        return node

    def parse_e_literal(self) -> ast.Literal:
        if node := self.match((TokenTypes.NUMBER, TokenTypes.STRING)):
            return ast.Literal(value=node.value)

        raise Exception("Expected a literal token", self.peek())
