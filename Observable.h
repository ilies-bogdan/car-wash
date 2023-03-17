#pragma once

#include <vector>
#include "Observer.h"


class Observable {
private:
	std::vector<Observer*> observers;
public:
	void addObserver(Observer* obs) {
		this->observers.push_back(obs);
	}

	void removeObserver(Observer* obs) {
		auto it = std::find(this->observers.begin(), this->observers.end(), obs);
		if (it != this->observers.end()) {
			this->observers.erase(it);
		}
	}

	void notifyAll() {
		for (auto obs : this->observers) {
			obs->update();
		}
	}
};