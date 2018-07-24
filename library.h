#ifndef LIBRARY_H
#define LIBRARY_H

#include "adds.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <tchar.h> 
#include <strsafe.h>
#include <time.h>

class item
{
public:
	item(TCHAR *nameIn, TCHAR *pathIn, verylong sizeIn, FILETIME timeCreated, FILETIME timeModified);
	~item();
	TCHAR* getName();
	TCHAR* getPath();
	verylong getSize();
	FILETIME created();
	FILETIME modified();
private:
	TCHAR *name;
	TCHAR *path;
	verylong size;
	FILETIME createTime;
	FILETIME lastModifiedTime;
};

class list
{
public:
	list();
	~list();
	void remAllElem();
	void addElem(item *newItemIn);
	item* getElem(int rowIn);
	int getRows();
	verylong getSize();
	bool remElem(int rowIn);
	bool remElem(item *itemIn);
	void changeElem(int rowIn, item *newItem);
	void emptyList();
	void operator= (list *in);
private:
	int rows;
	verylong size;
	int lenght;
	item **items;
};

class node
{
public:
	node(item *nodeItemIn);
	~node();
	void clear();
	item* getNodeItem();
	void setParent(node *parentIn);
	node* getParent();
	void unsetParent();
	void addChild(node *childItemIn);
	int childCount();
	node* getChild(int index);
	int getChildIndex(node *child);
	bool removeChild(int index);
	bool removeChild(node *child);
private:
	item *nodeItem;
	node *parent;
	int childrens;
	node **childs;
};

class itemsPack
{
public:
	itemsPack();
	~itemsPack();
	int addItem(item *itemIn);
	item* getItem(int index);
	int getItemIndex(item *itemIn);
	int itemsCount();
	verylong getSize();
private:
	int itemCounter;
	verylong size;
	int len;
	item **items;
};

class packageList
{
public:
	packageList();
	~packageList();
	void removePacks();
	void addElem(itemsPack *itemsPacksIn);
	itemsPack* getElem(int rowIn);
	int getRows();
private:
	int rows;
	itemsPack **itemsPacks;
};

//funkcje

verylong power(verylong base, int exponent);
verylong getFolderSize(TCHAR *path);
list* addToFileList(list *fileList, TCHAR *searchPath, DWORD param);
void sortFileList(list *fileList, DWORD param);
list* makeFileList(list *fileList, TCHAR **searchPaths, int queLen, DWORD param);

bool findBestPack(list *packList, list *actualBest, list *actualPath, int actualPack, verylong max, verylong min);
packageList* makePackList(list *packList, verylong max, verylong min);

#endif // LIBRARY_H
