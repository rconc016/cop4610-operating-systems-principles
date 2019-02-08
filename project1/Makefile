COMPILER=gcc
OUTPUT_DIR=out
LOGGING_DIR=../libs/logging
THREAD_COUNT=4

create_output:
	mkdir -p ${OUTPUT_DIR}

build_unsync: create_output pthreadsproject.c
	${COMPILER} -pthread pthreadsproject.c ${LOGGING_DIR}/logging.c -o ${OUTPUT_DIR}/pthreadsproject

build_sync: create_output pthreadsproject.c
	${COMPILER} -pthread pthreadsproject.c ${LOGGING_DIR}/logging.c -o ${OUTPUT_DIR}/pthreadsproject -D PTHREAD_SYNC

run_unsync: build_unsync
	${OUTPUT_DIR}/pthreadsproject ${THREAD_COUNT}

run_sync: build_sync
	${OUTPUT_DIR}/pthreadsproject ${THREAD_COUNT}

clean:
	rm -r out