# 关于各个lib的使用方法

## Framless
### qwidget 版本
```cpp
//窗口助手
    FramelessHelper* helper=new FramelessHelper(this);
    helper->activateOn(this);  //激活当前窗体
    helper->setTitleHeight(this->topBar->height());  //设置窗体的标题栏高度
    helper->setWidgetMovable(true);  //设置窗体可移动
    helper->setWidgetResizable(true);  //设置窗体可缩放
    helper->setRubberBandOnMove(false);  //设置橡皮筋效果-可移动
    helper->setRubberBandOnResize(false);  //设置橡皮筋效果-可缩放


```


### qml版本

* 如果是主窗口

```cpp
QQmlApplicationEngine engine;
engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

if (engine.rootObjects().isEmpty())
    return -1;
FramelessWindowHelper helper(&engine);

// 主窗口必须以这种方式
helper.addWindow("MainWindow");
```
* 如果不是主窗口

```qml
ApplicationWindow {
    objectName: "TestPage"

    //flags: Qt.FramelessWindowHint | Qt.Window | Qt.WindowMinimizeButtonHint
    // 非主窗口可以采用此种方式
    Component.onCompleted: FramelessWindowHelper.addWindow(objectName)
    ...
}
```
