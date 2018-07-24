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
#include <QCheckBox>
#include <QRadioButton>
#include "main_class.h"

main_class::main_class() : QWidget()
{//ui.setupUi(this);
	paths=0;
	addPathButton = new QPushButton("Add dir");
	QIntValidator *sizeValidator = new QIntValidator(0, 1073741824, this);

	sizeMax = new QLineEdit;
	sizeMin = new QLineEdit;
	sizeMax->setValidator(sizeValidator);
	sizeMin->setValidator(sizeValidator);
	sizeMaxBox = new QComboBox;
	sizeMinBox = new QComboBox;
	QStringList dividers = (QStringList() << "B" << "kB" << "MB" << "GB" << "TB");
	sizeMaxBox->addItems(dividers);
	sizeMaxBox->setCurrentIndex(2);
	sizeMinBox->addItems(dividers);
	sizeMinBox->setCurrentIndex(2);


	filesBox = new QCheckBox("files");
	filesBox->setChecked(true);
	foldersBox = new QCheckBox("folders");
	foldersBox->setChecked(true);
	ascDescIBox = new QCheckBox("descending");
	ascDescIIBox = new QCheckBox("descending");
	radioButtonsList = new QRadioButton* [10];
	QRadioButton *button = new QRadioButton("filename");
	radioButtonsList[0] = button;
	button = new QRadioButton("date created");
	radioButtonsList[1] = button;
	button = new QRadioButton("date modified");
	radioButtonsList[2] = button;
	button = new QRadioButton("file size");
	radioButtonsList[3] = button;
	button = new QRadioButton("file path");
	radioButtonsList[4] = button; /////
	button = new QRadioButton("file path");
	radioButtonsList[5] = button;
	button = new QRadioButton("filename");
	radioButtonsList[6] = button;
	button = new QRadioButton("date created");
	radioButtonsList[7] = button;
	button = new QRadioButton("date modified");
	radioButtonsList[8] = button;
	button = new QRadioButton("file size");
	radioButtonsList[9] = button;
	radioButtonsList[0]->setChecked(true);
	radioButtonsList[5]->setChecked(true);
	radioButtonsList[6]->setEnabled(false);

	QGroupBox *typeBox = new QGroupBox("Make packs from:");
	QGridLayout *typeLayout = new QGridLayout;
	typeLayout->addWidget(filesBox, 0, 0);
	typeLayout->addWidget(foldersBox, 0, 1);
	typeBox->setLayout(typeLayout);
	QGroupBox *sortIBox = new QGroupBox("Sort by:");
	QGridLayout *sortILayout = new QGridLayout;
	sortILayout->addWidget(radioButtonsList[0], 0, 0);
	sortILayout->addWidget(radioButtonsList[1], 1, 0);
	sortILayout->addWidget(radioButtonsList[2], 2, 0);
	sortILayout->addWidget(radioButtonsList[3], 3, 0);
	sortILayout->addWidget(radioButtonsList[4], 4, 0);
	sortILayout->addWidget(ascDescIBox, 5,0);
	sortIBox->setLayout(sortILayout);
	QGroupBox *sortIIBox = new QGroupBox("then by:");
	QGridLayout *sortIILayout = new QGridLayout;
	sortIILayout->addWidget(radioButtonsList[5], 0, 0);
	sortIILayout->addWidget(radioButtonsList[6], 1, 0);
	sortIILayout->addWidget(radioButtonsList[7], 2, 0);
	sortIILayout->addWidget(radioButtonsList[8], 3, 0);
	sortIILayout->addWidget(radioButtonsList[9], 4, 0);
	sortIILayout->addWidget(ascDescIIBox, 5,0);
	sortIIBox->setLayout(sortIILayout);
	QGridLayout *sortingLayout = new QGridLayout;
	sortingLayout->addWidget(typeBox, 0,0,1,2);
	sortingLayout->addWidget(sortIBox, 1,0);
	sortingLayout->addWidget(sortIIBox, 1,1);


	listTree = new QTreeWidget;
	listTree->setColumnCount(3);
	listTree->setHeaderLabels(QStringList() << "name" << "size" << "path");
	listTree->setSelectionMode(QAbstractItemView::NoSelection);
	listTree->header()->setMovable(false);
	packTree = new QTreeWidget;
	packTree->setColumnCount(2);
	packTree->setHeaderLabels(QStringList() << "name" << "size");
	packTree->setSelectionMode(QAbstractItemView::NoSelection);
	packTree->header()->setMovable(false);

	pathBox = new QGroupBox("Directories");
	pathLayout = new QGridLayout;
	pathBox->setLayout(pathLayout);
	pathLayout->addWidget(addPathButton, 0, 0, 1, 2);
	addPathLine();	
	sizeBox = new QGroupBox("Size");
	sizeLayout = new QGridLayout;
	sizeLayout->addWidget(sizeMax, 0,0);
	sizeLayout->addWidget(sizeMaxBox, 0,1);
	sizeLayout->addWidget(sizeMin, 0,2);
	sizeLayout->addWidget(sizeMinBox, 0,3);
	sizeBox->setLayout(sizeLayout);

	makeButton = new QPushButton("Make");
	devideButton = new QPushButton("Devide");
	fileList = new list;
	packsList = new packageList;
	layout = new QGridLayout;
	layout->addWidget(pathBox, 0,0);
	layout->addWidget(sizeBox, 1,0);
	layout->addLayout(sortingLayout, 0,1, 2,1);
	layout->addWidget(makeButton, 2,0,1,2);
	setLayout(layout);

	QObject::connect(addPathButton, SIGNAL(clicked()), this, SLOT(addPathLine()));
	QObject::connect(makeButton, SIGNAL(clicked()), this, SLOT(makeList()));
	QObject::connect(devideButton, SIGNAL(clicked()), this, SLOT(handleDevideButton()));

	QObject::connect(radioButtonsList[0], SIGNAL(clicked()), this, SLOT(menageRadioButtons()));
	QObject::connect(radioButtonsList[1], SIGNAL(clicked()), this, SLOT(menageRadioButtons()));
	QObject::connect(radioButtonsList[2], SIGNAL(clicked()), this, SLOT(menageRadioButtons()));
	QObject::connect(radioButtonsList[3], SIGNAL(clicked()), this, SLOT(menageRadioButtons()));
	QObject::connect(radioButtonsList[4], SIGNAL(clicked()), this, SLOT(menageRadioButtons()));
}

