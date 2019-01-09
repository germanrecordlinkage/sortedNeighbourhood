\name{sortedNeighbourhood.matchFiles}
\alias{sortedNeighbourhood.matchFiles}
\title{
Match multiple Objects 
}
\description{
This function matches objects of two input files according to their similarity
using Sorted Neighbourhood algorithm.
}
\usage{
sortedNeighbourhood.matchFiles(filenameA, filenameB, minSimilarity, windowSize, method = "tanimoto")
}
\arguments{
\item{filenameA}{
  a character string containing the filename of the first input file
}
\item{filenameB}{
  a character string containing the filename of the second input file
}
\item{minSimilarity}{
  a numeric value giving the lower bound of similarity coefficient to search for
}
\item{windowSize}{
  an integer value containing the window size for searching
}
\item{method}{
  an optional string parameter, that defines the method to work with; currently
  two methods are implemented: "tanimto" (default, reading objects as fingerprints,
  comparing objects by tanimoto coefficient) and "tanimotoXOR" (the same as
  "tanimoto" extended by a 128-bit XOR-hash-filter strategy for fast tanimoto
  comparison)
}

}
\value{
The function returns a data.frame with three columns:
\item{query}{
  this column contains the query object-ids
}
\item{match}{
  this column contains the matching object-ids
}
\item{similarity}{
  this column contains the corresponding similarity coefficients
}
}
\seealso{
\code{\link{sortedNeighbourhood.statistics}}
}
\examples{
## get name of example files with fingerprints in package directory

fileA <- file.path(path.package("sortedNeighbourhood"), "extdata/AA.csv")
fileB <- file.path(path.package("sortedNeighbourhood"), "extdata/BB.csv")

## search all objects from file A in file B

sortedNeighbourhood.matchFiles(fileA, fileB, 0.9, 5)

## statistics

sortedNeighbourhood.statistics()

## search all objects from file A in file B (with XOR-hash-optimization)

sortedNeighbourhood.matchFiles(fileA, fileB, 0.9, 5, "tanimotoXOR")

## statistics

sortedNeighbourhood.statistics()
}
\keyword{misc}
