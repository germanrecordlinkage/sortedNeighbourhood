sortedNeighbourhood.statistics <- function() {
	options("scipen"=16)
	result <- .Call(snStatisticsCall)
	return(data.frame(result))
}
