#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAstroid_clicked();
    void on_btnCloud_clicked();
    void on_btnHuygens_clicked();
    void on_btnHypo_clicked();
    void on_btnHeart_clicked();
    void on_Fancy_clicked();
    void on_btnStarfish_clicked();
    void on_btnFSierpinski_clicked();
    void on_btnFMandelbrot_clicked();
    void on_btnFJulia_clicked();
    void on_btnFTree_clicked();
    void on_btnFDragon_clicked();
    void on_spinScale_valueChanged(double arg1);
    void on_spinInterval_valueChanged(double arg1);
    void on_spinCount_valueChanged(int arg1);

    void on_btnBackground_clicked();

    void on_btnLineColor_clicked();

private:
    void update_ui();
    QDoubleSpinBox* mSpinInterval;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
