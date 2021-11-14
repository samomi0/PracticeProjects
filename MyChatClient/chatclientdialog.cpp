#include "chatclientdialog.h"
#include "ui_chatclientdialog.h"

ChatClientDialog::ChatClientDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatClientDialog)
{
    ui->setupUi(this);
    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(onRecvMsg()));
    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError()));
}

ChatClientDialog::~ChatClientDialog()
{
    delete ui;
}


//connect button
void ChatClientDialog::on_btn_Connect_clicked()
{

}
//disconnect button
void ChatClientDialog::on_btn_Disconnect_clicked()
{

}
//send button
void ChatClientDialog::on_btn_sendMsg_clicked()
{

}
//connect with server
void ChatClientDialog::onConnected()
{

}
//disconnect with server
void ChatClientDialog::onDisconnected()
{

}
//receive msg from server
void ChatClientDialog::onRecvMsg()
{

}
//error occured
void ChatClientDialog::onError()
{

}
