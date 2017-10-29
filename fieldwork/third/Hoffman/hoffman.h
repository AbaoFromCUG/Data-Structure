#ifndef HOFFMAN_H
#define HOFFMAN_H

#include <QObject>
#include<QFile>
#include<QIODevice>
#include<QDebug>
#include<QTextStream>
#include<QDataStream>
struct HoffmanNode
{
    HoffmanNode* parent;
    HoffmanNode* right;
    HoffmanNode* left;
    long long weight;
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

    ~HoffmanNode(){
        if(right){
            delete right;
        }
        if(left){
            delete left;
        }
    }
};

class Hoffman : public QObject
{
    Q_OBJECT
public:
    explicit Hoffman(QObject *parent = nullptr);
    ~Hoffman();

signals:
    void zipSuccess();

public slots:
    void startZip(QString fileName,QString enCodeFileName);
    void startUnZip(QString enCodeFileName,QString fileName);
protected:
    void count();
    void makeTree();
    void enCodeFile();
    void deCodeFile();
    void initCountArray();

    QString getString();
private:
    QString fileName;
    QString enCodeFileName;
    long long countArray[256];
    QString enCodeMap[256];
    HoffmanNode* root;
};

#endif // HOFFMAN_H
