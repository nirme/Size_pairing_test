#ifndef _UNICODE
#define _UNICODE
#endif
#ifndef UNICODE
#define UNICODE
#endif

#define MAX_PATH_LENGTH		260
#define MPL					MAX_PATH_LENGTH

//////////////////////////////////////////////////////////
//	DWORD sort_and_find
//	|bits| usage							|
//	|----|---what-to-search-----------------|
//	| 00 | files							|
//	| 01 | folders							|
//	| 02 | -reserved						|
//	| 03 | -reserved						|
//	|----|---sorting-order-I----------------|	if there are more than 1 then
//	| 04 | filenames ascending				|	the one with lower number is taken
//	| 05 | filenames descending				|
//	| 06 | date created older first			|
//	| 07 | date created younger first		|
//	| 08 | date last modified older first	|
//	| 09 | date last modified younger first	|
//	| 10 | size ascending					|
//	| 11 | size descending					|
//	| 12 | path ascending					|
//	| 13 | path descending					|
//	|----|---sorting-order-II---------------|	don't work with order by date and size
//	| 14 | path ascending					|
//	| 15 | path descending					|
//	| 16 | filenames ascending				|
//	| 17 | filenames descending				|
//	| 18 | date created older first			|
//	| 19 | date created younger first		|
//	| 20 | date last modified older first	|
//	| 21 | date last modified younger first	|
//	| 22 | size ascending					|
//	| 23 | size descending					|
//	| 24<| -reserved						|
//	|----|----------------------------------|
//////////////////////////////////////////////////////////
#define PACK_FILES 0x00000001
#define PACK_FOLDERS 0x00000002
#define ORDER_I_FILENAME_ASC 0x00000010
#define ORDER_I_FILENAME_DESC 0x00000020
#define ORDER_I_DATE_CREATED_ASC 0x00000040
#define ORDER_I_DATE_CREATED_DESC 0x00000080
#define ORDER_I_LAST_MODIFIED_ASC 0x00000100
#define ORDER_I_LAST_MODIFIED_DESC 0x00000200
#define ORDER_I_SIZE_ASC 0x00000400
#define ORDER_I_SIZE_DESC 0x00000800
#define ORDER_I_PATH_ASC 0x00001000
#define ORDER_I_PATH_DESC 0x00002000
#define ORDER_II_PATH_ASC 0x00004000
#define ORDER_II_PATH_DESC 0x00008000
#define ORDER_II_FILENAME_ASC 0x00010000
#define ORDER_II_FILENAME_DESC 0x00020000
#define ORDER_II_DATE_CREATED_ASC 0x00040000
#define ORDER_II_DATE_CREATED_DESC 0x00080000
#define ORDER_II_LAST_MODIFIED_ASC 0x00100000
#define ORDER_II_LAST_MODIFIED_DESC 0x00200000
#define ORDER_II_SIZE_ASC 0x00400000
#define ORDER_II_SIZE_DESC 0x00800000

typedef unsigned long long verylong;