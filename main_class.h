#ifndef MAIN_CLASS_H
#define MAIN_CLASS_H
#include "library.h"
#include <QtGui/QWidget>
#include <QString>
#include <QTextCodec>
#include <QObject>
#include <QPushButton>
#include <QByteArray>
#include <QFileDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QTreeWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>
#include <QCheckBox>
#include <QRadioButton>
#include "ui_main_class.h"

class main_class : public QWidget
{
	Q_OBJECT

public:
	main_class();
	~main_class();

private:
	int paths;
	QLineEdit **pathLineList;
	QPushButton **pathButtonList;
	QPushButton *addPathButton;
	QFileDialog *pathDialog;
	QLineEdit *sizeMax;
	QComboBox *sizeMaxBox;
	QLineEdit *sizeMin;
	QComboBox *sizeMinBox;
	QCheckBox *filesBox;
	QCheckBox *foldersBox;
	QCheckBox *ascDescIBox;
	QCheckBox *ascDescIIBox;
	QRadioButton **radioButtonsList;
	QTreeWidget *listTree;
	QTreeWidget *packTree;
	QPushButton *makeButton;
	QPushButton *devideButton;
	list *fileList;
	packageList *packsList;
	QGridLayout *pathLayout;
	QGridLayout *sizeLayout;
	QGroupBox *pathBox;
	QGroupBox *sizeBox;
	QGridLayout *layout;
	//Ui::main_classClass ui;

private slots:
	bool addPathLine();
	void selectPath();
	void makeList();
	void makeVisibleList(list *fileList);
	bool handleDevideButton();
	void menageRadioButtons();
};

#endif // MAIN_CLASS_H
