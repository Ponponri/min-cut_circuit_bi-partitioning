all:
	sudo apt install gcc-multilib -y
	gcc  -m32 m11102137.c -L ./ -l hmetis -o m11102137
clean:
	rm -rf m11102137
