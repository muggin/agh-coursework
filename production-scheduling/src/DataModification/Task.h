/*
 * Task.h
 *
 *  Created on: 28 kwi 2014
 *      Author: Filson
 */

#ifndef TASK_H_
#define TASK_H_

#include "Machine.h"

using namespace std;

/**
 * Klasa obiektu reprezentuj¹cego pojedyncze zadanie w ramach danej pracy.
 */
class Task{
private:
	Machine* machine;	//!< WskaŸnik do maszyny u¿ytej w zadaniu.
	int start;		//!< Czas rozpoczêcia zadania.
	int time;		//!< Czas trwania zadania.

public:
	/**
	 * Konstruktor klasy.
	 * \param machine WskaŸnik do maszyny u¿ytej przy zadaniu.
	 * \param startTimr Czas rozpoczêcia zadania.
	 * \param duration Czas trwania zadania.
	 */
	Task(Machine* machine, int startTime, int duration);

	/**
	 * Destruktor klasy.
	 */
	~Task();

	/**
	 * Getter maszyny.
	 * \return WskaŸnik do maszyny.
	 */
    Machine* getMachine() const {
	  	return machine;
	}

	/**
	 * Setter maszyny.
	 * \param machine WskaŸnik do maszyny.
	 */
	void setMachine(Machine* machine) {
	  	this->machine = machine;
	}

	/**
	 * Getter czasu pocz¹tkowego zadania.
	 * \return Czas rozpoczêcia zadania
	 */
	int getStart() const {
		return start;
	}

	/**
	 * Setter czasu pocz¹tkowego zadania.
	 * \param start Czas rozpoczêcia zadania.
	 */
	void setStart(int start) {
		this->start = start;
	}

	/**
	 * Getter czasu trwania zadania.
	 * \return Czas trwania zadania
	*/
	int getTime() const {
		return time;
	}

	/**
	 * Setter czasu trwania zadania.
	 * \param time Czas trwania zadania.
	 */
	void setTime(int time) {
		this->time = time;
	}
};
#endif /* TASK_H_ */
