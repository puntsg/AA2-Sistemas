#include "InputSystem.h"
#include "../Utils/ConsoleControl.h"
InputSystem::KeyBinding::KeyBinding(int key, OnKeyPressed onKeyPressed)
{
	_key = key;
	_onKeyPressed = onKeyPressed;
}

InputSystem::KeyBinding::~KeyBinding()
{
}

InputSystem::InputSystem()
{

}

InputSystem::~InputSystem()
{
	for (std::pair<int, KeyBindingList> pair : _keyBindingsMap)
	{
		KeyBindingList bindingsList = pair.second;
		for (KeyBinding* binding : bindingsList)
		{
			delete binding;
		}
	}
	_keyBindingsMap.clear();
}
InputSystem::KeyBinding* InputSystem::KeyAddListener(int key, KeyBinding::OnKeyPressed onKeyPress)
{
	_classMutex.lock();
	if (_keyBindingsMap.find(key) == _keyBindingsMap.end()) 
		_keyBindingsMap[key] = KeyBindingList();
	KeyBinding* keyBinding = new KeyBinding(key, onKeyPress);
	_keyBindingsMap[key].push_back(keyBinding);
	_classMutex.unlock();
	return keyBinding;
}

void InputSystem::RemoveAndDeleteListener(KeyBinding* keyBinding)
{
	int key = keyBinding->_key;
	_classMutex.lock();
	if (_keyBindingsMap.find(key) != _keyBindingsMap.end()) {
		KeyBindingList list = _keyBindingsMap[key];
		list.remove(keyBinding);
		delete keyBinding;
		if (list.size() == 0)
			_keyBindingsMap.erase(key);
	}
	_classMutex.unlock();
}

void InputSystem::KeyAddListenerAsync(int key, KeyBinding::OnKeyPressed onKeyPress)
{
	std::thread* addListenerThread = new std::thread(&InputSystem::KeyAddListener, this, key, onKeyPress);
	addListenerThread->detach();
}


void InputSystem::RemoveAndDeleteListenerAsync(KeyBinding* keyBinding)
{
	std::thread* removeListenerThread = new std::thread(&InputSystem::RemoveAndDeleteListener, this, keyBinding);
	removeListenerThread->detach();
}

void InputSystem::StartListen()
{
	_classMutex.lock();
	if (_state != Stopped)
	{
		_classMutex.unlock();
		return;
	}
	_state = Starting;
	std::thread* listenLoopThread = new std::thread(&InputSystem::ListenLoop,this);
	_classMutex.unlock();
}

void InputSystem::StopListen()
{
}

void InputSystem::ListenLoop()
{
	_classMutex.lock();
	_state = Listening;
	State _currentstate = _state;
	ConsoleControl::Lock();
	ConsoleControl::ClearKeyBuffer();
	ConsoleControl::Unlock();
	//CC::Lock();
	//CC::ClearKeyBuffer();
	//CC::Unlock();
	_classMutex.unlock();
	while (_currentstate == Listening)
	{
		//int key = CC::ReadNextKey();
		int key = ConsoleControl::ReadNextKey();
		if (key != 0) {
			_classMutex.lock();
			KeybindMap::iterator it = _keyBindingsMap.find(key);
			if (it != _keyBindingsMap.end()) {
				KeyBindingList list = it->second;
				for (KeyBinding* binding : list) {
					//binding->_onKeyPressed();
					std::thread* onPress = new std::thread(binding->_onKeyPressed);
					onPress->detach();
				}
			}
			_classMutex.unlock();
		}
		_classMutex.lock();
		_currentstate = _state;
		_classMutex.unlock();
	}
	_classMutex.lock();
	if (_state == Stopping)
		_state = Stopped;
	_classMutex.unlock();
}
