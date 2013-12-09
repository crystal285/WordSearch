#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "concretesearch.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void on_leInputWord_textChanged(const QString & text );
    void on_pbSearch_clicked();
    void on_sbPrefix_valueChanged( int i ){prefix = i ;searchWordChoice=-1;}
    void on_sbBER_valueChanged ( int i ){ber = i;searchWordChoice=-1;}
    void on_sbBERPR_valueChanged ( int i ){berpr = i;searchWordChoice=-1;}
private:
    int getSearchWordChoice();
    void setSearchWordAlgorithm();
private:
    int searchWordChoice;
    int prefix;
    int ber;
    int berpr;
    Ui::MainWindow *ui;
    ConcreteSearch* cs;
};

#endif // MAINWINDOW_H
