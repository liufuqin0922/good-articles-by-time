#include "ToolBar.h"

ToolBar::ToolBar(QWidget *parent)
	: QWidget(parent)
{
	QHBoxLayout *lyToolBar = new QHBoxLayout();
	m_pBtnShareCursor = new QPushButton(this);
	m_pBtnShareCursor ->setText("�����");

	m_pBtnPrev = new QPushButton(this);
	m_pBtnPrev ->setText("��һҳ");
	m_pLblIndex = new QLabel(this);
	m_pLblIndex->setText("1/12");
	m_pBtnNext = new QPushButton(this);
	m_pBtnNext ->setText("��һҳ");
	m_pBtnQuit = new QPushButton(this);
	m_pBtnQuit->setText("�˳�");
	lyToolBar->addWidget(m_pBtnShareCursor);
	lyToolBar->addWidget(m_pBtnPrev);
	lyToolBar->addWidget(m_pLblIndex);
	lyToolBar->addWidget(m_pBtnNext);
	lyToolBar->addWidget(m_pBtnQuit);

	this->setLayout(lyToolBar);
}

ToolBar::~ToolBar()
{

}
