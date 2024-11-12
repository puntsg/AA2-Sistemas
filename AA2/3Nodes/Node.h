#pragma once
#include "Vector2.h"
#include "NodeContent.h"
#include <mutex>


//Abraham recomana fer funci� auxiliar Is EMty per saber si casella �s vuida
			// i check content per saber de quin tipus �s el contingut
			// fer un cast com a Unity i fer cast aqu� "denamar l'objecte, pasar per refer�ncia..."
class Node
{
private:
	Vector2 _position;//per saber on �s cada casella que crearem, i trobar-la r�pidament sense repasar totes les caselles
	NodeContent* content = nullptr; //�s un punter perque inicialment el node est� vuit (per comoditat)
									//per evitar gastar mem�ria, cada casella �s un punter nullptr
	std::mutex _ClassMutex;
public:

	Node(Vector2 position);

	NodeContent* GetContent();
	
	//una indicaci� del compilador (no una funci� de .cpp, ja que nom�s s'agafa el .h) per saber quin tipus de contingut hi ha al node (sempre que siguin tipus NodeContent)
	template<typename T, typename = typename std::enable_if <std::is_base_of<NodeContent, T>::value>::type> 
	T* GetContent() { // T �s per el "template" de tipus limitat
	
		T* contentCasted = dynamic_cast<T*>(content);
		return contentCasted;
	}

	void SetContent(NodeContent* newContent);
	void DrawContent(Vector2 offset); //tindrem una grid en mitg de la consola, doncs hem de sumar l'offset per comen�ar a la cantonada de la grid enmig de la consola

	void Lock();
	void Unlock();
};

//un snake de 20x20, la serp t� cos i cap --->, score que baixa i puja
//					Snake(int size, )						ScoreManager o el joc en general
//mutex al mapa, el bloquejem quan un vol utilitzar el mapa, per evitar 