
#include "cammap.h"




CAMMap::CAMMap(int capacity,MapType type):
    AMMap(capacity)
{
    m_tMap=type;
}

CAMMap::CAMMap(const CAMMap &old):
    AMMap(old)
{
    m_tMap=old.m_tMap;
}


CAMMap::~CAMMap()
{
}



void CAMMap::printMap()
{
    for(int i=0;i<m_iNodeCount;i++){
        for(int j=0;j<m_iNodeCount;j++){
            if(m_iMatrix[i*this->m_iCapacity+j]==INT32_MAX){
                cout<<"|  ";
            }else {
                cout<<"|"<<m_iMatrix[i*m_iCapacity+j];

            }
        }
        std::cout<<"|"<<std::endl;
    }
}
