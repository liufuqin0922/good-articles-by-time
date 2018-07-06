#ifndef SERVERADDRESSSET_H
#define SERVERADDRESSSET_H

#include <QWidget>
#include "ui_ServerAddressSet.h"

class ServerAddressSet : public QWidget
{
	Q_OBJECT

public:
	ServerAddressSet(QWidget *parent = 0);
	~ServerAddressSet();
	
	static ServerAddressSet *s_instance;
	static ServerAddressSet *GetServerSetInstance();
	
private:
	Ui::ServerAddressSet ui;

	public slots:
		void serverQueDingBtnClicked();/*ȷ��*/
		void serverCancelBtnClicked();/*ȡ��*/

};

#endif // SERVERADDRESSSET_H
