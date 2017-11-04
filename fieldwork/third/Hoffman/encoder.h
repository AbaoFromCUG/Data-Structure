#ifndef ENCODER_H
#define ENCODER_H
#include<QFile>
#include<QDataStream>
#include <QObject>
struct HoffmanNode
{
    HoffmanNode* parent;
    HoffmanNode* right;
    HoffmanNode* left;
    long long weight;
    unsigned char key;
    HoffmanNode(long long aw=0,HoffmanNode* right=0,HoffmanNode* left=0) {
        weight=aw;
        this->right=right;
        this->left=left;
        if(this->left){
            this->left->parent=this;
        }
        if(this->right){
            this->right->parent=this;
        }
        this->parent=0;
    }
    bool isLastNode(){
        return !(right||left);
    }

    void setKey(char c){
        key=c;
    }
    ~HoffmanNode(){
        if(right){
            delete right;
        }
        if(left){
            delete left;
        }
    }
};
class EnCoder : public QObject
{
    Q_OBJECT
public:
    explicit EnCoder(QObject *parent = nullptr);


signals:
    void signal_enCoder(int status);

public slots:
    void enCodeFile(QString fromName,QString toName);
protected:
    void count();       //一次读入1024000
    void makeMap();
    void initCountArray();
    void enCode();
    unsigned char toUChar(const QString& str);
    QString getMessage();     //序列化
protected:
    qint64 countArray[256];
    QString enCodeMap[256];
    QString m_fromName;
    QString m_toName;

};

#endif // ENCODER_H
