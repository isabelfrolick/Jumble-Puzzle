/*
 * jumble.h
 *
 *  Created on: Nov. 8, 2021
 *      Author: 12894
 */

#pragma once

#ifndef JUMBLE_H_
#define JUMBLE_H_

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <time.h>


class JumblePuzzle{


public:
	typedef char* charArrayPtr;

	//destructor
	~JumblePuzzle();

	//JumblePuzzle();

	//constructors
	JumblePuzzle(const JumblePuzzle&); //copy constructor

	JumblePuzzle(const std::string&, const std::string&);

	//assignment operator
	JumblePuzzle& operator=(const JumblePuzzle&);

	//accessors
	charArrayPtr* getJumble() const;

	int getSize() const;

	int getRowPos() const;

	int getColPos() const;

	char getDirection() const;

	//functions used in game

	void showJumble(const charArrayPtr* jumble, const int size);

	void playGame();

	void testJumble();

private:
	charArrayPtr* myPuzzle;
	int rowNum;
	int colNum;
	int length;
	char direction;

	//helper functions
	charArrayPtr* createLocalCopy(const charArrayPtr* obj, const int len) const;
	charArrayPtr* createNewJumble(const int& len);
};


class BadJumbleException {
public:
	BadJumbleException(const std::string&);
	std::string& what();

private:
	std::string message;
};



#endif /* JUMBLE_H_ */