main_class::~main_class()
{
	delete addPathButton;
	delete sizeMax;
	delete sizeMin->validator();
	delete sizeMin;
	delete sizeMaxBox;
	delete sizeMinBox;
	listTree->clear();
	delete listTree;
	delete pathLayout;
	delete pathBox;
	delete sizeLayout;
	delete sizeBox;
	delete makeButton;
	delete devideButton;
	delete layout;
	fileList->remAllElem();
	delete fileList;
	delete packsList;
}
void main_class::menageRadioButtons()
{
	if (radioButtonsList[0]->isChecked() || radioButtonsList[4]->isChecked())
	{
		radioButtonsList[5]->setEnabled(true);
		radioButtonsList[6]->setEnabled(true);
		radioButtonsList[7]->setEnabled(true);
		radioButtonsList[8]->setEnabled(true);
		radioButtonsList[9]->setEnabled(true);
		ascDescIIBox->setEnabled(true);
		if (radioButtonsList[0]->isChecked())
			radioButtonsList[6]->setEnabled(false);
		else
			radioButtonsList[5]->setEnabled(false);
	}
	else
	{
		radioButtonsList[5]->setEnabled(false);
		radioButtonsList[6]->setEnabled(false);
		radioButtonsList[7]->setEnabled(false);
		radioButtonsList[8]->setEnabled(false);
		radioButtonsList[9]->setEnabled(false);
		ascDescIIBox->setEnabled(false);
		if (radioButtonsList[1]->isChecked())
			radioButtonsList[7]->setEnabled(false);
		if (radioButtonsList[2]->isChecked())
			radioButtonsList[8]->setEnabled(false);
		if (radioButtonsList[3]->isChecked())
			radioButtonsList[9]->setEnabled(false);
	}
	int i=5;
	while (i < 10)
	{
		if (radioButtonsList[i]->isChecked()  && !radioButtonsList[i]->isEnabled())
		{
			if (i == 5)
				radioButtonsList[6]->setChecked(true);
			else
				radioButtonsList[5]->setChecked(true);
			radioButtonsList[i]->setChecked(false);
		}
		i++;
	}
}
bool main_class::addPathLine()
{
	int i=0;
	while (i < paths)
		if (pathLineList[i++]->text().isEmpty())
		{
			QMessageBox *error = new QMessageBox(this);
			error->setModal(true);
			error->setText("There is still empty line for path.\n");
			error->addButton(QMessageBox::Ok);
			error->exec();
			delete error;
			return false;
		}
	QLineEdit *pathLine = new QLineEdit;
	QPushButton *pathButton = new QPushButton("Open");
	QLineEdit **tmpPathLineList = new QLineEdit* [paths+1];
	QPushButton **tmpPathButtonList = new QPushButton* [paths+1];

	i=0;
	while (i < paths)
	{
		tmpPathLineList[i] = pathLineList[i];
		tmpPathButtonList[i] = pathButtonList[i++];
	}
	tmpPathLineList[i] = pathLine;
	tmpPathButtonList[i] = pathButton;
	if (paths)
	{
	delete [] pathLineList;
	delete [] pathButtonList;
	}
	pathLineList = tmpPathLineList;
	pathButtonList = tmpPathButtonList;

	pathLayout->removeWidget(addPathButton);
	pathLayout->addWidget(pathLine, paths, 0);
	pathLayout->addWidget(pathButton, paths, 1);
	pathLayout->addWidget(addPathButton, paths+1, 0, 1, 2);
	paths++;
	
	QObject::connect(pathButtonList[i], SIGNAL(clicked()), this, SLOT(selectPath()));

	return true;
}
void main_class::selectPath()
{
	QPushButton *button = static_cast <QPushButton*> (sender());
	int i =0;
	while (i < paths && pathButtonList[i] != button)
		i++;
	pathDialog = new QFileDialog(this);
	pathDialog->setFileMode(QFileDialog::DirectoryOnly);
	pathDialog->exec();
	QString qwe = pathDialog->selectedFiles().at(0).toUtf8();
	qwe.append("/");
	pathLineList[i]->setText(qwe);
	delete pathDialog;
}
void main_class::makeList()
{
	int i=0, j=0;
	TCHAR *qw, *path, **pathsList = new TCHAR* [paths];
	while (i < paths)
	{
		if (!pathLineList[i]->text().isEmpty())
		{
			path = new TCHAR [pathLineList[i]->text().size()+1];
			pathLineList[i]->text().toWCharArray(path);
			pathsList[j++]=path;
			qw = _tcsrchr(path, _T('/')) + 1;
			qw[0] = _T('\0');
		}
		i++;
	}
	int len=fileList->getRows();
	fileList->remAllElem();
	delete fileList;
	fileList = new list;
	
	DWORD param = 0x00000000;
	if (filesBox->isChecked())
		param += PACK_FILES;
	if (foldersBox->isChecked())
		param += PACK_FOLDERS;
	if (radioButtonsList[0]->isChecked())
		if (!ascDescIBox->isChecked())
			param += ORDER_I_FILENAME_ASC;
		else
			param += ORDER_I_FILENAME_DESC;
	else if (radioButtonsList[1]->isChecked())
		if (!ascDescIBox->isChecked())
			param += ORDER_I_DATE_CREATED_ASC;
		else
			param += ORDER_I_DATE_CREATED_DESC;
	else if (radioButtonsList[2]->isChecked())
		if (!ascDescIBox->isChecked())
			param += ORDER_I_LAST_MODIFIED_ASC;
		else
			param += ORDER_I_LAST_MODIFIED_DESC;
	else if (radioButtonsList[3]->isChecked())
		if (!ascDescIBox->isChecked())
			param += ORDER_I_SIZE_ASC;
		else
			param += ORDER_I_SIZE_DESC;
	else if (radioButtonsList[4]->isChecked())
		if (!ascDescIBox->isChecked())
			param += ORDER_I_PATH_ASC;
		else
			param += ORDER_I_PATH_DESC;
	if (radioButtonsList[5]->isChecked() && radioButtonsList[5]->isEnabled())
		if (!ascDescIBox->isChecked())
			param += ORDER_II_PATH_ASC;
		else
			param += ORDER_II_PATH_DESC;
	else if (radioButtonsList[6]->isChecked() && radioButtonsList[6]->isEnabled())
		if (!ascDescIBox->isChecked())
			param += ORDER_II_FILENAME_ASC;
		else
			param += ORDER_II_FILENAME_DESC;
	else if (radioButtonsList[7]->isChecked() && radioButtonsList[7]->isEnabled())
		if (!ascDescIBox->isChecked())
			param += ORDER_II_DATE_CREATED_ASC;
		else
			param += ORDER_II_DATE_CREATED_DESC;
	else if (radioButtonsList[8]->isChecked() && radioButtonsList[8]->isEnabled())
		if (!ascDescIBox->isChecked())
			param += ORDER_II_LAST_MODIFIED_ASC;
		else
			param += ORDER_II_LAST_MODIFIED_DESC;
	else if (radioButtonsList[9]->isChecked() && radioButtonsList[9]->isEnabled())
		if (!ascDescIBox->isChecked())
			param += ORDER_II_SIZE_ASC;
		else
			param += ORDER_II_SIZE_DESC;

	makeFileList(fileList, pathsList, j, param);
	i=0;
	while (i < j)
		delete pathsList[i++];
	delete [] pathsList;
	makeVisibleList(fileList);
}
void main_class::makeVisibleList(list *fileList)
{
	int i=0, listLen = fileList->getRows();
	QTreeWidgetItem *treeItem;
	if (layout->indexOf(listTree) != -1)
	{
		layout->removeWidget(listTree);
		listTree->setParent(0);
		layout->removeWidget(devideButton);
		devideButton->setParent(0);
		listTree->clear();
	}
	if (layout->indexOf(packTree) != -1)
	{
		layout->removeWidget(packTree);
		packTree->setParent(0);
		packTree->clear();
	}
	while (i < listLen)
	{
		QString size = (QStringList() << QString::number(fileList->getElem(i)->getSize()/1048576) << "MB").join("");
		treeItem = new QTreeWidgetItem(QStringList() << QString::fromWCharArray(fileList->getElem(i)->getName()) << size << QString::fromWCharArray(fileList->getElem(i)->getPath()));
		treeItem->setTextAlignment(1, Qt::AlignRight);
		listTree->addTopLevelItem(treeItem);
		i++;
	}
	layout->addWidget(listTree, 3,0,1,2);
	layout->addWidget(devideButton, 4,0,1,2);
}

