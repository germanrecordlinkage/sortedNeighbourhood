\name{sortedNeighbourhood.statistics}
\alias{sortedNeighbourhood.statistics}
\title{
Print Statistics of last Search
}
\description{
This function returns the statistic results of the last call to matchFiles. 
}
\usage{
sortedNeighbourhood.statistics()
}
\value{
The function returns a data.frame with three columns:
\item{Checkpoint}{
  this column contains the statistics parameter
}
\item{Count}{
  this column contains the corresponding value
}
\item{Percentage}{
  this column contains the value Count in relation to the total sum of comparisons
}
}
\seealso{
\code{\link{sortedNeighbourhood.matchFiles}}
}
\examples{

## get name of example files with fingerprints in package directory

fileA <- file.path(path.package("sortedNeighbourhood"), "extdata/A.csv")
fileB <- file.path(path.package("sortedNeighbourhood"), "extdata/B.csv")

## search all objects from file A in file B

sortedNeighbourhood.matchFiles(fileA, fileB, 0.8, 5)

## statistics

sortedNeighbourhood.statistics()

}
\keyword{misc}
