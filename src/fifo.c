#include "fifo.h"

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id)
{
    struct request_msg message;

    for (;;) {
        if (xQueueReceive(requests, &message, portMAX_DELAY) == pdTRUE) {
            message.output = message.input + 5;
            message.handled_by = (uint32_t)id;
            xQueueSendToBack(results, &message, portMAX_DELAY);
        }
    }
}
