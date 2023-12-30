# change path  /Users/rdoetjes/moonpatrol to your path
# and we are running the docker container for a buil here.
PWD = $(shell pwd)

all:
	docker run --rm -v $(PWD):/src sgdk
	/usr/games/blastem out/rom.bin

