COMPILER=gcc
OUTPUT_DIR=out

build: pthreadsproject.c
	mkdir -p ${OUTPUT_DIR}
	${COMPILER} -pthread pthreadsproject.c -o ${OUTPUT_DIR}/pthreadsproject

run: build
	${OUTPUT_DIR}/pthreadsproject

clean:
	rm -r out