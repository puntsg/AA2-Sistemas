#include "Node.h"
#include "../Utils/ConsoleControl.h"
//#include "Utils/ConsoleControl.h"


Node::Node(Vector2 position)
{
	_position = position;
}

void Node::SetContent(NodeContent* newContent) {
	content = newContent;
}

NodeContent* Node::GetContent() {
	return content;
}

void Node::DrawContent(Vector2 offset) {
	if (content == nullptr)
	{
		Vector2 pos = offset + _position;
		CC::Lock();
		CC::SetPosition(pos.X, pos.Y);
		std::cout << ' ';
		CC::Unlock();
		return;
	}

	content->Draw(offset);
}

void Node::Lock() {
	_ClassMutex.lock();
}

void Node::Unlock() {
	_ClassMutex.unlock();
}
