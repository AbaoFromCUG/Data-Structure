from .JsonException import *

class JsonObject(dict):
    """
    save json  as object

    """
    def __init__(self):
        self.m_kvMap=dict()
        dict.__init__(self.m_kvMap)


    def get(self,k):
        return self.m_kvMap.get(k)

    def set(self, k,v):
        self.m_kvMap.update({k,v})


    def __getitem__(self, key):
        pass

    def __setitem__(self, key, value):
        pass
    def __str__(self):
        pass
    def items(self):
        return self.m_kvMap.items()


class JsonArray(list):

    def __init__(self):
        self.m_data=list()
        list.__init__(self.m_data)

    def __getitem__(self, index):
        return self.m_data[index]

    def __setitem__(self, key, value):
        self.m_data[key]=value

    def append(self,i):
        self.m_data.append(i)

    def get(self,i):
        return  self.m_data[i]

    def size(self):
        return  len(self.m_array)

    def _parse_data(self,data):
        if type(data)==JsonObject:
            ret ={}
            for key,vaule in data.m_kvMap.items():
                ret.update({key,self._parse_data(vaule)})
            return ret
        elif type(data)==JsonArray:
            ret=[]
            for i in data.m_data:
                ret.append(self._parse_data(i))
            return  ret
        else:
            return data


    def __str__(self):
        return ''.join(self.m_array)

    def toPython(self):
        return  self._parse_data(self)

    # =
    def __eq__(self, other):
        if isinstance(other,JsonArray):
            if not self.size()==other.size():
                return  False
            for i in range(0,self.size()):
                if not self.get(i)==other[i]:
                    return False
            return True
        else:
            raise JsonEqualException(type(self),type(other))
