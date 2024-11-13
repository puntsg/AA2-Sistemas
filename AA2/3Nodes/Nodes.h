#pragma once
#include "Vector2.h"
#include "INodeContent.h"
#include <mutex>
class Node
{
private:
	Vector2 _position; 
	INodeContent* _content = nullptr;
	std::mutex _classMutex;
public:
	Node(Vector2 position);
	INodeContent* GetnodeContent();

	template<typename T, typename = typename std::enable_if<std::is_base_of<INodeContent, T>::value>::type>
	T* GetContent() {
		T* contentCasted = dynamic_cast<T*>(_content);
		return contentCasted;
	}
	void SetContent(INodeContent* nodeContent);
	void DrawContent(Vector2 offset);
	void Lock();
	void Unlock();
};

