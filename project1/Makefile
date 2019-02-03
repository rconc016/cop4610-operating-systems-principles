COMPILER=gcc
OUTPUT_DIR=out
LOGGING_DIR=../libs/logging
THREAD_COUNT=4

build: pthreadsproject.c
	mkdir -p ${OUTPUT_DIR}
	${COMPILER} -pthread pthreadsproject.c ${LOGGING_DIR}/logging.c -o ${OUTPUT_DIR}/pthreadsproject -D PTHREAD_SYNC

run: build
	${OUTPUT_DIR}/pthreadsproject ${THREAD_COUNT}

clean:
	rm -r out