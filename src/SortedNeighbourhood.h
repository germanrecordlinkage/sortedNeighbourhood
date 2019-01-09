// SortedNeighbourhood.h
//
// Copyright (c) 2013
// Universitaet Duisburg-Essen
// Campus Duisburg
// Institut fuer Soziologie
// Prof. Dr. Rainer Schnell
// Lotharstr. 65
// 47057 Duisburg 
//
// This file is part of the R-Package "sortedNeighbourhood".
//
// "sortedNeighbourhood" is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// "sortedNeighbourhood" is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with "sortedNeighbourhood". If not, see <http://www.gnu.org/licenses/>.

#ifndef SORTEDNEIGHBOURHOOD_H
#define SORTEDNEIGHBOURHOOD_H

#include <math.h>
#include "Fingerprint.h"
#include "QueryResult.h"

// The class SortedNeighbourhood receives an array of instances of the class T.
// The array will be sorted according to the sortkey of the objects.
// A sorted neighbourhood matching will be performed by a given minimal similarity
// and a window size.

template <class T>
class SortedNeighbourhood {
	private:

	long long mSize;		// size of object-array 
	T **mObjects;			// array of objects
	
	public:

	// constructor
	// objects      : pointer on object array
	// size         : size of object array
	inline SortedNeighbourhood(T **objects, long long size) {
		mSize = size;
		mObjects = objects;

		// sort prints by sortkey
		sortObjects(0, size-1);
	}

	// destructor
	inline ~SortedNeighbourhood() {
		for (int i = 0; i < mSize; i++) {
			if (mObjects[i]) {
				delete mObjects[i];
			}
		}

		delete[] mObjects;
	}

	// perform a search for <minSimilarity> and <windowSize> and add the result to <result>
	inline void search(QueryResult *result, double minSimilarity, int windowSize) {
		int win_end;

		for (int i = 0; i < (mSize - 1); i++) {
			win_end = MIN(i + windowSize, mSize);

			// compare first item with all others in the window

			T *firstObject = mObjects[i];

			int firstSortKey = firstObject->getSortKey();
			for (int j = (i + 1); j < win_end; j++) {
				// only compare two objects belonging to the different files
				if (firstObject->getOrigin() != mObjects[j]->getOrigin()) {
					firstObject->match(result, mObjects[j], minSimilarity);
				}
			}
		}
	}

	private:

	void sortObjects(long long lowerIdx, long long upperIdx);
};

// quick sort objects bei sortkey
template<class T>
void SortedNeighbourhood<T>::sortObjects(long long lowerIdx, long long upperIdx) {
        if (lowerIdx < upperIdx) {
		T *swap;
		long long l = lowerIdx;
                int pivot = mObjects[upperIdx]->getSortKey();

		for (long long u = lowerIdx; u < upperIdx; u++) {
                        if (mObjects[u]->getSortKey() <= pivot) {
                                swap = mObjects[l];
                                mObjects[l] = mObjects[u];
                                mObjects[u] = swap;
                                l++;
                        }
                }

		swap = mObjects[l];
		mObjects[l] = mObjects[upperIdx];
		mObjects[upperIdx] = swap;

		sortObjects(lowerIdx, l - 1);
		sortObjects(l + 1, upperIdx);
        }
}

#endif
