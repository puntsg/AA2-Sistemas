#include "Nodes.h"
#include "../Utils/ConsoleControl.h"

Node::Node(Vector2 position)
{
	_position = position;
}

INodeContent* Node::GetnodeContent()
{
	return _content;
}

void Node::SetContent(INodeContent* nodeContent)
{
	_content = nodeContent;
}

void Node::DrawContent(Vector2 offset)
{
	if(_content == nullptr){
		Vector2 pos = offset + _position;
		CC::Lock();
		CC::SetPosition(pos.x, pos.y);
		std::cout << " ";
		CC::Unlock();
		return;
	}
	_content->Draw(offset);
}

void Node::Lock()
{
	_classMutex.lock();
}

void Node::Unlock()
{
	_classMutex.unlock();
}
