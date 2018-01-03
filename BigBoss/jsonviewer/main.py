import sys
from mainWindow import  *


if __name__=="__main__":
    app=QApplication(sys.argv)
    win=mainWindow()
    win.show()
    sys.exit(app.exec_())
    pass

