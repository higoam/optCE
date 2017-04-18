main: Ajusts.o Tflags.o Set.o Tcexamples.o Generatefiles.o Runalgorithm.o projeto.o
	g++ -o optCE projeto.o Ajusts.o Tflags.o Set.o Tcexamples.o Generatefiles.o Runalgorithm.o

projeto.o: projeto.cpp
	g++ -c projeto.cpp

Tflags.o: Ajusts.cpp Ajusts.h
	g++ -c Ajusts.cpp

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
	rm optCE projeto.o Ajusts.o Tflags.o Set.o Tcexamples.o Generatefiles.o Runalgorithm.o
