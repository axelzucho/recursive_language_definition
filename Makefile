SOURCES = main.cpp Language.cpp RecursiveStepRule.cpp
MAIN = language_generator.out

$(MAIN): $(SOURCES)
	g++ -std=c++11 $^ -Wall --pedantic -o $@

clean:
	rm -f $(MAIN) *.o *.zip

zip: clean
	zip -r $(MAIN).zip $(SOURCES) Makefile

.PHONY: clean zip