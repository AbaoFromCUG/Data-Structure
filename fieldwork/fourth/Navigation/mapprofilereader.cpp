#include "mapprofilereader.h"

MapProfileReader* MapProfileReader::m_reader = new MapProfileReader();
MapProfileReader::MapProfileReader()
{
    this->m_fileName="./profile.config";

    refresh();


}

void MapProfileReader::refresh()
{
    if(isFileExists()){
        QFile file(m_fileName);
        if(file.open(QIODevice::ReadOnly));{
            QJsonDocument doc=QJsonDocument::fromJson(file.readAll());
            QJsonObject obj=doc.object();
            m_iPointCount=obj.value("pointArray").toArray().count();
            {
                QJsonArray array= obj.value("pointArray").toArray();
                QList<ViewPoint> points;
                for(auto i : array){
                    QJsonObject obj=i.toObject();
                    points.push_back(ViewPoint::fromJsonObject(obj));
                }
                m_points=points;
            }
            {
                QJsonArray array= obj.value("lineArray").toArray();
                QList<ViewLine> lines;
                for(auto i : array){
                    QJsonObject obj=i.toObject();
                    lines.push_back(ViewLine::fromJsonObject(obj));
                }
                m_lines=lines;
            }
            m_imgSrc=obj.value("mapImg").toString();
        }
    }else{
        QJsonObject obj=getInitObject();
        QJsonDocument doc(obj);
        QFile file(m_fileName);
        if(file.open(QIODevice::WriteOnly)){
            QTextStream steam(&file);
            steam<<doc.toJson();
            refresh();
        }
    }
}

QJsonObject MapProfileReader::getInitObject()
{
    QJsonObject obj;
    obj.insert("mapImg",":/img/res/cug.png");
    obj.insert("pointArray",QJsonArray());
    obj.insert("lineArray",QJsonArray());
    return obj;
}

void MapProfileReader::writeToFile()
{
    /*ViewPoint{obj.value("index").toInt(),\
                obj.value("name").toString(),
                obj.value("type").toInt(),
                obj.value("desc").toString(),obj.value("imgSrc").toString(),obj.value("x").toDouble(),obj.value("y").toDouble()};
     */
    QJsonObject obj;
    obj.insert("mapImg",":/img/res/cug.png");
    QJsonArray points;
    for(auto i:m_points){
        QJsonObject obj;
        obj.insert("index",i.index);
        obj.insert("name",i.name);
        obj.insert("type",i.type);
        obj.insert("desc",i.desc);
        obj.insert("imgSrc",i.imgSrc);
        obj.insert("x",i.x);
        obj.insert("y",i.y);
        points.append(obj);
    }
    obj.insert("pointArray",points);
    QJsonArray lines;
    for(auto i:m_lines){
        QJsonObject obj;
        obj.insert("fromIndex",i.fromIndex);
        obj.insert("toIndex",i.toIndex);
        points.append(obj);
    }
    obj.insert("lineArray",lines);
    QFile file(m_fileName);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);
        stream<<QJsonDocument(obj).toJson();
    }else {
        throw "error";
    }
}

bool MapProfileReader::isFileExists()
{
    return QFile::exists(m_fileName);
}

QString MapProfileReader::getFileName() const
{
    return m_fileName;
}

void MapProfileReader::setFileName(const QString &value)
{
    m_fileName = value;
}

MapProfileReader *MapProfileReader::getInstance()
{
    return m_reader;
}

QString MapProfileReader::getMapImg()
{
    return m_imgSrc;
}

QList<ViewPoint>& MapProfileReader::getAllPoint()
{
    return m_points;
}

QList<ViewLine>& MapProfileReader::getAllLine()
{
    return m_lines;
}

void MapProfileReader::addNewViewPoint(ViewPoint &point)
{
    /*
     * return ViewPoint{obj.value("index").toInt(),\
                        obj.value("name").toString(),obj.value("type").toInt(),
obj.value("desc").toString(),obj.value("imgSrc").toString(),obj.value("x").toDouble(),obj.value("y").toDouble()};
     */
    //QJsonObject 　不适合大量修改
//    QJsonObject obj;
//    obj.insert("index",point.index);
//    obj.insert("name",point.name);
//    obj.insert("type",point.type);
//    obj.insert("desc",point.desc);
//    obj.insert("imgSrc",point.imgSrc);
//    obj.insert("x",point.x);
//    obj.insert("y",point.y);
    this->m_points.append(point);
    this->writeToFile();
}

void MapProfileReader::addNewViewLine(ViewLine &line)
{
    m_lines.append(line);
}

int MapProfileReader::getPointCount()
{
    return m_points.count();
}

int MapProfileReader::getLineCount()
{
    return m_lines.count();
}

void MapProfileReader::addPoint(QPointF point)
{
    ViewPoint p;
    p.desc="";
    p.name="拐点";
    p.index=this->getPointCount();
    p.imgSrc="";
    p.type=4;
    p.x=point.x();
    p.y=point.y();
    m_points.append(p);
    this->writeToFile();
}

QList<ViewPoint> MapProfileReader::getViewPoint()
{
    QList<ViewPoint> ps;
    for(auto i:m_points){
        if(i.type!=5){
            ps.append(i);
        }
    }
    return ps;
}
