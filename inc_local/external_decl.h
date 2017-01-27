
#ifndef EXTERNAL_DECL_H_
#define EXTERNAL_DECL_H_

#include <stdint.h>

typedef void * TaskHandle_t;
typedef TaskHandle_t osThreadId;

typedef void * QueueHandle_t;
typedef QueueHandle_t SemaphoreHandle_t;
typedef SemaphoreHandle_t osMutexId;
typedef QueueHandle_t osMessageQId;

typedef void (*os_pthread) (void const *argument);

typedef enum  {
  osPriorityIdle          = -3,          ///< priority: idle (lowest)
  osPriorityLow           = -2,          ///< priority: low
  osPriorityBelowNormal   = -1,          ///< priority: below normal
  osPriorityNormal        =  0,          ///< priority: normal (default)
  osPriorityAboveNormal   = +1,          ///< priority: above normal
  osPriorityHigh          = +2,          ///< priority: high
  osPriorityRealtime      = +3,          ///< priority: realtime (highest)
  osPriorityError         =  0x84        ///< system cannot determine priority or thread has illegal priority
} osPriority;

typedef enum  {
  osOK                    =     0,       ///< function completed; no error or event occurred.
  osEventSignal           =  0x08,       ///< function completed; signal event occurred.
  osEventMessage          =  0x10,       ///< function completed; message event occurred.
  osEventMail             =  0x20,       ///< function completed; mail event occurred.
  osEventTimeout          =  0x40,       ///< function completed; timeout occurred.
  osErrorParameter        =  0x80,       ///< parameter error: a mandatory parameter was missing or specified an incorrect object.
  osErrorResource         =  0x81,       ///< resource not available: a specified resource was not available.
  osErrorTimeoutResource  =  0xC1,       ///< resource not available within given time: a specified resource was not available within the timeout period.
  osErrorISR              =  0x82,       ///< not allowed in ISR context: the function cannot be called from interrupt service routines.
  osErrorISRRecursive     =  0x83,       ///< function called multiple times from ISR with same object.
  osErrorPriority         =  0x84,       ///< system cannot determine priority or thread has illegal priority.
  osErrorNoMemory         =  0x85,       ///< system is out of memory: it was impossible to allocate or reserve memory for the operation.
  osErrorValue            =  0x86,       ///< value of a parameter is out of range.
  osErrorOS               =  0xFF,       ///< unspecified RTOS error: run-time error but no other error message fits.
  os_status_reserved      =  0x7FFFFFFF  ///< prevent from enum down-size compiler optimization.
} osStatus;

typedef struct  {
  osStatus                 status;     ///< status code: event or error information
  union  {
    uint32_t                    v;     ///< message as 32-bit value
    void                       *p;     ///< message or mail as void pointer
    int32_t               signals;     ///< signal flags
  } value;                             ///< event value
    osMessageQId       def;                               ///< event definition
} osEvent;


typedef struct os_thread_def  {
  char                   *name;        ///< Thread name
  os_pthread             pthread;      ///< start address of thread function
  osPriority             tpriority;    ///< initial thread priority
  uint32_t               instances;    ///< maximum number of instances of that thread function
  uint32_t               stacksize;    ///< stack size requirements in bytes; 0 is default stack size
} osThreadDef_t;

#define osThreadDef(name, thread, priority, instances, stacksz)  \
const osThreadDef_t os_thread_def_##name = \
{ #name, (thread), (priority), (instances), (stacksz)  }

#define osThread(name)  \
&os_thread_def_##name

extern osThreadId osThreadCreate (const osThreadDef_t *thread_def, void *argument);
extern osThreadId osThreadGetId (void);
extern osStatus osThreadTerminate (osThreadId thread_id);
extern osStatus osThreadYield (void);
extern osStatus osThreadSetPriority (osThreadId thread_id, osPriority priority);
extern osPriority osThreadGetPriority (osThreadId thread_id);
extern osStatus osDelay (uint32_t millisec);


typedef struct os_mutex_def  {
  uint32_t                   dummy;    ///< dummy value.
} osMutexDef_t;

#define osMutexDef(name)  \
const osMutexDef_t os_mutex_def_##name = { 0 }

#define osMutex(name)  \
&os_mutex_def_##name

extern osMutexId osMutexCreate (const osMutexDef_t *mutex_def);
extern osStatus osMutexWait (osMutexId mutex_id, uint32_t millisec);
extern osStatus osMutexRelease (osMutexId mutex_id);
extern osStatus osMutexDelete (osMutexId mutex_id);


typedef struct os_messageQ_def  {
  uint32_t                queue_sz;    ///< number of elements in the queue
  uint32_t                 item_sz;    ///< size of an item
} osMessageQDef_t;

#define osMessageQDef(name, queue_sz, type)   \
const osMessageQDef_t os_messageQ_def_##name = \
{ (queue_sz), sizeof (type)  }

#define osMessageQ(name) \
&os_messageQ_def_##name

extern osMessageQId osMessageCreate (const osMessageQDef_t *queue_def, osThreadId thread_id);
extern osStatus osMessagePut (osMessageQId queue_id, uint32_t info, uint32_t millisec);
extern osEvent osMessageGet (osMessageQId queue_id, uint32_t millisec);


extern void *pvPortMalloc( size_t xWantedSize );
extern void vPortFree( void *pv );
extern void vTaskResume( TaskHandle_t xTaskToResume );
extern void vTaskSuspend( TaskHandle_t xTaskToSuspend );
#endif
