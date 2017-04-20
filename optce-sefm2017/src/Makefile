main: Adjust.o Tflags.o Set.o Tcexamples.o Generatefiles.o Runalgorithm.o Adjust.o project.o
	g++ -o optCE Adjust.o Tflags.o Set.o Tcexamples.o Generatefiles.o Runalgorithm.o project.o

Adjust.o: Adjust.cpp Adjust.h
	g++ -c Adjust.cpp

projeto.o: project.cpp
	g++ -c project.cpp

Tflags.o: Tflags.cpp Tflags.h
	g++ -c Tflags.cpp

Set.o: Set.cpp Set.h
	g++ -c Set.cpp

Tcexamples.o: Tcexamples.cpp Tcexamples.h
	g++ -c Tcexamples.cpp

Generatefiles.o: Generatefiles.cpp Generatefiles.h
	g++ -c Generatefiles.cpp

Runalgorithm.o: Runalgorithm.cpp Runalgorithm.h
	g++ -c Runalgorithm.cpp

clean:
	rm optCE *.o
