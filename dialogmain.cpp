#include "dialogmain.h"
#include "ui_dialogmain.h"
#include <QPrinterInfo>
//#include <QtPrintSupport/QPrinterInfo>
#include <QSettings>

DialogMain::DialogMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMain)
{
    ui->setupUi(this);

    m_firstDrawn = false;
    m_directoryModel = new QFileSystemModel(this);
    m_directoryModel->setFilter(QDir::NoDotAndDotDot|QDir::AllDirs);
    //ui->treeViewDirectories->setRootIndex(rootIndex);

    ui->treeViewDirectories->setModel(m_directoryModel);
    ui->treeViewDirectories->hideColumn(1);
    ui->treeViewDirectories->hideColumn(2);
    ui->treeViewDirectories->hideColumn(3);
    ui->treeViewDirectories->hideColumn(4);

    m_fileModel = new QFileSystemModel(this);
    m_fileModel->setFilter(QDir::NoDotAndDotDot|QDir::Files);
    ui->treeViewSourceFiles->setModel(m_fileModel);
    QList<QPrinterInfo> printers = QPrinterInfo::availablePrinters();
    foreach(QPrinterInfo printer, printers)
        ui->comboBoxFilePrinters->addItem(printer.printerName());
    ui->comboBoxFileTypes->addItem("*.tif");

   // connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
   // m_timer.start(2000);
    connect(m_directoryModel, SIGNAL(rootPathChanged(QString)),this,SLOT(onDirectoryRootPathChanged()));
    QModelIndex rootIndex = m_directoryModel->setRootPath("");

    //QTimer::singleShot(0, this, SLOT(onTimer()));
}

DialogMain::~DialogMain()
{
    delete ui;
}

void DialogMain::onDirectoryRootPathChanged()
{
   // m_timer.stop();
    QSettings settings;

    QString path = settings.value("lastPath", QVariant("")).toString();
    QModelIndex index = m_directoryModel->index(path,0);
    ui->treeViewDirectories->setCurrentIndex(index);
    ui->treeViewDirectories->scrollTo(index,QAbstractItemView::EnsureVisible);
    ui->treeViewSourceFiles->setRootIndex(m_fileModel->setRootPath(path));
}

void DialogMain::onFileRootPathChanged()
{
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
