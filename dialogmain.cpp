#include "dialogmain.h"
#include "ui_dialogmain.h"
#include <QtPrintSupport/QPrinterInfo>
#include <QSettings>

DialogMain::DialogMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMain)
{
    m_firstDrawn = false;
    QSettings settings;
    ui->setupUi(this);
    QString path = settings.value("lastPath", QVariant("")).toString();
    m_directoryModel = new QFileSystemModel(this);
    m_directoryModel->setFilter(QDir::NoDotAndDotDot|QDir::AllDirs);
    QModelIndex rootIndex = m_directoryModel->setRootPath("");
    QModelIndex index = m_directoryModel->index(path,0);
    //ui->treeViewDirectories->setRootIndex(rootIndex);

    ui->treeViewDirectories->setModel(m_directoryModel);
    ui->treeViewDirectories->hideColumn(1);
    ui->treeViewDirectories->hideColumn(2);
    ui->treeViewDirectories->hideColumn(3);
    ui->treeViewDirectories->hideColumn(4);
    ui->treeViewDirectories->setCurrentIndex(index);
    ui->treeViewDirectories->scrollTo(index,QTreeView::EnsureVisible);

    m_fileModel = new QFileSystemModel(this);
    m_fileModel->setFilter(QDir::NoDotAndDotDot|QDir::Files);
    ui->treeViewSourceFiles->setModel(m_fileModel);
    ui->treeViewSourceFiles->setRootIndex(m_fileModel->setRootPath(path));
    QList<QPrinterInfo> printers = QPrinterInfo::availablePrinters();
    foreach(QPrinterInfo printer, printers)
        ui->comboBoxFilePrinters->addItem(printer.printerName());
    ui->comboBoxFileTypes->addItem("*.tif");

    ui->treeViewDirectories->scrollTo(index,QTreeView::EnsureVisible);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    m_timer.start(1000);
}

DialogMain::~DialogMain()
{
    delete ui;
}

void DialogMain::onTimer()
{
    m_timer.stop();
    QModelIndex index = ui->treeViewDirectories->currentIndex();
    ui->treeViewDirectories->scrollTo(index);
    ui->treeViewSourceFiles->setVisible(false);
    ui->treeViewSourceFiles->resizeColumnToContents(0);
    ui->treeViewSourceFiles->setVisible(true);
}

void DialogMain::on_treeViewDirectories_clicked(const QModelIndex &index)
{
    QString path = m_directoryModel->fileInfo(index).absoluteFilePath();
    ui->treeViewSourceFiles->setRootIndex(m_fileModel->setRootPath(path));
    ui->treeViewSourceFiles->resizeColumnToContents(0);
    QSettings settings;
    settings.setValue("lastPath",path);
}
