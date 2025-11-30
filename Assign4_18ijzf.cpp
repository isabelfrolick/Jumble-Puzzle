

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <time.h>
#include "jumble.h"
using namespace std;

//typedef for charArrayPtr

typedef char* charArrayPtr;

//declaration of BadJumbleException
BadJumbleException::BadJumbleException(const string& myMessage) : message(myMessage){ }
string& BadJumbleException::what()  {
	return message;
}



//copy constructor, takes in a JumblePuzzle object address
JumblePuzzle::JumblePuzzle(const JumblePuzzle& obj){


	length = obj.getSize(); //use accessors to access parameters

	myPuzzle = createLocalCopy(obj.getJumble(), length); //createLocalCopy() is a helper function
															//creates a copy but can be used locally

	rowNum = obj.getRowPos();
	colNum = obj.getColPos();
	direction = obj.getDirection();


}

//accesssor functions, constant functions to prevent modifications

int JumblePuzzle::getSize() const{
	return length;
}


int JumblePuzzle::getRowPos() const{
	return rowNum;
}


int JumblePuzzle::getColPos() const{
	return colNum;
}

char JumblePuzzle::getDirection() const{
	return direction;
}


charArrayPtr* JumblePuzzle::getJumble() const{
	return myPuzzle;

}


//constructor with 2 string parameters, the word to hide and the difficulty level

JumblePuzzle::JumblePuzzle(const string& word, const string& diff){

	//store the length of the word to hide in the length attribute
	length = word.length();


	//check exception- checked in testing
	if(length < 3 || length > 10){
		throw BadJumbleException("Please choose a word between 3 and 10 letters in length.");
	}

	//multiply the length depending on the difficulty level

	if(diff == "easy"){
		length *= 2;
	}
	else if(diff == "medium"){
		length *= 3;
	}
	else if(diff == "hard"){
		length *= 4;
	}
	else{
		throw BadJumbleException("Please select a difficulty level of \"easy\", \"medium\" or \"hard\".");
	}

	//create a new puzzle using helper function
	//similar to creates a copy of the puzzle attribute but with the desired length
	myPuzzle = createNewJumble(length);


	//create a list of letters to fill the puzzle
	const char* allLetters = "abcdefghijklmnopqrstuvwxyz";


	srand(time(nullptr));

	//build 2D array
	for(int j=0; j< length; j++){
		for(int k=0; k <  length; k++){
			myPuzzle[j][k] = (char) allLetters[rand() % 25]; //parse the list of letters to fill the array
		}
	}

	rowNum = rand() % length; //randomly select the row and column number wanted
	colNum = rand() % length;


	myPuzzle[rowNum][colNum] = word.at(0); //place the first letter of the word to hide at the randomly
											//generated location

	if(myPuzzle[rowNum][colNum] != word.at(0)){ //if there is an error placing the word, this should never happen
		throw BadJumbleException("Invalid formation of puzzle.");
	}

	//generate the possible directions
	const char* dir = "nesw";

	//create 'boolean' variable to check when the entire word had been added
	int done = 0;

	//while the entire word to hide has not been added
	while(done != 1){

		//randomly generate a direction
		direction = dir[rand() % 4];

		//if the direction is north
		if(direction == 'n'){

			//iterate through entire word to hide
			for(unsigned int n = 1; n <  word.length(); n++){

				//if the row number - the length of the word to add is less than zero, break loop
				//the location of the first letter doesn't have enough space for going north
				//break the loop and regenerate a direction
				if((rowNum - word.length()) < 0){
					break;
				}
				//case for the last letter of the word
				//change done to break out of the while loop
				else if(n ==  word.length() - 1){
					myPuzzle[rowNum-n][colNum] = word.at(n);
					done = 1;
				}
				else{
					//add the next letter above the current location
					myPuzzle[rowNum -n][colNum] = word.at(n);
				}
			}
		}
		//same for west
		else if(direction == 'w'){
			for( unsigned int w = 1; w <  word.length(); w++){
				if((colNum - word.length()) < 0){
					break;
				}
				else if(w ==  word.length() - 1){
					myPuzzle[rowNum][colNum - w] = word.at(w);
					done = 1;
				}
				else{
					myPuzzle[rowNum][colNum - w] = word.at(w);
				}
			}
		}
		//same for south
		else if(direction == 's'){
			for(unsigned int s = 1; s <  word.length(); s++){
				//if the row number produced + the length of the word to be added
				//is less than the length of the entire puzzle, break
				if((rowNum + word.length()) < length ){
					break;
				}
				else if(s ==  (word.length() - 1)){
					myPuzzle[rowNum + s][colNum] = word.at(s);
					done = 1;
				}
				else{
					myPuzzle[rowNum + s][colNum] = word.at(s);
				}
			}
		}
		//same for east
		else if(direction == 'e'){
			for(unsigned int e= 1; e<  word.length(); e++){

				if((colNum - word.length()) < length){
					break;
				}
				else if(e ==  word.length() - 1){
					myPuzzle[rowNum][colNum + e] = word.at(e);
					done = 1;
				}
				else{
					myPuzzle[rowNum][colNum + e] = word.at(e);
				}
			}
		}

	}

}


