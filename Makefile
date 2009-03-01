.PHONY: all bin doc dist clean

all: bin doc

bin:
	@$(MAKE) -C src

doc:
	@$(MAKE) -C doc

dist:
	@$(MAKE) -C dist

clean:
	@$(MAKE) -C src clean
	@$(MAKE) -C doc clean

