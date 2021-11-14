#include "chatserverdialog.h"
#include "ui_chatserverdialog.h"
#include "customException.h"

ChatServerDialog::ChatServerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatServerDialog)
{
    ui->setupUi(this);
    //a signal:newConnect when client want to connect server
    connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnect()));
    //timer init
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
}

ChatServerDialog::~ChatServerDialog()
{
    delete ui;
}
//clean bad connection
void ChatServerDialog::onTimeOut()
{
    //check client sockets, remove the unconnected
    for(auto it : tcpClientList)
    {
        if(it->state() == QAbstractSocket::UnconnectedState)
        {
            tcpClientList.removeOne(it);
            qDebug("server has removed one Client.");
        }
    }
}
//"create server" button
void ChatServerDialog::on_btn_Create_clicked()
{
    //get port
    PORT = ui->portEdit->text().toUShort();
    //set server listen port
    if(tcpServer.listen(QHostAddress::Any, PORT) == true)
    {
        //disabled create button and portEdit
        ui->btn_Create->setEnabled(false);
        ui->portEdit->setEnabled(false);
        //start timer:every 5s
        timer.start(5000);

        qDebug() << "Server creation success.Port:" << PORT;
    }
    else
    {
        qDebug("Server creation failed.");
    }
}
//"close server" button
void ChatServerDialog::on_btn_Close_clicked()
{
    //clean client list
    tcpClientList.clear();
    //close socket
    tcpServer.close();
    //enabled create button and portEdit
    ui->portEdit->setEnabled(true);
    ui->btn_Create->setEnabled(true);
    //stop timer
    timer.stop();

    qDebug("Server closed.");
}
//connect client and save
void ChatServerDialog::onNewConnect()
{
    /* TODO:
     * 1.Better storage with client connection
    */
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
    /* TODO:
     * 1.Better search: O(1)search?
     * 2.Better read: large files/data could be transmited
     * 3.sql store: save chat history
    */
    for(auto it : tcpClientList)
    {
        if(it->bytesAvailable())
        {
            QByteArray buf = it->readAll();

            //TEST:server list display msg
            ui->listWidget->addItem(buf);
            ui->listWidget->scrollToBottom();

            onSendMsg(buf);
            break;
        }
    }
}
//send message to client
void ChatServerDialog::onSendMsg(const QByteArray& buf)
{
    /* TODO:
     * 1.only send msg to target client
    */
    //send msg to all
    for(auto it : tcpClientList)
    {
        it->write(buf);
    }
}

