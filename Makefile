obj = game.o block.o rules.o window.o
CXX = g++
CPPFLAGS = -std=c++11

game.exe : $(obj)
	$(CXX) $(CPPFLAGS) -o game.exe $(obj)
	make clean
$(obj):
#game.o : window.h
#block.o : block.h
#rules.o : rules.h
#window.o : window.h

.PHONY : clean
clean:
	-rm $(obj)
