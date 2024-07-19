import dataclasses
from typing import Any
import enum


class TokenTypes(enum.Enum):
    STRING = enum.auto()
    NUMBER = enum.auto()

    KEYWORD = enum.auto()
    NAME = enum.auto()

    OP_PLUS = enum.auto()
    OP_MUL = enum.auto()


@dataclasses.dataclass()
class Token:
    type_: TokenTypes
    value: Any  # FIXME add correct type hints (ex: if type_ is NUMBER then value MUST be a number)
    line: int = 0
    column: int = 0
