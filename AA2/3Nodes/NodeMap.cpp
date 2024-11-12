#include "NodeMap.h"

Node* NodeMap::UnSafeGetNode(Vector2 position)
{


	if (position.X >= _size.X || position.Y >= _size.Y)
	{
		return nullptr;
	}
	NodeColumn* column = _grid[position.X];
	Node* node = (*column)[position.Y];
	return node;
}

NodeMap::NodeMap(Vector2 size, Vector2 offset)
{
	_size = size;
	_offset = offset;

	for (int x = 0; x < size.X; x++) {
		
		NodeColumn* column = new NodeColumn();

		for (int y = 0; y < size.Y; y++)
		{
			column->push_back(new Node(Vector2(x,y)));
		}

		_grid.push_back(column);
	}
}

//pintar tota la taula sencera, NO ABUSAR DE LA FUNCIÓ
//no és segur, s'ha de programar bé
void NodeMap::UnSafeDraw()
{
	for (NodeColumn* column : _grid)
	{
		for (Node* node : *column)
		{
			node->DrawContent(_offset);
		}
	}
}

void NodeMap::SafePickNode(Vector2 position, SafePick safePickAction) //dona una casella per manipular-la sense riscos de que un altre la manipuli a la vegada
{
	_sizeMutex.lock();
	_gridMutex.lock();
	Node* node = UnSafeGetNode(position);
	_gridMutex.unlock();
	_sizeMutex.unlock();

	node->Lock();
	safePickAction(node);
	node->Unlock();




	
}

void NodeMap::SafeMultiPickNode(std::list<Vector2> positions, SafeMultiPick safeMultiPickAction)
{
	std::list<Node*> nodes;

	_sizeMutex.lock();
	_gridMutex.lock();

	for (Vector2 pos : positions)
	{
		nodes.push_back(UnSafeGetNode(pos));
	}

	_sizeMutex.unlock();
	_gridMutex.unlock();


	//Pregunta d'examen, aquesta part de codi lock unlock és la cosa que hem de anar amb ull
	//fem un _safeMultiNodeLockMutex per evitar que més gent utilitzi aquesta funció que pot donar error d'espera infinita
	_safeMultiNodeLockMutex.lock();

	for (Node* node : nodes) {
	
		if (node != nullptr) {
			node->Lock();
		}
	}

	_safeMultiNodeLockMutex.unlock();

	safeMultiPickAction(nodes);

	for (Node* node : nodes) {

		if (node != nullptr) {
			node->Unlock();
		}
	}
}

Vector2 NodeMap::GetSize()
{
	_sizeMutex.lock();
	Vector2 size = _size;
	_sizeMutex.unlock();
	return size;
}




