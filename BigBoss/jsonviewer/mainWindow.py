from    PyQt5.QtWidgets import *
from    PyQt5.QtCore import *

from PyQt5.QtGui import *
import  os
from mainWindow_ui import  *

import json

from JsonParser.Parser import *
class mainWindow(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)
        self.ui=Ui_MainWindow()
        self.ui.setupUi(self)
        self.setWindowTitle("JSON Viewer---untitle")
        self.m_fileName = ""
        self.initLogic()

    def slot_newFile(self):
        newfileName=QFileDialog.getSaveFileName(self,"New File",QStandardPaths.writableLocation(QStandardPaths.DesktopLocation),"*.json")[0]
        # print(os.path.splitext(newfileName))
        if newfileName=='':
            QMessageBox.warning(self,"Warning","You have not choose file")
            return

        elif os.path.splitext(newfileName)[1]!='.json':
            newfileName=newfileName+'.json'
        if os.path.isfile(newfileName):
            btn=QMessageBox.question(self,"警告","文件已经存在，是否覆盖?",QMessageBox.Yes|QMessageBox.No|QMessageBox.Cancel)
            if btn==QMessageBox.Yes:
                # choose Yse
                os.remove(newfileName)
                os.mknod(newfileName)
            elif btn==QMessageBox.Cancel:
                # choose Cancel
                return
        else:
            os.mknod(newfileName)
        self.m_fileName=newfileName
        self.updateFile()
        self.updateTitle()


    def updateTitle(self):
        if self.m_fileName=='':
            self.setWindowTitle("JSON Viewer---untitle")
        else:
            self.setWindowTitle("JsonViewer---%s"%QFile(self.m_fileName).fileName())
    def slot_openFile(self):
        newfileName=QFileDialog.getOpenFileName(self,"Open File",QStandardPaths.writableLocation(QStandardPaths.DesktopLocation),"*.json")[0]
        if newfileName=='':
            QMessageBox.warning(self,"Warning","You have not choose file")
        else:
            self.m_fileName=newfileName
            print("open file %s"%newfileName)
            self.updateTitle()
            self.updateFile()

    def slot_saveFile(self):
        #save file
        #self.updateFile(True)

        if self.m_fileName=='':
            newfileName = QFileDialog.getSaveFileName(self, "Open File",
                                                      QStandardPaths.writableLocation(QStandardPaths.DesktopLocation),
                                                      "*.json")[0]
            if newfileName=='':
                QMessageBox.warning(self, "Warning", "You have not choose file")
            elif not os.path.isfile(newfileName):
                try:
                    os.mknod(newfileName)
                except:
                    print("error when save file %s"%newfileName)
                    return
                self.m_fileName = newfileName
        else:
            try:
                with open(self.m_fileName,'w') as f:
                    f.write(self.ui.textEdit.toPlainText())
            except:
                print("error when write change to %s"%self.m_fileName)


    def slot_reloadFile(self):
        self.updateFile()

    def slot_otherSave(self):
        newFileName=QFileDialog.getSaveFileName(self,"Open File",QStandardPaths.writableLocation(QStandardPaths.DesktopLocation),"*.json")[0]
        if newFileName=='':
            QMessageBox.warning(self, "Warning", "You have not choose file")
            return
        elif os.path.splitext(newFileName)[1]!='.json':
            newFileName=newFileName+'.json'
        elif not os.path.isfile(newFileName):
            try:
                os.mknod(newFileName)
            except:
                print("error when other save file %s" % newFileName)
                return
        else:
            btn = QMessageBox.question(self, "警告", "文件已经存在，是否覆盖?",
                                       QMessageBox.Yes | QMessageBox.No | QMessageBox.Cancel)
            if btn == QMessageBox.Yes:
                # choose Yse
                os.remove(newFileName)
                os.mknod(newFileName)
            elif btn == QMessageBox.Cancel:
                # choose Cancel
                return
        try:
            with open(newFileName,'w') as f:
                f.write(self.ui.textEdit.toPlainText())
        except:
            print("error when other write file %s"%newFileName)
    def updateFile(self,isSave=False):
        if self.m_fileName=='':
            print("fileName is Null")
            return

        """
        if isSave==True:
            save
        else:
            upload
        :param isSave:
        :return:
        """
        if isSave:
            t='w'
        else:
            t='r'
        f=open(self.m_fileName,t)
        if isSave:
            f.write(self.ui.textEdit.toPlainText())
        else:
            self.ui.textEdit.setText(f.read())

    def initLogic(self):
        """
        init Logic


        :return:
        """
        self.ui.tree_json.setHeaderLabels(["Key", "Values","Type"])
        self.ui.tree_json.header().setStretchLastSection(True)
        self.ui.tree_json.header().setSectionResizeMode(QHeaderView.ResizeToContents)
        self.ui.action_newFile.triggered.connect(self.slot_newFile)
        self.ui.action_saveFile.triggered.connect(self.slot_saveFile)
        self.ui.action_openFile.triggered.connect(self.slot_openFile)
        self.ui.action_otherSaveFile.triggered.connect(self.slot_otherSave)
        self.ui.textEdit.textChanged.connect(self.slot_decodeBtn)


        self.ui.action_beautifulJSON.triggered.connect(self.slot_actionJsonFormat)
        self.ui.action_JSONPath.triggered.connect(self.slot_actionJsonPath)
        self.ui.action_JSONTree.triggered.connect(self.slot_actionJsonTree)

    def keyPressEvent(self, a0: QtGui.QKeyEvent):
        if a0.key()==Qt.Key_S:
            self.slot_saveFile()
            print("save change to %s"%self.m_fileName)

    def slot_actionJsonPath(self):
        self.ui.pageList.setCurrentIndex(1)

    def slot_actionJsonTree(self):
        self.ui.pageList.setCurrentIndex(0)

    def slot_actionJsonFormat(self):
        self.ui.pageList.setCurrentIndex(2)

    def slot_decodeBtn(self):
        self.ui.tree_json.clear()
        try:
            _dir = json.loads(self.ui.textEdit.toPlainText())
        except :
            print("Json format is error")
            return

        root=QTreeWidgetItem(self.ui.tree_json)
        for item in _dir.items():
            childItem=QTreeWidgetItem(root)
            childItem.setText(0,item[0])
            self.addToObj(item[1],childItem)
            pass
        # self.ui.tree_json.setItemsExpandable(False)
        self.ui.tree_json.expandAll(),

    def addToObj(self,ob,item):
        if isinstance(ob,dict):
            item.setText(2,"Object")
            item.setIcon(0,QIcon("./img/brackets_obj.png"))
            for t in ob.items():
                childItem=QTreeWidgetItem(item)
                childItem.setText(0,t[0])
                self.addToObj(t[1],childItem)
                pass
        elif isinstance(ob,list):
            item.setText(2,"Array")
            item.setIcon(0,QIcon("./img/brackets_array.png"))
            for t in ob:
                childItem=QTreeWidgetItem(item)
                self.addToObj(t,childItem)
        elif isinstance(ob,str):
            item.setText(2,"String")
            item.setText(1,"\"%s\""%ob)
        elif isinstance(ob,int) :
            item.setText(2, "Int")
            item.setText(1,"%s"%ob)
        elif isinstance(ob,float):
            item.setText(2, "Float")
            item.setText(1, "%s" % ob)
        pass




