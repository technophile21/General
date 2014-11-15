//
//  swap2numbers.cpp
//  Practice C++
//
//  Created by Manik Singhal on 6/6/14.
//
//

#include "Practice.h"

namespace Practice {

	void swap(int *a, int *b) {
		int tmp;
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}