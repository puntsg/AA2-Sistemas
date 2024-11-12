#pragma once
#include <vector>
#include <functional> //funcions autoregulades tancades
#include <mutex>
#include <list>

#include "Node.h"


class NodeMap
{
public:
	//fem...
	typedef std::vector<Node*> NodeColumn; //la fila original
	typedef std::vector<NodeColumn*> NodeGrid; //les columnes (tindrà valors per copia)

	typedef std::function<void(Node* node)> SafePick;
										//agafem grups de nodes per bloquejarlos (com totes les caselles de serp, o àrea d'efecte) 
										// i evitar que altres intentin modificar-los també mentre nosaltres modifiquem
	typedef std::function<void(std::list<Node*> nodes)> SafeMultiPick; //una list perque pot estar de sordenada

private:
	Vector2 _offset;

	Vector2 _size;
	std::mutex _sizeMutex; //teoria diu que no és necessari, però ho és, hem de protegir
	
	NodeGrid _grid;
	std::mutex _gridMutex;

	std::mutex _safeMultiNodeLockMutex;

	Node* UnSafeGetNode(Vector2 position);

public:

	NodeMap(Vector2 size, Vector2 offset);

	void UnSafeDraw();
	void SafePickNode(Vector2 position, SafePick safePickAction); //no donem possibilitat a equivorase peruqe rebem només node i acció sobre aquest
	void SafeMultiPickNode(std::list<Vector2> positions, SafeMultiPick safeMultiPickAction);
	Vector2 GetSize();
};

