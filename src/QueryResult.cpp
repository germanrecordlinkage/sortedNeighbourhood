// QueryResult.cpp
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

#include<stdlib.h>
#include<string.h>

#include "QueryResult.h"

// constructor
QueryResult::QueryResult(int sort) {
	mSize = 0;
	mRootNode = NULL;
	mSort = sort;
	mStat1 = 0;
	mStat2 = 0;
}

// destructor
QueryResult::~QueryResult() {
	QueryResultNode *node, *nextNode;
	if (mSort) {
		deleteNode(mRootNode);		// discard the whole result set recursivly
	} else {
		// discard the whole result iteratively for large scale results
		node = mRootNode;
		while (node != NULL) {
			if (node->mQueryId != NULL) {
				delete[] node->mQueryId;
			}
			if (node->mMatchId != NULL) {
				delete[] node->mMatchId;
			}
			nextNode = node->mRight;
			delete node;
			node = nextNode;
		}
	}
}

// delete a node and all its subnodes recursively
void QueryResult::deleteNode(QueryResultNode *node) {
	if (node != NULL) {
		if (node->mQueryId != NULL) {
			delete[] node->mQueryId;
		}
		if (node->mMatchId != NULL) {
			delete[] node->mMatchId;
		}
		deleteNode(node->mLeft);
		deleteNode(node->mRight);
		delete node;
	}
}

// add a matching pair and the corresponding similarity coefficient to the query result
void QueryResult::add(char *queryId, char *matchId, double similarity) {
	QueryResultNode *newNode;
	QueryResultNode **nextNodePtr;
	
	// create new node
	newNode = new QueryResultNode;

	// copy query id, match id and similarity
	if (queryId != NULL) {
		newNode->mQueryId = new char[strlen(queryId) + 1];
		strcpy(newNode->mQueryId, queryId);
	} else {
		newNode->mQueryId = NULL;
	}

	if (matchId != NULL) {
		newNode->mMatchId = new char[strlen(matchId) + 1];
		strcpy(newNode->mMatchId, matchId);
	} else {
		newNode->mMatchId = NULL;
	}

	newNode->mSimilarity = similarity;
	newNode->mLeft = NULL;
	newNode->mRight = NULL;

	if (mSort) {
		// if query results have to be sorted, find the right location
		// to insert the new node
		nextNodePtr = &mRootNode;

		while (*nextNodePtr != NULL) {
			if ((*nextNodePtr)->mSimilarity >= similarity) {
				nextNodePtr = &((*nextNodePtr)->mRight);
			} else {
				nextNodePtr = &((*nextNodePtr)->mLeft);
			}
		}

		// insert new node
		*nextNodePtr = newNode;
	} else {
		// if query results need not to be sorted
		// insert at end of list
		if (mRootNode == NULL) {
			mRootNode = newNode;
		} else {
			mRootNode->mLeft->mRight = newNode;
		}

		mRootNode->mLeft = newNode; // use mLeft as pointer to end node
	}
	
	mSize++;

}
