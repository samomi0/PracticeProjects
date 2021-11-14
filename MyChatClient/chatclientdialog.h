#ifndef CHATCLIENTDIALOG_H
#define CHATCLIENTDIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class ChatClientDialog; }
QT_END_NAMESPACE

class ChatClientDialog : public QDialog
{
    Q_OBJECT

public:
    ChatClientDialog(QWidget *parent = nullptr);
    ~ChatClientDialog();

private slots:
    //connect button
    void on_btn_Connect_clicked();
    //disconnect button
    void on_btn_Disconnect_clicked();
    //send button
    void on_btn_sendMsg_clicked();
    //connect with server
    void onConnected();
    //disconnect with server
    void onDisconnected();
    //receive msg from server
    void onRecvMsg();
    //error occured
    void onError();
private:
    Ui::ChatClientDialog *ui;
    //status
    bool isOnline;
    //client socket
    QTcpSocket tcpSocket;
    //serverIP
    QHostAddress serverIP;
    //serverPort
    quint16 serverPort;
    //username
    QString userName;
    //msg buffer
    QByteArray buf;
    QString msgStr;
};
#endif // CHATCLIENTDIALOG_H
