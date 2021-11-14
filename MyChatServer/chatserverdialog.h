#ifndef CHATSERVERDIALOG_H
#define CHATSERVERDIALOG_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class ChatServerDialog; }
QT_END_NAMESPACE

class ChatServerDialog : public QDialog
{
    Q_OBJECT

public:
    ChatServerDialog(QWidget *parent = nullptr);
    ~ChatServerDialog();

private slots:
    //"create server" button
    void on_btn_Create_clicked();
    //"close server" button
    void on_btn_Close_clicked();
    //connect client and save
    void onNewConnect();
    //receive message from client
    void onRecvMsg();
    //send message to target client
    void onSendMsg(const QByteArray& buf);
    //clean bad connection
    void onTimeOut();

private:
    Ui::ChatServerDialog *ui;
    QTcpServer tcpServer;
    //server port
    quint16 PORT;
    //save every client which is connected
    QList<QTcpSocket*> tcpClientList;
    //timer for cleaning bad connection
    QTimer timer;
};
#endif // CHATSERVERDIALOG_H
