#pragma once
#include <FreeRTOS.h>
#include <queue.h>

struct request_msg {
    int32_t input;
    int32_t output;
    uint32_t handled_by;
};

struct task_args
{
    QueueHandle_t request;
    QueueHandle_t response;
    int id;
};

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id);
