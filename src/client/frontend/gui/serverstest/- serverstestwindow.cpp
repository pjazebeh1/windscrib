
#include "serverstestwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QMessageBox>
#include <QApplication>

ServersTestWindow::ServersTestWindow(QWidget *parent)
    : QDialog(parent),
      table_(nullptr),
      startButton_(nullptr),
      stopButton_(nullptr),
      connectButton_(nullptr),
      clearButton_(nullptr),
      statusLabel_(nullptr),
      progressBar_(nullptr)
{
    setupUi();
}

void ServersTestWindow::setupUi()
{
    setWindowTitle("Windscribe - Server Connection Test");
    resize(1050, 600);
    setMinimumSize(800, 450);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel(
        "Server Connection Tester", this
    );

    QFont titleFont = titleLabel->font();
    titleFont.setBold(true);
    titleFont.setPointSize(titleFont.pointSize() + 3);
    titleLabel->setFont(titleFont);

    mainLayout->addWidget(titleLabel);

    table_ = new QTableWidget(this);
    table_->setColumnCount(6);

    table_->setHorizontalHeaderLabels({
        "Server",
        "Protocol",
        "Port",
        "Latency",
        "Status",
        "Details"
    });

    table_->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents
    );

    table_->horizontalHeader()->setStretchLastSection(true);

    table_->setSelectionBehavior(
        QAbstractItemView::SelectRows
    );

    table_->setSelectionMode(
        QAbstractItemView::SingleSelection
    );

    table_->setEditTriggers(
        QAbstractItemView::NoEditTriggers
    );

    table_->setAlternatingRowColors(true);

    mainLayout->addWidget(table_);

    progressBar_ = new QProgressBar(this);
    progressBar_->setRange(0, 100);
    progressBar_->setValue(0);

    mainLayout->addWidget(progressBar_);

    statusLabel_ = new QLabel(
        "Ready - No tests started", this
    );

    mainLayout->addWidget(statusLabel_);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    startButton_ = new QPushButton(
        "Start Test", this
    );

    stopButton_ = new QPushButton(
        "Stop Test", this
    );

    connectButton_ = new QPushButton(
        "Connect Selected", this
    );

    clearButton_ = new QPushButton(
        "Clear Results", this
    );

    buttonLayout->addWidget(startButton_);
    buttonLayout->addWidget(stopButton_);
    buttonLayout->addWidget(connectButton_);
    buttonLayout->addWidget(clearButton_);

    mainLayout->addLayout(buttonLayout);

    connect(
        startButton_,
        &QPushButton::clicked,
        this,
        &ServersTestWindow::onStartTestClicked
    );

    connect(
        stopButton_,
        &QPushButton::clicked,
        this,
        &ServersTestWindow::onStopTestClicked
    );

    connect(
        connectButton_,
        &QPushButton::clicked,
        this,
        &ServersTestWindow::onConnectSelectedClicked
    );

    connect(
        clearButton_,
        &QPushButton::clicked,
        this,
        &ServersTestWindow::onClearResultsClicked
    );

    stopButton_->setEnabled(false);
    connectButton_->setEnabled(false);
}

void ServersTestWindow::addServerRow(
    const QString &server,
    const QString &protocol,
    const QString &port
)
{
    int row = table_->rowCount();

    table_->insertRow(row);

    table_->setItem(
        row, 0, new QTableWidgetItem(server)
    );

    table_->setItem(
        row, 1, new QTableWidgetItem(protocol)
    );

    table_->setItem(
        row, 2, new QTableWidgetItem(port)
    );

    table_->setItem(
        row, 3, new QTableWidgetItem("--")
    );

    table_->setItem(
        row, 4, new QTableWidgetItem("Not tested")
    );

    table_->setItem(
        row, 5, new QTableWidgetItem("--")
    );
}

void ServersTestWindow::onStartTestClicked()
{
    QMessageBox::information(
        this,
        "Server Test",
        "The real VPN testing engine will be "
        "implemented in the next step."
    );

    statusLabel_->setText(
        "Waiting for the testing engine"
    );
}

void ServersTestWindow::onStopTestClicked()
{
    statusLabel_->setText(
        "Test stopped"
    );

    stopButton_->setEnabled(false);
    startButton_->setEnabled(true);
}

void ServersTestWindow::onConnectSelectedClicked()
{
    int row = table_->currentRow();

    if (row < 0) {
        QMessageBox::warning(
            this,
            "Select Server",
            "Please select a server first."
        );

        return;
    }

    QMessageBox::information(
        this,
        "Connect",
        "Connection through the selected server "
        "will be implemented in the next step."
    );
}

void ServersTestWindow::onClearResultsClicked()
{
    table_->setRowCount(0);

    progressBar_->setValue(0);

    statusLabel_->setText(
        "Results cleared"
    );

    connectButton_->setEnabled(false);
    stopButton_->setEnabled(false);
    startButton_->setEnabled(true);
}
