
from  enum import  Enum

class TokenEnum(Enum):
    # 下面关于token　类型的设计模式来源于网络
    jsonStartArray = 1
    jsonEndArray = 2
    jsonStartObj = 4
    jsonEndObj = 8

    jsonNULL = 16
    jsonNumber = 32
    jsonString = 64
    jsonBoolean = 128

    jsonComma = 256  # ,
    jsonColon = 512  #:

    jsonEndDoc = 1024
