#pragma once
#include <iostream>
#include<functional>
#include<list>
#include <map>
#include <mutex>

#define K_UP 72
#define K_DOWN 80
#define K_LEFT 75
#define K_RIGHT 77
#define K_SPACE 32
#define K_Enter 13
#define K_ESCAPE 27

#define K_A 97
#define K_W 119
#define K_S 115
#define K_D 100

#define K_0 48
#define K_1 49
#define K_2 50
#define K_3 51
#define K_4 52
#define K_5 53
#define K_6 54
#define K_7 55
#define K_8 56
#define K_9 57

class InputSystem
{
public:
	class KeyBinding {
		friend class InputSystem;
		public:
			typedef std::function<void()> OnKeyPressed;
		private:
			int _key;
			OnKeyPressed _onKeyPressed;
			KeyBinding(int key, OnKeyPressed onKeyPressed);
			~KeyBinding();
	};
	typedef std::list<KeyBinding*>KeyBindingList;
	typedef std::map<int, KeyBindingList> KeybindMap;
public:
	InputSystem();
	~InputSystem();
	KeyBinding* KeyAddListener(int key, KeyBinding::OnKeyPressed onKeyPress);
	void RemoveAndDeleteListener(KeyBinding* keyBinding);
	void KeyAddListenerAsync(int key, KeyBinding::OnKeyPressed onKeyPress);
	void RemoveAndDeleteListenerAsync(KeyBinding* keyBinding);

	void StartListen();
	void StopListen();
private:
	std::mutex _classMutex;
	KeybindMap _keyBindingsMap;

	enum State {
		Starting = 0,
		Listening = 1,
		Stopping = 2,
		Stopped = 3
	};
	State _state = State::Stopped;
	void ListenLoop();
};
