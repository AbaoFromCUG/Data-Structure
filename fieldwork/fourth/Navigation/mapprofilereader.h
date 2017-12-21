#ifndef MAPPROFILEREADER_H
#define MAPPROFILEREADER_H
#include<QString>
#include<QJsonObject>
#include<QFile>
#include<QJsonDocument>
#include<QJsonParseError>
#include<QList>
#include<QPointF>
#include<QLineF>
#include<QTextStream>
#include<QJsonArray>
//单例模式
//饿汉模式
struct ViewPoint{
    int index;
    QString name;   //名称
    int type;
    QString desc;   //描述
    QString imgSrc; //图片样例(可选)
    double x;
    double y;
    static ViewPoint fromJsonObject(QJsonObject& obj){
        if(obj.value("index").isUndefined()\
         ||!obj.value("name").isString()\
         ||obj.value("type").isUndefined()\
         ||!obj.value("desc").isString()\
         ||!obj.value("x").isDouble()\
         ||!obj.value("y").isDouble())
            throw "error";
        else{
            return ViewPoint{obj.value("index").toInt(),\
                        obj.value("name").toString(),obj.value("type").toInt(),obj.value("desc").toString(),obj.value("imgSrc").toString(),obj.value("x").toDouble(),obj.value("y").toDouble()};
        }
    }
};

struct ViewLine{
    int fromIndex;
    int toIndex;
    static ViewLine fromJsonObject(QJsonObject& obj){
        if(!obj.value("fromIndex").isObject()\
         ||!obj.value("toIndex").isObject()){
            throw "error";
        }else {
            return ViewLine{obj.value("fromIndex").toInt(),obj.value("toIndex").toInt()};
        }
    }
};

class MapProfileReader
{ //existsexistsexists
public:
    bool isFileExists();
    QString getFileName() const;
    void setFileName(const QString &value);
    static MapProfileReader* getInstance();


    QString getMapImg();
    QList<ViewPoint>& getAllPoint();
    QList<ViewLine>& getAllLine();
    void addNewViewPoint(ViewPoint& point);
    void addNewViewLine(ViewLine& line);
    int getPointCount();
    int getLineCount();
    void addPoint(QPointF point);

    QList<ViewPoint> getViewPoint();
private:
    MapProfileReader();
    void refresh();
    MapProfileReader static *m_reader;
    QString m_fileName;
    int m_iPointCount;
    QString m_imgSrc;

    QList<ViewPoint> m_points;
    QList<ViewLine> m_lines;
protected:
    QJsonObject getInitObject();

    void writeToFile();

};

#endif // MAPPROFILEREADER_H
