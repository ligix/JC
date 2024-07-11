from . import Token, TokenTypes
import string


class Lexer:
    def __init__(self, text: str):
        self.text = text
        self.text_length = len(text)
        self.cursor = 0

    def advance(self):
        if self.end():
            raise EOFError()
        ret = self.text[self.cursor]
        self.cursor += 1
        return ret

    def peek(self):
        if self.end():
            return None
        return self.text[self.cursor]

    def end(self):
        return self.cursor >= self.text_length

    def tokens(self):
        tokens = []
        while not self.end():
            match (c := self.advance()):
                case '"':
                    value = ""
                    while (c := self.advance()) != '"':
                        value += c
                    tokens.append(Token(TokenTypes.STRING, value))

                case _ if c in string.digits:
                    value = c
                    while (c := self.peek()) is not None and c in string.digits:
                        value += self.advance()
                    tokens.append(Token(TokenTypes.NUMBER, int(value)))

                case "+" | "*":
                    tokens.append(
                        Token(
                            {
                                "+": TokenTypes.OP_PLUS,
                                "*": TokenTypes.OP_MUL,
                            }[c],
                            None,
                        )
                    )

                case _:
                    raise ValueError(
                        f"Unexpected character {c}, expecting start of next token", c
                    )
        return tokens