//destructor
JumblePuzzle::~JumblePuzzle(){
	//if myPuzzle parameter is valid and exists
	if(myPuzzle){
		//delete each element
		for(int i=0; i<rowNum; i++){
			delete []myPuzzle[i];
		}
		//delete the array
		delete[] myPuzzle;
		//set to nullptr
		myPuzzle = nullptr;
	}

}

//assignment operator overloader
JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& puzzle){

	//check if object passed is valid
	if(this != &puzzle){
		//set the accessors to save the values
		rowNum = puzzle.getRowPos();
		colNum = puzzle.getColPos();
		length = puzzle.getSize();
		direction = puzzle.getDirection();

		//delete the memory from the heap
		for(int i=0; i <length; i++){
			delete[] myPuzzle[i];
		}
		delete[] myPuzzle;
		myPuzzle = nullptr;

		//create a copy of the puzzle
		int size = length;
		//create new puzzle
		charArrayPtr* puzzleJumble = new charArrayPtr[size];

		//create new char at each location
		for(int j=0; j<size; j++){
			myPuzzle[j] = new char[length];
		}

		//fill 2D arrays
		for(int k =0; k<length; k++){
			for(int l=0; l<length; l++){
				myPuzzle[k][l] = puzzleJumble[k][l];
			}
		}


	}
	//return the current object
	return *this;
}



//helper functions

//createNewJumble, to create a new puzzle with a length parameter
//used in the constructor
charArrayPtr* JumblePuzzle::createNewJumble(const int& len){
	//create new char** object (charArrayPtr*)
	charArrayPtr* myNew = new charArrayPtr[len];
	//iterate through loop, add elements
	for(int i=0; i < len; i++){
		myNew[i] = new char[len];
	}
	//return the created array
	return myNew;
}


//helper function used in copy constructor to create a local
//copy of the puzzle to be used in the copy constructor
//takes in a puzzle and a length
charArrayPtr* JumblePuzzle::createLocalCopy(const charArrayPtr* obj, const int len) const{
	int size = len; //local version of the length parameter passed
	//create new object of charArrayPtr* type
	charArrayPtr* myNew = new charArrayPtr[size];

	//iterate through the loop
	for(int i=0; i < size; i++){
		//add to elements
		myNew[i] = new char[size];
	}

	//create 2D array copy
	for( int j = 0; j<size; j++){
		for(int k = 0; k<size; k++){
			myNew[j][k] = obj[j][k];
		}
	}
	//return the copied version of the puzzle that was passed at the
	//length with which it was passed
	return myNew;
}

