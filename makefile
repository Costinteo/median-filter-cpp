CC = g++

medianfilter: medianfilter.cpp Image.cpp
	${CC} -o medianfilter medianfilter.cpp Image.cpp
