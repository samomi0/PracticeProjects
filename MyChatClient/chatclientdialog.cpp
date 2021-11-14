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
    isOnline = false;
    buf.clear();
    msgStr.clear();
}

ChatClientDialog::~ChatClientDialog()
{
    delete ui;
}


//connect button
void ChatClientDialog::on_btn_Connect_clicked()
{
    //get server Info
    serverIP.setAddress(ui->addressEdit->text());
    serverPort = ui->portEdit->text().toUShort();
    userName = ui->nameEdit->text();
    //try connect
    tcpSocket.connectToHost(serverIP, serverPort);
}
//disconnect button
void ChatClientDialog::on_btn_Disconnect_clicked()
{
    //last msg
    msgStr = "[" + userName + "] is Offline.";
    tcpSocket.write(msgStr.toUtf8());
    msgStr.clear();
    //close socket
    tcpSocket.disconnectFromHost();
}
//send button
void ChatClientDialog::on_btn_sendMsg_clicked()
{
    //get msg
    msgStr = ui->msgEdit->toPlainText();
    ui->msgEdit->clear();
    //check msgStr
    if(msgStr.size() < 1)
    {
        qDebug() << "Cannot send null value";
    }
    else
    {
        msgStr = userName + ":\n" + msgStr;
        tcpSocket.write(msgStr.toUtf8());
    }
}
//connect with server
void ChatClientDialog::onConnected()
{
    //change ui
    ui->btn_Connect->setEnabled(false);
    ui->addressEdit->setEnabled(false);
    ui->portEdit->setEnabled(false);
    ui->nameEdit->setEnabled(false);
    ui->msgEdit->setEnabled(true);
    ui->btn_sendMsg->setEnabled(true);
    //change status
    isOnline = true;

    //first msg
    msgStr = "[" + userName + "] is Online.";
    tcpSocket.write(msgStr.toUtf8());
    msgStr.clear();
}
//disconnect with server
void ChatClientDialog::onDisconnected()
{
    //change ui
    ui->msgEdit->setEnabled(false);
    ui->btn_sendMsg->setEnabled(false);
    ui->addressEdit->setEnabled(true);
    ui->portEdit->setEnabled(true);
    ui->nameEdit->setEnabled(true);
    ui->btn_Connect->setEnabled(true);
    //change status
    isOnline = false;
}
//receive msg from server
void ChatClientDialog::onRecvMsg()
{
    if(tcpSocket.bytesAvailable())
    {
        //get msg
        buf = tcpSocket.readAll();
        //display msg
        ui->listWidget->addItem(buf);
        ui->listWidget->scrollToBottom();
        buf.clear();
    }
}
//error occured
void ChatClientDialog::onError()
{
    //feedback networkError
    QMessageBox::critical(this, "Error:network", tcpSocket.errorString());
}
