#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cs = new ConcreteSearch(new Exact_Search());
    searchWordChoice = 0;
    ui->leInputWord->setFocus();
    prefix=10;
    ber=3;
    berpr=3;

}

MainWindow::~MainWindow()
{
    delete ui;
    delete cs;
}
void MainWindow::on_leInputWord_textChanged(const QString &text){
    if(3!=searchWordChoice){
        cs->setSearchWordAlgorithm(new letter_Search(prefix));
        searchWordChoice = 3;
    }
    QString res = cs->searchWord(ui->leInputWord->text().toStdString()).c_str();
    ui->tb_Results->setText(res);
}
void MainWindow::on_pbSearch_clicked(){
    QString s = ui->leInputWord->text();
    setSearchWordAlgorithm();
    QString res =cs->searchWord(s.toStdString()).c_str();
    ui->tb_Results->setHtml(res);
}

int MainWindow::getSearchWordChoice(){
    if(ui->rbExact->isChecked())
        return 0;
    if(ui->rbBER->isChecked())
        return 1;
    if(ui->rbBERPR->isChecked())
        return 2;
}
void MainWindow::setSearchWordAlgorithm(){
    int c = getSearchWordChoice();
    if(c==searchWordChoice)
        return;
    switch(c){
    case 0:
        cs->setSearchWordAlgorithm(new Exact_Search());
        searchWordChoice = 0;
        break;
    case 1:
        cs->setSearchWordAlgorithm(new BER_Search(ber));
        searchWordChoice = 1;
        break;
    case 2:
        cs->setSearchWordAlgorithm(new BER_PR_Search(berpr));
        searchWordChoice = 2;
    }
}
