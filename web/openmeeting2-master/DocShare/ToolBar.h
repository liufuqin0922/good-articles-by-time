#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>
#include <QWidget>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

class ToolBar :public QWidget
{
	Q_OBJECT

public:
	ToolBar(QWidget *parent);
	~ToolBar();

public:
	QPushButton * m_pBtnShareCursor;
	QPushButton * m_pBtnQuit;
	//��һҳ
	QPushButton * m_pBtnPrev; 
	QPushButton * m_pBtnNext;
	//��ʾ��ǰҳ�����/��ҳ��
	QLabel      * m_pLblIndex;
};

#endif // TOOLBAR_H
