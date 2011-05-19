#include "ffmpegui.h"
#include "ui_ffmpegui.h"

ffmpegui::ffmpegui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ffmpegui)
{
    connect (&commandProcess, SIGNAL(readyReadStandardOutput()),this, SLOT(outputCommand()));
    connect (&commandProcess, SIGNAL(readyReadStandardError()),this, SLOT(outputCommand()));

    ui->setupUi(this);
}

ffmpegui::~ffmpegui()
{
    delete ui;
}

void ffmpegui::setDestination(){
    QString file = QFileDialog::getSaveFileName (this, tr("Select Destination"),
                   QDesktopServices::storageLocation(QDesktopServices::MoviesLocation));
    ui->destPath->setText(file);

}

void ffmpegui::setSource(){
    QString file = QFileDialog::getOpenFileName(this, tr("Select Source File"),
                   QDesktopServices::storageLocation(QDesktopServices::MoviesLocation));
    ui->sourcePath->setText(file);
}

void ffmpegui::setScreencast()
{
    QStringList resol, arates, vrates;
    resol << "640x480" << "800x600" << "1024x768" << "1280x1024";
    arates << "10" << "30" << "50" << "70" << "100";
    vrates << "23.98" << "24" << "25" << "29.97" << "30";
    ui->comboResolution->clear();
    ui->comboFramerate->clear();
    ui->comboBitrate->clear();
    ui->comboSamplerate->clear();
    ui->comboBitdepth->clear();
    ui->comboAbitrate->clear();

    ui->abitrate->setText("Audio Quality");

    ui->comboResolution->addItems(resol);

    ui->comboFramerate->addItems(vrates);
    //ui->comboBitrate->addItem("1500");
    //ui->comboSamplerate->addItem("2400");
    ui->comboAbitrate->addItems(arates);
    ui->destPath->setText("outScreencast.mp4");

}

void ffmpegui::setPSP()
{
    ui->comboResolution->clear();
    ui->comboFramerate->clear();
    ui->comboBitrate->clear();
    ui->comboSamplerate->clear();
    ui->comboBitdepth->clear();
    ui->comboAbitrate->clear();

    ui->abitrate->setText("Bitrate");

    ui->comboResolution->addItem("240x320");
    ui->comboResolution->addItem("160x120");
    ui->comboFramerate->addItem("29.97");
    ui->comboBitrate->addItem("1500");
    ui->comboSamplerate->addItem("2400");
    ui->comboAbitrate->addItem("65535");
    ui->destPath->setText("outPSP.mp4");

}



void ffmpegui::setAndroid(){

    // Set Options which user can change

    ui->comboResolution->clear();
    ui->comboFramerate->clear();
    ui->comboBitrate->clear();
    ui->comboSamplerate->clear();
    ui->comboBitdepth->clear();
    ui->comboAbitrate->clear();

    ui->abitrate->setText("Bitrate");

    ui->comboResolution->addItem("240x320");
    ui->comboResolution->addItem("160x120");
    ui->comboFramerate->addItem("29.97");
    ui->comboBitrate->addItem("1500");
    ui->comboSamplerate->addItem("2400");
    ui->comboAbitrate->addItem("65535");
    ui->destPath->setText("outAndroid.mp4");

}


void ffmpegui::executeCommand()
{
    QStringList args;

    args << "-i";
    args << ui->sourcePath->text();
    args << "-y";
    args << "-s"; args << ui->comboResolution->currentText();
    args << "-r"; args << ui->comboFramerate->currentText();
    args << "-b"; args << ui->comboBitrate->currentText();
    args << "-ar"; args << ui->comboSamplerate->currentText();
    args << "-ab"; args << ui->comboBitrate->currentText();
    args << ui->destPath->text();

    if (ui->psp->isChecked()){
        args << "-vcodec"; args << "libxvid";
        args << "-acodec"; args << "libfaac";
        args << "-ac"; args << "2";
        args << "-f"; args << "psp";
    }

    if(ui->screencast->isChecked()){
        args << "-vcodec"; args << "libx264";
        args << "-acodec"; args << "libfaac";
        args << "-preset"; args << "slow";
        args << "-crf"; args << "22";
        args << "-threads"; args << "0";

    }

    if(ui->android->isChecked()){
        //Add android specific options here

        args << "-vcodec"; args << "libx264";
        args << "-acodec"; args << "libfaac";
    }


    commandProcess.start("ffmpeg", args);

}



void ffmpegui::outputCommand(){
    QByteArray cmdoutput = commandProcess.readAllStandardOutput();
    QString txtoutput = cmdoutput;
    ui->textBrowser->append(txtoutput);
    cmdoutput = commandProcess.readAllStandardError();
    txtoutput = cmdoutput;
    ui->textBrowser->append(txtoutput);
}