bool main_class::handleDevideButton()
{
	packTree->clear();
	layout->removeWidget(devideButton);
	devideButton->setParent(0);
	layout->removeWidget(listTree);
	listTree->setParent(0);
	listTree->clear();
	verylong maxSize=1024, minSize=1024, tmp=0;
	if (sizeMax->text().isEmpty() || sizeMin->text().isEmpty())
	{
		QMessageBox *error = new QMessageBox(this);
		error->setModal(true);
		error->setText("Specify size limits.\n");
		error->addButton(QMessageBox::Ok);
		error->exec();
		delete error;
		return false;
	}
	maxSize = power(1024, sizeMaxBox->currentIndex()) * (verylong)(sizeMax->text().toInt());
	minSize = power(1024, sizeMinBox->currentIndex()) * (verylong)(sizeMin->text().toInt());
	if (minSize >= maxSize)
	{
		QMessageBox *error = new QMessageBox(this);
		error->setModal(true);
		if (minSize > maxSize)
		{
			error->setText("Minimum size limit is bigger than maximum.\n Do you want to change their places?\n");
			error->setStandardButtons(QMessageBox::Yes);
			error->setStandardButtons(QMessageBox::No);
		}
		else
		{
			error->setText(".Minimum and maximum size limits are equal.\nYou need to specify the size interval.\n");
			error->setStandardButtons(QMessageBox::Ok);
		}
		if (error->exec() == QMessageBox::No || error->exec() == QMessageBox::Ok)
		{
			delete error;
			return false;
		}
		delete error;
		verylong tmp = maxSize;
		maxSize = minSize;
		minSize = tmp;
	}
	delete packsList;
	packsList = makePackList(fileList, maxSize, minSize);
	int i=0, j=0, len = packsList->getRows(), divider=0;
	itemsPack *pack;
	QTreeWidgetItem *item, *parent;
	verylong size=0;
	QColor bgColor(0,0,0);
	while (i < len)
	{
		pack = packsList->getElem(i);
		divider=0;
		size=pack->getSize();
		//while (size / power(1024,divider) > sizeMax->text().toInt())
			divider = sizeMinBox->currentIndex();//++;
		parent = new QTreeWidgetItem(QStringList() << (QStringList() << "pack " << QString::number(i)).join("") << (QStringList() << QString::number(pack->getSize() / power(1024, divider)) << sizeMaxBox->itemText(divider)).join(""));
		parent->setTextAlignment(1, Qt::AlignRight);
		bgColor.setRgb(int((rand()%56)+180),int((rand()%56)+180),int((rand()%56)+180));
		parent->setBackgroundColor(0, bgColor);
		parent->setBackgroundColor(1, bgColor);
		packTree->addTopLevelItem(parent);
		j=0;
		while (j < pack->itemsCount())
		{
			item = new QTreeWidgetItem(QStringList() << QString::fromWCharArray(pack->getItem(j)->getName()) << (QStringList() << QString::number(pack->getItem(j)->getSize() / power(1024, divider)) << sizeMaxBox->itemText(divider)).join(""));
			item->setTextAlignment(1, Qt::AlignRight);
			item->setBackgroundColor(0, bgColor);
			item->setBackgroundColor(1, bgColor);
			parent->addChild(item);
			j++;
		}
		i++;
	}
	i--;
	if (pack->getSize() > maxSize || pack->getSize() < minSize)
		parent->setText(0, "problem items");
	layout->addWidget(packTree, 3,0,1,2);
	return true;
}
