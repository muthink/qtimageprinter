#ifndef DIALOGMAIN_H
#define DIALOGMAIN_H

#include <QDialog>
#include <QFileSystemModel>
#include <QTimer>

namespace Ui {
class DialogMain;
}

class DialogMain : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogMain(QWidget *parent = 0);
    ~DialogMain();
    
private slots:
    void onDirectoryRootPathChanged();
    void on_treeViewDirectories_clicked(const QModelIndex &index);
    void onFileRootPathChanged();
private:
    bool                m_firstDrawn;
    Ui::DialogMain *ui;
    QFileSystemModel    *m_directoryModel;
    QFileSystemModel    *m_fileModel;
    QTimer              m_timer;
};

#endif // DIALOGMAIN_H
