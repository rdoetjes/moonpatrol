# change path  /Users/rdoetjes/moonpatrol to your path
# and we are running the docker container for a buil here.
all:
	docker run --rm -v /Users/rdoetjes/moonpatrol:/m68k -t registry.gitlab.com/doragasu/docker-sgdk:v1.80
	retrodevhelper run
