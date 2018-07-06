#ifndef CCOMMONWIDGET_H
#define CCOMMONWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QLayout>
#include <QtGui/QLabel>
#include <QtGui/QToolButton>
#include <windows.h>

#define DEF_NOCLIENT_SIZE		5

//��������ö��
enum ENUM_CommonWndFlag
{
    enum_GGWndFrameHint			 = 0x00000000,          // Ĭ��
	enum_GGWndTitlebarHint		 = 0x00000001,          // ֧�ֱ�����
    enum_GGWndResizeHint         = 0x00000002,          // ֧����ק�Ŵ���С
    enum_GGWndMinimizeButtonHint = 0x00000004,          // ֧����С����ť
    enum_GGWndMaximizeButtonHint = 0x00000008,          // ֧����󻯰�ť
    enum_GGWndCloseButtonHint    = 0x00000010,          // �йرհ�ť
	enum_GGWndDragMove           = 0x00000020,          // ֧��ȫ���϶�
	enum_GGWndNoActive           = 0x00000040,          // �������
	enum_GGWndSysBackground      = 0x00000080,          // ϵͳ����
	enum_GGWndMenuHint           = 0x00000100,          // ϵͳ�˵�

	enum_GGApplication = enum_GGWndMenuHint|enum_GGWndTitlebarHint | enum_GGWndResizeHint | enum_GGWndMinimizeButtonHint| enum_GGWndMaximizeButtonHint | enum_GGWndCloseButtonHint,

};    

Q_DECLARE_FLAGS(CommonWndFlags,ENUM_CommonWndFlag)
Q_DECLARE_OPERATORS_FOR_FLAGS(CommonWndFlags)

typedef struct _MARGINS
{
    int cxLeftWidth;      // width of left border that retains its size
    int cxRightWidth;     // width of right border that retains its size
    int cyTopHeight;      // height of top border that retains its size
    int cyBottomHeight;   // height of bottom border that retains its size
} MARGINS, *PMARGINS;

class CCommonWidget : public QWidget
{
	Q_OBJECT

public:
	CCommonWidget(QWidget *parent, CommonWndFlags WndFlag, Qt::WindowFlags f = 0);
	virtual ~CCommonWidget();

	//����Ĭ�ϱ�������ϵͳ��ť
	void CreateDefault(long lWndFlag);
	//��ָ����������ť
	void CreateSystemButton(QLayout* layout, CommonWndFlags WndFlag);
	//��ָ��������������
	void CreateSystemTitle(QLayout* layout);

	//���ñ���
	void SetTitle(const WCHAR* pwzTitle);
	//����ϵͳ����������
	void SetTaskBarTitle(const WCHAR* pwzTitle);
	//����Բ��
	void SetRoundCorner(int iSize);
	//���ھ���
	void CenterWindow(QWidget* parent = NULL);
	//������ǰ
	void Foreground(bool abShowFirst = true);

private:
	void MakeRoundCorner();

signals:
    void OnClose();

protected slots:
    void OnMaxClick();
    void OnRestoreClick();
	void OnMinClick();
	virtual void OnSysMenuClick();

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
	QToolButton*                                    m_pSysMenuButton;

protected:
	int												m_iRoundCornerSize;
	QMargins										m_oMaxMargins;
};

#endif // CCOMMONWIDGET_H
