all:
	docker build -f Dockerfile -t guillaumebeuzeboc/beuzebot .
run_docker:
	docker run -it -v /home/guillaume/code/beuzebot/src:/root/ws/src guillaumebeuzeboc/beuzebot bash
