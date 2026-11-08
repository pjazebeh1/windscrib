
#pragma once

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>

class ServersTestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ServersTestWindow(QWidget *parent = nullptr);

private slots:
    void onStartTestClicked();
    void onStopTestClicked();
    void onConnectSelectedClicked();
    void onClearResultsClicked();

private:
    void setupUi();
    void addServerRow(
        const QString &server,
        const QString &protocol,
        const QString &port
    );

    QTableWidget *table_;
    QPushButton *startButton_;
    QPushButton *stopButton_;
    QPushButton *connectButton_;
    QPushButton *clearButton_;
    QLabel *statusLabel_;
    QProgressBar *progressBar_;
};
