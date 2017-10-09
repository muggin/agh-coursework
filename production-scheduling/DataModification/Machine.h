/*
 * Machine.h
 *
 *  Created on: 28 kwi 2014
 *      Author: Filson
 */

#ifndef MACHINE_H_
#define MACHINE_H_

using namespace std;

/**
 * Klasa obiektu reprezentuj¹cego pojedyncz¹ maszynê.
 */
class Machine{
private:
	int id; //!< ID maszyny.

public:
	/**
	 * Konstruktor klasy.
	 * \param id Id maszyny
	 */
	Machine(int id);

	/**
	 * Destruktor klasy.
	 */
	~Machine();

	/**
	 * Getter dla id maszyny.
	 * \return Id maszyny.
	 */
	int getId() const {
		return id;
	}

	/**
	 * Setter dla id maszyny.
	 * \param id Id do ustawienia
	 */
	void setId(int id) {
		this->id = id;
	}
};



#endif /* MACHINE_H_ */
