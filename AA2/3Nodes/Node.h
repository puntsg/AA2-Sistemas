#pragma once
#include "Vector2.h"
#include "NodeContent.h"
#include <mutex>


//Abraham recomana fer funció auxiliar Is EMty per saber si casella és vuida
			// i check content per saber de quin tipus és el contingut
			// fer un cast com a Unity i fer cast aquí "denamar l'objecte, pasar per referència..."
class Node
{
private:
	Vector2 _position;//per saber on és cada casella que crearem, i trobar-la rápidament sense repasar totes les caselles
	NodeContent* content = nullptr; //és un punter perque inicialment el node està vuit (per comoditat)
									//per evitar gastar memòria, cada casella és un punter nullptr
	std::mutex _ClassMutex;
public:

	Node(Vector2 position);

	NodeContent* GetContent();
	
	//una indicació del compilador (no una funció de .cpp, ja que només s'agafa el .h) per saber quin tipus de contingut hi ha al node (sempre que siguin tipus NodeContent)
	template<typename T, typename = typename std::enable_if <std::is_base_of<NodeContent, T>::value>::type> 
	T* GetContent() { // T és per el "template" de tipus limitat
	
		T* contentCasted = dynamic_cast<T*>(content);
		return contentCasted;
	}

	void SetContent(NodeContent* newContent);
	void DrawContent(Vector2 offset); //tindrem una grid en mitg de la consola, doncs hem de sumar l'offset per començar a la cantonada de la grid enmig de la consola

	void Lock();
	void Unlock();
};

//un snake de 20x20, la serp té cos i cap --->, score que baixa i puja
//					Snake(int size, )						ScoreManager o el joc en general
//mutex al mapa, el bloquejem quan un vol utilitzar el mapa, per evitar 