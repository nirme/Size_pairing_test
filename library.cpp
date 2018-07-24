#include "library.h"

item::item(TCHAR *nameIn, TCHAR *pathIn, verylong sizeIn, FILETIME timeCreated, FILETIME timeModified)
{
	int len = _tcslen(nameIn)+1;
	name = new TCHAR [len];
	StringCchCopy(name, len, nameIn);
	len = _tcslen(pathIn)+1;
	path = new TCHAR [len];
	StringCchCopy(path, len, pathIn);
	size = sizeIn;
	createTime = timeCreated;
	lastModifiedTime = timeModified;
}
item::~item()
{
	delete name;
	delete path;
}
TCHAR* item::getName()
{
	return name;
}
TCHAR* item::getPath()
{
	return path;
}
verylong item::getSize()
{
	return size;
}
FILETIME item::created()
{
	return createTime;
}
FILETIME item::modified()
{
	return lastModifiedTime;
}

list::list()
{
	rows = 0;
	lenght=100;
	size=0;
	items = new item* [lenght];
}
list::~list()
{
	delete [] items;
}
void list::remAllElem()
{
	int i=0;
	while (i < rows)
		delete items[i++];
	rows = 0;
	delete items;
	lenght=100;
	items = new item* [lenght];
	size=0;
}
void list::addElem(item *newItemIn)
{
	if (rows >= lenght)
	{
		lenght+=100;
		item **tmpItems = new item* [lenght];
		int i=0;
		while (i < rows)
			tmpItems[i] = items[i++];
		delete [] items;
		items = tmpItems;
	}
	items[rows] = newItemIn;
	rows++;
	size+=newItemIn->getSize();
}
item* list::getElem(int rowIn)
{
	if (rowIn <rows && rowIn >=0)
		return items[rowIn];
	return 0;
}
int list::getRows()
{
	return rows;
}
verylong list::getSize()
{
	return size;
}
bool list::remElem(int rowIn)
{
	if (rowIn<0 || rowIn>=rows)
		return false;
	int i = rowIn;
	size-=items[i]->getSize();
	while (i < rows)
	{
		items[i] = items[i+1];
		i++;
	}
	rows--;
	return true;
}
bool list::remElem(item *itemIn)
{
	int rowIn=0;
	while (rowIn < rows && items[rowIn] != itemIn)
		rowIn++;
	if (rowIn>=rows)
		return false;
	int i = rowIn;
	size-=items[i]->getSize();
	while (i < rows)
	{
		items[i] = items[i+1];
		i++;
	}
	rows--;
	return true;
}
void list::changeElem(int rowIn, item *newItem)
{
	items[rowIn]=newItem;
}
void list::emptyList()
{
	rows=0;
	size=0;
}
void list::operator= (list *in)
{
	rows = in->getRows();
	size = in->getSize();
	int i=0;
	while (i < rows)
		items[i] = in->getElem(i++);
}

node::node(item *nodeItemIn)
{
	nodeItem=nodeItemIn;
	parent=0;
	childrens=0;
}
node::~node()
{
	if (parent)
		unsetParent();
	int i=0;
	while (i < childrens)
		childs[i++]->setParent(0);
	if (childrens > 0)
		delete [] childs;
}
void node::clear()
{
	int i=0;
	while (i < childrens)
	{
		childs[i]->clear();
		delete childs[i];
		i++;
	}
	childrens=0;
	if (i)
		delete [] childs;
	childs=0;
}
item* node::getNodeItem()
{
	return nodeItem;
}
void node::setParent(node *parentIn)
{
	parent = parentIn;
	//parentIn->addChild(this);
}
node* node::getParent()
{
	return parent;
}
void node::unsetParent()
{
	if (parent != 0)
	{
		parent->removeChild(parent->getChildIndex(this));
		parent = 0;
	}
}
void node::addChild(node *childItemIn)
{
	int i=0;
	node **tmpChilds = new node* [childrens +1];
	while (i< childrens)
		tmpChilds[i] = childs[i++];
	tmpChilds[i] = childItemIn;
	childItemIn->setParent(this);
	if (i)
		delete [] childs;
	childs = tmpChilds;
	childrens++;
}
int node::childCount()
{
	return childrens;
}
node* node::getChild(int index)
{
	if (index < 0 || index >= childrens)
		return 0;
	return childs[index];
}
int node::getChildIndex(node *child)
{
	int i=0;
	while (i < childrens)
	{
		if (childs[i] == child)
			return i;
		i++;
	}
	return -1;
}
bool node::removeChild(int index)
{
	if (index < 0 || index >= childrens)
		return false;
	childs[index]->setParent(0);
	int i=0;
	node **tmpChilds = new node* [childrens-1];
	while (i < index)
		tmpChilds[i] = childs[i++];
	int j=i;
	i++;
	while (i < childrens)
		tmpChilds[j++] = childs[i++];
	delete [] childs;
	childs = tmpChilds;
	childrens--;
	return true;
}
bool node::removeChild(node *child)
{
	return removeChild(getChildIndex(child));
}

