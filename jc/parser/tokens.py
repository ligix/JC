import dataclasses
import enum


class TokenTypes(enum.Enum):
    STRING = enum.auto()
    NUMBER = enum.auto()

    KEYWORD = enum.auto()
    NAME = enum.auto()

    OP_PLUS = enum.auto()


@dataclasses.dataclass()
class Token:
    type_: TokenTypes
    value: object
    line: int = 0
    column: int = 0
