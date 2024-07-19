import dataclasses
import enum


class ASTNode:
    pass


@dataclasses.dataclass
class Literal(ASTNode):
    value: str | int | bool | None


class Operator(enum.Enum):
    SUM = enum.auto()
    SUB = enum.auto()
    MUL = enum.auto()
    DIV = enum.auto()


@dataclasses.dataclass
class Binary(ASTNode):
    left: ASTNode
    op: Operator
    right: ASTNode
