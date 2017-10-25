/*!
 * 	\file Chromosom.h
    \brief Naglowek klasy Chromosom.

    Szczegolowy opis.
*/

#ifndef CHROMOSOM_H_
#define CHROMOSOM_H_

#define RANDOMREPAIR 50

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include "../DataModification/Database.h"
using namespace std;

/**
 * Klasa przechowuje chromosom. Ka�dy chromosom odpowiada jednemu poprawnemu rozwi�zaniu problemu.
 * Krzy�uj�c oraz mutuj�c wybrane chromosomy zbli�amy si� do optymalnego rozwi�zania.
 */

class Chromosom {
private:
    static Database* jobDatabase; //!< baza danych
	int fitness;	//!< Ocena chromosomu (jakosc rozwiazania).
	vector<int> genotype;	//!< Genotyp chromosomu (przechowuje rozwiazanie).

public:
    /**
	 * Domy�lny konstruktor klasy Chromosom.
	 * Tworzony Chromosom ma pusty genotyp.
	 */
	Chromosom();
	/**
	 * Konstruktor kt�ry pozwala na pocz�tkowe ustawienie genotypu.
	 * \param genotype genotyp chromosomu
	 */
    Chromosom(vector<int> genotype);

	virtual ~Chromosom();


	bool isValid();

	/**
	 * Funkcja pobiera wartosc fitness chromosomu.
	 * \return wartosc zmiennej fitness.
	 */
	 int getFitness() const;

    /**
	 * Funkcja ustawia baze danych wej�ciowych dla algorytmu.
	 * \param jobDatabase Baza danych wej�ciowych
	 */
    static void setJobDatabase(Database& jobDatabase);


	/**
	 * Funkcja zwraca referencje do genotypu chromosomu.
	 * \return referencja do genotypu chromosoma (const).
	 */
	const vector<int>& getGenotype() const;

    /**
	 * Funkcja zwraca referencje do bazy danych wej�ciowych.
	 * \return referencja do bazy danych wej�ciowych.
	 */
	static Database& getJobDatabase();

	/**
	 * Funkcja ustawia genotypu chromosomu.
	 * \param referencja do genotypu chromosomu.
	 */
	void setGenotype(vector<int>& genotype);

	/**
	 * Funkcja generuje randomowy genotyp dla chromosomu.
	 */
	void generateRandomGenotype();

	/**
	 * Funkcja oblicza przystosowanie chromosomu (fitness) na podstawie genotypu.
	 * \return wartosc zmiennej fitness.
	 */
	int countFitness() ;

	/**
	 * Funkcja wypisuje genotyp na standardowe wyj�cie (konsol�).
	 */
    void printGenotype() const;

    void printChromosom() const;

    /**
	 * Funkcja aktualizuje baz� danych wej�ciowych o czasu rozpocz�cia poszczeg�lnych zada� w ka�dej z prac.
	 */
    void updateDatabaseWithStartTimes();

    /**
	 * Funkcja ustawia zmienn� fitness na losow� warto�� z zakresu 0-999 (w celach testowych).
	 */
    void setRandomFitness();

    bool repairChromosom();

    static void setJobDatabase(Database* jobDatabase);


};

#endif /* CHROMOSOM_H_ */
