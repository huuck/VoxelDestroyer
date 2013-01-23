/*
 * arrayUtils.h
 *
 *  Created on: Oct 18, 2012
 *      Author: Gabi
 */

#ifndef ARRAYUTILS_H_
#define ARRAYUTILS_H_

float *concatArray(float *a, float *b, int from, int length) {
	int i;

	for(i = from; i < from+length; i++) {
		a[i] = b[i-from];
	}

	return a;
}

#endif /* ARRAYUTILS_H_ */
