all:
	@echo LEMBRE-SE: Edite sua grade antes de compilar...
	c++ -std=c++11 schedulator.cxx -o schedulator

clean:
	rm -f schedulator
