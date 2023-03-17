/*
* exceptions.h
* Exceptions classes
*/

#pragma once

#include <exception>
#include <string>

using std::exception;
using std::string;


/*
* Exception raised when the data is invalid
*/
class ValidationException : std::exception {
private:
	string message;
public:
	ValidationException() = default;

	ValidationException(const string& msg) : message{ msg } {
	}

	const string& getErrorMsg() const noexcept {
		return message;
	}
};

/*
* Exception raised when there is a repository error
*/
class RepositoryException : std::exception {
private:
	string message;
public:
	RepositoryException() = default;
	
	RepositoryException(const string& msg) : message{ msg } {
	}

	const string& getErrorMsg() const noexcept {
		return message;
	}
};

/*
* Exception raised when there is a file error
*/
class FileException : std::exception {
private:
	string message;
public:
	FileException() = default;
	
	FileException(const string& msg) : message{ msg } {
	}

	const string& getErrorMsg() const noexcept {
		return message;
	}
};