/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ztest.h>

#include <net/buf.c>

void nano_fifo_init(struct nano_fifo *fifo) {}
void nano_fifo_put_list(struct nano_fifo *fifo, void *head, void *tail) {}

nano_context_type_t sys_execution_context_type_get(void)
{
	return NANO_CTX_FIBER;
}

void *nano_fifo_get(struct nano_fifo *fifo, int32_t timeout)
{
	return ztest_get_return_value_ptr();
}

void nano_fifo_put(struct nano_fifo *fifo, void *data)
{
	ztest_check_expected_value(data);
}

#define BUF_COUNT 1
#define BUF_SIZE 74

static struct nano_fifo bufs_fifo;
static NET_BUF_POOL(bufs_pool, BUF_COUNT, BUF_SIZE, &bufs_fifo,
		NULL, sizeof(int));

static void init_pool(void)
{
	ztest_expect_value(nano_fifo_put, data, &bufs_pool);
	net_buf_pool_init(bufs_pool);
}

static void test_get_single_buffer(void)
{
	struct net_buf *buf;

	init_pool();

	ztest_returns_value(nano_fifo_get, bufs_pool);
	buf = net_buf_get_timeout(&bufs_fifo, 0, TICKS_NONE);

	assert_equal_ptr(buf, &bufs_pool[0], "Returned buffer not from pool");
	assert_equal(buf->ref, 1, "Invalid refcount");
	assert_equal(buf->len, 0, "Invalid length");
	assert_equal(buf->flags, 0, "Invalid flags");
	assert_equal_ptr(buf->frags, NULL, "Frags not NULL");
}

void test_main(void)
{
	ztest_test_suite(net_buf_test,
		ztest_unit_test(test_get_single_buffer)
	);

	ztest_run_test_suite(net_buf_test);
}
