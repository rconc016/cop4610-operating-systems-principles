COMPILER=gcc
OUTPUT_DIR=out
LOGGING_DIR=../libs/logging

build: pthreadsproject.c
	mkdir -p ${OUTPUT_DIR}
	${COMPILER} -pthread pthreadsproject.c ${LOGGING_DIR}/logging.c -o ${OUTPUT_DIR}/pthreadsproject

run: build
	${OUTPUT_DIR}/pthreadsproject

clean:
	rm -r out