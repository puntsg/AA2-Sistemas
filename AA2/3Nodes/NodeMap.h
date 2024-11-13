#pragma once
#include "Nodes.h"
#include <vector>
#include <functional>
#include <mutex>
#include <list>
class NodeMap
{
public:
	typedef std::vector<Node*> NodeColumn;
	typedef std::vector<NodeColumn> NodeGrid;

	typedef std::function<void(Node* node)> SafePick;
	typedef std::function<void(std::list<Node*> nodes)>SaveMultiPick;
private:
	Vector2 _offset;

	Vector2 _size;
	std::mutex _sizeMutex;
	
	NodeGrid _grid;
	std::mutex _gridMutex;

	std::mutex _saveMultiNodeLockMutex;
	
	Node* UnsaveGetNode(Vector2 position);
public:
	NodeMap(Vector2 size, Vector2 offset);

	Vector2 GetSize();

	void UnsaveDraw();
	void SafePickNode(Vector2 position, SafePick safePickAction);
	void SafeMultiPickNode(std::list<Vector2> positions, SaveMultiPick safeMultiPickAction);
};

