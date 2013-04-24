/*
 * map.h
 *
 *  Created on: Apr 24, 2013
 *      Author: SW-ITS-HHE
 */

#ifndef MAP_H_
#define MAP_H_

#include "list.h"

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct map *Map;
typedef ListElement MapElement;

typedef struct mapnode{
	Map map;
	char key[100];
	MapElement element;
}*MapNode;

//�����б�
struct map{
    List dataList;
    void (*put)(Map this, const char*, MapElement);
    MapNode (*get)(Map this, const char*);
    void (*forEach)(Map this,void(*)(MapNode, void*), void*);          //�����ڵ�
    int (*size)(Map this);
    void (*clearElement)(MapElement);            //�ڵ���Դ�ͷź���
};

Map newMap(void (*clearElement)(MapElement));      //newһ���б�����
void delMap(Map this);                 //ɾ��һ���б�����

#if defined(__cplusplus)
}
#endif


#endif /* MAP_H_ */