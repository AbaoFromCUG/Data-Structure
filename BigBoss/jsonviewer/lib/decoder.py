
from  enum import  Enum
from .JsonException import *
class Reader(object):
    def __init__(self,data):
        self.m_data=data
        self.m_cursor=0  #初始化游标
    def size(self):
        return  len(self.m_data)

    def nextPos(self):
        self.m_cursor+=1
        return self.m_data[self.m_cursor-1]

    def read(self,size):
        if self.m_cursor==self.size():
            return None
        cur=self.m_cursor
        if cur+size+1<self.size():
            ret=self.m_data[cur,cur+size+1]
            cur+=size+1
        else:
            ret=self.m_data[cur:]
            cur=self.size()
        self.m_cursor=cur
        return ret
    def current_pos(self):
        if self.m_cursor>=len(self.m_data)+1:
            return None
        return self.m_data[max(0,self.m_cursor-1)]
    def hasNext(self):
        return self.m_cursor<len(self.data)

    def prevPos(self):
        self.m_cursor=max(self.m_cursor-1,0)


class TokenEnum(Enum):
    # Signal token
    BEGIN_OBJECT = 1
    BEGIN_ARRAY = 2
    END_OBJECT = 4
    END_ARRAY = 8

    # variable token
    NULL = 16
    NUMBER = 32
    STRING = 64
    BOOL = 128

    # separator token
    COLON = 256
    COMMA = 512

    # end signal
    END_JSON = 65536



class TokenList(object):
    def __init__(self):
        self.m_tokenList=list()
        self.m_cursor=0

    def get_cursor_position(self):
        return  self.m_cursor

    def append(self,token):
        self.m_tokenList.append(token)

    def next(self):
        ret=self.m_tokenList[self.m_cursor]

class Token(object):
    def __init__(self,token_dype,value):
        self.m_type=token_dype
        self.m_value=value

    def get_type(self):
        return self.m_type

    def set_value(self,newValue):
        self.m_value=newValue

    def __str__(self):
        return  "Type: "+str(self.m_type)+" Value: "+str(self.m_value)

class Tokenizer(object):
    def __init__(self,reader):
        self.m_ch=''
        self.m_reader=reader
        self.m_tokenList=TokenList()
        self.tokenize()
    def get_tokens(self ):
        return self.m_tokenList

    def tokenize(self):
        tk=self.parse()
        self.m_tokenList.append(tk)
        while tk.get_type() !=TokenEnum.END_JSON:
            tk=self.parse()
            self.parse()
            self.m_tokenList.append(tk)

        pass

    def parse(self):
        def is_space(char):
            return  char in ('\n','\t','\r',' ','')

        def is_hex(char):
            return char.isdigit() or (ord(char) in range(ord('a'),ord('g')))

        def is_exp(char):
            return char in ('e',"E")

        def read():
            self.m_ch=self.m_reader.next_pos()

        def read_null():
            rem=self.m_reader.next_pos()+self.m_reader.next_pos()+self.m_reader.next_pos()
            if rem.lower()!="ull":
                raise JsonTypeException("null","where is %s"%rem)
            else:
                return Token(TokenEnum.NULL,"null")

        def read_bool(s):
            s=s.lower()
            if s=='t':
                #rem=self.m_reader.next_pos()+self.m_reader.next_pos+self.m_reader.next_pos()
                rem=self.m_reader.read(3)
            else:
                #rem=self.m_reader.next_pos()+self.m_reader.next_pos()+self.m_reader
                rem=self.m_reader.read(3)
            if rem.lower()!={'t':'rue','f':'alse'}[s]:
                raise JsonTypeException({'t': 'true', 'f': 'false'}[s], s + rem)
            else:
                return Token(TokenEnum.BOOL,s+rem)

        def read_str():
            ret=''
            while 1:
                read()
                if self.m_ch=='\\':
                    ret+='\\'
                    self.m_ch=self.m_reader.current_pos()
                    ret+=self.m_ch
                    if self.m_ch=='y':
                        for i in range(1,5,1):
                            read()
                            if is_hex(self.m_ch):
                                ret+=self.m_ch
                            else:
                                raise  JsonParseException('I')