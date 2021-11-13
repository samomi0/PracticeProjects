#include "chatserverdialog.h"
#include "ui_chatserverdialog.h"
#include "customException.h"

ChatServerDialog::ChatServerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatServerDialog)
{
    ui->setupUi(this);
    //a signal:newConnect when client want to connect server
    connect(&tcpServer, SIGNAL(newConnect()), this, SLOT(onNewConnect()));
}

ChatServerDialog::~ChatServerDialog()
{
    delete ui;
}
//"create server" button
void ChatServerDialog::on_btn_Create_clicked()
{
    //get port
    PORT = ui->portEdit->text().toUShort();
    //set server listen port
    if(tcpServer.listen(QHostAddress::Any, PORT) == true)
    {
        //enabled create button and portEdit
        ui->btn_Create->setEnabled(false);
        ui->portEdit->setEnabled(false);
        qDebug("Server creation success.");
    }
    else
    {
        qDebug("Server creation failed.");
    }
}
//connect client and save
void ChatServerDialog::onNewConnect()
{
    //TODO:Better storage with client connection
    //get client socket
    QTcpSocket* tcpClient = tcpServer.nextPendingConnection();
    //store socket
    tcpClientList.append(tcpClient);
    //connect client with server
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(onRecvMsg()));
}
//receive message from client
void ChatServerDialog::onRecvMsg()
{

}
//send message to target client
void ChatServerDialog::onSendMsg(const QByteArray& buf)
{

}

