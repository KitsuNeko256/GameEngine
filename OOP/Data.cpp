#include "common.h"
#include "Data.h"

#include <iostream>



Data::Data() {}
Data* Data::instance;
Data* Data::get() {
	if (instance == nullptr) instance = new Data();
	return instance;
}
