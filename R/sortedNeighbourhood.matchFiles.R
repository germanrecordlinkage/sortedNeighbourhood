sortedNeighbourhood.matchFiles <- function(filenameA, filenameB, minSimilarity, windowSize, method = "tanimoto") {
	if (method == "tanimoto") {
		methodId <- 1;
	} else if (method == "tanimotoXOR") {
		methodId <- 2;
	} else {
		stop("Unknown method");
	}

	result <- .Call(snMatchFilesCall, filenameA, filenameB, minSimilarity, windowSize, methodId)
	return(data.frame(result))
}