itemsPack::itemsPack()
{
	itemCounter=0;
	size=0;
	len=10;
	items = new item* [len];
}
itemsPack::~itemsPack()
{
	delete [] items;
}
int itemsPack::addItem(item *itemIn)
{
	if (itemCounter >= len)
	{
		len+=10;
		item **tmpItems = new item* [len];
		int i=0;
		while (i < itemCounter)
			tmpItems[i] = items[i++];
		delete [] items;
		items = tmpItems;
	}
	items[itemCounter] = itemIn;
	itemCounter++;
	size+=itemIn->getSize();
	return itemCounter;
}
item* itemsPack::getItem(int index)
{
	return items[index];
}
int itemsPack::getItemIndex(item *itemIn)
{
	int i=0;
	while (itemIn != items[i] && i < itemCounter)
		i++;
	if (i >= itemCounter)
		return -1;
	return i;
}
int itemsPack::itemsCount()
{
	return itemCounter;
}
verylong itemsPack::getSize()
{
	return size;
}

packageList::packageList()
{
	rows=0;
}
packageList::~packageList()
{
	int i=0;
	if (rows > 0)
		delete [] itemsPacks;
}
void packageList::removePacks()
{
	int i=0;
	while (i<rows)
		delete itemsPacks[i];
	rows=0;
}
void packageList::addElem(itemsPack *itemsPacksIn)
{
	itemsPack **tmpitemsPacks = new itemsPack* [rows+1];
	int i=0;
	while (i<rows)
		tmpitemsPacks[i] = itemsPacks[i++];
	tmpitemsPacks[i] = itemsPacksIn;
	if (i)
		delete [] itemsPacks;
	itemsPacks = tmpitemsPacks;
	rows++;
}
itemsPack* packageList::getElem(int rowIn)
{
	return itemsPacks[rowIn];
}
int packageList::getRows()
{
	return rows;
}


//funkcje

verylong power(verylong base, int exponent)
{
	if (exponent==0)
		return 1;
	if (base == 0)
		return 0;
	verylong out=1;
	int i=0;
	while (i < exponent)
	{
		out*=base;
		i++;
	}
	return out;
}

