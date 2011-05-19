#ifndef FFMPEGUI_H
#define FFMPEGUI_H

#include <QMainWindow>
#include <QProcess>
#include <QByteArray>
#include <QTextBrowser>
#include <QFileDialog>
#include <QDesktopServices>
#include <QComboBox>

namespace Ui {
    class ffmpegui;
}

class ffmpegui : public QMainWindow
{
    Q_OBJECT

public:
    explicit ffmpegui(QWidget *parent = 0);
    ~ffmpegui();

private slots:
    void executeCommand();
    void outputCommand();
    void setSource();
    void setDestination();
    void setPSP();
    void setScreencast();
    void setAndroid();

private:
    Ui::ffmpegui *ui;

    QProcess commandProcess;
};

#endif // FFMPEGUI_H
