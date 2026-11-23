#include <FreeRTOS.h>
#include <task.h>
#include "signaling.h"

void signal_handle_calculation(SemaphoreHandle_t request,
                               SemaphoreHandle_t response,
                               struct signal_data *data)
{
    for (;;) {
        if (xSemaphoreTake(request, portMAX_DELAY) == pdTRUE) {
            data->output = data->input + 5;
            vTaskDelay(pdMS_TO_TICKS(10));
            xSemaphoreGive(response);
        }
    }
}

BaseType_t signal_request_calculate(SemaphoreHandle_t request,
                                    SemaphoreHandle_t response,
                                    struct signal_data *data)
{
    (void)data;

    if (xSemaphoreGive(request) != pdTRUE) {
        return pdFALSE;
    }

    return xSemaphoreTake(response, pdMS_TO_TICKS(100));
}
