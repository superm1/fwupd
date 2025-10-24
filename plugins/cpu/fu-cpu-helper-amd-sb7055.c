/*
 * Copyright 2025 Richard Hughes <richard@hughsie.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include "config.h"

#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fu-cpu-helper-amd-sb7055-common.h"

#define DEFAULT_ITERATIONS 100000

static atomic_int g_error_count = 0;
static unsigned long g_iterations = DEFAULT_ITERATIONS;

typedef enum {
	TEST_RDRAND,
	TEST_RDSEED,
} TestType;

typedef struct {
	TestType test_type;
	unsigned long iterations;
} ThreadData;

static void *
test_thread_rdrand(void *arg)
{
	ThreadData *data = (ThreadData *)arg;
	for (unsigned long i = 0; i < data->iterations; i++) {
		fu_cpu_helper_amd_sb7055_test_rdrand();
	}
	return NULL;
}

static void *
test_thread_rdseed(void *arg)
{
	ThreadData *data = (ThreadData *)arg;
	for (unsigned long i = 0; i < data->iterations; i++) {
		fu_cpu_helper_amd_sb7055_test_rdseed();
	}
	return NULL;
}

int
main(int argc, char *argv[])
{
	pthread_t thread_rdrand, thread_rdseed;
	ThreadData data_rdrand, data_rdseed;
	int rc;

	/* parse iterations argument */
	if (argc > 1) {
		char *endptr;
		long iterations = strtol(argv[1], &endptr, 10);
		if (*endptr != '\0' || iterations <= 0) {
			fprintf(stderr, "Invalid iterations argument: %s\n", argv[1]);
			return 1;
		}
		g_iterations = (unsigned long)iterations;
	}

	/* prepare thread data */
	data_rdrand.test_type = TEST_RDRAND;
	data_rdrand.iterations = g_iterations;
	data_rdseed.test_type = TEST_RDSEED;
	data_rdseed.iterations = g_iterations;

	/* spawn RDRAND thread */
	rc = pthread_create(&thread_rdrand, NULL, test_thread_rdrand, &data_rdrand);
	if (rc != 0) {
		fprintf(stderr, "Failed to create RDRAND thread: %d\n", rc);
		return 1;
	}

	/* spawn RDSEED thread */
	rc = pthread_create(&thread_rdseed, NULL, test_thread_rdseed, &data_rdseed);
	if (rc != 0) {
		fprintf(stderr, "Failed to create RDSEED thread: %d\n", rc);
		pthread_join(thread_rdrand, NULL);
		return 1;
	}

	/* wait for both threads to complete */
	pthread_join(thread_rdrand, NULL);
	pthread_join(thread_rdseed, NULL);

	/* if we got here without crashing, the test passed */
	return 0;
}
