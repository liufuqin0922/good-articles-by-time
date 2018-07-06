#ifndef CCOMMONDIALOG_H
#define CCOMMONDIALOG_H

#include <QtGui/QDialog>
#include "ccommonwidget.h"

class CCommonDialog : public QDialog
{
	Q_OBJECT

public:
	CCommonDialog(QWidget *parent, CommonWndFlags WndFlag, Qt::WindowFlags f = 0);
	virtual ~CCommonDialog();

	//����Ĭ�ϱ�������ϵͳ��ť
	void CrateDefault(long lWndFlag);
	//��ָ����������ť
	void CrateSystemButton(QLayout* layout, CommonWndFlags WndFlag);
	//��ָ��������������
	void CrateSystemTitle(QLayout* layout);

	//���ñ���
	void SetTitle(const WCHAR* pwzTitle);
	//����ϵͳ����������
	void SetTaskBarTitle(const WCHAR* pwzTitle);
	//����Բ��
	void SetRoundCorner(int iSize);
	//���ھ���
	void CenterWindow(QWidget* parent = NULL);

private:
	void MakeRoundCorner();

signals:
    void OnClose();

protected slots:
    void OnMaxClick();
    void OnRestoreClick();
	void OnMinClick();

protected:
	virtual bool winEvent (MSG* msg, long *result);
	virtual void resizeEvent (QResizeEvent* event);
	virtual void paintEvent (QPaintEvent* event);

	virtual void OnPaint(QPainter* painter);

private:
	CommonWndFlags									m_lWndFlag;
	QLabel*											m_pTitleLabel;
	QLayout*										m_pTitleLayout;
	QToolButton*									m_pCloseButton;
	QToolButton*									m_pMaxButton;
	QToolButton*									m_pRestoreButton;
	QToolButton*									m_pMinButton;

private:
	int												m_iRoundCornerSize;
	QMargins										m_oMaxMargins;
};

#endif // CCOMMONDIALOG_H
