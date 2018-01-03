"""
All Json Error
such as
1. out of index in array
2. key is not in object
3. and more

"""


class JsonTypeException(Exception):
    def __init__(self,expected='',actual=''):
        Exception.__init__(self,"JsonTypeException: Expected %s, Actual %s"%(expected,actual))

class JsonParseException(Exception):
    def __init__(self, msg='E'):
        msg_dict = {
            'E': 'ParseError',
            'T': 'TypeError',
            'I': 'Illegal Character',
            'T': 'Illegal Token',
            'U': 'Unexpected Token',
        }
        Exception.__init__(self, msg_dict.get(msg, msg))

class JsonEqualException(Exception):
    def __init__(self,expected='',actual=''):
        Exception.__init__(self,"JsonEqualException: can't equal use '=',%s, Actual %s"%(expected,actual))