verylong getFolderSize(TCHAR *path)
{
	verylong size=0;
	HANDLE hInf = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA *fileInfo = new WIN32_FIND_DATA;
	TCHAR tmpPath[MPL];
	StringCchCopy (tmpPath, MPL, path);
	StringCchCat (tmpPath, MPL, _T("*"));
	hInf = FindFirstFile(tmpPath, fileInfo);
	FindNextFile(hInf, fileInfo);
	while (FindNextFile(hInf, fileInfo) != 0)
	{
		if (fileInfo->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			TCHAR foldPath[MPL];
			StringCchCopy (foldPath, MPL, path);
			StringCchCat (foldPath, MPL, fileInfo->cFileName);
			StringCchCat (foldPath, MPL, _T("//"));
			size+=getFolderSize(foldPath);
		}
		else
			size+=(unsigned long long(fileInfo->nFileSizeHigh) * (unsigned long long(MAXDWORD)+1)) + fileInfo->nFileSizeLow;
	}
	delete fileInfo;
	FindClose(hInf);
	return size;
}
list* addToFileList(list *fileList, TCHAR *path, DWORD param)
{
	item *newItem;	
	HANDLE hInf = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA *fileInfo = new WIN32_FIND_DATA;
	TCHAR tmpPath[MPL];
	StringCchCopy (tmpPath, MPL, path);
	StringCchCat (tmpPath, MPL, _T("*"));
	hInf = FindFirstFile(tmpPath, fileInfo);
//	if (hInf == INVALID_HANDLE_VALUE)
//		return 0;
	FindNextFile(hInf, fileInfo);
	while (FindNextFile(hInf, fileInfo) != 0)
	{
		if ((fileInfo->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (param & PACK_FOLDERS))
		{
			TCHAR foldPath[MPL];
			StringCchCopy (foldPath, MPL, path);
			StringCchCat (foldPath, MPL, fileInfo->cFileName);
			StringCchCat (foldPath, MPL, _T("/"));
			newItem = new item(fileInfo->cFileName, path, getFolderSize(foldPath), fileInfo->ftCreationTime, fileInfo->ftLastWriteTime);
			fileList->addElem(newItem);
		}
		else if (!(fileInfo->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (param & PACK_FILES))
		{
			newItem = new item(fileInfo->cFileName, path, ((unsigned long long(fileInfo->nFileSizeHigh) * (unsigned long long(MAXDWORD)+1)) + fileInfo->nFileSizeLow), fileInfo->ftCreationTime, fileInfo->ftLastWriteTime);
			fileList->addElem(newItem);
		}
	}
	delete fileInfo;
	FindClose(hInf);
	return fileList;
}
list* makeFileList(list *fileList, TCHAR **searchPaths, int queLen, DWORD param)
{
	int i=0, j=queLen;
	if (param & ORDER_I_PATH_DESC)
		while (j>0)
			addToFileList(fileList, searchPaths[--j], param);
	else
		while (i < queLen)
			addToFileList(fileList, searchPaths[i++], param);
	sortFileList(fileList, param);
	return fileList;
}
void sortFileList(list *fileList, DWORD param)
{
	item *tmp;
	if (param & ORDER_I_FILENAME_ASC)
	{
		int i=1, flag=1;
		long long comp=0;
		while (flag)
		{
			flag = 0;
			i=1;
			while (i < fileList->getRows())
			{
				comp = _tcsicmp(fileList->getElem(i-1)->getName(), fileList->getElem(i)->getName());
				if (comp > 0)
				{
					tmp = fileList->getElem(i-1);
					fileList->changeElem(i-1, fileList->getElem(i));
					fileList->changeElem(i, tmp);
					flag = 1;
				}
				else if (comp == 0)
				{
					if (param & ORDER_II_PATH_ASC)
						comp = _tcsicmp(fileList->getElem(i-1)->getPath(), fileList->getElem(i)->getPath());
					else if (param & ORDER_II_PATH_DESC)
						comp = _tcsicmp(fileList->getElem(i)->getPath(), fileList->getElem(i-1)->getPath());
					else if (param & ORDER_II_DATE_CREATED_ASC)
						comp = CompareFileTime(&fileList->getElem(i)->created(), &fileList->getElem(i-1)->created());
					else if (param & ORDER_II_DATE_CREATED_DESC)
						comp = CompareFileTime(&fileList->getElem(i-1)->created(), &fileList->getElem(i)->created());
					else if (param & ORDER_II_LAST_MODIFIED_ASC)
						comp = CompareFileTime(&fileList->getElem(i)->modified(), &fileList->getElem(i-1)->modified());
					else if (param & ORDER_II_LAST_MODIFIED_DESC)
						comp = CompareFileTime(&fileList->getElem(i-1)->modified(), &fileList->getElem(i)->modified());
					else if (param & ORDER_II_SIZE_ASC)
						comp = fileList->getElem(i-1)->getSize() - fileList->getElem(i)->getSize();
					else if (param & ORDER_II_SIZE_DESC)
						comp = fileList->getElem(i)->getSize() - fileList->getElem(i-1)->getSize();
					if (comp > 0)
					{
						tmp = fileList->getElem(i-1);
						fileList->changeElem(i-1, fileList->getElem(i));
						fileList->changeElem(i, tmp);
						flag = 1;
					}
				}
				i++;
			}
		}
	}
	else if (param & ORDER_I_FILENAME_DESC)
	{
		int i=1, flag=1;
		long long comp=0;
		while (flag)
		{
			flag = 0;
			i=1;
			while (i < fileList->getRows())
			{
				comp = _tcsicmp(fileList->getElem(i-1)->getName(), fileList->getElem(i)->getName());
				if (comp < 0)
				{
					tmp = fileList->getElem(i-1);
					fileList->changeElem(i-1, fileList->getElem(i));
					fileList->changeElem(i, tmp);
					flag = 1;
				}
				else if (comp == 0)
				{
					if (param & ORDER_II_PATH_ASC)
						comp = _tcsicmp(fileList->getElem(i-1)->getPath(), fileList->getElem(i)->getPath());
					else if (param & ORDER_II_PATH_DESC)
						comp = _tcsicmp(fileList->getElem(i)->getPath(), fileList->getElem(i-1)->getPath());
					else if (param & ORDER_II_DATE_CREATED_ASC)
						comp = CompareFileTime(&fileList->getElem(i)->created(), &fileList->getElem(i-1)->created());
					else if (param & ORDER_II_DATE_CREATED_DESC)
						comp = CompareFileTime(&fileList->getElem(i-1)->created(), &fileList->getElem(i)->created());
					else if (param & ORDER_II_LAST_MODIFIED_ASC)
						comp = CompareFileTime(&fileList->getElem(i)->modified(), &fileList->getElem(i-1)->modified());
					else if (param & ORDER_II_LAST_MODIFIED_DESC)
						comp = CompareFileTime(&fileList->getElem(i-1)->modified(), &fileList->getElem(i)->modified());
					else if (param & ORDER_II_SIZE_ASC)
						comp = fileList->getElem(i-1)->getSize() - fileList->getElem(i)->getSize();
					else if (param & ORDER_II_SIZE_DESC)
						comp = fileList->getElem(i)->getSize() - fileList->getElem(i-1)->getSize();
					if (comp > 0)
					{
						tmp = fileList->getElem(i-1);
						fileList->changeElem(i-1, fileList->getElem(i));
						fileList->changeElem(i, tmp);
						flag = 1;
					}
				}
				i++;
			}
		}
	}
	else if (param & ORDER_I_DATE_CREATED_ASC)
	{
		int i=1, flag=1;
		long long comp=0;
		while (flag)
		{
			i=1;
			flag = 0;
			while (i < fileList->getRows())
			{
				comp = CompareFileTime(&fileList->getElem(i-1)->created(), &fileList->getElem(i)->created());
				if (comp > 0)
				{
					tmp = fileList->getElem(i-1);
					fileList->changeElem(i-1, fileList->getElem(i));
					fileList->changeElem(i, tmp);
					flag = 1;
				}
				i++;
			}
		}
	}
	else if (param & ORDER_I_DATE_CREATED_DESC)
	{
		int i=1, flag=1;
		long long comp=0;
		while (flag)
		{
			i=1;
			flag = 0;
			while (i < fileList->getRows())
			{
				comp = CompareFileTime(&fileList->getElem(i-1)->created(), &fileList->getElem(i)->created());
				if (comp < 0)
				{
					tmp = fileList->getElem(i-1);
					fileList->changeElem(i-1, fileList->getElem(i));
					fileList->changeElem(i, tmp);
					flag = 1;
				}
				i++;
			}
		}
	}
	else if (param & ORDER_I_LAST_MODIFIED_ASC)
	{
		int i=1, flag=1;
		long long comp=0;
		while (flag)
		{
			i=1;
			flag = 0;
			while (i < fileList->getRows())
			{
				comp =CompareFileTime(&fileList->getElem(i-1)->modified(), &fileList->getElem(i)->modified());
				if (comp > 0)
				{
					tmp = fileList->getElem(i-1);
					fileList->changeElem(i-1, fileList->getElem(i));
					fileList->changeElem(i, tmp);
					flag = 1;
				}
				i++;
			}
		}
	}
	else if (param & ORDER_I_LAST_MODIFIED_DESC)
	{
		int i=1, flag=1;
		long long comp=0;
		while (flag)
		{
			i=1;
			flag = 0;
			while (i < fileList->getRows())
			{
				comp = CompareFileTime(&fileList->getElem(i-1)->modified(), &fileList->getElem(i)->modified());
				if (comp < 0)
				{
					tmp = fileList->getElem(i-1);
					fileList->changeElem(i-1, fileList->getElem(i));
					fileList->changeElem(i, tmp);
					flag = 1;
				}
				i++;
			}
		}
	}
	else if (param & ORDER_I_SIZE_ASC)
	{
		int i=1, flag=1;
		long long comp=0;
		while (flag)
		{
			i=1;
			flag = 0;
			while (i < fileList->getRows())
			{
				comp = fileList->getElem(i-1)->getSize() - fileList->getElem(i)->getSize();
				if (comp > 0)
				{
					tmp = fileList->getElem(i-1);
					fileList->changeElem(i-1, fileList->getElem(i));
					fileList->changeElem(i, tmp);
					flag = 1;
				}
				i++;
			}
		}
	}
	else if (param & ORDER_I_SIZE_DESC)
	{
		int i=1, flag=1;
		long long comp=0;
		while (flag)
		{
			i=1;
			flag = 0;
			while (i < fileList->getRows())
			{
				comp = fileList->getElem(i-1)->getSize() - fileList->getElem(i)->getSize();
				if (comp > 0)
				{
					tmp = fileList->getElem(i-1);
					fileList->changeElem(i-1, fileList->getElem(i));
					fileList->changeElem(i, tmp);
					flag = 1;
				}
				i++;
			}
		}
	}
	else if (param & ORDER_I_PATH_ASC)
	{
		int i=1, flag=1;
		long long comp=0;
		while (flag)
		{
			i=1;
			flag = 0;
			while (i < fileList->getRows())
			{
				comp = _tcsicmp(fileList->getElem(i-1)->getPath(), fileList->getElem(i)->getPath());
				if (comp > 0)
				{
					tmp = fileList->getElem(i-1);
					fileList->changeElem(i-1, fileList->getElem(i));
					fileList->changeElem(i, tmp);
					flag = 1;
				}
				else if (comp == 0)
				{
					if (param & ORDER_II_FILENAME_ASC)
						comp = _tcsicmp(fileList->getElem(i-1)->getName(), fileList->getElem(i)->getName());
					else if (param & ORDER_II_FILENAME_DESC)
						comp = _tcsicmp(fileList->getElem(i)->getName(), fileList->getElem(i-1)->getName());
					else if (param & ORDER_II_DATE_CREATED_ASC)
						comp = CompareFileTime(&fileList->getElem(i)->created(), &fileList->getElem(i-1)->created());
					else if (param & ORDER_II_DATE_CREATED_DESC)
						comp = CompareFileTime(&fileList->getElem(i-1)->created(), &fileList->getElem(i)->created());
					else if (param & ORDER_II_LAST_MODIFIED_ASC)
						comp = CompareFileTime(&fileList->getElem(i)->modified(), &fileList->getElem(i-1)->modified());
					else if (param & ORDER_II_LAST_MODIFIED_DESC)
						comp = CompareFileTime(&fileList->getElem(i-1)->modified(), &fileList->getElem(i)->modified());
					else if (param & ORDER_II_SIZE_ASC)
						comp = fileList->getElem(i-1)->getSize() - fileList->getElem(i)->getSize();
					else if (param & ORDER_II_SIZE_DESC)
						comp = fileList->getElem(i)->getSize() - fileList->getElem(i-1)->getSize();
					if (comp > 0)
					{
						tmp = fileList->getElem(i-1);
						fileList->changeElem(i-1, fileList->getElem(i));
						fileList->changeElem(i, tmp);
						flag = 1;
					}
				}
				i++;
			}
		}
	}
	else
	{
		int i=1, flag=1;
		long long comp=0;
		while (flag)
		{
			i=1;
			flag = 0;
			while (i < fileList->getRows())
			{
				comp = _tcsicmp(fileList->getElem(i-1)->getPath(), fileList->getElem(i)->getPath());
				if (comp < 0)
				{
					tmp = fileList->getElem(i-1);
					fileList->changeElem(i-1, fileList->getElem(i));
					fileList->changeElem(i, tmp);
					flag = 1;
				}
				else if (comp == 0)
				{
					if (param & ORDER_II_FILENAME_ASC)
						comp = _tcsicmp(fileList->getElem(i-1)->getName(), fileList->getElem(i)->getName());
					else if (param & ORDER_II_FILENAME_DESC)
						comp = _tcsicmp(fileList->getElem(i)->getName(), fileList->getElem(i-1)->getName());
					else if (param & ORDER_II_DATE_CREATED_ASC)
						comp = CompareFileTime(&fileList->getElem(i)->created(), &fileList->getElem(i-1)->created());
					else if (param & ORDER_II_DATE_CREATED_DESC)
						comp = CompareFileTime(&fileList->getElem(i-1)->created(), &fileList->getElem(i)->created());
					else if (param & ORDER_II_LAST_MODIFIED_ASC)
						comp = CompareFileTime(&fileList->getElem(i)->modified(), &fileList->getElem(i-1)->modified());
					else if (param & ORDER_II_LAST_MODIFIED_DESC)
						comp = CompareFileTime(&fileList->getElem(i-1)->modified(), &fileList->getElem(i)->modified());
					else if (param & ORDER_II_SIZE_ASC)
						comp = fileList->getElem(i-1)->getSize() - fileList->getElem(i)->getSize();
					else if (param & ORDER_II_SIZE_DESC)
						comp = fileList->getElem(i)->getSize() - fileList->getElem(i-1)->getSize();
					if (comp > 0)
					{
						tmp = fileList->getElem(i-1);
						fileList->changeElem(i-1, fileList->getElem(i));
						fileList->changeElem(i, tmp);
						flag = 1;
					}
				}
				i++;
			}
		}
	}
}
bool findBestPack(list *packList, list *actualBest, list *actualPath, int actualPack, verylong max, verylong min)
{
	int i=actualPack, lenght=packList->getRows();
	verylong size=0;
	while (i < lenght)
	{
		size = actualPath->getSize()+packList->getElem(i)->getSize();
		if (i < lenght && size < max)
		{
			actualPath->addElem(packList->getElem(i));
			findBestPack(packList, actualBest, actualPath, i+1, max, min);
			actualPath->remElem(actualPath->getRows()-1);
		}
		if (size <= max && size > actualBest->getSize())
		{
			int w=0;
			actualBest->emptyList();
			while (w < actualPath->getRows())
				actualBest->addElem(actualPath->getElem(w++));
			actualBest->addElem(packList->getElem(i));
		}
		i++;
	}
	if (actualBest->getSize() <= min)
		return false;
	return true;
}

packageList* makePackList(list *packList, verylong max, verylong min)
{
	if (!packList->getRows())
		return 0;
	packageList *packs = new packageList;
	list *tmpPackList = new list, *actualBest = new list, *actualPath = new list;
	int i =0;
	while (i < packList->getRows())
		tmpPackList->addElem(packList->getElem(i++));
	itemsPack *pack, *problemPack = new itemsPack;
	int len = tmpPackList->getRows(), ii=0;
	while (ii < len)
		if (tmpPackList->getElem(ii)->getSize() > max)
		{
			problemPack->addItem(tmpPackList->getElem(ii));
			tmpPackList->remElem(ii);
			len--;
		}
		else
			ii++;
	while (len)
	{
		if (findBestPack(tmpPackList, actualBest, actualPath, 0, max, min))
		{
			pack = new itemsPack;
			int j=0;
			while (j < actualBest->getRows())
			{
				tmpPackList->remElem(actualBest->getElem(j));
				pack->addItem(actualBest->getElem(j++));
			}
			actualBest->emptyList();
			actualPath->emptyList();
			packs->addElem(pack);
		}
		else
		{
			problemPack->addItem(tmpPackList->getElem(0));
			tmpPackList->remElem(0);
		}
		len = tmpPackList->getRows();
	}
	if (problemPack->itemsCount())
		packs->addElem(problemPack);
	else
		delete problemPack;
	delete tmpPackList;
	delete actualBest;
	delete actualPath;
	return packs;
}

//end
